import QtQuick 1.1
import com.nokia.meego 1.0

import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants

Item {
    id: headerItem

    property alias text: title.text
    property alias subtext: subtitle.text
    property bool loading: false
    property bool showindicator: true

    signal clicked

    clip: true

    anchors {
        left: parent.left;
        right: parent.right
    }

    height: screen.currentOrientation === Screen.Portrait ?
                UIConstants.HEADER_DEFAULT_HEIGHT_PORTRAIT :
                UIConstants.HEADER_DEFAULT_HEIGHT_LANDSCAPE + (UIConstants.DEFAULT_MARGIN * 2)

    Image {
        id: headerBackground
        anchors.fill: parent
        source: "image://theme/color6-meegotouch-view-header-fixed" // + (theme.inverted ? "-inverted" : "")
    }

    Column {

        anchors {
            left: parent.left
            leftMargin: UIConstants.DEFAULT_MARGIN
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        Text {
            id: title

            verticalAlignment: Text.AlignVCenter
            font.pixelSize: UIConstants.FONT_XLARGE
            font.family: UIConstants.FONT_FAMILY
            color: !theme.inverted ?
                       UIConstants.COLOR_FOREGROUND :
                       UIConstants.COLOR_INVERTED_FOREGROUND
            width: parent.width
            wrapMode: Text.WordWrap
        }

        Text {
            id: subtitle
            font.pixelSize: UIConstants.FONT_SMALL
            font.family: UIConstants.FONT_FAMILY_LIGHT
            color: theme.inverted ?
                       Settings.getValue("LIST_SUBTITLE_COLOR_INVERTED") :
                       Settings.getValue("LIST_SUBTITLE_COLOR");
            verticalAlignment: Text.AlignVCenter

            width: parent.width
            wrapMode: Text.WordWrap

            visible: subtitle.text

        }

    }

    Item {
        id: loaderItem

        visible: showindicator

        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            margins: UIConstants.DEFAULT_MARGIN
        }

        width: 46;
        height: 46;

        Loader {
            id: loader
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            sourceComponent: loading ? busyIndicator : refreshIcon
        }

        Component {
            id: refreshIcon

            Image {
                source: "image://theme/icon-m-toolbar-refresh" + (theme.inverted ? "-white" : "")
            }

        }

        Component {
            id: busyIndicator

            BusyIndicator {
                running: loading;
                platformStyle: BusyIndicatorStyle { size: "medium" }
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                header.clicked();
            }
        }
    }
}
