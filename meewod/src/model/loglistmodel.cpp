#include "../src/model/loglistmodel.hpp"
#include "../src/core/servicehandler.hpp"

LogListModel::LogListModel(const QSqlDatabase& db, QObject *parent)
    : QAbstractListModel(parent)
    , _serviceHandler(new ServiceHandler)
{
    _db = db;

    QHash<int, QByteArray> roles;
    roles[WorkoutLogListIdRole] = "logid";
    roles[WorkoutLogListNameRole] = "logname";
    roles[WorkoutLogListDateRole] = "logdate";
    roles[WorkoutLogListDescriptionRole] = "logdesc";
    roles[WorkoutLogListHandlestampRole] = "loghandlestamp";
    setRoleNames(roles);

    loadLogListFromDB();

    connect(_serviceHandler, SIGNAL(putListItemsRequestFineshed(int)), this, SLOT(listBackedUp(int)));
    connect(_serviceHandler, SIGNAL(handlerError(int)), this, SLOT(listBackupError(int)));
}

LogListModel::~LogListModel()
{
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("QSQLITE");

    delete _serviceHandler;
}

void LogListModel::addLogItem(const QString& name, const QString &date, const QString &description)
{
    int id = -1;

    LogListItem * item = new LogListItem(id, name, QDate::fromString(date, "dd-MM-yyyy"), description, QString::number(QDateTime::currentMSecsSinceEpoch()));

    beginInsertRows(QModelIndex(), 0, 0);

    _logList.prepend(item);

    endInsertRows();

    emit countChanged();

   //appendRow(item);

    //saveLogListItemToDB(item);
}

void LogListModel::updateLogItem(const int& index, const QString &name, const QString &date, const QString &description)
{

    LogListItem * item = new LogListItem(index, name, QDate::fromString(date, "dd-MM-yyyy"), description, QString::number(QDateTime::currentMSecsSinceEpoch()));

    //qDebug() << "index " << index << " " << item->getId() << " " << item->getName() << " " << item->getDate().toString() << " " << item->getDescription();

    _logList.replace(index, item);

    QModelIndex idx = createIndex(index,0);

    emit dataChanged(idx, idx);

    //updateLogListItemToDB(item);
}

void LogListModel::deleteLogItem(const int &index)
{
    removeRow(index);
}

void LogListModel::appendRow(LogListItem *item)
{
    appendRows(QList<LogListItem*>() << item);
}

void LogListModel::appendRows(const QList<LogListItem *> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);

    foreach(LogListItem *item, items) {
        _logList.append(item);
    }

    endInsertRows();

    emit countChanged();
}

bool LogListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    if(row < 0 || row >= _logList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row);

    delete _logList.takeAt(row);

    endRemoveRows();

    return true;
}

bool LogListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    if(row < 0 || (row+count) >= _logList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row+count-1);

    for(int i=0; i<count; ++i) {
        delete _logList.takeAt(row);
    }

    endRemoveRows();

    return true;
}




//void LogListModel::syncListItems()
//{
//    ServiceHandler remoteService;
//    remoteService.requestPutLogList(_logList);

//    qDebug() << "sync list items ";
//}

QVariantMap LogListModel::getLogItem(const int& index) const
{
    QVariantMap entry;

    if(index >= _logList.count()) {
        return entry;
    }

    LogListItem * item = _logList.at(index);  

    entry.insert("logid", index);
    entry.insert("logname", item->getName());
    entry.insert("logdate", item->getStringDate());
    entry.insert("logdesc", item->getDescription());
    entry.insert("loghandlestamp", item->getHandleStamp());

    return entry;
}


int LogListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _logList.count();
}

