#ifndef BENCHMARKLISTITEM_HPP
#define BENCHMARKLISTITEM_HPP

#include <QObject>

class BenchmarkListItem : QObject
{        

public:    
    BenchmarkListItem();
    BenchmarkListItem(const int& id,const QString& type, const QString& name, const QString& description, const QString& text);
    ~BenchmarkListItem();

    int getId() const;
    void setId(const int &);

    QString getType() const;
    void setType(const QString &);

    QString getName() const;
    void setName(const QString &);

    QString getDescription() const;
    void setDescription(const QString &);

    QString getWorkoutText() const;
    void setWorkoutText(const QString &);
signals:
    void dataChanged();
private:
    int _id;
    QString _type;
    QString _name;
    QString _description;
    QString _workouttext;
};

#endif // BENCHMARKLISTITEM_HPP
