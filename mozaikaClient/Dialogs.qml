import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: rootDialog
    width: dfltWidth
    height: dfltHeight

    property int dfltWidth: 446
    property int dfltHeight: 100
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property int indexInListDialogs: -1
    color: rootDialog.noColor

    anchors.horizontalCenter: parent.horizontalCenter

    property var nameFamilia

    property var avatarClients:"qrc:/resourses/avatar/cop.tif"

    property var timeMessage: "Когда-то"

    property var lastMessageUser

    property var isChecked

    property var isGroup

    property var countUnChecked

    property var isOnline

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //много проверти для забирания данных с класса user и message


    //    property type name: value
    //    property type name: value
    //    property type name: value
    //    property type name: value


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Image {
//        id: image
//        anchors.fill: parent
//        source: "qrc:/resourses/kontacti/uvedomlenie_o_soobshenii.tif"
//        opacity: rootDialog.customOpacity
//    }

    Rectangle{
//    function loadChat(){

//    }


        id: image
        anchors.fill: parent
        color: "white"
        opacity: rootDialog.customOpacity
        radius: 20
//        border.width: 3
//        border.color: !isChecked ? "white" : "black"
    }

    //общий
    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: rootDialog.noColor


        Rectangle {
            id: rectangle1
            x: 99
            y: 0
            width: 280
            height: 50
            color: rootDialog.noColor

            Text {
                id: textNameDialog
                x: 0
                y: 0
                width: 280
                height: 50
                text: nameFamilia
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                font.weight: Font.Bold
            }
        }

        Rectangle {
            id: rectangle2
            x: 99
            y: 50
            width: 280
            height: 50
            color: rootDialog.noColor

            Text {
                id: textMessage
                x: 0
                y: 0
                width: 280
                height: 50
                font.pixelSize: 12
                text: lastMessageUser
                elide: Text.ElideRight
                font.bold: !isChecked
                verticalAlignment: Text.AlignTop
                textFormat: Text.AutoText
                clip: false
            }
        }

        Rectangle {
            id: rectangle3
            x: 360
            y: 78
            width: 87
            height: 22
            color: rootDialog.noColor

            Text {
                id: text3
                x: -8
                text: timeMessage
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                anchors.rightMargin: 20
            }
        }
        Rectangle{
            id: mask
            x: 0
            y: 0
            width: 100
            height: 100
            color: rootDialog.noColor
            clip: true

            Rectangle{
                width: parent.width - 30
                height: parent.height - 30
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                radius: 35
                border.width: 1
                border.color: "#068d9d"
                clip: true


                Image {
                    id: image1
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    source: avatarClients
//                    anchors.rightMargin: 8
//                    anchors.bottomMargin: 7
//                    anchors.leftMargin: 8
//                    anchors.topMargin: 8

                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: parent
                    }
                }
            }                //                    fillMode: Image.PreserveAspectCrop
        }

        Rectangle {
            id: rectangle4
            x: 379
            y: 0
            width: 67
            height: 78
            color: rootDialog.noColor
        }

        Rectangle {
            id: msgIsCheked
            x: 391
            y: 17
            width: 44
            height: 44
            color: "#068d9d"
            radius: 7
            visible: !isChecked

            Text {
                id: msgIsChekedText
                x: -12
                y: -17
                color: "#ffffff"
                text: countUnChecked
                anchors.fill: parent
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: msgIsOnline
            x: 22
            y: 69
            width: 12
            height: 12
            color: "#068d9d"
            radius: 6
            visible: isOnline
        }

    }
    MouseArea{
        anchors.fill: parent

        onClicked: {


            //            userChatObject.currentDialog = index
            currentDialogOpen = clientData.getIdDialog(indexInListDialogs)
            client.sendReadAllMessageByChat(currentDialogOpen)
            client.getMessagesInDialog(clientData.getIdDialog(indexInListDialogs))




            loader.sourceComponent  = userChat;
            console.log("Открыть диалог с данным юзером" + indexInListDialogs)
        }
    }

    Component.onCompleted: {


    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:2}D{i:8}
}
##^##*/
