#include <QDebug>

#include "services/LocalDatasetWatcher.hpp"

LocalDatasetWatcher::LocalDatasetWatcher(QDir datasetRoot, QObject* parent):
    QObject(parent),
    datasetRoot(std::move(datasetRoot)),
    watcher({ datasetRoot.absolutePath() }),
    currentItems(datasetRoot.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
{
    qDebug() << "Initial config:" << currentItems;
    for(const auto item: currentItems)
    {
        if(!item.isDir()) //we don't care about subdirectories' contents
        {
            watcher.addPath(item.absoluteFilePath());
        }
    }
    qDebug() << "Initial watcher config:" << watcher.files() << "|" << watcher.directories();

    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged, this, &LocalDatasetWatcher::handleDirectoryChange);
    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, this, &LocalDatasetWatcher::handleFileChange);
}

//creating, renaming, deleting a file/directory will trigger a handleDirectoryChange with path being its parent
//renaming / deleting / modifying a watched file will trigger a handleFileChange with path being itself
//so:
// - handle creating, renaming, deleting a file/directory in handleDirectoryChange (to do that in one place)
// - handle modifications in handleFileChange (because we know the modified file's path

void LocalDatasetWatcher::handleDirectoryChange(const QString& path)
{
    //we check removing first, to correctly handle renaming-by-deletion logic
    if(auto removedItem = getRemovedItem(); removedItem.has_value())
    {
        if(!removedItem->isDir())
        {
            watcher.removePath(removedItem->absoluteFilePath());
        }

        currentItems.removeIf([removedItem](const QFileInfo& fileInfo) {
            return fileInfo.absoluteFilePath() == removedItem->absoluteFilePath();
        });
        //TODO: emit signal
    }

    //check adding
    if(auto addedItem = getAddedItem(); addedItem.has_value())
    {
        if(!addedItem->isDir())
        {
            watcher.addPath(addedItem->absoluteFilePath());
        }

        currentItems.append(*addedItem);
        //TODO: emit signal
    }
    qDebug() << "Dir change:" << path << "(dirs: " << watcher.directories() << ", paths:" << watcher.files() << ")";
}

void LocalDatasetWatcher::handleFileChange(const QString& path) {
    const QFileInfo pathInfo(path);
    if(!currentItems.contains(pathInfo) || !pathInfo.exists())
    {
        //it is a creation or a deletion (handled by handleDirectoryChange)
        return;
    }
    //TODO: emit signal
}

std::optional<QFileInfo> LocalDatasetWatcher::getAddedItem() const
{
    QFileInfoList newEntries = datasetRoot.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    for(const auto& entry: newEntries)
    {
        if(!currentItems.contains(entry))
        {
            return entry;
        }
    }

    return std::nullopt;
}

std::optional<QFileInfo> LocalDatasetWatcher::getRemovedItem() const
{
    QFileInfoList newEntries = datasetRoot.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    for(const auto& entry: currentItems)
    {
        if(!newEntries.contains(entry))
        {
            return entry;
        }
    }

    return std::nullopt;
}