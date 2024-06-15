#pragma once

#include <QFileInfo>
#include <QObject>
#include <QUrl>
#include <QVariant>

class DatasetItem: public QObject
{
    Q_OBJECT

    public:
        enum Type
        {
            Image, Tagfile, Directory, Unknown
        };
        Q_ENUM(Type)

        DatasetItem(const QFileInfo& fileInfo, const Type& type, QObject* parent = nullptr):
            QObject(parent),
            path(fileInfo.absoluteFilePath()),
            name(fileInfo.fileName()),
            type(type)
        {
        }

        Q_PROPERTY(const QUrl path MEMBER path CONSTANT)
        Q_PROPERTY(const QString name MEMBER name CONSTANT)
        Q_PROPERTY(const Type type MEMBER type CONSTANT)

        const QUrl path;
        const QString name;
        const Type type;
};

class ImageDatasetItem: public DatasetItem
{
    Q_OBJECT

    public:
        ImageDatasetItem(const QFileInfo& fileInfo, QObject* parent = nullptr):
            DatasetItem(fileInfo, Type::Image, parent)
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

class TagfileDatasetItem: public DatasetItem
{
    Q_OBJECT

    public:
        TagfileDatasetItem(const QFileInfo& fileInfo, const QString& tags, QObject* parent = nullptr):
            DatasetItem(fileInfo, Type::Tagfile, parent),
            tags(tags)
        {
        }

        Q_PROPERTY(QString tags MEMBER tags NOTIFY tagsChanged)
        //QList<DatasetItem*> associatedImages

    signals:
        void tagsChanged();

    private:
        QString tags;
};
