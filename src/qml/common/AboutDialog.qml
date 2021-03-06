import QtQuick 1.1
import com.nokia.meego 1.0

QueryDialog {
    id: aboutDialog

    icon: 'qrc:/resources/meewodicon64.png'

    titleText: qsTr("About MeeWOD");

    message: "Version " + Settings.getValue("appversion") +
             "\nBy Lars Arnbak" +
             "\nContact: arnbak@gmail.com" +
             "\n" +
             "\nMeeWOD is a Crossfit tracking application for your Nokia N9" +
             "\n" +
             "\nLicensed under GPL v3 at: " +
             "\ngithub.com/arnbak/meewod-harmattan"

    acceptButtonText: "Ok"
}
