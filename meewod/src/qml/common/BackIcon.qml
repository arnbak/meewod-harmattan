import QtQuick 1.1
import com.nokia.meego 1.0

ToolIcon {
    platformIconId: enabled ? "toolbar-back" : "toolbar-back-dimmed"
    anchors.left: parent.left
    onClicked: {
        pageStack.pop()
    }
}

