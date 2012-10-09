#ifndef RECORDLISTMODEL_HPP
#define RECORDLISTMODEL_HPP

#include <QAbstractListModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

#include "../cpp/content/recordlistitem.hpp"


class RecordListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:    
    RecordListModel(const QSqlDatabase& db, QObject *parent = 0);
    ~RecordListModel();

    enum RecordListRoles {
        RecordUidRole,
        RecordIdRole,
        RecordNameRole,
        RecordCompletionTimeRole,
        RecordDateRole,
        RecordDescriptionRole,
        RecordCategoryRole
    };

public:
    Q_INVOKABLE void clear() const;
    Q_INVOKABLE void persist() const;
    Q_INVOKABLE bool running() const;

    Q_INVOKABLE void addItem(const QString& name, const QString& completiontime, const QString& date, const QString& description, const QString& category);
    Q_INVOKABLE QVariantMap getItem(const int& index) const;
    Q_INVOKABLE void updateItem(const int& index, const QString& name, const QString& completiontime, const QString& date, const QString& description, const QString& category);
    Q_INVOKABLE void removeItem(const int& index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE QVariantMap get(const int &index) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;


    void appendRow(RecordListItem *item);
    void appendRows(const QList<RecordListItem *> &items);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());


private:
    void persistItem(RecordListItem * item);
    void loadItems();

signals:
    void countChanged();
private:
    QList<RecordListItem *> _recordList;
    QSqlDatabase _db;
};

#endif // RECORDLISTMODEL_HPP
