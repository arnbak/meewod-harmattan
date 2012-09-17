import QtQuick 1.1
import com.nokia.meego 1.0

import "../common"
import "../js/UIConstants.js" as UIConstants

Page {
    anchors.margins: UIConstants.DEFAULT_MARGIN
    anchors.topMargin: header.height

    tools: ToolBarLayout {
        id: tabBarLayout
        visible: true

        BackIcon {}
    }

//    PageHeader {
//        id: header
//        title: "Profil"
//    }
}
