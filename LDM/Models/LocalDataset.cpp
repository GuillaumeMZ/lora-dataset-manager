#include "./LocalDataset.hpp"

LocalDataset::LocalDataset(const QDir& datasetRoot, QObject* parent):
    QObject(parent),
    datasetRoot(datasetRoot),
    watcher(datasetRoot, this)
{
    Q_ASSERT(QObject::connect(&watcher, &LocalDatasetWatcher::itemAdded, this, &LocalDataset::onItemAdded));
    Q_ASSERT(QObject::connect(&watcher, &LocalDatasetWatcher::itemRemoved, this, &LocalDataset::onItemRemoved));
    Q_ASSERT(QObject::connect(&watcher, &LocalDatasetWatcher::itemModified, this, [this](QFileInfo item) { emit itemModified(fromFileInfo(item)); }));
    Q_ASSERT(QObject::connect(&watcher, &LocalDatasetWatcher::datasetRemoved, this, [this] { emit datasetRemoved(); }));

    Q_ASSERT(QObject::connect(this, &LocalDataset::itemAdded, this, &LocalDataset::itemsChanged));
    Q_ASSERT(QObject::connect(this, &LocalDataset::itemRemoved, this, &LocalDataset::itemsChanged));
    //QObject::connect(this, &LocalDataset::itemModified, this, [this] { emit itemsChanged(); }); ?
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

    emit itemAdded(newItem);
}

void LocalDataset::onItemRemoved(QFileInfo itemInfo)
{
    qsizetype removedItemsCount = items.removeIf([itemInfo](DatasetItem* currentItem) { return QUrl(itemInfo.absoluteFilePath()) == currentItem->path; });
    if(removedItemsCount == 0)
    {
        return; //shouldn't happen
    }

    for(DatasetItem* item: items)
    {
        item->unregisterBuddy(itemInfo);
    }

    emit itemRemoved(itemInfo);
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
