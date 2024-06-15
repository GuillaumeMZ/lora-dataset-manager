#pragma once

#include <QList>
#include <QObject>
#include <QQmlEngine>

#include "models/DatasetItem.hpp"
#include "models/LocalDataset.hpp"

class DatasetViewerViewModel: public QObject
{
    Q_OBJECT
    //QML_ELEMENT

    public:
        DatasetViewerViewModel(LocalDataset* dataset, QObject* parent = nullptr):
            QObject(parent),
            dataset(dataset)
        {
            QObject::connect(dataset, &LocalDataset::itemsChanged, this, [this]() { emit imagesChanged(); });
        }

        Q_PROPERTY(QList<ImageDatasetItem*> images READ images NOTIFY imagesChanged FINAL)

        QList<ImageDatasetItem*> images() const;

    signals:
        void imagesChanged();

    private:
        LocalDataset* dataset;
};
