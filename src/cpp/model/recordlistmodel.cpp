#include "../cpp/model/recordlistmodel.hpp"

RecordListModel::RecordListModel(const QSqlDatabase &db, QObject *parent)
    : QAbstractListModel(parent)
{
    _db = db;

    QHash<int, QByteArray> roles;
    roles[RecordUidRole] = "uid";
    roles[RecordIdRole] = "modelid";
    roles[RecordNameRole] = "name";
    roles[RecordCompletionTimeRole] = "time";
    roles[RecordDateRole] = "date";
    roles[RecordDescriptionRole] = "description";
    roles[RecordCategoryRole] = "category";
    setRoleNames(roles);


}

RecordListModel::~RecordListModel()
{
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("QSQLITE");
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

void RecordListModel::addItem(const QString &name, const QString &completiontime, const QString &date, const QString &description,  const QString &category)
{
    RecordListItem * item = new RecordListItem(name, completiontime, QDate::fromString(date, "dd-MM-yyyy"), description, category);

    beginInsertRows(QModelIndex(), 0, 0);
    _recordList.prepend(item);
    endInsertRows();

    emit countChanged();

    qDebug() << "add item named " + item->getName();
}

QVariantMap RecordListModel::getItem(const int &index) const
{
    QVariantMap entry;

    if(index >= _recordList.count()) {
        return entry;
    }

    RecordListItem * item = _recordList.at(index);

    entry.insert("modelid", index);
    entry.insert("uid", item->getUid());
    entry.insert("name", item->getName());
    entry.insert("time", item->getCompletionTime());
    entry.insert("date", item->getStringDate());
    entry.insert("description", item->getDescription());
    entry.insert("category", item->getCategory());
    return entry;
}

void RecordListModel::updateItem(const int &index, const QString &name, const QString &completiontime, const QString &date, const QString &description, const QString &category)
{
    RecordListItem * item = _recordList.at(index);

    item->setName(name);
    item->setCompletionTime(completiontime);
    item->setDate(QDate::fromString(date, "dd-MM-yyyy"));
    item->setDescription(description);
    item->setCategory(category);

    _recordList.replace(index, item);

    QModelIndex idx = createIndex(index, 0);

    emit dataChanged(idx, idx);
}

void RecordListModel::removeItem(const int &index)
{
    removeRow(index);
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

    if(role == RecordUidRole)
    {
        return _recordList[index.row()]->getUid();
    }
    else if (role == RecordIdRole)
    {
        return _recordList[index.row()]->getModelId();
    }
    else if (role == RecordNameRole)
    {
        qDebug() << "record name " << _recordList[index.row()]->getName() << " for index " << index.row();
        return _recordList[index.row()]->getName();
    }
    else if(role == RecordCompletionTimeRole)
    {
        return _recordList[index.row()]->getCompletionTime();
    }
    else if(role == RecordDateRole)
    {
        return _recordList[index.row()]->getStringDate();
    }
    else if(role == RecordDescriptionRole)
    {
        return _recordList[index.row()]->getDescription();
    }
    else if(role == RecordCategoryRole)
    {
        return _recordList[index.row()]->getCategory();
    }
    else
    {
        return QVariant();
    }
}

QVariantMap RecordListModel::get(const int &index) const
{
    QVariantMap mapItem;

    if(index < 0 || index >  _recordList.count())
    {
        return mapItem;
    }

    RecordListItem* listItem = _recordList.at(index);

    mapItem.insert("date", listItem->getStringDate());

    return mapItem;
}

