#include <QDebug>
#include <QUrl>
#include <QUrlQuery>

#include "services/booru/BooruSearchService.hpp"
#include "services/GlobalNetworkService.hpp"

void BooruSearchRequest::start(const BooruSearchParameters& searchParameters)
{
    QNetworkReply* searchReply = DoSearch(searchParameters.provider, searchParameters.query);

    QObject::connect(searchReply, &QNetworkReply::errorOccurred, this, [this, searchReply](QNetworkReply::NetworkError _) {
        //TODO: format error message
        qDebug() << "error\n";
        emit this->errorOccured(searchReply->errorString());
    });

    QObject::connect(searchReply, &QNetworkReply::finished, this, [this, searchReply] {
        qDebug() << "finished\n";

        QDomDocument xmlResponse;
        if(QDomDocument::ParseResult parseResult = xmlResponse.setContent(searchReply); !parseResult)
        {
            //TODO: format error message
            emit errorOccured(parseResult.errorMessage);
            return;
        }

        std::variant<QList<BooruImage*>, QString> reparseResult = ParseBooruXmlResponse(xmlResponse);
        if(std::holds_alternative<QString>(reparseResult))
        {
            emit errorOccured(std::get<QString>(reparseResult));
            return;
        }

        emit finished(std::get<QList<BooruImage *>>(reparseResult));
    });
}

static QNetworkReply* DoSearch(const QString& provider, const QString& query)
{
    QUrlQuery urlParameters {
        { "page", "dapi" },
        { "s", "post" },
        { "q", "index" },
        //TODO: change
        { "limit", "100" },
        { "pid", "0" },
        { "tags", query }
    };

    //FIXME
    QString providerBaseUrl;
    if(provider == "Gelbooru")
    {
        providerBaseUrl = "gelbooru.com";
    }
    else if(provider == "Safebooru")
    {
        providerBaseUrl = "safebooru.org";
    }
    else
    {
        //error, unknown provider. TODO: report error
    }

    QString providerUrl = QString("https://%1/index.php").arg(providerBaseUrl);

    QUrl queryUrl(providerUrl);
    queryUrl.setQuery(urlParameters);

    QNetworkRequest request(queryUrl);
    QNetworkReply* reply = GlobalNetworkService::get().get(request);

    return reply;
}

static std::variant<QList<BooruImage*>, QString> ParseBooruXmlResponse(const QDomDocument& document)
{
    qDebug() << "Complete XML:" << document.toString();

    QDomElement postsNode = document.firstChildElement("posts");
    if(postsNode.isNull())
    {
        return "Parsing error: root element \"posts\" was not found.";
    }

    QList<BooruImage*> result;

    QDomElement postNode = postsNode.firstChildElement("post");

    for(; !postNode.isNull(); postNode = postNode.nextSiblingElement("post"))
    {
        QDomElement fileUrlNode    = postNode.firstChildElement("file_url");
        QDomElement previewUrlNode = postNode.firstChildElement("preview_url");

        if(fileUrlNode.isNull() || previewUrlNode.isNull())
        {
            qDebug() << "Parsing error: could not find file_url or preview_url; skipping image.";
            continue;
        }

        QString fileUrl    = fileUrlNode.text();
        QString previewUrl = previewUrlNode.text();

        result.append(new BooruImage(QUrl(previewUrl), QUrl(fileUrl)));
    }

    return result;
}