import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../common"
import "../pages"
import "../js/UIConstants.js" as UIConstants
import "../js/constants.js" as ExtrasConstans

Page {
    id: benchmarkWorkoutsPage

    BenchmarkWorkoutDetailPage { id: benchmarkWorkoutTextPage }

    property bool networkRequestRunning: false

    tools: ToolBarLayout {
        id: toolBar
        visible: true

        BackIcon {}
    }

    function refresh() {
        if(!networkRequestRunning) {
            benchmarkListModel.requestList();
            networkRequestRunning = true;
        }
    }

    RefreshableHeader {
        id: header
        text: qsTr("Benchmark Workouts")
        subtext: qsTr("Everything is hard until its easy")

        loading: networkRequestRunning

        onClicked: {
            refresh();
        }
    }

    TextField {
        id: searchField

        anchors {
            top: header.bottom
            //top: parent.top
            left: parent.left
            right: parent.right
            topMargin: UIConstants.DEFAULT_MARGIN
            leftMargin: UIConstants.DEFAULT_MARGIN
            rightMargin: UIConstants.DEFAULT_MARGIN
        }

        placeholderText: qsTr('Search')
        inputMethodHints: Qt.ImhNoPredictiveText

        onTextChanged: searchTimer.start()

        Image {
            id: clearSearchText
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: (searchField.activeFocus || searchField.text) ?
                        'image://theme/icon-m-input-clear' :
                        'image://theme/icon-m-common-search'
        }

        MouseArea {
            anchors.fill: clearSearchText

            onClicked: {
                inputContext.reset()
                searchField.text = ''
            }
        }

        Timer {
            id: searchTimer
            interval: 50
            running: false
            repeat:  false

            onTriggered: {
                //console.log("search filter")
                benchmarkListModel.setFilterWildcard(searchField.text)
            }
        }
    }

    ListView {
        id: benchmarkListView
        anchors {
            top: searchField.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            topMargin: UIConstants.DEFAULT_MARGIN
        }
        model: benchmarkListModel
        keyNavigationWraps: true
        clip: true

        section.property: 'name'

        delegate: Item {
            id: listItem
            height: 90
            width: parent.width

            ListItemBackground {
                id: background
                //anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
                //anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
                visible: mouseArea.pressed
            }

            //            Separator {
            //                anchors.leftMargin: -UIConstants.DEFAULT_MARGIN
            //                anchors.rightMargin: -UIConstants.DEFAULT_MARGIN
            //            }

            Row {
                anchors.fill: parent
                anchors.margins: UIConstants.DEFAULT_MARGIN

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width

                    LabelTitle {
                        id: mainText
                        text: name
                    }

                    LabelSubtitle {
                        id: subText
                        text: type
                        visible: text != ""                        
                    }
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
                        benchmarkWorkoutTextPage._workoutid = id;
                        benchmarkWorkoutTextPage._type = type;
                        benchmarkWorkoutTextPage._name = name;
                        benchmarkWorkoutTextPage._description = description;
                        benchmarkWorkoutTextPage._wodtext = wodtext;

                        pageStack.push(benchmarkWorkoutTextPage);
                    }
                }
            }
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {

            if (benchmarkListModel.count === 0) {                
                refresh();
            }

        } else if (status === PageStatus.Inactive) {
            // In this case the page is no longer visible:
            // Stop all the resource-consuming activities like camera, video playback,
            // sensors, gps access, and so on. In general, there should be no activity in
            // case of most of the applications.
            // indicator.running = false
            console.log("inactive");
            //benchmarkListModel.persist();h
        }
    }

//    BusyIndicator {
//        id: busyIndicator
//        visible: networkRequestRunning
//        running: visible
//        platformStyle: BusyIndicatorStyle { size: 'large' }
//        anchors.centerIn: parent
//    }

    FastScroll {
        listView: benchmarkListView
    }

    InfoBanner {
        id: benchmarkActivityInfoBanner
        topMargin: UIConstants.DEFAULT_MARGIN
        leftMargin: UIConstants.DEFAULT_MARGIN
        parent: benchmarkWorkoutsPage
    }

    ConfirmDialog {
        id: confirmRefresh
        titleText: qsTr("Reload?")

        message: qsTr("Do you want to download all benchmark workouts again ?")

        onAccepted: {
            refresh();
        }
    }

    Connections {
        target: benchmarkListModel

        onBenchmarkListError: {
            networkRequestRunning = false;
            benchmarkActivityInfoBanner.text = message;
            benchmarkActivityInfoBanner.show();
        }

        onBenchmarkListUpdated: {
            networkRequestRunning = false;

            benchmarkActivityInfoBanner.text = "Fetched Benchmark Workouts";
            benchmarkActivityInfoBanner.show();
        }

    }

}
