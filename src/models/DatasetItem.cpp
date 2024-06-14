#include "models/DatasetItem.hpp"

DatasetItem::DatasetItem(const QFileInfo &fileInfo, QObject *parent):
    DatasetItem(fileInfo, fileInfo.isDir() ? Type::Directory : Type::Unknown, QVariant(), parent)
{
}

DatasetItem::DatasetItem(
        const QFileInfo& fileInfo,
        const QList<DatasetItem*>& associatedTagfiles,
        const QList<DatasetItem*>& concurrents,
        QObject* parent
):
    DatasetItem(fileInfo, Type::Image, QVariant::fromValue(new ImageInfo(associatedTagfiles, concurrents, this)), parent)
{
}

DatasetItem::DatasetItem(const QFileInfo& fileInfo, const QString& tags, QObject* parent):
    DatasetItem(fileInfo, Type::Tagfile, QVariant::fromValue(new TagfileInfo(tags, this)), parent)
{
}
