import QtQuick 1.1

BorderImage {
    anchors.fill: parent
    visible: mouseArea.pressed
    source: 'image://theme/meegotouch-list-fullwidth-'+(theme.inverted ? "inverted-" : "")+'background-pressed-vertical-center'
}
