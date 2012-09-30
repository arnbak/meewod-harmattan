import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../common"
import "../pages"
import "../delegates"
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstans
import "../js/tools.js" as MWT

Page {
    id: dailyPage
    anchors.fill: parent

    AboutDialog { id: aboutDialog }

    property bool networkRequestRunning: false

    Menu {
        id: settingsMenu

        MenuLayout {

            //            MenuItem {
            //                text: qsTr("Log in")
            //                visible: false
            //                enabled: visible
            //            }

            MenuItem {
                text: qsTr("Settings")
                visible: true
                enabled: visible
                onClicked: {
                    MWT.createPageComponentAndPushToStack("../pages/SettingsPage.qml");
                }
            }

            MenuItem {
                text: qsTr("About")
                onClicked: {
                    aboutDialog.open();
                }
            }
        }
    }

    tools: ToolBarLayout {
        id: toolBar
        visible: true

        BackIcon {
            id: disabledBack
            enabled: false
        }

        //        ToolIcon {
        //            id: refreshIcon
        //            anchors.left: disabledBack.right
        //            iconId: "toolbar-refresh"
        //            onClicked: {
        //                confirmRefresh.open();
        //            }
        //        }

        ToolIcon {
            id: createLogItemIcon
            anchors.right: createPersonalRecordIcon.left
            iconId: "toolbar-history"
            onClicked: {
                MWT.createPageComponentAndPushToStack("../pages/LogPage.qml");
            }
        }

        ToolIcon {
            id: createPersonalRecordIcon
            anchors.right: benchmarksIcon.left
            iconId: "toolbar-contact"
            onClicked: {
                MWT.createPageComponentAndPushToStack("../pages/RecordPage.qml");
            }
        }

        ToolIcon {
            id: benchmarksIcon
            anchors.right: settingsIcon.left
            iconId: "toolbar-clock"
            onClicked: {
                MWT.createPageComponentAndPushToStack("../pages/BenchmarkWorkoutPage.qml");
            }
        }

        ToolIcon {
            id: settingsIcon
            iconId: "toolbar-view-menu"
            onClicked: (settingsMenu.status === DialogStatus.Closed) ? settingsMenu.open() : settingsMenu.close()
            anchors.right: parent === undefined ? undefined : parent.right
        }
    }

    ConfirmDialog {
        id: confirmRefresh

        titleText: qsTr("Reload")

        message: qsTr("Do you wan't to fetch the daily workout from crossfit.com ?")

        onAccepted: {
            refresh();
        }
    }

    RefreshableHeader {
        id: header
        text: qsTr("Daily WOD's")
        subtext: qsTr("Daily Workouts From Crossfit.com")

        loading: networkRequestRunning;

        onClicked: {
            refresh();
        }
    }

    ListView {
        id: listView
        model: dailyListModel

        contentHeight: listView.height - header.height

        anchors {
            top: header.bottom            
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        x: 0;

        cacheBuffer: 100;

        //section.delegate: SectionHeader {}
        section.property: 'published'

        delegate: DailyListDelegate {
            id: listItem
        }
    }

    function refresh () {
        if(!networkRequestRunning) {
            dailyListModel.requestList();
            networkRequestRunning = true;
        }
    }

    FastScroll {
        listView: listView
    }

    InfoBanner {
        id: dailyPageInfoBanner
        topMargin: UIConstants.DEFAULT_MARGIN
        leftMargin: UIConstants.DEFAULT_MARGIN
        parent: dailyPage
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {

            //            if (dailyListModel.count === 0) {
            //                confirmRefresh.open();
            //            }

        } else if (status === PageStatus.Inactive) {
            // In this case the page is no longer visible:
            // Stop all the resource-consuming activities like camera, video playback,
            // sensors, gps access, and so on. In general, there should be no activity in
            // case of most of the applications.
            // indicator.running = false
            //console.log("inactive");
            //benchmarkListModel.persist();h
        }
    }

    Connections {
        target: dailyListModel

        onListError: {
            networkRequestRunning = false;
            dailyPageInfoBanner.text = message;
            dailyPageInfoBanner.show();
        }

        onListFetched: {
            networkRequestRunning = false;
            dailyPageInfoBanner.text = "Daily workouts fetched"
            dailyPageInfoBanner.show();
        }
    }
}
