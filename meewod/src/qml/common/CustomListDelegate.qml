import QtQuick 1.1
import com.nokia.meego 1.0
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants

Item {
    id: customListDelegate

    signal clicked

    property string listTitle: model.title
    property string listSubtitle: model.subtitle ? model.subtitle : ''
    property string sourceUrl: model.source_url ? model.source_url : ''
    property bool pressable: true

    width: parent.width

    height: UIConstants.LIST_ITEM_HEIGHT_SMALL

    BorderImage {
        anchors.fill: parent
        visible: mouseArea.pressed && pressable
        source: theme.inverted ?  'image://theme/meegotouch-list-inverted-background-pressed-vertical-center':
        'image://theme/meegotouch-list-background-pressed-vertical-center'
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: customListDelegate.clicked()
    }

    Item {
        anchors.fill: parent
        anchors {
            leftMargin: UIConstants.DEFAULT_MARGIN
            rightMargin: UIConstants.DEFAULT_MARGIN
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - viewDetails.width - ExtrasConstants.LIST_ITEM_SPACING

            Text {
                id: titleText
                text: listTitle
                font.family: UIConstants.FONT_FAMILY
                font.pixelSize: ExtrasConstants.LIST_TILE_SIZE
                color: theme.inverted ?
                           ExtrasConstants.LIST_TITLE_COLOR_INVERTED :
                ExtrasConstants.LIST_TITLE_COLOR
                width: parent.width
                elide: Text.ElideRight
            }

            Text {
                id: subtitleText
                text: listSubtitle
                font.family: "Nokia Pure Text Light"
                font.pixelSize: ExtrasConstants.LIST_SUBTILE_SIZE
                color: theme.inverted ?
                           ExtrasConstants.LIST_SUBTITLE_COLOR_INVERTED :
                ExtrasConstants.LIST_SUBTITLE_COLOR
                visible: listSubtitle
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

}
