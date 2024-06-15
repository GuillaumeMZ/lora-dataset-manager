#include "viewmodels/DatasetViewerViewModel.hpp"

QList<ImageDatasetItem*> DatasetViewerViewModel::images() const
{
    QList<ImageDatasetItem*> result;

    for(auto item: dataset->getItems())
    {
        if(item->type != DatasetItem::Type::Image)
        {
            continue;
        }

        result.append(qobject_cast<ImageDatasetItem*>(item));
    }

    return result;
}
