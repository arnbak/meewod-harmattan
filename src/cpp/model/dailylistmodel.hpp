#ifndef DAILYLISTMODEL_HPP
#define DAILYLISTMODEL_HPP

#include <QDebug>
#include <QAbstractListModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "../cpp/content/dailylistitem.hpp"
#include "../cpp/core/servicehandler.hpp"

class DailyListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum DailyListRoles {
        DailyTitleRole,
        DailyDescriptionRole,
        DailyDateTimeRole,
        DailyDateRole,
        DailyUriRole
    };

    DailyListModel(const QSqlDatabase& db, QObject *parent = 0);
    ~DailyListModel();

    Q_INVOKABLE void clear();
    Q_INVOKABLE void persist();
    Q_INVOKABLE bool running();
    Q_INVOKABLE void requestList();

    Q_INVOKABLE QVariantMap get(const int &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QModelIndex indexFromItem(DailyListItem* item) const;

    void appendRow(DailyListItem *item);
    void appendRows(const QList<DailyListItem *> &items);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    void loadList();
    void deleteList();


public slots:
    void dailyListFetched(QList<DailyListItem*> list);
    void error(const int& error);

signals:
    void countChanged();
    void listFetched();
    void listError(const QString& message);

private:
    QList<DailyListItem *> _dailyList;
    ServiceHandler * _serviceHandler;
    QSqlDatabase _db;
    bool _running;

};

#endif // DAILYLISTMODEL_HPP