QVariant LogListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > _logList.count())
    {
        return QVariant();
    }

    if(role == WorkoutLogListIdRole)
    {
        return _logList[index.row()]->getId();
    }
    else if (role == WorkoutLogListNameRole)
    {
        return _logList[index.row()]->getName();
    }
    else if (role == WorkoutLogListDateRole)
    {
        return _logList[index.row()]->getStringDate();
    }
    else if(role == WorkoutLogListDescriptionRole)
    {
        return _logList[index.row()]->getDescription();
    }
    else if(role == WorkoutLogListHandlestampRole)
    {
        return _logList[index.row()]->getHandleStamp();
    }
    else
    {
        return QVariant();
    }
}

void LogListModel::loadLogListFromDB()
{    
    _logList.clear();

    QSqlQuery selQuery("SELECT a.id, a.name, a.date, a.description, a.handlestamp "
                       "FROM workoutlog a "
                       "ORDER BY a.date desc");

    if(selQuery.exec())
    {

        while (selQuery.next())
        {
            LogListItem * item = new LogListItem(selQuery.value(0).toInt(),
                                                 selQuery.value(1).toString(),
                                                 selQuery.value(2).toDate(),
                                                 selQuery.value(3).toString());

            item->setHandleStamp(selQuery.value(4).toString());

            appendRow(item);

        }
    }


}

void LogListModel::updateLogListItemToDB(LogListItem *item)
{    
    QSqlQuery updateQuery;

    updateQuery.prepare("UPDATE workoutlog "
                        "SET name=:name, date=:date, description=:description, handlestamp=:handlestamp "
                        "WHERE id=:id");

    updateQuery.bindValue(":id", item->getId());

    updateQuery.bindValue(":name", item->getName());
    updateQuery.bindValue(":date", item->getDate());

    updateQuery.bindValue(":description", item->getDescription());
    updateQuery.bindValue(":handlestamp", QDateTime::currentDateTime().toMSecsSinceEpoch());


    if(!updateQuery.exec())
    {
        qDebug() << "error " << _db.lastError();
    }
}

void LogListModel::deleteFromDB() {

    QSqlQuery delQuery("DELETE FROM workoutlog");

    if(!delQuery.exec())
    {
        qDebug() << "could not delete log workouts";
    }
}

void LogListModel::persist()
{
    deleteFromDB();

    QSqlDatabase::database().transaction();

    QSqlQuery saveQuery(_db);

    saveQuery.prepare("INSERT INTO workoutlog "
                      " (id, name, date, description, handlestamp) "
                      " VALUES (?,?,?,?,?)");

    QVariantList ids;
    QVariantList names;
    QVariantList dates;
    QVariantList descriptions;
    QVariantList handlestamps;

    Q_FOREACH (LogListItem *item, _logList) {
        ids.append(_logList.indexOf(item));
        names.append(item->getName());
        dates.append(item->getDate());
        descriptions.append(item->getDescription());
        handlestamps.append(QDateTime::currentDateTime().toMSecsSinceEpoch());
    }

    saveQuery.addBindValue(ids);
    saveQuery.addBindValue(names);
    saveQuery.addBindValue(dates);
    saveQuery.addBindValue(descriptions);
    saveQuery.addBindValue(handlestamps);

    //qDebug() << "handle stamp " << QDateTime::currentDateTime().toMSecsSinceEpoch();

    if(!saveQuery.execBatch()) {
        qDebug() << "could not persisted " << _logList.size() << " logged workouts to db";
    }

    QSqlDatabase::database().commit();
}

void LogListModel::listBackedUp(const int & )
{
    //qDebug() << "hello";
    emit listItemsBackedUp();
}

void LogListModel::listBackupError(const int &)
{
    //qDebug() << "error";
    emit listItemsBackUpError();
}

void LogListModel::requestList()
{

}

void LogListModel::syncListWithRemote()
{
    _serviceHandler->requestPutLogList(_logList);

}

QVariantMap LogListModel::get(const int &index) const
{
    QVariantMap mapItem;

    if(index < 0 || index >  _logList.count())
    {
        return mapItem;
    }

    LogListItem* listItem = _logList.at(index);

    mapItem.insert("date", listItem->getStringDate());

    return mapItem;
}
