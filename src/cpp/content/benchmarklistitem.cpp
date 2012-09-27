#include "../cpp/content/benchmarklistitem.hpp"

BenchmarkListItem::BenchmarkListItem() { }

BenchmarkListItem::BenchmarkListItem(const int &id, const QString &type, const QString &name, const QString &description, const QString &text)
    : _id(id),
      _type(type),
      _name(name),
      _description(description),
      _workouttext(text)
{

}

BenchmarkListItem::~BenchmarkListItem()
{

}

int BenchmarkListItem::getId() const
{
    return _id;
}

void BenchmarkListItem::setId(const int &id)
{
    _id = id;
}

QString BenchmarkListItem::getType() const
{
    return _type;
}

void BenchmarkListItem::setType(const QString &type)
{
    _type = type;
}

QString BenchmarkListItem::getName() const
{    
    return _name;
}

void BenchmarkListItem::setName(const QString &name)
{
    _name = name;
}

QString BenchmarkListItem::getDescription() const
{
    return _description;
}

void BenchmarkListItem::setDescription(const QString &description)
{
    _description = description;
}

QString BenchmarkListItem::getWorkoutText() const
{
    return _workouttext;
}

void BenchmarkListItem::setWorkoutText(const QString &workouttext)
{
    _workouttext = workouttext;
}

