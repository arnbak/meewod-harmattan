import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../common"
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasContstans


Sheet {
    id: createLogItemPage

    property int currentIndex: -1

    property string logEntryName
    property string logEntryDate
    property string logEntryDescription

    property variant item

    acceptButtonText: qsTr("Save")
    rejectButtonText: qsTr("Cancel")

    DatePickerDialog {
        id: dateSelectorDialog
        titleText: qsTr("Date Of Workout")
        acceptButtonText: "Ok"
        rejectButtonText: "Cancel"

        onAccepted: {
            //dd-MM-yyyy
            var month = (dateSelectorDialog.month.toString().length === 1) ? "0"+dateSelectorDialog.month : dateSelectorDialog.month;
            var day = (dateSelectorDialog.day.toString().length === 1) ? "0"+dateSelectorDialog.day : dateSelectorDialog.day;
            var entry = day + "-" + month + "-" + dateSelectorDialog.year;

            if(entry.length !== 0) {
                //console.log(" entry " + entry);
                //logEntryDate = entry;
                dateText.text = entry;
            }
        }

        onRejected: {
            //            logEntryDate = '';
            //            dateText.text = '';
        }
    }

    content: Flickable {
        anchors.fill: parent
        contentHeight: sheetContent.height

        Column {
            id: sheetContent
            spacing: 12

            anchors{top: parent.top; left: parent.left; right: parent.right; margins: 15}

            Label {
                id: nameLabel
                text: qsTr("Name:")
                font.pointSize: 26
            }

            TextField {
                id: nameText
                width: parent.width
                placeholderText: qsTr("Log entry name")
                text: logEntryName
            }

            Item {
                id: dateSelection
                height: 66
                width: parent.width

                ListItemBackground {
                    id: backgroundId
                    anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
                    anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
                    visible: mouseArea.pressed
                }

                Label {
                    id: dateLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: ExtrasContstans.FONT_FAMILY_LIGHT
                    font.pixelSize: ExtrasContstans.LIST_TILE_SIZE
                    text: "Date: "
                }

                Label {
                    id: dateText
                    anchors.left: dateLabel.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: ExtrasContstans.FONT_FAMILY_BOLD
                    font.pixelSize: ExtrasContstans.LIST_TILE_SIZE
                    text: logEntryDate
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: backgroundId
                    onClicked: {
                        // for some reason month in the js Date() function is off by 1
                        // solved it by using Qt.formatDateTime ..
                        var today = new Date();
                        dateSelectorDialog.year = Qt.formatDateTime(today, "yyyy");
                        dateSelectorDialog.month = Qt.formatDateTime(today, "MM");
                        dateSelectorDialog.day = Qt.formatDateTime(today, "dd");
                        dateSelectorDialog.open();
                    }
                }
            } //end Item

            Label {
                id: descriptionLabel
                text: qsTr("Description:")
                font.pointSize: 26
            }

            TextArea {
                id: descriptionText
                placeholderText: qsTr("Description")
                height: Math.max (200, implicitHeight)
                width: parent.width

                onCursorPositionChanged: {
                    descriptionText.positionToRectangle(cursorPosition);
                }

                text: logEntryDescription

                wrapMode: TextEdit.Wrap
            }

//            Item {
//                id: rating
//                hei

//                anchors {
//                    left: parent.left
//                    right: parent.right
//                    top: descriptionText.bottom
//                    topMargin: UIConstants.DEFAULT_MARGIN
//                }

//                Label {
//                    id: ratingLabel
//                    anchors.verticalCenter: parent.verticalCenter
//                    font.family: ExtrasContstans.FONT_FAMILY_LIGHT
//                    font.pixelSize: ExtrasContstans.LIST_TILE_SIZE
//                    text: qsTr("Rate your workout:");
//                }

//                RatingIndicator {
//                    id: ratingIndicator
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.right: parent.right
//                    maximumValue: 5
//                    ratingValue: 3
//                    count: 4
//                    inverted: theme.inverted
//                }
//            }



            Button {
                anchors.right: parent.right
                text: qsTr("Delete")
                width: 150
                onClicked: {
                    console.log("delete " + currentIndex);
                    logListModel.deleteLogItem(currentIndex);
                    createLogItemPage.close();

                    logEntryName = '';
                    logEntryDate = '';
                    logEntryDescription = '';

                    nameText.text = '';
                    dateText.text = '';
                    descriptionText.text = '';

                }

                visible: currentIndex !== -1
            }
        }
    }

    onAccepted: {

        console.log("update " + currentIndex + " " + nameText.text + " " + dateText.text + " " + descriptionText.text);

        if(currentIndex === -1) {
            logListModel.addLogItem(nameText.text, dateText.text, descriptionText.text);
        } else if(currentIndex !== -1) {
            logListModel.updateLogItem(currentIndex, nameText.text, dateText.text, descriptionText.text);
        }

        nameText.text = '';
        dateText.text = '';
        descriptionText.text = '';

    }

    onRejected: {
        currentIndex = -1;

        logEntryName = '';
        logEntryDate = '';
        logEntryDescription = '';

        nameText.text = '';
        dateText.text = '';
        descriptionText.text = '';
    }

    onStatusChanged: {

        //createLogItemPage.currentItem = workoutLogModel.get(index);

        //console.log("onstatus " + status + " index " + currentIndex);

        if(status === DialogStatus.Opening) {

            //console.log("opening");

            if(currentIndex === -1) {
                createLogItemPage.logEntryDate = '';
                createLogItemPage.logEntryDescription = '';
                createLogItemPage.logEntryName = '';
            } else {
                item = logListModel.getLogItem(currentIndex);
                nameText.text = item.logname;
                dateText.text = item.logdate;
                descriptionText.text = item.logdesc;
            }

        } else if(status === DialogStatus.Opened) {
            //console.log("opened");
        }
    }
}
