#include "../src/core/servicehandler.hpp"

ServiceHandler::ServiceHandler()
    : _nwr(new NetworkRequestHandler)
{
    connect(_nwr, SIGNAL(error(int)), this, SLOT(error(int)));
    connect(_nwr, SIGNAL(getResult(QString)), this, SLOT(handleGetRequestResult(QString)));
    connect(_nwr, SIGNAL(putResult(QString)), this, SLOT(handlePutRequestRequest(QString)));
    connect(_nwr, SIGNAL(postResult(QString)), this, SLOT(handlePostRequestResult(QString)));
}

ServiceHandler::~ServiceHandler()
{
    delete _nwr;
}

void ServiceHandler::handlePutRequestRequest(const QString &result)
{
    //qDebug() << "put result " << result;
    Q_UNUSED(result)
    emit putListItemsRequestFineshed(10);
}

void ServiceHandler::handlePostRequestResult(const QString &result)
{
    // qDebug() << "post result " << result;

    if(result.isEmpty())
    {
        return;
    }

    JsonReader reader;
    reader.parse(result);

    int type = reader.result().toMap()["type"].toInt();

    if(type == 1) {

        //qDebug() << "getBenchmark List status " << reader.result().toMap()["statuscode"].toInt();

        QList<BenchmarkListItem *> list;

        foreach (QVariant v, reader.result().toMap()["benchmarkcontent"].toList()) {
            BenchmarkListItem * item = new BenchmarkListItem(v.toMap()["id"].toInt(),
                                                                   v.toMap()["type"].toString(),
                                                                   v.toMap()["name"].toString(),
                                                                   v.toMap()["description"].toString(),
                                                                   v.toMap()["workouttext"].toString());

            list.append(item);

        }

        emit benchmarkListFetched(list);
    } else if(type == 2) {
        QList<DailyListItem *> list;

        foreach (QVariant v, reader.result().toMap()["dailycontent"].toList()) {
            DailyListItem * item = new DailyListItem(v.toMap()["title"].toString(),
                                                     QDateTime::fromMSecsSinceEpoch(v.toMap()["published"].toLongLong()),
                                                     v.toMap()["text"].toString(),
                                                     v.toMap()["uri"].toString());

            list.append(item);

        }

        //qDebug() << "getDaily List status " << reader.result().toMap()["statuscode"].toInt();
        //qDebug() << "Size " << list.size();
        emit dailyListFetched(list);
    } else {
        //qDebug() << "error happend ";
        emit error(2);
    }
}

void ServiceHandler::handleGetRequestResult(const QString &result)
{
    //qDebug() << "get result " << result;

    if(result.isEmpty())
    {
        return;
    }

    JsonReader reader;
    reader.parse(result);

    int type = reader.result().toMap()["type"].toInt();

    if(type == 1) {

        //qDebug() << "getBenchmark List status " << reader.result().toMap()["statuscode"].toInt();

        QList<BenchmarkListItem *> list;

        foreach (QVariant v, reader.result().toMap()["benchmarkcontent"].toList()) {
            BenchmarkListItem * item = new BenchmarkListItem(v.toMap()["id"].toInt(),
                                                                   v.toMap()["type"].toString(),
                                                                   v.toMap()["name"].toString(),
                                                                   v.toMap()["description"].toString(),
                                                                   v.toMap()["workouttext"].toString());

            list.append(item);

        }

        emit benchmarkListFetched(list);
    } else if(type == 2) {
        QList<DailyListItem *> list;

        foreach (QVariant v, reader.result().toMap()["dailycontent"].toList()) {
            DailyListItem * item = new DailyListItem(v.toMap()["title"].toString(),
                                                     QDateTime::fromMSecsSinceEpoch(v.toMap()["published"].toLongLong()),
                                                     v.toMap()["text"].toString(),
                                                     v.toMap()["uri"].toString());            

            list.append(item);

        }

        //qDebug() << "getDaily List status " << reader.result().toMap()["statuscode"].toInt();
        //qDebug() << "Size " << list.size();
        emit dailyListFetched(list);
    } else {
        qDebug() << "error happend ";
        emit error(2);
    }
}

void ServiceHandler::error(const int &err)
{
   // qDebug() << "error " << err;
    emit handlerError(err);
}


void ServiceHandler::requestPutLogList(QList<LogListItem*> list)
{
    QNetworkRequest request;
    request = QNetworkRequest(QUrl("https://arnbak.com:8443/meewod/rest/wod/create/backup"));

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    request.setRawHeader("Host", "arnbak.com:8443");
    request.setRawHeader("Content-Type", "application/json; charset=utf-8");
    request.setRawHeader("ACCEPT", "application/json");
    request.setRawHeader("Accept-Charset", "utf-8");
    request.setRawHeader("User-Agent", QString("MeeWOD/0.0.1 (MeeGo/Harmattan)").toUtf8());

    QVariantList variantList;

    Q_FOREACH (LogListItem *logItem, list) {
        QVariantMap map;
        map["id"] = list.indexOf(logItem);
        map["name"] = logItem->getName();
        map["date"] = logItem->getDate();
        map["description"] = logItem->getDescription();
        map["handlestamp"] = logItem->getHandleStamp();
        variantList.append(map);
    }

    JsonWriter w;

    if(w.stringify(variantList)) {
        QString json = w.result();
        _nwr->putRequest(request, json.toUtf8());
        //qDebug() << "put request made " << json.toUtf8();
    }
    else
    {
        qDebug() << "failed to stringify " << w.errorString();
    }
}

void ServiceHandler::requestDailyList()
{
    QNetworkRequest request;

    request = QNetworkRequest(QUrl("https://arnbak.com:8443/meewod/rest/wod/list/daily"));
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    request.setRawHeader("Host", "arnbak.com:8443");
    request.setRawHeader("Content-Type", "application/json; charset=utf-8");
    request.setRawHeader("ACCEPT", "application/json");
    request.setRawHeader("Accept-Charset", "utf-8");
    request.setRawHeader("User-Agent", QString("MeeWOD/0.0.1 (MeeGo/Harmattan)").toUtf8());

    //qDebug() << "request made";
    QString data;
    _nwr->postRequest(request, data.toUtf8());
}

void ServiceHandler::requestBenchmarkList()
{
    QNetworkRequest request;

    request = QNetworkRequest(QUrl("https://arnbak.com:8443/meewod/rest/wod/list/benchmarks"));
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    request.setSslConfiguration(config);

    request.setRawHeader("Host", "arnbak.com:8443");
    request.setRawHeader("Content-Type", "application/json; charset=utf-8");
    request.setRawHeader("ACCEPT", "application/json");
    request.setRawHeader("Accept-Charset", "utf-8");
    request.setRawHeader("User-Agent", QString("MeeWOD/0.0.1 (MeeGo/Harmattan)").toUtf8());

    //qDebug() << "request made";    
    QString data;
    _nwr->postRequest(request, data.toUtf8());
}
