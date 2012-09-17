import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../common"
import "../pages"
import "../delegates"
import "../js/UIConstants.js" as UIConstants

Page {
    id: logListPage

    LogCreateUpdatePage { id: createLogItemPage }

    property bool networkRequestRunning: false

    anchors.fill: parent

    Menu {
        id: logSettingsMenu

        MenuLayout {

            MenuItem {
                text: qsTr("Back Up")
                onClicked: {
                    confirmUpload.open();
                }
            }
        }
    }

    tools: ToolBarLayout {
        id: toolBar
        visible: true

        BackIcon {
            id: backButtonIcon
        }

        CreateIcon {
            id: createLogItemIcon
            onClicked: {
                createLogItemPage.currentIndex = -1;
                createLogItemPage.open();
            }
            anchors.right: parent.right
        }

//        ToolIcon {
//            id: logMenuIcon
//            iconId: "toolbar-view-menu"
//            onClicked: (logSettingsMenu.status === DialogStatus.Closed) ? logSettingsMenu.open() : logSettingsMenu.close()
//            anchors.right: parent === undefined ? undefined : parent.right
//        }
    }



    PageHeader {
        id: header
        text: qsTr("Workout Log")
    }

    ListView {
        id: logListView

        anchors {
            top: header.bottom            
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        model: logListModel

        contentHeight: logListView.height - header.height

        keyNavigationWraps: true

        clip: true

        x: 0;

        cacheBuffer: 100;

        section.property: 'date'

        delegate: Item {
            id: listItem
            height: 90
            width: parent.width

            ListItemBackground {
                id: background
                visible: mouseArea.pressed
            }

            Row {
                anchors.fill: parent
                anchors.margins: UIConstants.DEFAULT_MARGIN

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width

                    LabelTitle {
                        id: mainText
                        text: logname
                    }

                    RatingIndicator {
                        id: ratingIndicator
                        //anchors.verticalCenter: parent.verticalCenter
                        //anchors.right: parent.right
                        maximumValue: 5
                        ratingValue: 2
                        inverted: false
                    }

                    LabelSubtitle {
                        id: subText
                        text: logdate
                    }
                }
            }



            ListArrowIcon {
                id: listArrow
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

    }

    FastScroll {
        listView: logListView
        enabled: true;
        visible: logListModel.count > 15
        clip: true
    }

    ScrollDecorator {
        flickableItem: logListView
        enabled: true
        visible: logListModel.count < 15
    }

    ConfirmDialog {
        id: confirmUpload
        titleText: qsTr("Backup?")

        message: qsTr("Do you want to backup your log items?\nThis will make it possible to access your items from other devices..")

        onAccepted: {
            console.log("on accepted");
//            logListModel.syncListWithRemote();
//            networkRequestRunning = true;
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {
            // In our example we know that the page is now visible,
            // activate normal state of operations:
            // start up whatever is stopped when page becomes inactive
            //indicator.running = true
            console.log("active");
        }
        else if (status === PageStatus.Inactive) {
            // In this case the page is no longer visible:
            // Stop all the resource-consuming activities like camera, video playback,
            // sensors, gps access, and so on. In general, there should be no activity in
            // case of most of the applications.
            //indicator.running = false
            console.log("inactive");
            logListModel.persist();
        }
    }

    InfoBanner {
        id: logListInfoBanner
        topMargin: UIConstants.DEFAULT_MARGIN
        leftMargin: UIConstants.DEFAULT_MARGIN
        parent: logListPage
    }

    BusyIndicator {
        id: busyIndicator
        visible: networkRequestRunning
        running: visible
        platformStyle: BusyIndicatorStyle { size: 'large' }
        anchors.centerIn: parent
    }

    Connections {
        target: logListModel

        onListItemsBackedUp: {
            networkRequestRunning = false;

            logListInfoBanner.text = "Items backed up";
            logListInfoBanner.show();
        }

        onListItemsBackUpError: {
            networkRequestRunning = false;
            logListInfoBanner.text = "Error requesting service";
            logListInfoBanner.show();
        }
    }

}
