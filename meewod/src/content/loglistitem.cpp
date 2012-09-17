#include "../src/content/loglistitem.hpp"

LogListItem::LogListItem(const int &id, const QString& name, const QDate &date, const QString &desc)
    : _id(id),
      _name(name),
      _date(date),
      _description(desc)
{

}

LogListItem::LogListItem(const int &id, const QString& name, const QDate &date, const QString &desc, const QString& handlestamp)
    : _id(id),
      _name(name),
      _date(date),
      _description(desc),
      _handlestamp(handlestamp)
{

}

LogListItem::~LogListItem() { }

int LogListItem::getId() const
{
    return _id;
}

void LogListItem::setId(const int &id)
{
    _id = id;
}

QString LogListItem::getName() const
{
    return _name;
}

void LogListItem::setName(const QString &name)
{
    _name = name;
}

QDate LogListItem::getDate() const
{   
    return _date;
}

QString LogListItem::getStringDate() const {
    return _date.toString("dd-MM-yyyy");
}

QString LogListItem::getFastScrollDate() const {
    return _date.toString("dd-MM-yyyy");
}

void LogListItem::setDate(const QDate &date)
{
    _date = date;
}

QString LogListItem::getDescription() const
{
    return _description;
}

void LogListItem::setDescription(const QString &description)
{
    _description = description;
}

//QDateTime LogListItem::getHandleStamp()const
//{
//    return QDateTime::currentDateTime();
//}

QString LogListItem::getHandleStamp() const {
    return _handlestamp;
}

void LogListItem::setHandleStamp(const QString &handlestamp)
{
    _handlestamp = handlestamp;
}
