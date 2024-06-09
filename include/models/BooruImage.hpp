#pragma once

#include <utility>

#include <QObject>
#include <QUrl>

//TODO: rename attributes imageThumbnailUrl and fullImageUrl so that they match the XML
class BooruImage: public QObject
{
    Q_OBJECT

    public:
        BooruImage(QUrl imageThumbnailUrl, QUrl fullImageUrl, QObject* parent = nullptr):
            QObject(parent),
            imageThumbnailUrl(std::move(imageThumbnailUrl)),
            fullImageUrl(std::move(fullImageUrl))
        {
        }

        BooruImage(const BooruImage& rhs, QObject* parent = nullptr):
                BooruImage(rhs.imageThumbnailUrl, rhs.fullImageUrl, parent)
        {
        }

        Q_PROPERTY(const QUrl imageThumbnailUrl MEMBER imageThumbnailUrl CONSTANT)
        Q_PROPERTY(const QUrl fullImageUrl MEMBER fullImageUrl CONSTANT)

        const QUrl imageThumbnailUrl;
        const QUrl fullImageUrl;
};