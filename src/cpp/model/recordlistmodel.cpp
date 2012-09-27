#include "../cpp/model/recordlistmodel.hpp"

RecordListModel::RecordListModel(const QSqlDatabase &db, QObject *parent)
    : QAbstractListModel(parent)
{
    _db = db;
}

RecordListModel::~RecordListModel()
{
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("QSQLITE");
}

void RecordListModel::appendRow(RecordListItem *item)
{
    appendRows(QList<RecordListItem*>() << item);
}

void RecordListModel::appendRows(const QList<RecordListItem *> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);

    foreach(RecordListItem *item, items) {
        _recordList.append(item);
    }

    endInsertRows();

    emit countChanged();
}


bool RecordListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || row >= _recordList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row);

    delete _recordList.takeAt(row);

    endRemoveRows();

    return true;
}

bool RecordListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    if(row < 0 || (row+count) >= _recordList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row+count-1);

    for(int i=0; i<count; ++i) {
        delete _recordList.takeAt(row);
    }

    endRemoveRows();

    return true;
}

int RecordListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _recordList.count();
}


QVariant RecordListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > _recordList.count())
    {
        return QVariant();
    }

    //    if(role == WorkoutLogListIdRole)
    //    {
    //        return _logList[index.row()]->getId();
    //    }
    //    else if (role == WorkoutLogListNameRole)
    //    {
    //        return _logList[index.row()]->getName();
    //    }
    //    else if (role == WorkoutLogListDateRole)
    //    {
    //        return _logList[index.row()]->getStringDate();
    //    }
    //    else if(role == WorkoutLogListDescriptionRole)
    //    {
    //        return _logList[index.row()]->getDescription();
    //    }
    //    else if(role == WorkoutLogListHandlestampRole)
    //    {
    //        return _logList[index.row()]->getHandleStamp();
    //    }
    //    else
    //    {
    return QVariant();
    //    }
}

void RecordListModel::clear() const
{

}


void RecordListModel::persist() const
{

}

bool RecordListModel::running() const
{
    return false;
}

