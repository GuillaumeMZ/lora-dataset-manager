#include "./DatasetItem.hpp"

void ImageDatasetItem::registerBuddy(DatasetItem* buddy)
{
    if(buddy->type == Type::Image && buddy->baseName == baseName)
    {
        concurrents.append(buddy);
        emit concurrentsChanged();
    }

    if(buddy->type == Type::Tagfile && buddy->baseName == baseName)
    {
        associatedTagfile = buddy;
        emit associatedTagfileChanged();
    }
}

void ImageDatasetItem::unregisterBuddy(const QFileInfo& buddy)
{
    if(concurrents.removeIf([buddy](DatasetItem* item) { return QUrl(buddy.absoluteFilePath()) == item->path; }) != 0)
    {
        emit concurrentsChanged();
    }

    if(associatedTagfile != nullptr && QUrl(buddy.absoluteFilePath()) == associatedTagfile->path)
    {
        associatedTagfile = nullptr;
        emit associatedTagfileChanged();
    }
}

void TagfileDatasetItem::registerBuddy(DatasetItem* buddy)
{
    if(buddy->type == Type::Image && buddy->baseName == baseName)
    {
        associatedImages.append(buddy);
        emit associatedImagesChanged();
    }
}

void TagfileDatasetItem::unregisterBuddy(const QFileInfo& buddy)
{
    if(associatedImages.removeIf([buddy](DatasetItem* item) { return QUrl(buddy.absoluteFilePath()) == item->path; }) != 0)
    {
        emit associatedImagesChanged();
    }
}
