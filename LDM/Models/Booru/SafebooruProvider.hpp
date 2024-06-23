#pragma once

#include "./BooruProvider.hpp"

class SafebooruProvider: public BooruProvider
{
	public:
		QNetworkRequest prepareRequest(const BooruSearchParameters& parameters) override;
		std::variant<QList<BooruImage*>, QString> tryParseReply(QNetworkReply& reply) const override;
};
