#ifndef RECORDLISTMODEL_HPP
#define RECORDLISTMODEL_HPP

#include <QAbstractListModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "../src/content/recordlistitem.hpp"

class RecordListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    RecordListModel(const QSqlDatabase& db, QObject *parent = 0);
    ~RecordListModel();

    Q_INVOKABLE void clear() const;
    Q_INVOKABLE void persist() const;
    Q_INVOKABLE bool running() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void appendRow(RecordListItem *item);
    void appendRows(const QList<RecordListItem *> &items);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

signals:
    void countChanged();
private:
    QList<RecordListItem *> _recordList;
    QSqlDatabase _db;
};

#endif // RECORDLISTMODEL_HPP
