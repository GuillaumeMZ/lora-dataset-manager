#pragma once

#include <QObject>

#include "models/EasyListModel.hpp"
#include "models/BooruImage.hpp"
#include "models/ScheduledDownloadBooruImage.hpp"

class GrabberViewModel: public QObject
{
    Q_OBJECT

    public:
        GrabberViewModel(QObject* parent = nullptr):
            QObject(parent),
            queriedImages(new EasyListModel<BooruImage*>(parent)),
			scheduledImages(new EasyListModel<ScheduledDownloadBooruImage*>(parent))
        {
        }

        Q_INVOKABLE void runSearch(const QString& booruProvider, const QString& query);
		Q_INVOKABLE bool isImageMarkedForDownload(const QUrl& imageUrl) const;
	    Q_INVOKABLE void addImageToDownloadList(const BooruImage* target, const QString& downloadName, bool downloadTags);
		Q_INVOKABLE void removeImageFromDownloadList(const QUrl& imageUrl);

        Q_PROPERTY(EasyListModel<BooruImage*>* queriedImages MEMBER queriedImages NOTIFY queriedImagesChanged)
	    Q_PROPERTY(EasyListModel<ScheduledDownloadBooruImage*>* scheduledImages MEMBER scheduledImages NOTIFY scheduledImagesChanged)

    signals:
        void queryStarted();
        void queryFinished();
        void errorOccured(QString errorDescription);
        void queriedImagesChanged();
	    void scheduledImagesChanged();

    private:
        EasyListModel<BooruImage*>* queriedImages;
	    EasyListModel<ScheduledDownloadBooruImage*>* scheduledImages;
};