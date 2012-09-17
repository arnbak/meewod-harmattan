import QtQuick 1.1
import com.nokia.meego 1.1

import "../common"
import "../pages"
import "../delegates"
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants

Column {

    property int workoutid: -1
    property string type: ''
    property string name: ''
    property string description: ''
    property string wodtext: ''

    id: wodDetailColumn

    width: parent.width

    spacing: UIConstants.DEFAULT_MARGIN


    Item {
        anchors.left: parent.left
        anchors.right: parent.right

        height: UIConstants.DEFAULT_MARGIN
    }

    SectionLeftTextDelegate {
        id: nameTextSection
        sectionName: "Name"
    }

    Label {
        id: nameText
        text: name
    }

    SectionRightTextDelegate {
        id: descriptionSection
        sectionName: "Description"
    }

    Text {
        width: parent.width
        id: descriptionId
        text: description
        font.family: ExtrasConstants.FONT_FAMILY_LIGHT
        font.pixelSize: ExtrasConstants.FONT_LIGHT_SIZE
        wrapMode: Text.WordWrap
    }

    Text {
        width: parent.width
        id: wodTextId
        text: wodtext
        font.family: ExtrasConstants.FONT_FAMILY_LIGHT
        font.pixelSize: ExtrasConstants.FONT_LIGHT_SIZE
    }

    SectionRightTextDelegate {
        id: typeSectioin
        sectionName: "Type"
    }
}
