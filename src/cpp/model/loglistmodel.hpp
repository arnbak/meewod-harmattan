#ifndef WORKOUTLOGLISTMODEL_HPP
#define WORKOUTLOGLISTMODEL_HPP

#include <QDebug>
#include <QAbstractListModel>
#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "../cpp/content/loglistitem.hpp"
#include "../cpp/core/servicehandler.hpp"


class LogListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:

    enum WorkoutLogListRoles {
        WorkoutLogListIdRole,
        WorkoutLogListNameRole,
        WorkoutLogListDateRole,
        WorkoutLogListDescriptionRole,
        WorkoutLogListHandlestampRole
    };

    LogListModel(const QSqlDatabase& db, QObject *parent = 0);
    ~LogListModel();

public:
    Q_INVOKABLE void addLogItem(const QString& name, const QString& date, const QString& description);
    Q_INVOKABLE void updateLogItem(const int& index, const QString& name, const QString& date, const QString& description);
    Q_INVOKABLE void deleteLogItem(const int& index);

    Q_INVOKABLE void persist();


    Q_INVOKABLE QVariantMap getLogItem(const int& index) const;

    Q_INVOKABLE void requestList();
    Q_INVOKABLE void syncListWithRemote();

    Q_INVOKABLE QVariantMap get(const int &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void appendRow(LogListItem *item);
    void appendRows(const QList<LogListItem *> &items);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

public slots:
    void listBackedUp(const int&);
    void listBackupError(const int&);

private:
    void loadItems();
    //void saveLogListItemToDB(LogListItem* item);
    //void updateLogListItemToDB(LogListItem* item);
    void persistItem(LogListItem* item);
    void deleteFromDB();

signals:
    void countChanged();
    void listItemsBackedUp();
    void listItemsBackUpError();

private:
    QList<LogListItem *> _logList;
    QSqlDatabase _db;
    ServiceHandler * _serviceHandler;
    bool _running;
};

#endif // WORKOUTLOGLISTMODEL_HPP
