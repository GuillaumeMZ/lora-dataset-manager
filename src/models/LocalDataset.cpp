#include "models/LocalDataset.hpp"

LocalDataset::LocalDataset(const QDir& datasetRoot, QObject* parent):
    QObject(parent),
    datasetRoot(datasetRoot),
    watcher(datasetRoot, this)
{
    for(const auto& fileInfo: datasetRoot.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
    {
        onItemAdded(fileInfo);
    }

    QObject::connect(&watcher, &LocalDatasetWatcher::itemAdded, this, &LocalDataset::onItemAdded);
    QObject::connect(&watcher, &LocalDatasetWatcher::itemRemoved, this, &LocalDataset::onItemRemoved);
    QObject::connect(&watcher, &LocalDatasetWatcher::itemModified, this, [this](QFileInfo item) { emit itemModified(fromFileInfo(item)); });
    QObject::connect(&watcher, &LocalDatasetWatcher::datasetRemoved, this, [this] { emit datasetRemoved(); });
}

void LocalDataset::onItemAdded(QFileInfo itemInfo)
{
    DatasetItem* newItem = fromFileInfo(itemInfo);

    for(DatasetItem* item: items)
    {
        item->registerBuddy(newItem);
        newItem->registerBuddy(item);
    }

    items.append(newItem);

    emit itemsChanged();
}

void LocalDataset::onItemRemoved(QFileInfo itemInfo)
{
    DatasetItem* oldItem = fromFileInfo(itemInfo);

    qsizetype removedItemsCount = items.removeIf([oldItem](DatasetItem* currentItem) { return oldItem->path == currentItem->path; });
    if(removedItemsCount == 0)
    {
        return; //shouldn't happen
    }

    for(DatasetItem* item: items)
    {
        item->unregisterBuddy(oldItem);
    }

    emit itemsChanged();
}

DatasetItem* LocalDataset::fromFileInfo(const QFileInfo& fileInfo)
{
    const QString extension = fileInfo.suffix().toLower();

    if(IMAGE_FORMATS->contains(extension))
    {
        return new ImageDatasetItem(fileInfo, this);
    }
    else if(*TAGFILE_FORMAT == extension)
    {
        QFile tagfile(fileInfo.absoluteFilePath());
        tagfile.open(QIODevice::ReadOnly | QIODevice::ExistingOnly);
        QString tags = tagfile.readAll();
        tagfile.close();

        return new TagfileDatasetItem(fileInfo, tags, this);
    }
    else if(fileInfo.isDir())
    {
        return new DatasetItem(fileInfo, DatasetItem::Type::Directory, this);
    }
    else
    {
        return new DatasetItem(fileInfo, DatasetItem::Type::Unknown, this);
    }
}
