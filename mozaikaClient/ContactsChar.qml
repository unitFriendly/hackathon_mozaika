import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    property int dfltWidth: 506
    property int dfltHeight: 100
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property int fontSize: 20

    property int indexRepeaterChar: 0
    property string textRepeaterChar: "s"

    property int dfltHeightContactList: 84
    property var tmpContactName



    width: dfltWidth
    height: dfltHeight
    //    border.width: 1
    //    border.color: "white"

    color: noColor

    function loadContactsInChar(){
        for(var i = 0; i < columnContactList.data.length;i++)
        {
            columnContactList.data[i].destroy()
        }

        var countD = clientData.getCountContactsInMap(textRepeaterChar);

        var tmp;


        var list = []

        var counter = 0

        for(var i=0;i<countD;i++){
            if (clientData.getLoginContact(textRepeaterChar, i) != clientData.getCurrentLogin()){
                tmp = tmpContactName.createObject(columnContactList,
                                                  {
                                                      nameContact: clientData.getNameContact(textRepeaterChar, i),
                                                      indexContact: i,

                                                      pathAvatarContact: clientData.getPathAvatarContact(textRepeaterChar, i) != ""?"file:///" +currentDir+"/" + clientData.getPathAvatarContact(textRepeaterChar, i):"qrc:/resourses/avatar/cop.tif",
                                                      login: clientData.getLoginContact(textRepeaterChar, i)
                                                      //                                                   textRepeaterContactsName: contactsss.getName(i)
                                                  });
                counter++
            }
        }

        if(counter == 0)
            root.visible = false

        rootLineCharList.height= countD * dfltHeightContactList - 50
    }

    Rectangle {
        id: rootCharContact
        width: 50
        height: 50
        color: noColor

        Text {
            id: rootCharContactText
            color: "#ffffff"
            anchors.fill: parent
            text: textRepeaterChar
            font.pixelSize: fontSize
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            Component.onCompleted: {
                // console.log("textRepeaterChar", textRepeaterChar)
            }
        }
    }

    Column {
        id: columnContactList
        y:30
    }

    //    Rectangle {
    //        id: contactPageMain
    //        x: 50
    //        y: 8
    //        width: 448
    //        height: 84
    //        color: noColor
    //        //                opacity: 0.7
    //        //                border.color: mouseContacts.containsPress ? "white" : noColor
    //        //                border.width: 1

    ////        Rectangle {
    ////            id: contactPageAvatar
    ////            x: 0
    ////            y: 0
    ////            width: 84
    ////            height: parent.height
    ////            color: noColor

    ////            Rectangle {
    ////                id: contactPageAvatarMask
    ////                x: 10
    ////                y: 10
    ////                width: 64
    ////                height: 65
    ////                color: "#ffffff"
    ////                radius: contactPageAvatarMask.width / 2


    ////                Image {
    ////                    id: image1
    ////                    anchors.fill: parent
    ////                    fillMode: Image.PreserveAspectCrop
    ////                    source: "qrc:/resourses/avatar/cop.tif"
    ////                    layer.enabled: true
    ////                    layer.effect: OpacityMask {
    ////                        maskSource: parent
    ////                    }
    ////                }
    ////            }

    //            Rectangle {
    //                x: 80
    //                y: 0
    //                width: 367
    //                height: 84
    //                color: noColor

    ////                Text {
    ////                    property int fontSize: 20
    ////                    id: textName
    ////                    anchors.fill: parent
    ////                    text: contactsss.getName(textRepeaterChar,index)
    ////                    font.pixelSize: textName.fontSize
    ////                    color: "white"
    ////                    verticalAlignment: Text.AlignVCenter
    ////                    leftPadding: 10
    ////                }

    //                CheckBox {
    //                    id: checkBox
    //                    checked: true
    //                    width: 20
    //                    height: 20
    //                    x: 300
    //                    y: 25

    //                    background: Rectangle{
    //                        //                                anchors.fill: parent
    //                        width: 20
    //                        height: 20
    //                        color: noColor
    //                        radius: parent.width/2
    //                        border.width: 1
    //                        border.color: "white"

    //                    }
    //                    indicator: Rectangle{
    //                        anchors.centerIn: parent
    //                        width: 14
    //                        height: 14
    //                        x: 6
    //                        y: 6
    //                        radius: 7
    //                        color: "white"
    //                        visible: !checkBox.checked
    //                    }
    //                }

    //            }
    //        }


    //    }

    Rectangle {
        id: rootLineCharList
        y: 0
        anchors.top: rootCharContact.bottom
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.horizontalCenter: rootCharContact.horizontalCenter
        width: 2
        //        height: columnContactList.model * dfltHeightContactList - 70
        color: "#ffffff"
    }

    Component.onCompleted: {
        tmpContactName= Qt.createComponent("ContactPageMain.qml");
        console.log("huyyy")
        loadContactsInChar();
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
