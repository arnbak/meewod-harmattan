import QtQuick 1.1
import com.nokia.meego 1.0

import "../common"
import "../pages"
import "../delegates"
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
                createRecordItemPage.selectedIndex = -1;
                createRecordItemPage.open();
            }

        }
    }

    RefreshableHeader {
        id: header
        text: qsTr("Personal Records");
        subtext: qsTr("Keep track of your progress");
        showindicator: false
    }

    ListView {
        id: listView
        model: recordListModel

        contentHeight: listView.height - header.height

        anchors {
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        clip: true

        delegate: RecordListDelegate {
            id: listItem

            onClicked: {

                createRecordItemPage.selectedIndex = index;
                createRecordItemPage.item = recordListModel.getItem(index);
                //console.log(recordListModel.getItem(index).uid);
                createRecordItemPage.open();
                //console.log("hi")
            }

            onPressAndHold: {
                console.log("hi 2")
            }


        }
    }





}





