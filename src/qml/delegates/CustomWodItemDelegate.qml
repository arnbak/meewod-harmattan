import QtQuick 1.1
import com.nokia.meego 1.0

import "../js/UIConstants.js" as UIConstants

Item {
    id: wodItem

    property alias title: titleText.text
    property alias text: wodText.text

    signal clicked

    height: 100
    anchors.left: parent.left
    anchors.right: parent.right

    Rectangle {
        id: background
        anchors.fill: parent
        color: UIConstants.COLOR_SELECT
        opacity: 0.0
    }

    Column {
        id: column
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.left: parent.left

        Text {
            id: titleText
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.margins: 8
            font.pixelSize: UIConstants.FONT_LARGE

            //color:
            elide: Text.ElideRight

            Behavior on color {
                ColorAnimation { duration: 300 }
            }
        }

        Text {
            id: wodText
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 8

            font.pixelSize: UIConstants.FONT_SMALL
            elide: Text.ElideRight

            Behavior on opacity {
                NumberAnimation { properties: "opacity"; duration: 300 }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: column
        onClicked:{
            root.clicked();
            // Start a short animation by changing the background opacity once the delegate is being clicked
            clickAnimation.start();
        }
    }

    SequentialAnimation {
        id: clickAnimation
        PropertyAnimation{target: background; properties:"opacity";to: 1.0; duration:75}
        PropertyAnimation{target: background; properties:"opacity";to: 0.0; duration:75}

    }
}

