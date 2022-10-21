import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12

Rectangle{
    id: messageMultimedia
    property var fontMsgColor

    width: 300
    height: 200
    color: fontMsgColor
//    border.color: "white"
//    border.width: 1
    radius: 10



//    property bool flagWhenMessage: false

    property string fileNameText: "video.mp4"

    property int customHeight: 200



    anchors.right: {
        if (flagWhenMessage1)
            parent.right

    }
    anchors.left: {
        if (!flagWhenMessage1)
            parent.left
    }

    property bool isPlay: true

    Rectangle{
        id: videoMesageMask
        width: parent.width
        height: customHeight
        anchors.fill: parent
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        color: noColor
        Video{
            id: videoMessage
            anchors.top: parent.top
            width: parent.width - 20
            height: parent.height - 20
            anchors.horizontalCenter: parent.horizontalCenter

            source: fileNameText

            MouseArea{
                anchors.fill: parent

                onClicked: {


                }
            }
        }

        MouseArea{
            id: mouseContent
            anchors.fill: parent

            hoverEnabled: true

            onClicked: {

            }
        }
    }

    //    Rectangle{
    //        anchors.fill: parent
    //        color: "gray"
    //        opacity: mouseShtorka.containsMouse ? 0.3 : 0
    //        width: parent.width
    //        height: parent.height

    //        MouseArea{
    //            id: mouseShtorka

    //            hoverEnabled: true
    //            anchors.fill: parent
    //        }
    //    }

    ToolTipVideo {
        height: parent.height
        width: parent.width
        visible: mouseContent.containsMouse ? true : false

    }

    //    Rectangle{
    //        x: 0
    //        y: customHeight
    //        width: parent.width
    //        height: 30
    //        color: noColor
    ////        border.width: 1
    ////        border.color: "black"
    //        Text{
    //            x: 0
    //            y: 0
    //            width: customHeight
    //            height: 30
    //            text: fileNameText
    //            elide: Text.ElideRight
    //            verticalAlignment: Text.AlignVCenter
    //            leftPadding: 10
    //        }

    //        MouseArea{
    //            anchors.fill: parent

    //            onClicked: {

    //            }
    //        }
    //    }
//    Separator{
//        anchors.top: parent.bottom
//    }



    Component.onCompleted: {
        videoMessage.play()
        videoMessage.pause()
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}
}
##^##*/
