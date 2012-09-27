import QtQuick 1.1
import com.nokia.meego 1.0

import "../js/constants.js" as ExtrasConstants

Label {
    id: labelSubtitle
    font.family: ExtrasConstants.FONT_FAMILY_LIGHT
    font.pixelSize: ExtrasConstants.LIST_SUBTILE_SIZE
    color: theme.inverted ?
               Settings.getValue("LIST_SUBTITLE_COLOR_INVERTED") :
               Settings.getValue("LIST_SUBTITLE_COLOR")

    width: parent.width
    wrapMode: Text.WordWrap
}
