#pragma once

#include <QObject>

#include "models/EasyListModel.hpp"
#include "models/BooruImage.hpp"

class GrabberViewModel: public QObject
{
    Q_OBJECT

    public:
        GrabberViewModel(QObject* parent = nullptr):
            QObject(parent),
            queriedImages(new EasyListModel<BooruImage*>(parent))
        {
        }

        Q_INVOKABLE void runSearch(const QString& booruProvider, const QString& query);

        Q_PROPERTY(EasyListModel<BooruImage*>* queriedImages MEMBER queriedImages NOTIFY queriedImagesChanged)

    signals:
        void queriedImagesChanged();

    private:
        EasyListModel<BooruImage*>* queriedImages;
};