TARGET = meewod

# Add more folders to ship with the application, here
qml_deployment.source = qml
qml_deployment.target = 
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

# Use share-ui interface
CONFIG += shareuiinterface-maemo-meegotouch mdatauri


!simulator {
    #LIBS += -lmdeclarativecache
    # booster flags
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic
}

QT += network sql webkit declarative

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += cpp/main.cpp \
    cpp/json/json.cpp \
    cpp/json/jsonparser.cpp \
    cpp/content/benchmarklistitem.cpp \
    cpp/content/dailylistitem.cpp \
    cpp/content/loglistitem.cpp \
    cpp/content/recordlistitem.cpp \
    cpp/core/meewodapp.cpp \
    cpp/model/benchmarklistmodel.cpp \
    cpp/model/dailylistmodel.cpp \
    cpp/model/loglistmodel.cpp \
    cpp/model/recordlistmodel.cpp \    
    cpp/model/sortmodel.cpp \
    cpp/core/servicehandler.cpp \
    cpp/core/networkrequesthandler.cpp \
    cpp/core/meewodshareui.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    cpp/json/json.h \
    cpp/core/meewodapp.hpp \
    cpp/content/benchmarklistitem.hpp \
    cpp/content/dailylistitem.hpp \
    cpp/content/loglistitem.hpp \
    cpp/content/recordlistitem.hpp \
    cpp/model/benchmarklistmodel.hpp \
    cpp/model/dailylistmodel.hpp \
    cpp/model/loglistmodel.hpp \
    cpp/model/recordlistmodel.hpp \   
    cpp/model/sortmodel.hpp \
    cpp/core/servicehandler.hpp \
    cpp/core/networkrequesthandler.hpp \
    cpp/core/settings.hpp \
    cpp/core/meewodshareui.hpp

OTHER_FILES += \
	resources/meewodicon80.png \
    resources/meewodicon64.png \
    meewod_harmattan.desktop \
    resources/splash-land.png \   



contains(MEEGO_EDITION,harmattan) {
    message(Harmattan Build)
    DEFINES += Q_WS_HARMATTAN

    target.path = /opt/meewod/bin

    desktopfile.files = meewod_harmattan.desktop
    desktopfile.path = /usr/share/applications

    icon.files = resources/meewodicon80.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    splash.files = resources/splash.png
    splash.path = /opt/meewod

    INSTALLS += target desktopfile icon splash
}

RESOURCES += \
    res.qrc
