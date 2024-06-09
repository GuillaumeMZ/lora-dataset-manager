#pragma once

#include <variant>

#include <QList>
#include <QNetworkReply>
#include <QObject>
#include <QtXml/QDomComment>

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
        BooruSearchRequest(QObject* parent = nullptr):
            QObject(parent)
        {
        }

        void start(const BooruSearchParameters& searchParameters);

    signals:
        void finished(QList<BooruImage*> queriedImages);
        void errorOccured(QString errorDescription);
};