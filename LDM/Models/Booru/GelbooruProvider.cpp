#include <QDomDocument>
#include <QUrl>
#include <QUrlQuery>

#include "./GelbooruProvider.hpp"

QNetworkRequest PrepareGelbooruRequest(const QString& booruBaseUrl, const BooruSearchParameters& parameters)
{
	QUrlQuery urlParameters {
	    { "page", "dapi" },
	    { "s", "post" },
	    { "q", "index" },
	    //TODO: change
	    { "limit", "100" },
	    { "pid", "0" },
	    { "tags", parameters.query }
	};

	QUrl queryUrl(QString("https://%1/index.php").arg(booruBaseUrl));
	queryUrl.setQuery(urlParameters);

	return QNetworkRequest(queryUrl);
}

QNetworkRequest GelbooruProvider::prepareRequest(const BooruSearchParameters& parameters)
{
	return PrepareGelbooruRequest("gelbooru.com", parameters);
}

std::variant<QList<BooruImage*>, QString> GelbooruProvider::tryParseReply(QNetworkReply& reply) const
{
    QDomDocument xmlResponse;
    if(QDomDocument::ParseResult parseResult = xmlResponse.setContent(&reply); !parseResult)
    {
        //TODO: error message
        return "";
    }

    QDomElement postsNode = xmlResponse.firstChildElement("posts");
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
