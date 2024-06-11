#include <algorithm>
#include <utility>

#include <QDebug>

#include "viewmodels/GrabberViewModel.hpp"
#include "services/booru/BooruSearchService.hpp"

void GrabberViewModel::runSearch(const QString& booruProvider, const QString& query)
{
    queriedImages->clear();
    emit queryStarted();

    BooruSearchRequest* searchRequest = new BooruSearchRequest(this);

    QObject::connect(searchRequest, &BooruSearchRequest::finished, this, [this](QList<BooruImage*> queriedImages) {
        for(const auto image: queriedImages)
        {
            image->setParent(this);
            this->queriedImages->append(image);
        }

        emit queryFinished();
        emit queriedImagesChanged();
    });

    QObject::connect(searchRequest, &BooruSearchRequest::errorOccured, this, [this](QString errorDescription) {
        emit this->errorOccured(std::move(errorDescription));
    });

    searchRequest->start(BooruSearchParameters { booruProvider, query });
}

bool GrabberViewModel::isImageMarkedForDownload(const QUrl& imageUrl) const
{
	return std::find_if(scheduledImages->cbegin(), scheduledImages->cend(), [imageUrl](auto item) {
		return item->target->fullImageUrl == imageUrl;
	}) != scheduledImages->cend();
}

void GrabberViewModel::addImageToDownloadList(const BooruImage* target, const QString& downloadName, bool downloadTags)
{
	if(isImageMarkedForDownload(target->fullImageUrl))
	{
		return;
	}

	scheduledImages->append(new ScheduledDownloadBooruImage(target, downloadName, downloadTags, this));

	emit scheduledImagesChanged();
}

void GrabberViewModel::removeImageFromDownloadList(const QUrl& imageUrl)
{
	scheduledImages->removeIf([imageUrl](auto item) {
		return item->target->fullImageUrl == imageUrl;
	});
}
