import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: mediaTextMessage

    property var name

    property var vectorImage
    property var vectorMusic
    property var vectorVideo
    property var vectorObject



    property bool isOneMessge: false

    property int dfltHeight: 230
    property int dfltWidth: 300
    property color noColor: "#00000000"

    property int countAttachment: 1
    property int heightAttachment: 230

    property int calcHeightText

    property int calcHeight: (sizeOneLineHeight + 1) * textMessage.lineCount

    //    property int heightmulimedua: 230

    property bool flagWhenMessage1: true
    property string messageText: "Ay"

    property string attachmentFileName: "filename.wmv"

    property real customOpacity: 0.7

    property int fontSize: 12

    //~~~~~~~~~~~~~~~~~Color~~~~~~~~~~~~~~~~~~~~~~~~
    property color enemyColor: "gray"
    property color selfColor: "#068d9d"
    property color selfColorText: "#ffffff"
    property color enemyColorText: "#000000"

    //~~~~~~~~~~~~~~~~~~Width~~~~~~~~~~~~~~~~~~~~~~~
    property real sizeOnePXWidth: 5
    property int sizeMessage: 10

    //~~~~~~~~~~~~~~~~~~Height~~~~~~~~~~~~~~~~~~~~~~~
    property int sizeOneLineHeight: 14
    property int dfltHeightText: 36
    property int dfltHeightRect: 50
    property int dfltHeightMul: 200
    property var contentImg

    property int countImg: 0
    property int countVid: 0
    property int countAud: 0
    property int countText: 0

    anchors.leftMargin: 7
    anchors.rightMargin: 7

    anchors.right: {
        if (flagWhenMessage1)
        {
            parent.right
        }
    }

    anchors.left: {
        if (!flagWhenMessage1)
        {
            parent.left
        }
    }

    width: dfltWidth
    height: dfltHeightMul  + textMessage.height + 24

    color: "transparent"/*flagWhenMessage ? selfColor : enemyColor*/
    radius: 15

//        border.color:  "black"
//        border.width: 1

    Column {
        id: columnMaskMedia
        //            x: 0
        //            y: 35

        spacing: 10
//        visible: messageText !=""
        Rectangle {
            id: maskTextMessage
            width: dfltWidth
            height: {
                if (textMessage.lineCount == 1 || textMessage.lineCount == 2)
                {
                    dfltHeightRect
                    calcHeightText = dfltHeightRect
                }
                else
                {
                    calcHeight + 14
                    calcHeightText = calcHeight + 14
                }
            }
            color: /*selfColor*/flagWhenMessage1 ? selfColor : enemyColor
            radius: 10

            MouseArea{
                anchors.fill: parent
                onClicked: {
//                    isOneMessge = !isOneMessge
                }
            }

            Text {
                id: textMessage
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                //        width: 100
                height: {
                    if (calcHeight < 50)
                    {
                        dfltHeightText - 10
                    }
                    else
                    {
                        calcHeight
                    }
                }

                text: messageText
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                //                leftPadding: 10
                color: flagWhenMessage1 ? selfColorText : enemyColorText

                wrapMode: Text.Wrap
            }
        }



        Repeater{
            id: repImg
            model: countImg

            PictureWidget{
                sourcePicture: "file:///" +currentDir+"/" +vectorImage[index]
                fontMsgColor: flagWhenMessage1 ? selfColor : enemyColor
                Component.onCompleted: {
                    console.log("PictureWidget", sourcePicture)
                    console.log("flagWhenMessage1", flagWhenMessage1)
                    console.log("fontMsgColor", fontMsgColor)
                }
            }

        }

        Repeater{
            id: repAudio
            model: countAud
            AudioWidget{
                filePath: "file:///" +currentDir+"/" +vectorMusic[index]
                fontMsgColor: flagWhenMessage1 ? selfColor : enemyColor

                Component.onCompleted: {
                    console.log("flagWhenMessage", flagWhenMessage1)
                    console.log("fontMsgColor", fontMsgColor)
                }
            }
        }

        Repeater{
            id: repText
            model: countText

            TextWidget{
                sourceText: /*"file:///" +currentDir+"/" +*/vectorObject[index]
                fontMsgColor: flagWhenMessage1 ? selfColor : enemyColor
                Component.onCompleted: {
                    console.log("flagWhenMessage", flagWhenMessage1)
                    console.log("fontMsgColor", fontMsgColor)
                }
            }
        }

        Repeater{
            id: repVideo
            model: countVid
            MediaWidget{
                fileNameText: "file:///" +currentDir+"/" +vectorVideo[index]
                fontMsgColor: flagWhenMessage1 ? selfColor : enemyColor
                Component.onCompleted: {
                    console.log("flagWhenMessage", flagWhenMessage1)
                    console.log("fontMsgColor", fontMsgColor)
                }
            }
        }
        Rectangle {
            id: timeMask
            width: dfltWidth
            height: 24
            color: noColor
        }

    }


    //        Repeater{
    //            id: repeaterMediaGroup

    //            anchors.fill: parent
    //            model: 4

    //            Rectangle {
    //                id: mediaMask
    //                width: dfltWidth
    //                height: 230
    //                color: noColor

    //                MediaWidget{
    //                    anchors.fill: parent
    //                    fileNameText: attachmentFileName
    //                }
    //            }
    //        }


}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}D{i:7;locked:true}
}
##^##*/
