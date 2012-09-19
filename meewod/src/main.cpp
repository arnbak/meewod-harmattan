#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDeclarativeView>
#include "../src/core/meewodapp.hpp"
#include "../src/core/settings.hpp"

#include <qmlapplicationviewer.h>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QDeclarativeView *viewer = new QDeclarativeView;

    app->setApplicationName("MeeWOD");
    app->setOrganizationName("arnbak");
    app->setOrganizationDomain("com.arnbak");
    app->setApplicationVersion("0.0.2");
    app->setFont(QFont("Nokia Pure Text"));

    Settings* settings = new Settings(app.data() );

    if(!settings->contains("theme-inverted")){
        settings->setValue("theme-inverted", true);
    }

    settings->setValue("appversion", app->applicationVersion());
    settings->setValue("LIST_SUBTITLE_COLOR", "blue");
    settings->setValue("LIST_SUBTITLE_COLOR_INVERTED", "yellow");

    QDeclarativeContext * context = viewer->rootContext();
    context->setContextProperty("Settings", settings);

    MeeWodApp * appContent = new MeeWodApp(context);

    viewer->setSource(QUrl("qrc:qml/pages/main.qml"));
    viewer->showFullScreen();

    int result = app->exec();

    delete appContent;
    delete viewer;

    return result;
}
