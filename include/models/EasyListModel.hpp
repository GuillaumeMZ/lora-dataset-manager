#pragma once

#include <QAbstractListModel>
#include <QList>

template<typename T>
class EasyListModel: public QAbstractListModel
{
    public:
        explicit EasyListModel(QObject* parent = nullptr):
            QAbstractListModel(parent)
        {
        }

        void append(const T& value);
        void clear();

	    template <typename Predicate>
	    void removeIf(Predicate predicate);

	    typename QList<T>::const_iterator cbegin() const;
	    typename QList<T>::const_iterator cend() const;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

    private:
        QList<T> items;
};

template<typename T>
void EasyListModel<T>::append(const T& value)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items.append(value);
    endInsertRows();
}

template<typename T>
void EasyListModel<T>::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    items.clear();
    endRemoveRows();
}

template<typename T>
template<typename Predicate>
void EasyListModel<T>::removeIf(Predicate predicate)
{
	items.removeIf(predicate);
}

template<typename T>
typename QList<T>::const_iterator EasyListModel<T>::cbegin() const
{
	return items.cbegin();
}

template<typename T>
typename QList<T>::const_iterator EasyListModel<T>::cend() const
{
	return items.cend();
}

template<typename T>
int EasyListModel<T>::rowCount(const QModelIndex& parent) const
{
    return items.count();
}

template<typename T>
QVariant EasyListModel<T>::data(const QModelIndex& index, int role) const
{
    int actualIndex = index.row();
    if(!index.isValid() || actualIndex < 0 || actualIndex >= items.count())
    {
        return {};
    }

    return QVariant::fromValue(items.at(actualIndex));
}

template<typename T>
QHash<int, QByteArray> EasyListModel<T>::roleNames() const
{
    QHash<int, QByteArray> result;
    result[Qt::UserRole + 1] = "item";

    return result;
}