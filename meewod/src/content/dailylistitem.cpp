#include "../src/content/dailylistitem.hpp"

DailyListItem::DailyListItem() { }
DailyListItem::DailyListItem(const QString &title, const QDateTime &published, const QString &text, const QString &uri)
    : _title(title),
      _published(published),
      _text(text),
      _uri(uri)
{

}

DailyListItem::~DailyListItem() { }

void DailyListItem::setTitle(const QString &title)
{
    _title = title;
}

QString DailyListItem::getTitle() const
{
    return _title;
}

QString DailyListItem::getDate() const
{
    QString s;
    s = _published.toLocalTime().toString("dd-MM-yyyy");
    return s;
}

QDate DailyListItem::getQDate() const
{
    return _published.date();
}

void DailyListItem::setPublished(const QDateTime &time)
{
    _published = time;
}

qint64 DailyListItem::getPublished() const
{
    return _published.toMSecsSinceEpoch();
}

QString DailyListItem::getDescription() const
{
    return _text;
}

void DailyListItem::setDescription(const QString &text)
{
    _text = text;
}

QString DailyListItem::getUri() const
{
    return _uri;
}

void DailyListItem::setUri(const QString &uri)
{
    _uri = uri;
}
