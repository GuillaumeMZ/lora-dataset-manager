#pragma once

#include <QObject>
#include <QUrl>

//TODO: rename attributes imageThumbnailUrl and fullImageUrl so that they match the XML
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

        BooruImage(const BooruImage& rhs, QObject* parent = nullptr):
                BooruImage(rhs.imageThumbnailUrl, rhs.fullImageUrl, parent)
        {
        }

        Q_PROPERTY(QUrl imageThumbnailUrl MEMBER imageThumbnailUrl CONSTANT)
        Q_PROPERTY(QUrl fullImageUrl MEMBER fullImageUrl CONSTANT)

    private:
        QUrl imageThumbnailUrl;
        QUrl fullImageUrl;
};