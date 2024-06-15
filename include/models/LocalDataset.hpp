#pragma once

#include <QDir>
#include <QFileInfo>
#include <QObject>

#include "models/DatasetItem.hpp"
#include "services/LocalDatasetWatcher.hpp"

Q_GLOBAL_STATIC(const QList<QString>, IMAGE_FORMATS, {"png", "jpg", "jpeg", "bmp", "webp"})
Q_GLOBAL_STATIC(const QString, TAGFILE_FORMAT, "txt")

class LocalDataset: public QObject
{
    Q_OBJECT

    public:
        LocalDataset(const QDir& datasetRoot, QObject* parent = nullptr);

        //Q_INVOKABLE void save(const DatasetItem* item);
        //Q_INVOKABLE void saveAll();

        Q_PROPERTY(QList<DatasetItem*> items MEMBER items NOTIFY itemsChanged)

        const QList<DatasetItem*>& getItems() const
        {
            return items;
        }

    signals:
        void itemsChanged();
        void itemModified(DatasetItem* item);
        void datasetRemoved();

    private slots:
        void onItemAdded(QFileInfo item);
        //void onItemRemoved(QFileInfo item);
        //void onDatasetRemoved();

    private:
        DatasetItem* fromFileInfo(const QFileInfo& fileInfo);

    private:
        QDir datasetRoot;
        QList<DatasetItem*> items;
        LocalDatasetWatcher watcher;
};
