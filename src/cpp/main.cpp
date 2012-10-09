#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include "../cpp/core/meewodapp.hpp"
#include "../cpp/core/settings.hpp"

#include <QUuid>

#include <qmlapplicationviewer.h>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer; // = new QmlApplicationViewer;

    app->setApplicationName("MeeWOD");
    app->setOrganizationName("arnbak");
    app->setOrganizationDomain("com.arnbak");
    app->setApplicationVersion("0.0.2");
    app->setFont(QFont("Nokia Pure Text"));

    //qDebug() << "UUID " << QUuid::createUuid();

    Settings* settings = new Settings(app.data());

    if(!settings->contains("theme-inverted")){
        settings->setValue("theme-inverted", true);
    }

    settings->setValue("appversion", app->applicationVersion());
    settings->setValue("LIST_SUBTITLE_COLOR", "blue");
    settings->setValue("LIST_SUBTITLE_COLOR_INVERTED", "yellow");

    QDeclarativeContext * context = viewer.rootContext();
    context->setContextProperty("Settings", settings);

    MeeWodApp * appContent = new MeeWodApp(context);
    viewer.setMainQmlFile(QLatin1String("qml/pages/main.qml"));
    viewer.showFullScreen();

    int result = app->exec();

    delete appContent;
    //delete viewer;
    delete settings;

    return result;
}
