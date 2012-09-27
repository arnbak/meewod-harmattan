import QtQuick 1.1
import com.nokia.meego 1.0

import "../common"
import "../delegates"
import "../js/tools.js" as MWT
import "../js/UIConstants.js" as UIConstants

Page {
    id: settingsPage

    tools: ToolBarLayout {
        id: tabBarLayout
        visible: true

        BackIcon {}
    }

    PageHeader {
        id: header
        text: qsTr("Settings")
    }

    Item {
        id: profileSettings
        height: 90
        width: parent.width
        visible: false

        anchors.top: header.bottom

        ListItemBackground {
            id: background
            visible: mouseArea.pressed
        }

        Row {
            //anchors.fill: parent

            anchors {
                fill: parent
                leftMargin: UIConstants.DEFAULT_MARGIN
                rightMargin: UIConstants.DEFAULT_MARGIN
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width

                LabelTitle {
                    id: mainText
                    text: qsTr("Profile")
                }

                LabelSubtitle {
                    id: subText
                    text:qsTr("Profile settings")
                }
            }
        }

        ListArrowIcon { }

        MouseArea {
            id: mouseArea
            anchors.fill: background
            onClicked: {

                MWT.createPageComponentAndPushToStack("../pages/ProfileSettingsPage.qml")

            }
        }
    }


    SectionRightTextDelegate {

        id: themeSettingsSection

        sectionName: qsTr("Theme Settings")

        anchors {
            top: profileSettings.visible ? profileSettings.bottom : header.bottom

            leftMargin: UIConstants.DEFAULT_MARGIN
            rightMargin: UIConstants.DEFAULT_MARGIN

        }
    }

    ButtonRow {
        id: themeSelection

        anchors {
            top: themeSettingsSection.bottom
            left: parent.left
            right: parent.right
            leftMargin: UIConstants.DEFAULT_MARGIN
            rightMargin: UIConstants.DEFAULT_MARGIN
        }

        Button {
            id: blackSelection
            text: qsTr("Black")
            checked: theme.inverted
            onClicked: {
                theme.inverted = true;
                Settings.setValue("theme-inverted", theme.inverted);
            }
        }

        Button {
            id: whiteSelection
            text: qsTr("White")
            checked: !theme.inverted
            onClicked: {
                theme.inverted = false;
                Settings.setValue("theme-inverted", theme.inverted);
            }
        }
    }

}


