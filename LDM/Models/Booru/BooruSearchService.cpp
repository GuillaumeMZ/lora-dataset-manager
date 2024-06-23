#include <memory>

#include <QDebug>
#include <QUrl>
#include <QUrlQuery>

#include "./BooruSearchService.hpp"
#include "./GelbooruProvider.hpp"
#include "./SafebooruProvider.hpp"
#include "../GlobalNetworkService.hpp"

void BooruSearchRequest::start(const BooruSearchParameters& searchParameters)
{
	std::shared_ptr<BooruProvider> provider;
	if(searchParameters.provider == "Gelbooru")
	{
		provider = std::make_shared<GelbooruProvider>();
	}
	else if(searchParameters.provider == "Safebooru")
	{
		provider = std::make_shared<SafebooruProvider>();
	}
	else
	{
		qDebug() << "Internal error: failed to create a provider: unknown provider" << searchParameters.provider;
		return;
	}

    QNetworkReply* searchReply = GlobalNetworkService::get().get(provider->prepareRequest(searchParameters));

    QObject::connect(searchReply, &QNetworkReply::errorOccurred, this, [this, searchReply](QNetworkReply::NetworkError _) {
        //TODO: format error message
        emit this->errorOccured(searchReply->errorString());
    });

    QObject::connect(searchReply, &QNetworkReply::finished, this, [this, provider, searchReply] {
        std::variant<QList<BooruImage*>, QString> reparseResult = provider->tryParseReply(*searchReply);
        if(std::holds_alternative<QString>(reparseResult))
        {
            emit errorOccured(std::get<QString>(reparseResult));
            return;
        }

        emit finished(std::get<QList<BooruImage*>>(reparseResult));
    });
}
