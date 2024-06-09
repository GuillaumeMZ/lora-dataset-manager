#pragma once

#include "services/booru/BooruProvider.hpp"

class GelbooruProvider: public BooruProvider
{
    public:
        QNetworkRequest prepareRequest(const BooruSearchParameters &parameters) override;
        std::variant<QList<BooruImage *>, QString> tryParseReply(QNetworkReply &reply) const override;
};