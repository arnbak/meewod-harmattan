import QtQuick 1.1
import com.nokia.meego 1.0

BusyIndicator {
    id: indicator
    anchors.centerIn: parent
    platformStyle: BusyIndicatorStyle { size: "large" }
    running: true
}
