import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: contactPageMain

    property string nameContact
    property string pathAvatarContact
    property int  indexContact
    property string login

    x: 50
    y: 8
    width: 448
    height: 84
    color: noColor
    //                opacity: 0.7
//    border.color: mouseContacts.containsPress ? "white" : noColor
//    border.width: 1

    Rectangle {
        id: contactPageAvatar
        x: 0
        y: 0
        width: 84
        height: parent.height
        color: noColor

        Rectangle {
            id: contactPageAvatarMask
            x: 10
            y: 10
            width: 64
            height: 65
            color: "#ffffff"
            radius: contactPageAvatarMask.width / 2


            Image {
                id: image1
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: pathAvatarContact
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: parent
                }
            }
        }

        Rectangle {
            x: 80
            y: 0
            width: 367
            height: 84
            color: noColor


            Text {
                property int fontSize: 20
                id: textName
                anchors.fill: parent
                text: nameContact
                font.pixelSize: textName.fontSize
                color: "white"
                verticalAlignment: Text.AlignVCenter
                leftPadding: 10
            }

            CheckBox {
                id: checkBox
                visible: createChatType == "group_chat"
                checked: false
                width: 20
                height: 20
                x: 300
                y: 25


                onCheckedChanged: {




                    if (checkState == Qt.Checked){
                        counter = counter + 1
                        logins.push(login)
                    }
                    else{
                        counter = counter - 1
                        var tmp_list = []
                        for(var i = 0; i<logins.length; i++)
                            if(logins[i]!=login)
                                tmp_list.push(logins[i])
                        logins = tmp_list
                    }
                }

                background: Rectangle{
                    //                                anchors.fill: parent
                    width: 20
                    height: 20
                    color: noColor
                    radius: parent.width/2
                    border.width: 1
                    border.color: "white"

                }
                indicator: Rectangle{
                    anchors.centerIn: parent
                    width: 14
                    height: 14
                    x: 6
                    y: 6
                    radius: 7
                    color: "white"
                    visible: checkBox.checked
                }
            }
        }
    }

    MouseArea {
        id: mouseContacts
        enabled: createChatType != "group_chat"
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            if (createChatType == "non_chat")
            {
                currentContactOpen = indexContact
                currentCharContactOpen = textRepeaterChar
                loader.sourceComponent = profileMember
            }
            if(createChatType == "just_chat")
            {
                if(clientData.isExistDialogWithUser(clientData.getLoginContact(textRepeaterChar, indexContact)))
                {
                    console.log("Dialog is exist")
                }
                else
                {
                    client.createChat([clientData.getLoginContact(textRepeaterChar, indexContact)],"","",false)
                    client.getMyDialogs()
                    loader.sourceComponent = listDialog
                }
            }
            if(createChatType == "private_chat"){
                client.createPrivateChat(clientData.getLoginContact(textRepeaterChar, indexContact))
            }


        }
    }
}
