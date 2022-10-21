import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: addContact

    property int dfltWidth: 506
    property int dfltHeight: 900
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property int sizeHeightRectName: 84

    property int fontSize: 14
    property var tmpContactsChar
    property string chat_title: "Контакты"



    property int counter: 0
    property var logins: []


    ConfidenceWidget{
        id: confidence
        onClicked: {
            confidence.show()
        }
    }

    width: dfltWidth
    height: dfltHeight
    color: noColor


    function loadContacts(){
        for(var i = 0; i < columnContact.data.length;i++)
        {
            columnContact.data[i].destroy()
        }

        var countD = clientData.getCountMapContacts();

        var tmp;

        for(var i=0;i<countD;i++){
            tmp = tmpContactsChar.createObject(columnContact,
                                               {
                                                   indexRepeaterChar: i,
                                                   textRepeaterChar: clientData.getCharMapContacts(i),
                                                   dfltHeight: clientData.getCountContactsInMap(clientData.getCharMapContacts(i)) * sizeHeightRectName
                                                   //                                                   textRepeaterContactsName: contactsss.getName(i)
                                               });
        }

        if(createChatType == "just_chat")
            chat_title = "Создать чат"
        else if(createChatType == "group_chat")
            chat_title = "Создать группу"
        else if(createChatType == "private_chat")
            chat_title = "Создать приватный чат"
        else if(createChatType == "non_chat")
            chat_title = "Контакты"

        scrollContacts.contentHeight= clientData.getc * sizeHeightRectName
    }


    onCounterChanged: {
        if(counter > 0)
            chat_title = "Выбрано: " + counter
        else chat_title = "Создать группу"
    }

    Rectangle{
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "black"

        Image {
            id: mainPhone
            anchors.fill: parent
            source: "qrc:/picture/phone.tif"
            opacity: customOpacity
        }
        Rectangle {
            id: rectangle
            x: 0
            y: 0
            width: 506
            height: 60
            color: "#068d9d"

            Rectangle {
                id: rectangle1
                x: 0
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Image {
                    id: image
                    x: 8
                    y: 0
                    width: 40
                    height: 60
                    source: "qrc:/resourses/chat/nazad_strelochka.tif"
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        loader.sourceComponent = listDialog
                    }
                }
            }

            Rectangle {
                id: rectangle2
                x: 195
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Text {
                    id: text2
                    x: 0
                    y: 0
                    width: 117
                    height: 60
                    color: "#ffffff"
                    text: chat_title
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                id: rectangle3
                x: 389
                y: 0
                width: 117
                height: 60
                color: "#00000000"

                Image {
                    id: image1
                    x: 44
                    y: 8
                    width: 65
                    height: 44
                    source: "qrc:/picture/luppa.tif"
                    fillMode: Image.PreserveAspectFit
                }
                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        console.log("Здесь будет фильтр")
                    }
                }
            }
        }

        Rectangle {
            id: rectangle4
            x: 0
            y: 59
            width: 506
            height: 841
            color: "#00000000"

            ScrollView{
                id: scrollContacts
                anchors.fill: parent
                width: parent.width
                height: parent.height
                contentWidth: parent.width


                clip: true

                Column{
                    id: columnContact
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    spacing: 10
                }
            }
        }
    }

    Rectangle {
        id: addNewDialogMask
        x: 434
        y: 828
        visible: createChatType == "group_chat" && counter > 0
        width: 72
        height: 72

        anchors.right: addContact.right
        anchors.rightMargin: 15

        anchors.bottom: addContact.bottom
        anchors.bottomMargin: 15

        radius: addNewDialogMask.width / 7

        opacity: customOpacity

        color: addNewDialogMouse.containsPress ? Qt.lighter(biruzoviu) : biruzoviu

        Image {
            id: addNewDialog
            x: 11
            y: 11
            width: 50
            height: 50
            source: "qrc:/resourses/create chat_2.tif"
            fillMode: Image.PreserveAspectFit
        }

        MouseArea{
            id: addNewDialogMouse
            anchors.fill: parent

            onClicked: {
                //                    loader.sourceComponent = contactsList
                if(createChatType == "group_chat"){
                    client.createChat(logins, "Групповой чат", "", true)
                }

                client.getMyDialogs()
                loader.sourceComponent = listDialog
                //var str = "123213"
                //testMap.createNewDialog(str)


                console.log("loader.source = contactsList")
            }
        }
    }


    Component.onCompleted: {
        tmpContactsChar = Qt.createComponent("ContactsChar.qml");
        loadContacts()
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
