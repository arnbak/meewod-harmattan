import QtQuick 1.1
import com.nokia.meego 1.0
import "../js/tools.js" as MWT

ToolIcon {
    platformIconId: "toolbar-settings"
    anchors.right: parent.right
    onClicked: {
        MWT.createPageComponentAndPushToStack("../pages/SettingsPage.qml")
    }
}
