import QtQuick 1.1
import com.nokia.meego 1.0

import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants

Rectangle {

    property alias text: title.text
    property alias secondaryText: subtitle.text

    property real contentOpacity: 1.0
    property int contentMargins: 0

    width: parent ? parent.width : 0

    height: screen.currentOrientation === Screen.Portrait ? UIConstants.HEADER_DEFAULT_HEIGHT_PORTRAIT : UIConstants.HEADER_DEFAULT_HEIGHT_LANDSCAPE

    anchors.horizontalCenter: parent.horizontalCenter

    color: "transparent"

    Column {

        anchors.left: parent.left
        anchors.leftMargin: UIConstants.DEFAULT_MARGIN
        anchors.right: parent.right
        anchors.rightMargin: contentMargins
        anchors.verticalCenter: parent.verticalCenter

        Label {

            anchors.left: parent.left
            anchors.right: parent.right

            id: title

            verticalAlignment: Text.AlignVCenter

            color: theme.inverted ? UIConstants.COLOR_INVERTED_FOREGROUND : UIConstants.COLOR_FOREGROUND

            font.pixelSize: UIConstants.FONT_LARGE

            font.family: UIConstants.FONT_FAMILY_LIGHT

            elide: Text.ElideRight

            opacity: contentOpacity

        }

        Label {

            id: subtitle

            anchors.left: text.length > 0 ? parent.left : undefined
            anchors.right: text.length > 0 ? parent.right : undefined

            verticalAlignment: Text.AlignVCenter

            color: theme.inverted ?
                       Settings.getValue("LIST_SUBTITLE_COLOR_INVERTED") :
                       Settings.getValue("LIST_SUBTITLE_COLOR");


            font.pixelSize: UIConstants.FONT_SMALL

            elide: Text.ElideRight

            opacity: contentOpacity

        }

    }

    Rectangle {
//        id: sectionDelegateDivider
//        width: parent.width -
//               sectionDelegateText.width -
//               UIConstants.DEFAULT_MARGIN
        height: 1
        color: theme.inverted ?
                   ExtrasConstants.LIST_SUBTITLE_COLOR_INVERTED :
                   ExtrasConstants.LIST_SUBTITLE_COLOR

        //anchors.verticalCenter: parent.verticalCenter

        anchors.left: parent.left
        anchors.leftMargin: contentMargins
        anchors.right: parent.right
        anchors.rightMargin: contentMargins
        anchors.bottom: parent.bottom
    }



//    Separator {

//        anchors.left: parent.left
//        anchors.leftMargin: contentMargins
//        anchors.right: parent.right
//        anchors.rightMargin: contentMargins
//        anchors.bottom: parent.bottom

//    }

}
