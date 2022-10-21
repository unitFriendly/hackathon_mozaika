import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: chatDialog

    property int dfltWidth: 506
    property int dfltHeight: 900
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property int heightToolBar: 60
    property int countIndexVessage: 0

    property int fontSize: 14

    property var newMassege

    property var newMediaMessage

    property var str: "Здравствуйте, товарищи! Это лучший месснджер написанный 5 научной ротой в Инновационном Военном Технополисе ЭРА"









    function scrollToBottom()
    {
        scrollChat.ScrollBar.vertical.position = 1 - scrollChat.ScrollBar.vertical.size
    }




    property var musicW
    property var imgW
    property var textW
    property var universalMedia


    function createEveryThingMessage(vectorImage, vectorMusic, vectorVideo, vectorObject, textMsg, isSender)
    {
        console.log("createEveryThingMessage", vectorImage, vectorMusic, vectorVideo, vectorObject, textMsg, isSender, vectorImage.length)
        var heighttextWidget = 50
        var heightvideoWidget = 200
        var heightaudioWidget = 50
        var heightpictureWidget = 170
        var he = heighttextWidget*vectorObject.length +
                heightvideoWidget *vectorVideo.length+
                heightaudioWidget*vectorMusic.length+
                heightpictureWidget*vectorImage.length
        console.log(he)
        var tmp = newMediaMessage.createObject(columnChat,
                                               {
                                                   flagWhenMessage1: isSender,
                                                   countImg: vectorImage.length,
                                                   countAud: vectorMusic.length,
                                                   countVid: vectorVideo.length,
                                                   countText: vectorObject.length,
                                                   sizeMessage: clientData.getLength(textMsg),
                                                   messageText: textMsg,
                                                   dfltHeightMul: he,
                                                   vectorImage:   vectorImage,
                                                   vectorMusic:   vectorMusic,
                                                   vectorVideo:   vectorVideo,
                                                   vectorObject:   vectorObject,


                                               });
        console.log(he)
    }








    function createMediaMessage()
    {
        console.log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~createMediaMessage")
        var tmp = newMediaMessage.createObject(columnChat,
                                               {
                                                   flagWhenMessage: true,
                                                   countAttachment: 5,
                                                   sizeMessage: 111,
                                                   messageText: str

                                               });
    }

    function creareNewMessage()
    {
        var countIndex = contactsss.getCountIndexMessage();
        var tmpMessage = newMassege.createObject(columnChat,
                                                 {
                                                     sizeMessage: testMap.getSizeMessage(countIndex),
                                                     messageText: testMap.getMassage(countIndex),
                                                     flagWhenMessage: testMap.getIsCheked(countIndex)
                                                 });
    }

    function ebaka(){
        //        repeaterChat.model = 0
        //        console.log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EBAKA")
        //        console.log(currentDialogOpen)
        //        console.log(clientData.getDialogIsGroup(currentDialogOpen))
        //        console.log(clientData.getCountMembers(currentDialogOpen))
        //        console.log(clientData.getDialogIsOnline(currentDialogOpen))
        //        console.log(currentDialogOpen)
        //        console.log(currentDialogOpen)


        var indexDialog = clientData.getIndexDialog(currentDialogOpen);
        text1.text = clientData.getDialogIsGroup(indexDialog) ? clientData.getCountMembers(indexDialog) + " участника" : (clientData.getDialogIsOnline(indexDialog)? "в сети" : "не в сети")
        //        client.sendReadAllMessageByChat(clientData.getIdDialog(indexDialog))

        // ОЧЕНЬ ВАЖНО МБ ПРИГОДИТЬСЯ
        //        clientData.setAllReadMessageInDialog(currentDialogOpen);

        for(var i = 0; i < columnChat.data.length;i++)
        {
            columnChat.data[i].destroy()
        }

        for(var i=0;i < clientData.getCountMessages(indexDialog);i++)
        {
            var str="file:///" +currentDir+"/" +clientData.getAvatarPathContact(indexDialog,i);
            console.log(str)

            if(clientData.checkAttachInMsg(indexDialog,i)){
                createEveryThingMessage(
                            clientData.getImageInMsg(indexDialog,i),
                            clientData.getMusicInMsg(indexDialog,i),
                            clientData.getVideoInMsg(indexDialog,i),
                            clientData.getAnyFilesInMsg(indexDialog,i),
                            clientData.getTextMessage(indexDialog,i),
                            clientData.getIsSenderMessage(indexDialog,i)
                            );
            }
            else
                var tmp=newMassege.createObject(columnChat,
                                                {
                                                    sizeMessage: clientData.getLength(clientData.getTextMessage(indexDialog,i)),
                                                    messageText: clientData.getTextMessage(indexDialog,i),
                                                    flagWhenMessage: clientData.getIsSenderMessage(indexDialog,i),
                                                    messageTime: clientData.getDateMessage(indexDialog,i),
                                                    messageStatus: 3,
                                                    avatarClient: str,
                                                    isGroupDialog: clientData.getDialogIsGroup(indexDialog)

                                                });
        }

        scrollToBottom();
    }

    function updateStatusMessage(d_id, m_id, status){
        if(currentDialogOpen==d_id)
        {
            ebaka()
        }
    }

    function updateChat(id_chat){

        //        if(loader.sourceComponent == userChat)
        //        {
        if(currentDialogOpen == id_chat)
        {

            ebaka()
            //client.getMessagesInDialog(clientData.getIdDialog(currentDialogOpen))

            //console.log("messageAnswer.lenght", messageAnswer.size())
            //                repeaterChat.update()
        }
        //        }
    }

    width: dfltWidth
    height: dfltHeight

    color: noColor

    Rectangle{
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: "qrc:/picture/phone.tif"
            opacity: 0.7
        }


        Rectangle {
            id: rectangle2
            x: 0
            y: 0
            width: parent.width
            height: heightToolBar
            color: biruzoviu

            Rectangle {
                id: rectangle
                x: 114
                y: 0
                width: 278
                height: heightToolBar
                color: noColor

                Rectangle {
                    id: rectangle1
                    width: rectangle1.height
                    height: heightToolBar
                    color: noColor
                    Rectangle {
                        id: rectangle5
                        x: 8
                        y: 8
                        width: 44
                        height: 44
                        color: "#ffffff"
                        radius: rectangle5.width / 2
                        Image {
                            id: image1
                            x: 8
                            y: 8
                            anchors.fill: parent
                            source: clientData.getPathAvatar(clientData.getIndexDialog(currentDialogOpen)) ==""?"qrc:/resourses/avatar/efreitor.tif":"file:///" +currentDir+"/" + clientData.getPathAvatar(clientData.getIndexDialog(currentDialogOpen))
                            layer.enabled: true
                            anchors.rightMargin: 0
                            layer.effect: OpacityMask {
                                maskSource: parent
                            }
                            fillMode: Image.PreserveAspectCrop
                            anchors.leftMargin: 0
                            anchors.bottomMargin: 0
                        }
                    }
                }


                Rectangle {
                    id: rectangle3
                    x: 60
                    y: 0
                    width: 218
                    height: 30
                    color: noColor
                    Text {
                        id: text2
                        color: "#ffffff"
                        text: clientData.getNameDialog(clientData.getIndexDialog(currentDialogOpen))
                        anchors.fill: parent
                        font.pixelSize: fontSize
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 10
                    }
                }

                Rectangle {
                    id: rectangle4
                    x: 60
                    y: 30
                    width: 218
                    height: 30
                    color: noColor
                    Text {
                        id: text1
                        color: "#ffffff"
                        text: clientData.getDialogIsGroup(clientData.getIndexDialog(currentDialogOpen)) ? clientData.getCountMembers(clientData.getIndexDialog(currentDialogOpen)) + " участника" : (clientData.getDialogIsOnline(clientData.getIndexDialog(currentDialogOpen))? "в сети" : "не в сети")
                        anchors.fill: parent
                        font.pixelSize: fontSize
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 10
                    }
                }
            }

            Rectangle {
                id: rectangle6
                x: 0
                y: 0
                width: heightToolBar
                height: heightToolBar
                color: noColor

                Image {
                    id: image
                    x: 8
                    y: 0
                    width: 40
                    height: heightToolBar
                    source: "qrc:/resourses/resourses v4/ri_tochki.tif"
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent

                        onClicked: {
                            navDrawer.showNavDrawer()
                            console.log("navDrawer.showNavDrawer()")
                        }
                    }
                }
            }

            Rectangle {
                id: rectangle7
                x: 446
                y: 0
                width: 60
                height: heightToolBar
                color: noColor

                Image {
                    id: image2
                    anchors.fill: parent
                    source: "qrc:/picture/arrow.tif"
                    anchors.leftMargin: 7
                    anchors.topMargin: 7
                    anchors.rightMargin: 7
                    anchors.bottomMargin: 7
                    fillMode: Image.PreserveAspectFit

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            loader.sourceComponent = listDialog
                            //                            loader1.source = "ListDialogs.qml"
                        }
                    }
                }
            }
        }

        Rectangle {
            id: messageZone
            x: 0
            y: 61
            width: parent.width
            height: 839
            color: "#00000000"

            Rectangle {
                id: zoneChat
                x: 0
                y: 0
                anchors.top: rectangle2.bottom
                anchors.topMargin: 5
                width: parent.width
                height: 782
                color: "#00000000"


                ScrollView{
                    id: scrollChat
                    anchors.fill: parent
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 2
                    anchors.bottomMargin: 8

                    contentWidth: parent.width
                    //                    contentHeight: clientData.getCountDialogs() * (columnChat.spacing + message.height)

                    clip: true
                    //                    LayoutMirroring.enabled: true

                    //                    property var t: repeaterChat.model * (columnChat.spacing + message.height)
                    //                    ScrollBar.vertical.position: t


                    Column{
                        id: columnChat
                        anchors.fill: parent

                        spacing: 15

                        //                        Rectangle{
                        //                            width: 1
                        //                            height: date.height - 10
                        //                            color: "#00000000"
                        //                        }

                        //                        Repeater{
                        //                            id: repeaterChat
                        //                            anchors.fill: parent

                        //                            model: clientData.getCountMessages(currentDialogOpen)

                        //                            Massage{
                        //                                id: message

                        //                                messageText: clientData.getTextMessage(currentDialogOpen, index)
                        //                                flagWhenMessage: clientData.getIsSenderMessage(currentDialogOpen, index)//testBoolArray[index]
                        //                                messageTime: clientData.getDateMessage(currentDialogOpen, index)
                        //                                sizeMessage: clientData.getSizeTextMessage(currentDialogOpen, index)
                        //                                messageStatus: clientData.getStatusMessage(currentDialogOpen, index)


                        //                                Component.onCompleted: {
                        //                                    console.log(repeaterChat.model)
                        //                                    console.log(index)

                        //                                    contactsss.setCountIndexMessage(countIndexVessage++)
                        //                                }
                        //                            }


                        //contactsss.setCountIndexMessage(countIndexVessage)
                    }

                    onContentHeightChanged: {
                        scrollToBottom();
                        //                        repeaterChat.update()
                    }

                    Component.onCompleted: {
                        scrollToBottom();

                    }

                }
            }

            DownBar {
                id: downBar
                //                anchors.top: scrollChat.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                //                currentDialogDownBar: currentDialog
            }
        }

        Rectangle {
            id: date
            x: 213
            y: 61
            width: 81
            height: 30
            color: "#ffffff"
            radius: 5
            opacity: customOpacity

            Text {
                id: text3
                anchors.fill: parent
                text: qsTr("Сегодня")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
    Component.onCompleted: {
        console.log("UserChar open");
        newMediaMessage = Qt.createComponent("MediaTextMessage.qml")
        universalMedia = Qt.createComponent("UniversalMediafileWidget.qml")

        musicW = Qt.createComponent("AudioWidget.qml")
        imgW = Qt.createComponent("PictureWidget.qml")
        textW = Qt.createComponent("TextWidget.qml")


        testMap.onEverythingMessage.connect(createEveryThingMessage);
        //        testMap.onEverythingMessage.connect(createMediaMessage);






        newMassege = Qt.createComponent("Massage.qml");

        //                newMediaMessage = Qt.createComponent("MediaTextMessage.qml");

        console.log("~~~~~~~~~~~~~~~~~~~~~~~~~~~newMediaMessage")
        //        newMediaMessage = Qt.createComponent("MediaTextMessage.qml")
        //        client.onUpdateStatusMessage.connect(updateStatusMessage)
        //        client.onMessageReceived.connect(updateChat);

        //        testMap.onCreateNewMassage.connect(creareNewMessage);

        //                testMap.onMediaMessage.connect(createMediaMessage)
        client.onUpdateChat.connect(updateChat)

    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
