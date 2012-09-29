import QtQuick 1.1
import com.nokia.meego 1.0

import "../common"
import "../pages"
import "../delegates"
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants

Page {
    property int _workoutid: -1
    property string _type: ''
    property string _name: ''
    property string _description: ''
    property string _wodtext: ''

    id: detailsPage

    RefreshableHeader {
        id: header
        text: _name
        subtext: _type
    }

    tools: ToolBarLayout {
        id: toolbarLayout
        visible: true

        BackIcon {}

        ToolIcon {
            id: shareIcon
            platformIconId: "toolbar-share"
            onClicked: {
                ShareUI.share(_name, "");
            }
        }
    }

    Flickable {

        id: flicker
        flickableDirection: "VerticalFlick"
        clip: true

        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right            
            leftMargin: UIConstants.DEFAULT_MARGIN
            rightMargin: UIConstants.DEFAULT_MARGIN
        }

        Column {

            width: parent.width
            spacing: 15

            Label {
                id: workoutDescriptionText

                font.family: ExtrasConstants.FONT_FAMILY_BOLD
                font.pixelSize: ExtrasConstants.FONT_DEFAULT_SIZE

                wrapMode: Text.WordWrap
                width: parent.width

                text: _description
            }

            Label {
                id: workoutText

                font.family: ExtrasConstants.FONT_FAMILY_LIGHT
                font.pixelSize: ExtrasConstants.FONT_DEFAULT_SIZE

                wrapMode: Text.WordWrap

                width: parent.width

                text: _wodtext
            }

        }
    }

    ScrollDecorator {
        id: scrollableItem
        flickableItem: flicker
    }
}
