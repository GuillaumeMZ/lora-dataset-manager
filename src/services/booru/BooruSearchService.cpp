#include <QDebug>
#include <QUrl>
#include <QUrlQuery>

#include "services/booru/BooruSearchService.hpp"
#include "services/booru/GelbooruProvider.hpp"
#include "services/GlobalNetworkService.hpp"

void BooruSearchRequest::start(const BooruSearchParameters& searchParameters)
{
//    const BooruProvider* provider = FindBooruProvider(searchParameters.provider);
//    if(provider == nullptr)
//    {
//        emit errorOccured("...");
//    }
    GelbooruProvider provider;

    QNetworkReply* searchReply = GlobalNetworkService::get().get(provider.prepareRequest(searchParameters));

    QObject::connect(searchReply, &QNetworkReply::errorOccurred, this, [this, searchReply](QNetworkReply::NetworkError _) {
        //TODO: format error message
        emit this->errorOccured(searchReply->errorString());
    });

    QObject::connect(searchReply, &QNetworkReply::finished, this, [this, provider, searchReply] {
        std::variant<QList<BooruImage*>, QString> reparseResult = provider.tryParseReply(*searchReply);
        if(std::holds_alternative<QString>(reparseResult))
        {
            emit errorOccured(std::get<QString>(reparseResult));
            return;
        }

        emit finished(std::get<QList<BooruImage*>>(reparseResult));
    });
}