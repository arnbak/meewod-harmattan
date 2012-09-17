#include "../src/model/sortmodel.hpp"

SortModel::SortModel(QObject *parent) :
    QSortFilterProxyModel(parent),
    _model(0)
{

    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

SortModel::~SortModel()
{
}

void SortModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);

    _model = qobject_cast<BenchmarkListModel *>(sourceModel);

    connect(_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)), Qt::UniqueConnection);
}

bool SortModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent)

    const QModelIndex index = sourceModel()->index(source_row, 0);

    const QString name = _model->data(index, BenchmarkListModel::WodNameRole).toString();
    const QString type = _model->data(index, BenchmarkListModel::WodTypeRole).toString();

    return (name.contains(filterRegExp()) || type.contains(filterRegExp()));
}


void SortModel::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    emit dataChanged(mapFromSource(topLeft), mapFromSource(bottomRight));
}

QVariantMap SortModel::get(int rowIndex) const
{
    const QModelIndex index = _model->index(rowIndex, 0);

    return _model->get(index.row());
}

void SortModel::persist()
{
    _model->persist();
}

void SortModel::requestList()
{
    _model->requestList();
}

void SortModel::clear()
{
    _model->clear();
}

