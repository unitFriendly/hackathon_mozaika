import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.2

Rectangle {
    id: downBar

    property int dfltWidth: 506
    property int dfltHeight: 56

    property color enemyColor: "gray"
    property color biruzoviu: "#068d9d"
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property int fontSize: 12
    property var filesSelected:[]

    //    property var currentDialogDownBar: -1

    function sendMesage()
    {
        var textMessage = writeMessage.text

        console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", textMessage)

        //        testMap.createNewMessage(writeMessage.text, true);

        //        var tmpMessage = newMassege.createObject(columnChat,
        //                                                 {
        //                                                     sizeMessage:  clientData.getLength(textMessage),
        //                                                     messageText: textMessage,
        //                                                     flagWhenMessage: true,
        //                                                     messageTime: "15:13",
        //                                                     messageStatus: 2,
        //                                                     file: filesSelected
        //                                                 });

        //        contactsss.setCountIndexMessage(contactsss.getCountIndexMessage());
        writeMessage.clear();
        //                    testMap.createNewMessage("My answer", false);
        //                    contactsss.setCountIndexMessage(contactsss.getCountIndexMessage());
        console.log("Сообщение отправлено в диалог >>>", currentDialogOpen)

        var tmpIdMsg = client.generateTmpIdMsg();
        //        var dialogID = clientData.getIdDialog(currentDialogOpen)

        if(textMessage=="")
            textMessage="файлы"

        client.addMessage(currentDialogOpen, tmpIdMsg, textMessage, filesSelected);
        client.sendMessage(currentDialogOpen, tmpIdMsg, textMessage, filesSelected);

        chatDialog.scrollToBottom();

    }


    FileDialog {
        id: fileOpenDialog
        //            fileMode
        title: "Select an image file"
        folder: shortcuts.documents
        selectMultiple: true
        //            nameFilters: [
        //                "Image files (*.png *.jpeg *.jpg)",
        //            ]
        onAccepted: {
            //                image.source = fileOpenDialog.fileUrl


            //                var tmpList=[]
            //                filesSelected = fileOpenDialog.fileUrls;
            var tmp=[]
            for(var i=0;i<fileOpenDialog.fileUrls.length;i++){
                tmp.push(fileOpenDialog.fileUrls[i])
            }
            filesSelected=tmp;
            sendMesage()

            console.log(filesSelected)
        }
    }


    width: dfltWidth
    height: dfltHeight
    color: noColor
    opacity: customOpacity

    Rectangle {
        id: dontKnowButton
        x: 14
        y: 4
        width: 49
        height: 48
        color: biruzoviu
        radius: 5

        Image {
            id: image
            x: 5
            y: 5
            width: 39
            height: 38
            //            anchors.fill: parent
            source: "qrc:/resourses/chat/treugol`nik.tif"
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            rotation: 180
            fillMode: Image.PreserveAspectFit

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    console.log("Я не понимаю, что это такое сука...")
                }
            }
        }
    }

    Rectangle {
        id: chooseFile
        x: 69
        y: 4
        width: 49
        height: 48
        color: mouseScrepka.containsPress ? Qt.lighter(biruzoviu) : biruzoviu
        radius: 5

        Image {
            id: image1
            x: 5
            y: 5
            width: 39
            height: 38
            //            anchors.fill: parent
            source: "qrc:/resourses/chat/prikrepit`.tif"
            fillMode: Image.PreserveAspectFit
            scale: mouseScrepka.containsPress ? 1.2 : 1
            MouseArea{
                id: mouseScrepka
                anchors.fill: parent

                onClicked: {

                    fileOpenDialog.open()

                    console.log("Выберите файл")
                }
            }
        }
    }

    TextField {
        id: writeMessage
        x: 124
        y: 4
        width: 319
        height: 48
        placeholderText: qsTr("Написать сообщение...")

        selectByMouse: true
        color: "#ffffff"
        opacity: 1

        background: Rectangle {
            anchors.fill: parent
            color: biruzoviu
            radius: 7

        }
    }

    Rectangle {
        id: sendFileOrMessage
        x: 449
        y: 4
        width: 49
        height: 48
        color: sendMessageMouse.containsPress ? Qt.lighter(biruzoviu) : biruzoviu
        radius: 5
        focus: true
        Image {
            id: image2
            x: 5
            y: 5
            width: 39
            height: 38
            source: "qrc:/resourses/chat/otpravit`.tif"
            fillMode: Image.PreserveAspectFit
            opacity: 1
            scale: sendMessageMouse.containsPress ? 1.2 : 1

            MouseArea{
                id: sendMessageMouse
                anchors.fill: parent

                onClicked: {
                    downBar.sendMesage()
                    //                      testMap.emitMultiWidget()
                    //                    testMap.getMediaMessage()
                }
            }
        }

        Keys.onEnterPressed: {

            downBar.sendMesage()
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}D{i:3}D{i:6}
}
##^##*/
