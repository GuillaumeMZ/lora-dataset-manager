#pragma once

#include <optional>

#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QList>
#include <QObject>

#include "models/DatasetItem.hpp"

class LocalDatasetWatcher: public QObject
{
    Q_OBJECT

    public:
        LocalDatasetWatcher(QDir datasetRoot, QObject *parent = nullptr);

    signals:
        void itemAdded();
        void itemRemoved();
        void itemModified();
        void datasetRemoved();

    private slots:
        void handleDirectoryChange(const QString& path);
        void handleFileChange(const QString& path);

    private:
        //Returns the relative path
        std::optional<QFileInfo> getAddedItem() const;
        //Returns the relative path
        std::optional<QFileInfo> getRemovedItem() const;

    private:
        QDir datasetRoot;
        QFileSystemWatcher watcher;
        QFileInfoList currentItems;
};