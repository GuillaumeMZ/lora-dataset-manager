#pragma once

#include <QFileInfo>
#include <QObject>
#include <QUrl>
#include <QVariant>

class DatasetItem: public QObject
{
    Q_OBJECT

    public:
        /**
        * Creates a DatasetItem of type Directory or Unknown, depending on whether fileInfo is one.
        */
        DatasetItem(const QFileInfo& fileInfo, QObject* parent = nullptr);
        /**
         * Creates a DatasetItem of type Image
         */
        DatasetItem(
                const QFileInfo& fileInfo,
                const QList<DatasetItem*>& associatedTagfiles,
                const QList<DatasetItem*>& concurrents,
                QObject* parent = nullptr
        );
        /**
         * Creates a DatasetItem of type Tagfile
         */
        DatasetItem(const QFileInfo& fileInfo, const QString& tags, QObject* parent = nullptr);

        enum Type
        {
            Image, Tagfile, Directory, Unknown
        };
        Q_ENUM(Type);

        Q_PROPERTY(const QUrl path MEMBER path CONSTANT)
        Q_PROPERTY(const QString name MEMBER name CONSTANT)
        Q_PROPERTY(const Type type MEMBER type CONSTANT)
        Q_PROPERTY(const QVariant specificInfos MEMBER specificInfos CONSTANT)

    private:
        DatasetItem(const QFileInfo& fileInfo, const Type& type, const QVariant& specificInfos, QObject* parent = nullptr):
            QObject(parent),
            path(fileInfo.absoluteFilePath()),
            name(fileInfo.baseName()),
            type(type),
            specificInfos(specificInfos)
        {
        }

        const QUrl path;
        const QString name;
        const Type type;
        const QVariant specificInfos;
};

class ImageInfo: public QObject
{
    Q_OBJECT

    public:
        ImageInfo(const QList<DatasetItem*>& associatedTagfiles, const QList<DatasetItem*>& concurrents, QObject* parent = nullptr):
            QObject(parent),
            associatedTagfiles(associatedTagfiles),
            concurrents(concurrents)
        {
        }

        Q_PROPERTY(QList<DatasetItem*> associatedTagfiles MEMBER associatedTagfiles NOTIFY associatedTagfilesChanged)
        Q_PROPERTY(QList<DatasetItem*> concurrents MEMBER concurrents NOTIFY concurrentsChanged)

    signals:
        void associatedTagfilesChanged();
        void concurrentsChanged();

    private:
        QList<DatasetItem*> associatedTagfiles;
        QList<DatasetItem*> concurrents;
};

class TagfileInfo: public QObject
{
    Q_OBJECT

    public:
        TagfileInfo(const QString& tags, QObject* parent = nullptr):
            QObject(parent),
            tags(tags)
        {
        }

        Q_PROPERTY(QString tags MEMBER tags NOTIFY tagsChanged)

    signals:
        void tagsChanged();

    private:
        QString tags;
};
