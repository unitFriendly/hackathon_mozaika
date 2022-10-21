import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle{
    id: root

    function createChat()
    {
        createChatType = "just_chat"
        loader.sourceComponent = contactsList
        navDrawer.closeNavDrawer()
        console.log("createChat")
    }

    function createGroup()
    {
        createChatType = "group_chat"
        loader.sourceComponent = contactsList
        navDrawer.closeNavDrawer()
        console.log("createGroup")
    }

    function createPrivateChat()
    {
        createChatType = "private_chat"
        loader.sourceComponent = contactsList
        navDrawer.closeNavDrawer()
        console.log("createPrivateGroup")
    }

    function listContacts()
    {
        createChatType = "non_chat"
        loader.sourceComponent = contactsList
        navDrawer.closeNavDrawer()
        console.log("listContacts")
    }


    property var functionMenuElementArray: [createChat, createGroup,createPrivateChat,listContacts]

    property int fontSize: 20
    property int sizeHeightMenuElement: 60
    property int dfltWidthElementMenu: 337
    property color noColor: "#00000000"

    property var textArray: ["Создать чат", "Создать группу", "Создать приватный чат", "Контакты"]
    property var pictureArray: ["qrc:/resourses/create chat_2.tif", "qrc:/resourses/resourses v4/gruppa.tif", "qrc:/resourses/resourses v4/private chat.tif", "qrc:/resourses/shtorka/contakti.tif"]


    width: dfltWidthElementMenu
    height: sizeHeightMenuElement
    color: mouse.containsMouse ? Qt.darker(biruzoviu ) : noColor

    Rectangle {
        id: rectangle
        x: 20
        y: 0
        width: 60
        height: 60
        color: "#00000000"

        Image {
            id: image
            height: 30
            anchors.fill: parent

            anchors.leftMargin: 15
            anchors.topMargin: 15
            anchors.rightMargin: 15
            anchors.bottomMargin: 15
                        fillMode: Image.PreserveAspectCrop
        }
    }

    Rectangle {
        id: rectangle1
        x: 101
        y: 0
        width: 198
        height: 60
        color: "#00000000"

        Text {
            id: text1
            anchors.fill: parent
            color: "#ffffff"
            font.pixelSize: fontSize
            verticalAlignment: Text.AlignVCenter
        }      
    }

    MouseArea{
        id: mouse
        anchors.fill: parent

        hoverEnabled: true

        onClicked: {
            functionMenuElementArray[index]()
        }
    }

    Component.onCompleted: {
        text1.text = textArray[index]
        image.source = pictureArray[index]

    }
}
