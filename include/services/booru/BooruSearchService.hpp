#pragma once

#include <variant> //is it even useful ?

#include <QList>
#include <QNetworkReply> //todo: move
#include <QObject>
#include <QtXml/QDomComment> //todo: move

#include "models/BooruImage.hpp"

struct BooruSearchParameters
{
    const QString& provider;
    const QString& query;
};

class BooruSearchRequest: public QObject
{
    Q_OBJECT

    public:
		using QObject::QObject;

		void start(const BooruSearchParameters& searchParameters);

    signals:
        void finished(QList<BooruImage*> queriedImages);
        void errorOccured(QString errorDescription);
};