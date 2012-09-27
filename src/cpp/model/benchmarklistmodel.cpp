#include "../cpp/model/benchmarklistmodel.hpp"

BenchmarkListModel::BenchmarkListModel(const QSqlDatabase& db, QObject *parent)
    : QAbstractListModel(parent),
      _serviceHandler(new ServiceHandler)

{
    _db = db;

    QHash<int, QByteArray> roles;
    roles[WodIdRole] = "id";
    roles[WodTypeRole] = "type";
    roles[WodNameRole] = "name";
    roles[WodDescriptionRole] = "description";
    roles[WodTextRole] = "wodtext";
    setRoleNames(roles);    

    loadList();

    connect(_serviceHandler, SIGNAL(benchmarkListFetched(QList<BenchmarkListItem*>)), this, SLOT(benchmarkListFetched(QList<BenchmarkListItem*>)));
    connect(_serviceHandler, SIGNAL(handlerError(int)), this, SLOT(error(int)));
}

BenchmarkListModel::~BenchmarkListModel()
{
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase("QSQLITE");

    delete _serviceHandler;
}

void BenchmarkListModel::clear()
{   
    beginResetModel();
    _benchmarkList.clear();
    endResetModel();

    emit countChanged();
}

void BenchmarkListModel::persist() {

    deleteList();

    QSqlDatabase::database().transaction();
    QSqlQuery saveQuery(_db);

    saveQuery.prepare("INSERT INTO benchwods (id, type, name, description, workouttext) "
                      "VALUES (?,?,?,?,?)");

    QVariantList itemIds;
    QVariantList itemTypes;
    QVariantList itemNames;
    QVariantList itemDescriptions;
    QVariantList itemTexts;

    Q_FOREACH (BenchmarkListItem *item, _benchmarkList) {
        itemIds.append(item->getId());
        itemTypes.append(item->getType());
        itemNames.append(item->getName());
        itemDescriptions.append(item->getDescription());
        itemTexts.append(item->getWorkoutText());
    }

    saveQuery.addBindValue(itemIds);
    saveQuery.addBindValue(itemTypes);
    saveQuery.addBindValue(itemNames);
    saveQuery.addBindValue(itemDescriptions);
    saveQuery.addBindValue(itemTexts);

    if(!saveQuery.execBatch()) {
        qDebug() << "error saving " << _benchmarkList.size() << " workouts to db";
    }

    QSqlDatabase::database().commit();
}



QModelIndex BenchmarkListModel::indexFromItem(BenchmarkListItem *item) const
{
    Q_ASSERT(item);
    for(int row=0; row<_benchmarkList.size(); ++row) {
        if(_benchmarkList.at(row) == item) return index(row);
    }
    return QModelIndex();
}

int BenchmarkListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _benchmarkList.count();
}

QVariant BenchmarkListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > _benchmarkList.count())
    {
        return QVariant();
    }

    if(role == WodIdRole)
    {
        return _benchmarkList[index.row()]->getId();
    }
    if (role == WodTypeRole)
    {
        return _benchmarkList[index.row()]->getType();
    }
    else if(role == WodNameRole)
    {
        return _benchmarkList[index.row()]->getName();
    }
    else if(role == WodDescriptionRole)
    {
        return _benchmarkList[index.row()]->getDescription();
    }
    else if(role == WodTextRole)
    {
        return _benchmarkList[index.row()]->getWorkoutText();
    }
    else
    {
        return QVariant();
    }
}

QVariantMap BenchmarkListModel::get(const int &index) const
{
    QVariantMap mapItem;

    if(index < 0 || index >  _benchmarkList.count())
    {
        return mapItem;
    }

    BenchmarkListItem* listItem = _benchmarkList.at(index);

    mapItem.insert("name", listItem->getName());

    return mapItem;
}

void BenchmarkListModel::loadList()
{

    clear();

    QSqlQuery selQuery("SELECT a.id, a.type, a.name, a.description, a.workouttext "
                       "FROM benchwods a "
                       "ORDER by a.id");

    if(selQuery.exec())
    {

        while (selQuery.next())
        {
            BenchmarkListItem *item = new BenchmarkListItem(selQuery.value(0).toInt(),
                                                                  selQuery.value(1).toString(),
                                                                  selQuery.value(2).toString(),
                                                                  selQuery.value(3).toString(),
                                                                  selQuery.value(4).toString());

            _benchmarkList.append(item);
        }

    }

    //qDebug() << "loaded " << _benchmarkList.count() << " benchmark workouts";
}

void BenchmarkListModel::benchmarkListFetched(const QList<BenchmarkListItem *>& list)
{
    clear();

    appendRows(list);

    //qDebug() << "fetched list of size " << list.size();

    _running = false;

    persist();

    emit benchmarkListUpdated();
}

void BenchmarkListModel::error(const int &error) {

    QString msg;
    msg = "Request to service failed with error code: " + QString::number(error);

    emit benchmarkListError(msg);
}

void BenchmarkListModel::deleteList()
{
    QSqlQuery delQuery("DELETE FROM benchwods");

    if(!delQuery.exec())
    {
        qDebug() << "could not delete benchmark workouts";
    }
}

void BenchmarkListModel::appendRow(BenchmarkListItem *item)
{
    appendRows(QList<BenchmarkListItem*>() << item);
}

void BenchmarkListModel::appendRows(const QList<BenchmarkListItem *> &items)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
    foreach(BenchmarkListItem *item, items) {
        _benchmarkList.append(item);
    }
    endInsertRows();

    emit countChanged();
}

bool BenchmarkListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || row >= _benchmarkList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row);
    delete _benchmarkList.takeAt(row);
    endRemoveRows();
    return true;
}

bool BenchmarkListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || (row+count) >= _benchmarkList.size())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row+count-1);

    for(int i=0; i<count; ++i) {
        delete _benchmarkList.takeAt(row);
    }

    endRemoveRows();

    return true;
}

bool BenchmarkListModel::running()
{
    return _running;
}

void BenchmarkListModel::requestList()
{
    _serviceHandler->requestBenchmarkList();
}


