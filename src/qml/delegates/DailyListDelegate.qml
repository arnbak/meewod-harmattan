import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstants
import "../common"

Item {

    id: dailyListDelegate

    signal clicked

    property string title: model.title
    property string date: model.date
    property string description: model.description
    property string uri: model.uri

    property bool pressable: true

    clip: true

    width: parent.width

    height: listColumn.height

    ListItemBackground {
        id: background
        visible: mouseArea.pressed
    }

    Separator {
        anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
        anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
    }

    Column {
        id: listColumn

        anchors {
            left: parent.left
            right: parent.right
            leftMargin: UIConstants.DEFAULT_MARGIN
            rightMargin: UIConstants.DEFAULT_MARGIN
        }

        width: parent.width

        Label {
            id: titleText

            font.family: ExtrasConstants.FONT_FAMILY_BOLD
            font.pixelSize: UIConstants.FONT_LARGE

            color: theme.inverted ?
                       ExtrasConstants.LIST_TITLE_COLOR_INVERTED :
                       ExtrasConstants.LIST_TITLE_COLOR

            text: title

            width: parent.width
        }

        Label {
            id: subTitleText

            font.family: ExtrasConstants.FONT_FAMILY_LIGHT
            font.pixelSize: UIConstants.FONT_SMALL

            color: theme.inverted ?
                       Settings.getValue("LIST_SUBTITLE_COLOR_INVERTED") :
                       Settings.getValue("LIST_SUBTITLE_COLOR")

            width: parent.width
            text: date


        }

        Label {
            id: descriptionText

            text: description
            font.family: ExtrasConstants.FONT_FAMILY
            font.pixelSize: ExtrasConstants.FONT_DEFAULT_SIZE
            color: theme.inverted ?
                       ExtrasConstants.LIST_TITLE_COLOR_INVERTED :
                       ExtrasConstants.LIST_TITLE_COLOR
            visible: true

            width: parent.width
            wrapMode: Text.WordWrap
        }

    }



    MouseArea {
        id: mouseArea
        anchors.fill: background
        onClicked: {
            if(model !== "") {
                //                            benchmarkWorkoutTextPage._workoutid = id;
                //                            benchmarkWorkoutTextPage._type = type;
                //                            benchmarkWorkoutTextPage._name = name;
                //                            benchmarkWorkoutTextPage._description = description;
                //                            benchmarkWorkoutTextPage._wodtext = wodtext;

                //                            mainPage.pageStack.push(benchmarkWorkoutTextPage);
            }
        }

        onPressAndHold: {
            //console.log("Eventually share item " + index);

            ShareUI.share(title, uri);
        }
    }


}

