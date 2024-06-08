#include "viewmodels/GrabberViewModel.hpp"

void GrabberViewModel::runSearch(const QString& booruProvider, const QString& query)
{
    queriedImages->clear();

    emit queriedImagesChanged();
}

