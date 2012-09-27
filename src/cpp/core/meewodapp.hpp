#ifndef MEEWODAPP_HPP
#define MEEWODAPP_HPP

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSharedPointer>
#include <QDesktopServices>
#include <QDeclarativeContext>
#include <QDir>
#include <QDebug>
#include <QVariant>

#include "../cpp/model/loglistmodel.hpp"
#include "../cpp/model/benchmarklistmodel.hpp"
#include "../cpp/model/dailylistmodel.hpp"
#include "../cpp/model/recordlistmodel.hpp"
#include "../cpp/model/sortmodel.hpp"
#include <cpp/core/servicehandler.hpp>


class MeeWodApp : public QObject
{
    Q_OBJECT
public:
    MeeWodApp(QDeclarativeContext * context);
    ~MeeWodApp();
public:
    BenchmarkListModel* getBenchmarkListModel() const;
    DailyListModel* getDailyListModel() const;
    LogListModel* getWorkoutLogListModel() const;
    RecordListModel* getPersonalRecordModel() const;

private:
    QSqlDatabase createDatabase() const;

private:    
    BenchmarkListModel * _benchmarkListModel;
    DailyListModel * _dailyListModel;
    LogListModel *_logListModel;
    RecordListModel *_recordListModel;
    SortModel *_sortModel;
    QDeclarativeContext * _context;
};

#endif // MEEWODAPP_HPP
