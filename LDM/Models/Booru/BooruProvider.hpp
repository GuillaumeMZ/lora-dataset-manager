#pragma once

#include <variant>

#include <QList>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>

#include "./BooruImage.hpp"
#include "./BooruSearchService.hpp"

class BooruProvider
{
    public:
        virtual QNetworkRequest prepareRequest(const BooruSearchParameters& parameters) = 0;
        virtual std::variant<QList<BooruImage*>, QString> tryParseReply(QNetworkReply& reply) const = 0;
};
