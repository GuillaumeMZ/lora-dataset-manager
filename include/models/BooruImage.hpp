#pragma once

#include <QObject>
#include <QUrl>

class BooruImage: public QObject
{
    Q_OBJECT

    public:
        BooruImage(const QUrl& imageThumbnailUrl, const QUrl& fullImageUrl, QObject* parent = nullptr):
            QObject(parent),
            imageThumbnailUrl(imageThumbnailUrl),
            fullImageUrl(fullImageUrl)
        {
        }

        Q_PROPERTY(QUrl imageThumbnailUrl MEMBER imageThumbnailUrl CONSTANT)
        Q_PROPERTY(QUrl fullImageUrl MEMBER fullImageUrl CONSTANT)

    private:
        QUrl imageThumbnailUrl;
        QUrl fullImageUrl;
};