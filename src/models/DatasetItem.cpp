#include "models/DatasetItem.hpp"

DatasetItem DatasetItem::FromUnknown(const QFileInfo &fileInfo, QObject *parent)
{
    return DatasetItem(fileInfo, Type::Unknown, QVariant(), parent);
}

DatasetItem DatasetItem::FromDirectory(const QFileInfo &fileInfo, QObject *parent)
{
    return DatasetItem(fileInfo, Type::Directory, QVariant(), parent);
}

DatasetItem DatasetItem::FromImage(
        const QFileInfo& fileInfo,
        const QList<DatasetItem *>& associatedTagfiles,
        const QList<DatasetItem *>& concurrents,
        QObject* parent
)
{
    return DatasetItem(fileInfo, Type::Image, QVariant::fromValue(ImageInfo(associatedTagfiles, concurrents)), parent);
}

DatasetItem DatasetItem::FromTagfile(const QFileInfo& fileInfo, const QString& tags, QObject* parent)
{
    return DatasetItem(fileInfo, Type::Tagfile, QVariant::fromValue(TagfileInfo(tags)));
}