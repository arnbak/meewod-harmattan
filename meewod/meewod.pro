TARGET = meewod

# Add more folders to ship with the application, here
qml_deployment.source = src/qml
qml_deployment.target = src
DEPLOYMENTFOLDERS = qml_deployment

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qt-boostable qdeclarative-boostable
CONFIG += meegotouch


!simulator {
    #LIBS += -lmdeclarativecache
    # booster flags
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic
}

QT += network sql webkit declarative

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/json/json.cpp \
    src/json/jsonparser.cpp \
    src/content/benchmarklistitem.cpp \
    src/content/dailylistitem.cpp \
    src/content/loglistitem.cpp \
    src/content/recordlistitem.cpp \
    src/core/meewodapp.cpp \
    src/model/benchmarklistmodel.cpp \
    src/model/dailylistmodel.cpp \
    src/model/loglistmodel.cpp \
    src/model/recordlistmodel.cpp \    
    src/model/sortmodel.cpp \
    src/core/servicehandler.cpp \
    src/core/networkrequesthandler.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    src/json/json.h \
    src/core/meewodapp.hpp \
    src/content/benchmarklistitem.hpp \
    src/content/dailylistitem.hpp \
    src/content/loglistitem.hpp \
    src/content/recordlistitem.hpp \
    src/model/benchmarklistmodel.hpp \
    src/model/dailylistmodel.hpp \
    src/model/loglistmodel.hpp \
    src/model/recordlistmodel.hpp \   
    src/model/sortmodel.hpp \
    src/core/servicehandler.hpp \
    src/core/networkrequesthandler.hpp \
    src/core/settings.hpp

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \       
    src/resources/meewodicon80.png \
    src/resources/meewodicon64.png \
    meewod_harmattan.desktop \
    src/resources/splash-land.png \
    ../README.md


contains(MEEGO_EDITION,harmattan) {
    message(Harmattan Build)
    DEFINES += Q_WS_HARMATTAN

    target.path = /opt/meewod/bin

    desktopfile.files = meewod_harmattan.desktop
    desktopfile.path = /usr/share/applications

    icon.files = src/resources/meewodicon80.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    splash.files = src/resources/splash.png
    splash.path = /opt/meewod

    INSTALLS += target desktopfile icon splash
}

RESOURCES += \
    src/res.qrc
