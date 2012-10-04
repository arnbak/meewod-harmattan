import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants
import "../common"

Item {
    id: recordListDelegate

    signal clicked
    signal pressAndHold

    property string name: model.name
    property string time: model.time
    property string date: model.date
    property string category: model.category

    property bool pressable: true

    clip: true

    width: parent.width

    height: UIConstants.LIST_ITEM_HEIGHT_DEFAULT

    ListItemBackground {
        id: background
        visible: mouseArea.pressed
    }

    Separator {
        anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
        anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            recordListDelegate.clicked()
        }

        onPressAndHold: {
            recordListDelegate.pressAndHold()
            //console.log("index " + index);
        }
    }



    Column {
        id: listColumn

        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
            leftMargin: UIConstants.DEFAULT_MARGIN
            rightMargin: UIConstants.DEFAULT_MARGIN
        }

        width: parent.width

        Text {
            id: recordName
            text: name

            font.family: UIConstants.FONT_FAMILY
            font.pixelSize: ExtrasConstants.LIST_TILE_SIZE
            color: theme.inverted ?
                       ExtrasConstants.LIST_TITLE_COLOR_INVERTED :
                       ExtrasConstants.LIST_TITLE_COLOR
            width: parent.width
            elide: Text.ElideRight
        }

        Text {
            id: recordTime
            text: time
            font.family: "Nokia Pure Text Light"
            font.pixelSize: ExtrasConstants.LIST_SUBTILE_SIZE
            color: theme.inverted ?
                       ExtrasConstants.LIST_SUBTITLE_COLOR_INVERTED :
                       ExtrasConstants.LIST_SUBTITLE_COLOR
            visible: time
            width: parent.width
            elide: Text.ElideRight
        }
    }

    Image {
        id: viewDetails
        source: !theme.inverted ?
                    "image://theme/icon-m-common-drilldown-arrow" :
                    "image://theme/icon-m-common-drilldown-arrow-inverse"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        visible: pressable
    }
}
