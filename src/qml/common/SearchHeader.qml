import QtQuick 1.1
import com.nokia.meego 1.0
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants

Image {
    id: headerItem

    property alias text: headerText.text

    height: parent.width < parent.height ? UIConstants.HEADER_DEFAULT_HEIGHT_PORTRAIT
                                         : UIConstants.HEADER_DEFAULT_HEIGHT_LANDSCAPE
    width: parent.width

    source: "image://theme/color6-meegotouch-view-header-fixed" + (theme.inverted ? "-inverted" : "")

    Item {

        anchors {
            fill: parent
            topMargin: parent.width < parent.height
                       ? UIConstants.HEADER_DEFAULT_TOP_SPACING_PORTRAIT
                       : UIConstants.HEADER_DEFAULT_TOP_SPACING_LANDSCAPE
            bottomMargin: parent.width < parent.height
                          ? UIConstants.HEADER_DEFAULT_BOTTOM_SPACING_PORTRAIT
                          : UIConstants.HEADER_DEFAULT_BOTTOM_SPACING_LANDSCAPE
            rightMargin: UIConstants.DEFAULT_MARGIN
            leftMargin: UIConstants.DEFAULT_MARGIN
        }

        Label {
            id: headerText
            anchors {
                verticalCenter: parent.verticalCenter;
                left: parent.left
            }
            font.pixelSize: UIConstants.FONT_XLARGE
            font.family: UIConstants.FONT_FAMILY
            text: headerItem.text
        }
    }
}
