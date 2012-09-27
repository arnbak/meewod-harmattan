#include <QtCore/QDebug>
#include "../cpp/core/networkrequesthandler.hpp"

NetworkRequestHandler::NetworkRequestHandler(QObject *parent)
    : QObject(parent),
      _currentData(""),
      _currentRequest(QNetworkRequest()),
      _currentResult("")
{

}

NetworkRequestHandler::~NetworkRequestHandler() { }

void NetworkRequestHandler::putRequest(const QNetworkRequest &request, const QByteArray& data)
{

    _currentData = data;
    _currentRequest = request;

    //qDebug() << "url from putrequest " << _currentRequest.url().toString();

    _networkReply = _networkAccessManager.put(request, data);

    connect(_networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
    connect(_networkReply, SIGNAL(finished()), this, SLOT(putRequestFinished()));
}

void NetworkRequestHandler::postRequest(const QNetworkRequest &request, const QByteArray &data)
{
    _currentData = data;
    _currentRequest = request;

    _networkReply = _networkAccessManager.post(request, data);

    connect(_networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
    connect(_networkReply, SIGNAL(finished()), this, SLOT(postRequestFinished()));
}

void NetworkRequestHandler::getRequest(const QNetworkRequest &request)
{
    _currentRequest = request;
    _networkReply = _networkAccessManager.get(request);

    connect(_networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
    connect(_networkReply, SIGNAL(finished()), this, SLOT(getRequestFinished()));
}

void NetworkRequestHandler::httpError(const QNetworkReply::NetworkError &err)
{
    //qDebug() << "Network request error " << err;
    emit error(err);
}

void NetworkRequestHandler::putRequestFinished()
{
    //qDebug() << "put finished";
    QVariant redirTarget = _networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if(_networkReply->error())
    {
        return;
    }
    else if (!redirTarget.isNull())
    {
        _url = _url.resolved(redirTarget.toUrl());
        _networkReply->deleteLater();

        //qDebug() << "url " << _url.toString();

        _currentRequest.setUrl(_url);

        if(_currentData == "")
        {
            putRequest(_currentRequest, _currentData);
        }

        return;
    }
    else
    {
        _currentResult = _networkReply->readAll();
        emit putResult(_currentResult);
    }

    disconnect(_networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
    disconnect(_networkReply, SIGNAL(finished()), this, SLOT(putRequestFinished()));
    _networkReply->deleteLater();
    _networkReply = 0;

    _currentData = "";
    _currentRequest = QNetworkRequest();
    _currentResult = "";
}

void NetworkRequestHandler::postRequestFinished()
{
    //qDebug() << "put finished";
    QVariant redirTarget = _networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if(_networkReply->error())
    {
        return;
    }
    else if (!redirTarget.isNull())
    {
        _url = _url.resolved(redirTarget.toUrl());
        _networkReply->deleteLater();

        //qDebug() << "url " << _url.toString();

        _currentRequest.setUrl(_url);

        if(_currentData == "")
        {
            postRequest(_currentRequest, _currentData);
        }

        return;
    }
    else
    {
        _currentResult = _networkReply->readAll();
        emit postResult(_currentResult);
    }

    disconnect(_networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
    disconnect(_networkReply, SIGNAL(finished()), this, SLOT(postRequestFinished()));
    _networkReply->deleteLater();
    _networkReply = 0;

    _currentData = "";
    _currentRequest = QNetworkRequest();
    _currentResult = "";
}

void NetworkRequestHandler::getRequestFinished()
{
    QVariant redirTarget = _networkReply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if(_networkReply->error())
    {
        return;
    }
    else if (!redirTarget.isNull())
    {
        _url = _url.resolved(redirTarget.toUrl());
        _networkReply->deleteLater();

        _currentRequest.setUrl(_url);

        getRequest(_currentRequest);

        return;
    }
    else
    {
        _currentResult = _networkReply->readAll();
        emit getResult(_currentResult);
    }

    disconnect(_networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
    disconnect(_networkReply, SIGNAL(finished()), this, SLOT(getRequestFinished()));
    _networkReply->deleteLater();
    _networkReply = 0;

    _currentData = "";
    _currentRequest = QNetworkRequest();
    _currentResult = "";
}


