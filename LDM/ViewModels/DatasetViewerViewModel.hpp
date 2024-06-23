#pragma once

#include <QList>
#include <QObject>
#include <QQmlEngine>

#include "../Models/DatasetItem.hpp"
#include "../Models/LocalDataset.hpp"

class DatasetViewerViewModel: public QObject
{
    Q_OBJECT
    //QML_ELEMENT

    public:
        DatasetViewerViewModel(LocalDataset* dataset, QObject* parent = nullptr):
            QObject(parent),
            dataset(dataset)
        {
            Q_ASSERT(QObject::connect(dataset, &LocalDataset::itemAdded, this, &DatasetViewerViewModel::onItemAdded));
            Q_ASSERT(QObject::connect(dataset, &LocalDataset::itemRemoved, this, &DatasetViewerViewModel::onItemRemoved));
        }

        Q_PROPERTY(LocalDataset* dataset MEMBER dataset CONSTANT)
        Q_PROPERTY(QList<ImageDatasetItem*> images MEMBER images NOTIFY imagesChanged)

    private slots:
        void onItemAdded(DatasetItem* item);
        void onItemRemoved(QFileInfo itemInfo);

    signals:
        void imagesChanged();

    private:
        LocalDataset* dataset;
        QList<ImageDatasetItem*> images;
};
