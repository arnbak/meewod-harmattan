#ifndef LOGLISTITEM_HPP
#define LOGLISTITEM_HPP

#include <QObject>
#include <QDateTime>
#include <QDate>

class LogListItem
{

public:    
    LogListItem(const int &id, const QString& name, const QDate& date, const QString& desc);
    LogListItem(const int &id, const QString& name, const QDate& date, const QString& desc, const QString& handlestamp);
    ~LogListItem();

    int getId() const;
    void setId(const int& id);

    QString getName() const;
    void setName(const QString& name);

    QDate getDate() const;
    QString getStringDate() const;
    QString getFastScrollDate() const;
    void setDate(const QDate& date);

    QString getDescription() const;
    void setDescription(const QString& description);

    //QDateTime getHandleStamp() const;
    QString getHandleStamp() const;
    void setHandleStamp(const QString& handlestamp);

private:
    int _id;
    QString _name;
    QDate _date;
    QString _description;
    QString _handlestamp;
};

#endif // WORKOUTLOGLISTITEM_HPP
