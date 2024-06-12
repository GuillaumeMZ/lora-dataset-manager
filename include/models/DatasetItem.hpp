#pragma once

#include <QFileInfo>
#include <QObject>
#include <QUrl>
#include <QVariant>

class DatasetItem: public QObject
{
    Q_OBJECT //Q_GADGET ??

    public:
        static DatasetItem FromUnknown(const QFileInfo& fileInfo, QObject* parent = nullptr);
        static DatasetItem FromDirectory(const QFileInfo& fileInfo, QObject* parent = nullptr);
        static DatasetItem FromImage(
                const QFileInfo& fileInfo,
                const QList<DatasetItem*>& associatedTagfiles,
                const QList<DatasetItem*>& concurrents,
                QObject* parent = nullptr
        );
        static DatasetItem FromTagfile(const QFileInfo& fileInfo, const QString& tags, QObject* parent = nullptr);

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

class ImageInfo
{
    Q_GADGET

    public:
        ImageInfo() = default; //shouldn't be used, only here to make q_declare_metatype happy
        ImageInfo(const ImageInfo&) = default;
        ImageInfo(const QList<DatasetItem*>& associatedTagfiles, const QList<DatasetItem*>& concurrents):
            associatedTagfiles(associatedTagfiles),
            concurrents(concurrents)
        {
        }
        ~ImageInfo() = default;

        Q_PROPERTY(const QList<DatasetItem*> associatedTagfiles MEMBER associatedTagfiles CONSTANT)
        Q_PROPERTY(const QList<DatasetItem*> concurrents MEMBER concurrents CONSTANT)

    private:
        const QList<DatasetItem*> associatedTagfiles;
        const QList<DatasetItem*> concurrents;
};
Q_DECLARE_METATYPE(ImageInfo)

class TagfileInfo
{
    Q_GADGET

    public:
        TagfileInfo() = default; //shouldn't be used, only here to make q_declare_metatype happy
        TagfileInfo(const TagfileInfo&) = default;
        TagfileInfo(const QString& tags):
            tags(tags)
        {
        }
        ~TagfileInfo() = default;

        Q_PROPERTY(const QString tags MEMBER tags CONSTANT)

    private:
        const QString tags;
};
Q_DECLARE_METATYPE(TagfileInfo)

