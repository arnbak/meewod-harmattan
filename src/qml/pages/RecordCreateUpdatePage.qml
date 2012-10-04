import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../common"

import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasContstans

Sheet {
    id: createRecordItemPage

    acceptButtonText: qsTr("Save")
    rejectButtonText: qsTr("Cancel")

    property int selectedIndex: -1

    property alias recordname: nameId.text
    property alias recordtime: timeText.text
    property alias recorddate: dateText.text
    property alias recorddescription: descriptionText.text
    property alias recordcategory: categoryText.text

    property variant item

    TimePickerDialog {
        id: timePickerDialog
        titleText: qsTr("Record time")
        acceptButtonText: qsTr("Ok")
        rejectButtonText: qsTr("Cancel")

        onAccepted: {
            var hour = (timePickerDialog.hour.toString().length === 1) ? "0"+timePickerDialog.hour : timePickerDialog.hour;
            var minute = (timePickerDialog.minute.toString().length === 1) ? "0"+timePickerDialog.minute :timePickerDialog.minute;
            var second = (timePickerDialog.second.toString().length === 1) ? "0"+timePickerDialog.second :timePickerDialog.second;

            timeText.text = hour + ":" + minute + ":" + second;
        }

    }

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
    }

    content: Flickable {
        anchors.fill: parent

        Column {
            id: sheetContent
            spacing: 12

            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: UIConstants.DEFAULT_MARGIN
            }

            Label {
                text: qsTr("Name: ")
                font.family: UIConstants.FONT_FAMILY_LIGHT
            }

            TextField {
                id: nameId
                width: parent.width
                placeholderText: qsTr("Record Name ex. 500m row")
            }

            Item {
                id: timeSelector
                height: 66
                width: parent.width

                ListItemBackground {
                    id: timeSelBackground
                    anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
                    anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
                    visible: timeSelMouseArea.pressed
                }

                Label {
                    id: timeLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: ExtrasContstans.FONT_FAMILY_LIGHT
                    font.pixelSize: UIConstants.FONT_DEFAULT
                    text: qsTr("Completion Time: ")
                }

                Label {
                    id: timeText
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: ExtrasContstans.FONT_FAMILY_BOLD
                    font.pixelSize: UIConstants.FONT_LARGE
                    text: qsTr("00:00:00")
                }

                MouseArea {
                    id: timeSelMouseArea
                    anchors.fill: timeSelBackground

                    onClicked: {
                        timePickerDialog.open();
                        console.log("date sel width : "+ timeSelector.width)
                    }
                }
            } //time selector item

            Item {
                id: dateSelector
                height: 66
                width: parent.width

                ListItemBackground {
                    id: dateSelectorBackground
                    anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
                    anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
                    visible: dateSelectorMouseArea.pressed

                }

                Label {
                    id: dateLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: ExtrasContstans.FONT_FAMILY_LIGHT
                    font.pixelSize: UIConstants.FONT_DEFAULT
                    text: qsTr("Date: ")
                }

                Label {
                    id: dateText
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: ExtrasContstans.FONT_FAMILY_BOLD
                    font.pixelSize: UIConstants.FONT_LARGE
                    text: qsTr("dd:MM:yyyy")
                }

                MouseArea {
                    id: dateSelectorMouseArea
                    anchors.fill: dateSelectorBackground
                    onClicked: {
                        // for some reason month in the js Date() function is off by 1
                        // solved it by using Qt.formatDateTime ..
                        var today = new Date();
                        dateSelectorDialog.year = Qt.formatDateTime(today, "yyyy");
                        dateSelectorDialog.month = Qt.formatDateTime(today, "MM");
                        dateSelectorDialog.day = Qt.formatDateTime(today, "dd");
                        dateSelectorDialog.open();

                        console.log("date sel width : "+ dateSelector.width)
                    }
                }
            } //end dateselector item


            Label {
                id: descriptionLabel
                text: qsTr("Description:")
                font.pointSize: 26
            }

            TextArea {
                id: descriptionText
                placeholderText: qsTr("Description")
                height: Math.max (100, implicitHeight)
                width: parent.width

                onCursorPositionChanged: {
                    descriptionText.positionToRectangle(cursorPosition);
                }

                //text: logEntryDescription

                wrapMode: TextEdit.Wrap
            }

            Label {
                id: categoryLabel
                text: qsTr("Category:")
                font.pointSize: 26
            }

            TextField {
                id: categoryText
                placeholderText: qsTr("Workout Category (ex swimming)")
                //height: Math.max (100, implicitHeight)
                width: parent.width

                //                onCursorPositionChanged: {
                //                    categoryText.positionToRectangle(cursorPosition);
                //                }

                //text: logEntryDescription

                //wrapMode: TextEdit.Wrap
            }
        }

    } // end flickable

    onAccepted: {
        console.log("add item " + recordtime + " " + recorddate);

        if(selectedIndex === -1) {
            recordListModel.addItem(recordname, recordtime, recorddate, recorddescription, recordcategory);
        } else if(selectedIndex !== -1) {
            recordListModel.updateItem(selectedIndex, recordname, recordtime, recorddate, recorddescription, recordcategory);

        }
    }

    Component.onCompleted: {
        console.log("Status " + status === PageStatus.Active)
    }

    function init() {
        console.log("init")

        recordname = ''
        recorddescription = ''
        recordcategory = ''
        recorddate = qsTr("dd:MM:yyyy")
        recordtime = qsTr("00:00:00")
    }

    onStatusChanged: {

        //createLogItemPage.currentItem = workoutLogModel.get(index);

        //console.log("onstatus " + status + " index " + currentIndex);

        if(status === DialogStatus.Opening) {

            //console.log("opening");

            if(selectedIndex === -1) {
                init();
            } else {

                recordname = item.name;
                recorddate = item.date;
                recordtime = item.time;
                //                item = logListModel.getLogItem(currentIndex);
                //                nameText.text = item.logname;
                //                dateText.text = item.logdate;
                //                descriptionText.text = item.logdesc;
            }

        } else if(status === DialogStatus.Opened) {
            //console.log("opened");
        }
    }


}
