#ifndef SORTMODEL_HPP
#define SORTMODEL_HPP

#include <QSortFilterProxyModel>

#include "../cpp/model/benchmarklistmodel.hpp"

class SortModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:

    SortModel(QObject * parent = 0);
    ~SortModel();

public:

    Q_INVOKABLE void clear();
    Q_INVOKABLE void persist();
    Q_INVOKABLE void requestList();

    void setSourceModel(QAbstractItemModel *sourceModel);

    Q_INVOKABLE QVariantMap get(int rowIndex) const;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

signals:
    void countChanged();
    void benchmarkListUpdated();
    void benchmarkListError(const QString &message);

private Q_SLOTS:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    BenchmarkListModel * _model;

};

#endif // SORTMODEL_HPP
