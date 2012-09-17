#ifndef SERVICEHANDLER_HPP
#define SERVICEHANDLER_HPP

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include <QtCore/QRegExp>
#include <QtCore/QUrl>
#include <QtGui/QTextEdit>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QSslConfiguration>

#include "../src/content/loglistitem.hpp"
#include "../src/content/benchmarklistitem.hpp"
#include "../src/content/dailylistitem.hpp"
#include "../src/core/networkrequesthandler.hpp"
#include "../src/json/json.h"

class ServiceHandler : public QObject
{
    Q_OBJECT
public:
    ServiceHandler();
    ~ServiceHandler();

public:
    void requestBenchmarkList();
    void requestDailyList();
    void requestPutLogList(QList<LogListItem*> list);    

public slots:    
    void handleGetRequestResult(const QString& result);
    void handlePutRequestRequest(const QString& result);
    void handlePostRequestResult(const QString& result);

signals:
    void benchmarkListFetched(const QList<BenchmarkListItem*> &list);
    void dailyListFetched(const QList<DailyListItem*> &list);
    void putListItemsRequestFineshed(const int & result);
    void handlerError(const int& errorcode);

private slots:
    void error(const int &err);

private:
    NetworkRequestHandler * _nwr;
};

#endif // MEEWODSERVICEHANDLER_HPP
