import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12

Rectangle{
    id: messageMultimedia

    color: "gray"

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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


   // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    property var contentImg
    property var countVid
    property var countAud
    property var countText


    property int countImg: 0
    property int countVid: 0
    property int countAud: 0
    property int countText: 0

    property var messageText: "Шаблонsadsadasdsadsad adasdsadasd asdasdasdasd asdasdasda asdasdasd asdasdasdas asdasdasdas"

    property bool flagWhenMessage: true
    property string fileNameText

    property int customHeight: 200

    property color noColor: "#00000000"

    property int dfltWidth: 300
    property int dfltHeightMul: 230

    property int calcHeightText

    property int calcHeight: (sizeOneLineHeight + 1) * textMessage.lineCount

    width: dfltWidth
    height: dfltHeightMul

    anchors.right: {
        if (flagWhenMessage)
            parent.right

    }
    anchors.left: {
        if (!flagWhenMessage)
            parent.left
    }

    property bool isPlay: true

    Column{
        id: allFiles
        anchors.fill: parent
        spacing: 2

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
            color: noColor

            Text {
                id: textMessage
                anchors.fill: parent
                //                anchors.right: parent.right
                //                anchors.left: parent.left
                //                anchors.bottom: timeMessage.top
                //                anchors.top: parent.top
                //        anchors.topMargin: 10
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
                color: flagWhenMessage ? selfColorText : enemyColorText

                wrapMode: Text.Wrap
            }
        }

        Repeater{
            id: repImg
            model: countImg

            PictureWidget{

            }
        }

        Repeater{
            id: repAudio
            model: countAud

            AudioWidget{

            }
        }

        Repeater{
            id: repText
            model: countText
            TextWidget{
                sourceText: "Ghbdtn!"
            }
        }

        Repeater{
            id: repVideo
            model: countVid

            MediaWidget{

            }
        }
    }
}

//    Rectangle{
//        width: parent.width
//        height: customHeight
//        color: "gray"
//        visible: mouseContent.containsPress ? false : true
//        opacity: 0.3


//    }

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
//            text: fileNameText + "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"
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




/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}
}
##^##*/
