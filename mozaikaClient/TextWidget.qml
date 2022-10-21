import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.2

Rectangle {
    id: textWidget

    property var sourceText
    property var fontMsgColor

    FileDialog{
        id: fileDialog
        selectFolder: true
        onAccepted: {
            console.log("filedialog")

            var path = fileDialog.folder;
            clientData.saveFile(sourceText, path);
        }

    }

    width: 300
    height: 50

    color: fontMsgColor
    //    opacity: 0.7
    radius: 10
    //    border.color: "white"
    //    border.width: 1

    Text {
        color: "#ffffff"
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.rightMargin: 8
        anchors.bottomMargin: 8
        anchors.leftMargin: 52
        anchors.topMargin: 8
        font.underline: true
        font.bold: true
        font.pointSize: 16
        text: clientData.getFileNameWithoutPath(sourceText)
        elide: Text.ElideRight
    }

    //    Separator{
    //        anchors.top: parent.bottom
    //    }

    Rectangle {
        id: rectangle
        x: 12
        y: 8
        width: 34
        height: 34
        color: "#ffffff"
        radius: 17

        Image {
            id: download
            x: 0
            y: 0
            width: 34
            height: 34
            source: "picture/download.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {
            fileDialog.open()
        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/
