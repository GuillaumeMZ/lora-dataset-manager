#pragma once

#include <utility>

#include <QObject>

#include "models/BooruImage.hpp"

class ScheduledDownloadBooruImage: public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(const BooruImage* target MEMBER target CONSTANT)
	    Q_PROPERTY(const QString downloadName MEMBER downloadName CONSTANT)
	    Q_PROPERTY(const bool downloadTags MEMBER downloadTags CONSTANT)

	    ScheduledDownloadBooruImage(
	        const BooruImage* target, QString downloadName, bool downloadTags, QObject *parent = nullptr
		):
	        QObject(parent),
 			target(target),
	        downloadName(std::move(downloadName)),
	        downloadTags(downloadTags)
	    {
	    }

		const BooruImage* target;
		const QString downloadName; //empty == default name
	    const bool downloadTags;
};