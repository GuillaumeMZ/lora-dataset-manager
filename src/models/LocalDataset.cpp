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
    // QObject::connect(&watcher, &LocalDatasetWatcher::itemRemoved, this, &LocalDataset::onItemRemoved);
    // QObject::connect(&watcher, &LocalDatasetWatcher::itemModified, this, [this](QFileInfo item) { emit itemModified(fromFileInfo(item)); });
    QObject::connect(&watcher, &LocalDatasetWatcher::datasetRemoved, this, [this] { emit datasetRemoved(); });
}

void LocalDataset::onItemAdded(QFileInfo item)
{
    items.append(fromFileInfo(item));
    //TODO: trigger a recomputation of associatedTagfiles/concurrents/associatedImages

    emit itemsChanged();
}

DatasetItem* LocalDataset::fromFileInfo(const QFileInfo& fileInfo)
{
    const QString extension = fileInfo.suffix().toLower();

    DatasetItem* result;
    if(IMAGE_FORMATS->contains(extension))
    {
        result = new ImageDatasetItem(fileInfo, this);
    }
    else if(*TAGFILE_FORMAT == extension)
    {
        QFile tagfile(fileInfo.absoluteFilePath());
        tagfile.open(QIODevice::ReadOnly | QIODevice::ExistingOnly);
        QString tags = tagfile.readAll();
        tagfile.close();

        result = new TagfileDatasetItem(fileInfo, tags, this);
    }
    else if(fileInfo.isDir())
    {
        result = new DatasetItem(fileInfo, DatasetItem::Type::Directory, this);
    }
    else
    {
        result = new DatasetItem(fileInfo, DatasetItem::Type::Unknown, this);
    }

    return result;
}
