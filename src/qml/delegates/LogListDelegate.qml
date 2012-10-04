import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants
Item {
    id: logListDelegate

    signal clicked

    property string logEntryName: model.logname
    property string logEntryDate: model.logdate

    property bool pressable: true

    width: parent.width

    height: UIConstants.LIST_ITEM_HEIGHT_DEFAULT

    BorderImage {
        anchors.fill: parent
        visible: mouseArea.pressed && pressable
        source: theme.inverted ?
                    'image://theme/meegotouch-list-inverted-background-pressed-vertical-center':
                    'image://theme/meegotouch-list-background-pressed-vertical-center'
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: logListDelegate.clicked()
    }

    Item {
        anchors.fill: parent     

        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width

            Text {
                id: logEntryNameId
                text: logEntryName
                font.family: UIConstants.FONT_FAMILY
                font.pixelSize: ExtrasConstants.LIST_TILE_SIZE
                color: theme.inverted ?
                           ExtrasConstants.LIST_TITLE_COLOR_INVERTED :
                           ExtrasConstants.LIST_TITLE_COLOR
                width: parent.width
                elide: Text.ElideRight
            }

            Text {
                id: logEntryDateId
                text: logEntryDate
                font.family: "Nokia Pure Text Light"
                font.pixelSize: ExtrasConstants.LIST_SUBTILE_SIZE
                color: theme.inverted ?
                           ExtrasConstants.LIST_SUBTITLE_COLOR_INVERTED :
                           ExtrasConstants.LIST_SUBTITLE_COLOR
                visible: logEntryDate
                width: parent.width
                elide: Text.ElideRight
            }
        }

    }

}
