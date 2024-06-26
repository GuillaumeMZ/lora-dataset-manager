#pragma once

#include <QDir>
#include <QFileInfo>
#include <QObject>

#include "./DatasetItem.hpp"
#include "./LocalDatasetWatcher.hpp"

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
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QUrl path READ path CONSTANT)

        void load()
        {
            for(const auto& fileInfo: datasetRoot.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
            {
                onItemAdded(fileInfo);
            }
        }

        QString name() const { return datasetRoot.dirName(); }
        QUrl path() const { return datasetRoot.absolutePath(); }

    signals:
        void itemsChanged();
        void itemAdded(DatasetItem* item);
        void itemRemoved(QFileInfo item);
        void itemModified(DatasetItem* item);
        void datasetRemoved();

    private slots:
        void onItemAdded(QFileInfo item);
        void onItemRemoved(QFileInfo item);

    private:
        DatasetItem* fromFileInfo(const QFileInfo& fileInfo);

    private:
        const QDir datasetRoot;
        QList<DatasetItem*> items;
        LocalDatasetWatcher watcher;
};
