#ifndef DAILYLISTITEM_HPP
#define DAILYLISTITEM_HPP

#include <QObject>
#include <QDateTime>

class DailyListItem
{
public:
    DailyListItem();
    DailyListItem(const QString& title, const QDateTime& published, const QString& text, const QString& uri);
    ~DailyListItem();

    QString getTitle() const;
    void setTitle(const QString& title);

    QString getDate() const;

    QDate getQDate() const;

    void setPublished(const QDateTime& time);
    qint64 getPublished() const;

    QString getDescription() const;
    void setDescription(const QString& text);

    QString getUri() const;
    void setUri(const QString& uri);

private:
    QString _title;
    QDateTime _published;
    QString _text;
    QString _uri;
};

#endif // DAILYLISTITEM_HPP
