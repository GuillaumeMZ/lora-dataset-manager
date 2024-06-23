#pragma once

#include "./BooruProvider.hpp"

//Free function because it is used by Gelbooru and Safebooru (and maybe others in the future ?)
QNetworkRequest PrepareGelbooruRequest(const QString& booruBaseUrl, const BooruSearchParameters& parameters);

class GelbooruProvider: public BooruProvider
{
    public:
        QNetworkRequest prepareRequest(const BooruSearchParameters& parameters) override;
        std::variant<QList<BooruImage *>, QString> tryParseReply(QNetworkReply &reply) const override;
};
