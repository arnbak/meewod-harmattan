import QtQuick 1.1
import com.nokia.meego 1.0

import "../common"
import "../pages"
import "../js/UIConstants.js" as UIConstants

Page {
    id: recordListPage

    RecordCreateUpdatePage { id: createRecordItemPage }

    property bool networkRequestRunning: false

    tools: ToolBarLayout {
        id: toolBar
        visible: true

        BackIcon {}

        CreateIcon {
            id: createItem
            onClicked: {
                console.log("create");
                createRecordItemPage.open();
            }

            //createpage: "../pages/CreatePersonalRecordPage.qml"
        }
    }

    RefreshableHeader {
        id: header
        text: qsTr("Personal Records");
        subtext: qsTr("Keep track of your progress");
        showindicator: false
    }

    Item {

        anchors {
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right            
        }

        ListView {
            id: logListView
            anchors.fill: parent
            model: personalRecordModel

            clip: true

            delegate: Item {
                id: listItem
                height: 88
                width: parent.width

                ListItemBackground {
                    id: background
                    visible: mouseArea.pressed
                }

                Separator {
                    anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
                    anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
                }

                Row {
                    anchors.fill: parent
                    anchors.margins: UIConstants.DEFAULT_MARGIN

                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width

//                        LabelTitle {
//                            id: mainText
//                            text: logname
//                        }

//                        LabelSubtitle {
//                            id: subText
//                            text: logdate
//                        }
                    }
                }

                ListArrowIcon {
                    anchors.rightMargin: UIConstants.DEFAULT_MARGIN
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: background
                    onClicked: {
                        if(model !== "") {
                            console.log("index " + index + " selected");
                            createLogItemPage.currentIndex = index;
                            createLogItemPage.open();
                        }
                    }
                }
            }

            ScrollDecorator {
                flickableItem: logListView
            }
        }
    }



}
