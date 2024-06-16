#include "models/DatasetItem.hpp"

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

void ImageDatasetItem::unregisterBuddy(DatasetItem* buddy)
{
    if(buddy->type == Type::Image && buddy->baseName == baseName)
    {
        //should we emit if removeIf succeded ?
        concurrents.removeIf([buddy](DatasetItem* item) { return item->path == buddy->path; });
        emit concurrentsChanged();
    }

    if(buddy->type == Type::Tagfile && buddy->baseName == baseName)
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

void TagfileDatasetItem::unregisterBuddy(DatasetItem* buddy)
{
    if(buddy->type == Type::Image && buddy->baseName == baseName)
    {
        //should we emit if removeIf succeded ?
        associatedImages.removeIf([buddy](DatasetItem* item) { return item->path == buddy->path; });
        emit associatedImagesChanged();
    }
}
