#include "../cpp/model/dailylistmodel.hpp"


DailyListModel::DailyListModel(const QSqlDatabase &db, QObject *parent)
    : QAbstractListModel(parent)
    , _serviceHandler(new ServiceHandler)    
{
    _db = db;

    QHash<int, QByteArray> roles;
    roles[DailyTitleRole] = "title";
    roles[DailyDescriptionRole] = "description";
    roles[DailyUriRole] = "uri";
    roles[DailyDateRole] = "date";
    roles[DailyDateTimeRole] = "published";
    setRoleNames(roles);

    connect(_serviceHandler, SIGNAL(dailyListFetched(QList<DailyListItem*>)), this, SLOT(dailyListFetched(QList<DailyListItem*>)));
    connect(_serviceHandler, SIGNAL(handlerError(int)), this, SLOT(error(int)));

    loadList();
}

DailyListModel::~DailyListModel()
{
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("QSQLITE");

    delete _serviceHandler;
}

void DailyListModel::clear()
{
    beginResetModel();
    _dailyList.clear();
    endResetModel();

    emit countChanged();
}

void DailyListModel::persist()
{
    deleteList();

    QSqlDatabase::database().transaction();
    QSqlQuery saveQuery(_db);

    saveQuery.prepare("INSERT INTO dailywods (id, title, text, uri) "
                      "VALUES (?,?,?,?)");

    QVariantList idlist;
    QVariantList titlelist;
    QVariantList textlist;
    QVariantList urilist;


    Q_FOREACH (DailyListItem *item, _dailyList) {
        idlist.append(item->getPublished());
        titlelist.append(item->getTitle());
        textlist.append(item->getDescription());
        urilist.append(item->getUri());
    }

    saveQuery.addBindValue(idlist);
    saveQuery.addBindValue(titlelist);
    saveQuery.addBindValue(textlist);
    saveQuery.addBindValue(urilist);

    if(!saveQuery.execBatch()) {
        qDebug() << "error " << _db.lastError();
    }

    QSqlDatabase::database().commit();
}

void DailyListModel::loadList()
{
    clear();
    QSqlQuery selQuery("SELECT a.id, a.title, a.text, a.uri "
                       "FROM dailywods a "
                       "ORDER by a.id DESC");

    if(selQuery.exec())
    {

        while (selQuery.next())
        {
            DailyListItem *item = new DailyListItem(selQuery.value(1).toString(),
                                                    QDateTime::fromMSecsSinceEpoch(selQuery.value(0).toLongLong()),
                                                    selQuery.value(2).toString(),
                                                    selQuery.value(3).toString());

            _dailyList.append(item);
        }

    }

    //qDebug() << "loaded " << _dailyList.count() << " from db ";

}

void DailyListModel::deleteList()
{
    QSqlQuery delQuery("DELETE FROM dailywods");

    if(!delQuery.exec())
    {
        qDebug() << "could not delete daily workouts";
    }
}

QModelIndex DailyListModel::indexFromItem(DailyListItem *item) const
{
    Q_ASSERT(item);
    for(int row=0; row<_dailyList.size(); ++row) {
        if(_dailyList.at(row) == item) return index(row);
    }
    return QModelIndex();
}

int DailyListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _dailyList.count();
}

QVariant DailyListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > _dailyList.count())
    {
        return QVariant();
    }

    if(role == DailyTitleRole)
    {
        return _dailyList[index.row()]->getTitle();
    }
    if (role == DailyDescriptionRole)
    {
        return _dailyList[index.row()]->getDescription();
    }
    else if(role == DailyUriRole)
    {
        return _dailyList[index.row()]->getUri();
    }
    else if(role == DailyDateRole)
    {
        return _dailyList[index.row()]->getDate();
    }
    else if(role == DailyDateTimeRole)
    {
        return QString("test time");

    }
    else
    {
        return QVariant();
    }
}

void DailyListModel::error(const int &error)
{
    QString msg;
    msg = "Request to service failed with error code: " + QString::number(error);
    emit listError(msg);
}

void DailyListModel::dailyListFetched(QList<DailyListItem *> list)
{
    clear();
    //qDebug() << "dailyListFetched of size " << list.size();
    appendRows(list);
    _running = false;
    persist();
    emit listFetched();
}

void DailyListModel::appendRow(DailyListItem *item)
{
    appendRows(QList<DailyListItem*>() << item);
}

void DailyListModel::appendRows(const QList<DailyListItem *> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
    foreach(DailyListItem *item, items)
    {
        _dailyList.append(item);
    }
    endInsertRows();

    emit countChanged();
}

bool DailyListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || row >= _dailyList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row);
    delete _dailyList.takeAt(row);
    endRemoveRows();
    return true;
}

bool DailyListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || (row+count) >= _dailyList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row+count-1);

    for(int i=0; i<count; ++i) {
        delete _dailyList.takeAt(row);
    }

    endRemoveRows();

    return true;
}

bool DailyListModel::running()
{
    return _running;
}

void DailyListModel::requestList() {
    _serviceHandler->requestDailyList();
}

QVariantMap DailyListModel::get(const int &index) const
{
    QVariantMap mapItem;

    if(index < 0 || index >  _dailyList.count())
    {
        return mapItem;
    }

    DailyListItem* listItem = _dailyList.at(index);

    mapItem.insert("published", listItem->getDate());

    return mapItem;
}
