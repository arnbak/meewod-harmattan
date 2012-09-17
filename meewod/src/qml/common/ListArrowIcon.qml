import QtQuick 1.1

Image {
    source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "")
    anchors.right: parent.right;
    anchors.verticalCenter: parent.verticalCenter
}
