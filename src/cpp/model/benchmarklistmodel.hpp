#ifndef BENCHMARKLISTMODEL_HPP
#define BENCHMARKLISTMODEL_HPP

#include <QtCore/QDebug>
#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QAbstractListModel>
#include <QStringList>
#include "../cpp/content/benchmarklistitem.hpp"
#include "../cpp/core/servicehandler.hpp"

class BenchmarkListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:

    enum WodListRoles {
        WodIdRole,
        WodTypeRole,
        WodNameRole,
        WodDescriptionRole,
        WodTextRole
    };

    BenchmarkListModel(const QSqlDatabase& db, QObject *parent = 0);
    ~BenchmarkListModel();

public:

    Q_INVOKABLE void clear();
    Q_INVOKABLE void persist();
    Q_INVOKABLE bool running();
    Q_INVOKABLE void requestList();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariantMap get(const int &index) const;

    QModelIndex indexFromItem(BenchmarkListItem* item) const;

    void appendRow(BenchmarkListItem *item);
    void appendRows(const QList<BenchmarkListItem *> &items);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

public slots:
    void benchmarkListFetched(const QList<BenchmarkListItem*>& list);
    void error(const int& error);

private:
    void loadList();
    void deleteList();

signals:
    void countChanged();
    void benchmarkListUpdated();
    void benchmarkListError(const QString &message);

private:
    QList<BenchmarkListItem *> _benchmarkList;
    ServiceHandler * _serviceHandler;
    QSqlDatabase _db;
    bool _running;
};

#endif // BENCHMARKLISTMODEL_HPP
