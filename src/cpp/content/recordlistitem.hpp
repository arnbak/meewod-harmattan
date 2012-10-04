#ifndef RECORDLISTITEM_HPP
#define RECORDLISTITEM_HPP

#include <QUuid>
#include <QDate>

class RecordListItem
{
public:
    RecordListItem();
    RecordListItem(const QString& name, const QString& completion, const QDate& date, const QString& description, const QString& category );
    ~RecordListItem();

    QString getUid() const;

    void setModelId(const int& id);
    int getModelId() const;

    void setName(const QString& name);
    QString getName() const;

    void setCompletionTime(const QString& completion);
    QString getCompletionTime() const;

    QDate getDate() const;
    void setDate(const QDate& date);
    QString getStringDate() const;
    QString getFastScrollDate() const;

    QString getDescription() const;
    void setDescription(const QString& description);

    QString getCategory() const;
    void setCategory(const QString& category);


private:
    QUuid _uid;
    int _modelid;
    QString _name;
    QString _completiontime;
    QDate _date;
    QString _description;
    QString _category;
};

#endif // RECORDLISTITEM_HPP
