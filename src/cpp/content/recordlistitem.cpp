#include "../cpp/content/recordlistitem.hpp"

RecordListItem::RecordListItem()
{

}

RecordListItem::RecordListItem(const QString &name, const QString &completion, const QDate &date, const QString &description, const QString &category)
    : _uid(QUuid::createUuid()),
      _name(name),
      _completiontime(completion),
      _date(date),
      _description(description),
      _category(category)
{

}

RecordListItem::~RecordListItem()
{

}

QString RecordListItem::getUid() const
{
    return _uid.toString();
}

void RecordListItem::setModelId(const int& id)
{
    _modelid = id;
}


int RecordListItem::getModelId() const
{
    return _modelid;
}

QString RecordListItem::getName() const
{
    return _name;
}

void RecordListItem::setName(const QString &name)
{
    _name = name;
}

void RecordListItem::setCompletionTime(const QString& completion)
{
    _completiontime = completion;
}

QString RecordListItem::getCompletionTime() const
{
    return _completiontime;
}

QDate RecordListItem::getDate() const
{
    return _date;
}

QString RecordListItem::getStringDate() const {
    return _date.toString("dd-MM-yyyy");
}

QString RecordListItem::getFastScrollDate() const {
    return _date.toString("dd-MM-yyyy");
}

void RecordListItem::setDate(const QDate& date)
{
    _date = date;
}

QString RecordListItem::getDescription() const
{
    return _description;
}

void RecordListItem::setDescription(const QString& description)
{
    _description = description;
}

QString RecordListItem::getCategory() const
{
    return _category;
}

void RecordListItem::setCategory(const QString& category)
{
    _category = category;
}


