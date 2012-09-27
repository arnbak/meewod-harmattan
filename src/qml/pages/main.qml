import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: mainWindow

    Component.onCompleted: {
        var comp = Qt.createComponent("DailyPage.qml");
        if (comp.status === Component.Ready) {
            var page = comp.createObject(pageStack);
            pageStack.pop();
            pageStack.push(page);
        }

        var theme_inverted = Settings.getValue("theme-inverted");

        //console.log("theme name " + theme_inverted + " " + theme.inverted)

        theme.inverted = theme_inverted

        //console.log("theme name " + theme_inverted + " " + theme.inverted)
    }

}
