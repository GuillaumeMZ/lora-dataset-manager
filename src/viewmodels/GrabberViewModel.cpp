#include <utility>

#include <QDebug>

#include "viewmodels/GrabberViewModel.hpp"
#include "services/booru/BooruSearchService.hpp"

void GrabberViewModel::runSearch(const QString& booruProvider, const QString& query)
{
    queriedImages->clear();

    BooruSearchRequest* searchRequest = new BooruSearchRequest(this);

    QObject::connect(searchRequest, &BooruSearchRequest::finished, this, [this](QList<BooruImage*> queriedImages) {
        for(const auto image: queriedImages)
        {
            image->setParent(this);
            this->queriedImages->append(image);
        }

        emit queriedImagesChanged();
    });

    QObject::connect(searchRequest, &BooruSearchRequest::errorOccured, this, [this](QString errorDescription) {
        emit this->errorOccured(std::move(errorDescription));
    });

    searchRequest->start(BooruSearchParameters {booruProvider, query});
}
