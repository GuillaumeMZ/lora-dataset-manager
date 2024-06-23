#include "viewmodels/DatasetViewerViewModel.hpp"

void DatasetViewerViewModel::onItemAdded(DatasetItem* item)
{
    if(item->type != DatasetItem::Type::Image)
    {
        return;
    }

    images.append(qobject_cast<ImageDatasetItem*>(item));
    emit imagesChanged();

    //no need to handle tagfiles because tags are embedded inside the imagedatasetitem
}

void DatasetViewerViewModel::onItemRemoved(QFileInfo itemInfo)
{

}
