import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0

import "../js/constants.js" as Constants


Label {
    id: labelTitle

    font.family: Constants.FONT_FAMILY
    font.pixelSize: Constants.LIST_TILE_SIZE

    color: theme.inverted ?
               Constants.LIST_TITLE_COLOR_INVERTED :
               Constants.LIST_TITLE_COLOR

    width: parent.width
    wrapMode: Text.WordWrap
}

//RatingIndicator {
//    id: ratingIndicator
//    //anchors.left: mainText.right
//    maximumValue: 5
//    ratingValue: 3
//    inverted: theme.inverted
//}


