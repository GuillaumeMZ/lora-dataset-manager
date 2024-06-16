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
            baseName(fileInfo.baseName()),
            type(type)
        {
        }

        Q_PROPERTY(const QUrl path MEMBER path CONSTANT)
        Q_PROPERTY(const QString name MEMBER name CONSTANT)
        Q_PROPERTY(const Type type MEMBER type CONSTANT)

        virtual void registerBuddy(DatasetItem* buddy) { /* no-op */ }
        virtual void unregisterBuddy(DatasetItem* buddy) { /* no-op */ }

        const QUrl path;
        const QString name;
        const QString baseName;
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

        Q_PROPERTY(DatasetItem* associatedTagfile MEMBER associatedTagfile NOTIFY associatedTagfileChanged)
        Q_PROPERTY(QList<DatasetItem*> concurrents MEMBER concurrents NOTIFY concurrentsChanged)

        void registerBuddy(DatasetItem* buddy) override;
        void unregisterBuddy(DatasetItem* buddy) override;

    signals:
        void associatedTagfileChanged();
        void concurrentsChanged();

    private:
        DatasetItem* associatedTagfile {};
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

        Q_PROPERTY(QList<DatasetItem*> associatedImages MEMBER associatedImages NOTIFY associatedImagesChanged)
        Q_PROPERTY(QString tags MEMBER tags NOTIFY tagsChanged)

        void registerBuddy(DatasetItem* buddy) override;
        void unregisterBuddy(DatasetItem* buddy) override;

    signals:
        void associatedImagesChanged();
        void tagsChanged();

    private:
        QList<DatasetItem*> associatedImages;
        QString tags;
};
