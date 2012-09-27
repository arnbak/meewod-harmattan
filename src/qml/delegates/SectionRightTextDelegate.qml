import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.1


import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants

Item {
    property alias sectionName: sectionDelegateText.text

    id: sectionRightTextDelegate

    anchors { left: parent.left; right: parent.right }

    height: sectionDelegateText.height + UIConstants.DEFAULT_MARGIN

    Rectangle {
        id: sectionDelegateDivider
        width: parent.width -
               sectionDelegateText.width -
               UIConstants.DEFAULT_MARGIN
        height: 1
        color: theme.inverted ?
                   ExtrasConstants.LIST_SUBTITLE_COLOR_INVERTED :
                   ExtrasConstants.LIST_SUBTITLE_COLOR
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: sectionDelegateText
        color: theme.inverted ?
                   ExtrasConstants.LIST_SUBTITLE_COLOR_INVERTED :
                   ExtrasConstants.LIST_SUBTITLE_COLOR
        font.pixelSize: ExtrasConstants.LIST_SUBTILE_SIZE
        font.family: "Nokia Pure Text Light"
        anchors.left: sectionDelegateDivider.right
        anchors.leftMargin: UIConstants.DEFAULT_MARGIN
        anchors.verticalCenter: sectionDelegateDivider.verticalCenter
        width: Math.min(2 * parent.width / 3, helperText.width)
        elide: Text.ElideRight
    }

    Text {
        id: helperText
        font.pixelSize: ExtrasConstants.LIST_SUBTILE_SIZE
        font.family: "Nokia Pure Text Light"
        text: sectionDelegateText.text
        visible: false
    }
}
