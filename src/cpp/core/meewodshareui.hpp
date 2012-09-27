#ifndef MEEWODSHAREUI_HPP
#define MEEWODSHAREUI_HPP

#include <QObject>
#include <QDebug>

#ifndef QT_SIMULATOR
    #include <maemo-meegotouch-interfaces/shareuiinterface.h>
    #include <MDataUri>
    #include <QDBusInterface>
    #include <QDBusPendingCall>
#endif

class MeeWODShareUi : public QObject
{
    Q_OBJECT

public:
    MeeWODShareUi(QObject * parent = 0);
    Q_INVOKABLE void share(const QString& title, const QString& url);
};

#endif // MEEWODSHAREUI_HPP
