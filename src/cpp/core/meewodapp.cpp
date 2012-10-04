#include <QtDeclarative/QDeclarativeContext>
#include <QtCore/QDebug>
#include <QSharedPointer>

#include "../cpp/core/meewodapp.hpp"


static const QString DBNAME = "meewod.db";
static const QString APPDIR = "arnbak";
static const QString APPNAME = "meewod";

MeeWodApp::MeeWodApp(QDeclarativeContext *context)
    : QObject()
    , _context(context)
{    
    QSqlDatabase db = createDatabase();

    _dailyListModel = new DailyListModel(db);
    _logListModel = new LogListModel(db);
    _recordListModel = new RecordListModel(db);

    _benchmarkListModel = new BenchmarkListModel(db);
    _sortModel = new SortModel();
    _sortModel->setSourceModel(_benchmarkListModel);

    connect(_benchmarkListModel, SIGNAL(countChanged()), _sortModel, SIGNAL(countChanged()), Qt::UniqueConnection);
    connect(_benchmarkListModel, SIGNAL(benchmarkListUpdated()), _sortModel, SIGNAL(benchmarkListUpdated()), Qt::UniqueConnection);
    connect(_benchmarkListModel, SIGNAL(benchmarkListError(QString)), _sortModel, SIGNAL(benchmarkListError(QString)), Qt::UniqueConnection);

    _context->setContextProperty("dailyListModel", _dailyListModel);
    _context->setContextProperty("logListModel", _logListModel);
    _context->setContextProperty("recordListModel", _recordListModel);
    _context->setContextProperty("benchmarkListModel", _sortModel);

    MeeWODShareUi shareUi;
    context->setContextProperty("ShareUI", &shareUi);
}

MeeWodApp::~MeeWodApp()
{

    delete _benchmarkListModel;
    delete _dailyListModel;
    delete _logListModel;
    delete _recordListModel;
    //delete _context;
}

BenchmarkListModel* MeeWodApp::getBenchmarkListModel() const
{
    return _benchmarkListModel;
}

LogListModel* MeeWodApp::getWorkoutLogListModel() const
{
    return _logListModel;
}

DailyListModel* MeeWodApp::getDailyListModel() const
{
    return _dailyListModel;
}

RecordListModel * MeeWodApp::getPersonalRecordModel() const
{
    return _recordListModel;
}

QSqlDatabase MeeWodApp::createDatabase() const {
    //http://qt-project.org/forums/viewthread/13059
    QString dbPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

    QDir directory;

    if(!directory.exists(dbPath)) {
        directory.mkpath(dbPath);
    }

    QString absoluteDBName = dbPath + QDir::separator() + DBNAME;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(absoluteDBName);

    if(db.open()) {
        QSqlQuery createWorklogTableQuery("CREATE TABLE IF NOT EXISTS workoutlog "
                                          "(id INTEGER PRIMARY KEY, "
                                          "name TEXT, "
                                          "date DATE, "
                                          "description TEXT, "
                                          "handlestamp REAL )");

        if(!createWorklogTableQuery.exec())
        {
            qDebug() << "last error "  << db.lastError();
        }

        QSqlQuery createBenchmarkWorkoutTableQuery("CREATE TABLE IF NOT EXISTS benchwods "
                                                   "(id INTEGER PRIMARY KEY, "
                                                   "type TEXT, "
                                                   "name TEXT, "
                                                   "description TEXT, "
                                                   "workouttext TEXT )");

        if(!createBenchmarkWorkoutTableQuery.exec())
        {
            qDebug() << "last error "  << db.lastError();
        }

        QSqlQuery createDailyWorkoutTableQuery("CREATE TABLE IF NOT EXISTS dailywods "
                                               "(id real PRIMARY KEY, "
                                               "title TEXT, "
                                               "text TEXT, "
                                               "uri TEXT )");
        if(!createDailyWorkoutTableQuery.exec())
        {
            qDebug() << "last error "  << db.lastError();
        }

        //        QSqlQuery createPersonalRecordTableQuery("CREATE TABLE IF NOT EXISTS personalrecords "
        //                                               "(id real PRIMARY KEY, "
        //                                               "title TEXT, "
        //                                               "text TEXT, "
        //                                               "date TEXT )");
        //        if(createPersonalRecordTableQuery.exec())
        //        {
        //            qDebug("created personal records table");
        //        } else {
        //            qDebug() << "last error "  << db.lastError();
        //        }

    } else {
        qDebug() << "not created";
    }
    return db;
}
