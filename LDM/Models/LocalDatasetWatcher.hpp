#pragma once

#include <optional>

#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QList>
#include <QObject>

class LocalDatasetWatcher: public QObject
{
    Q_OBJECT

    public:
        LocalDatasetWatcher(QDir datasetRoot, QObject *parent = nullptr);

    signals:
        void itemAdded(QFileInfo);
        void itemRemoved(QFileInfo);
        void itemModified(QFileInfo);
        void datasetRemoved();

    private slots:
        void handleDirectoryChange(const QString& path);
        void handleFileChange(const QString& path);

    private:
        std::optional<QFileInfo> getAddedItem() const;
        std::optional<QFileInfo> getRemovedItem() const;

    private:
        QDir datasetRoot;
        QFileSystemWatcher watcher;
        QFileInfoList currentItems;
};
