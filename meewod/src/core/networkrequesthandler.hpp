#ifndef NETWORKREQUESTHANDLER_HPP
#define NETWORKREQUESTHANDLER_HPP

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class NetworkRequestHandler : public QObject
{
Q_OBJECT
public:
    NetworkRequestHandler(QObject *parent = 0);
    ~NetworkRequestHandler();

    void getRequest(const QNetworkRequest &request);    
    void putRequest(const QNetworkRequest &request, const QByteArray &data);
    void postRequest(const QNetworkRequest &request, const QByteArray &data);

signals:
    void error(const int &);
    void getResult(const QString &);
    void putResult(const QString &);
    void postResult(const QString &);

private slots:
    void httpError(const QNetworkReply::NetworkError &err);
    void getRequestFinished();
    void putRequestFinished();
    void postRequestFinished();

private:
    void executeRequest(const QNetworkRequest &request, const QByteArray &data = 0);

    QNetworkAccessManager _networkAccessManager;
    QNetworkReply *_networkReply;

    QByteArray _currentData;
    QNetworkRequest _currentRequest;
    QString _currentResult;

    QUrl _url;
};

#endif // NETWORKREQUEST_HPP
