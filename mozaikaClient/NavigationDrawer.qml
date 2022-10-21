import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: navigationDrawer
    property int dfltWidth: 506
    property int dfltHeight: 900
    width: dfltWidth//Math.min(dfltWidth, dfltHeight) / 3 * 2
    height: dfltHeight

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"
    property int fontSize: 20

    function closeNavDrawer()
    {
        closeNavDrower.start()
    }

    function showNavDrawer()
    {
        openNavDrawer.start()
        console.log("showNavDrawer()")

        imgAvatar.source=currentUser.getAvatarFile()!=""?"file:///" +currentDir+"/" +  currentUser.getAvatarFile() : "qrc:/resourses/avatar/cop.tif"
        tbName.text=currentUser.getName();
        tbLogin.text=currentUser.getLogin();
    }


    color: noColor
//    opacity: 0.3

    property var textArray: ["Создать чат", "Создать группу", "Создать приватный чат", "Контакты"]
    property var pictureArray: ["qrc:/resourses/create chat_2.tif", "qrc:/resourses/shtorka/plusplus.tif", "qrc:/resourses/shtorka/zakochek.tif", "qrc:/resourses/shtorka/contakti.tif"]


    MouseArea{
        anchors.fill: parent
    }

    NumberAnimation {
        id: openNavDrawer
        target: navigationDrawer
        property: "x"
        from: -dfltWidth
        to: 0
        loops: 1
        duration: 300
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: closeNavDrower
        target: navigationDrawer
        property: "x"
        from: 0
        to: -dfltWidth
        loops: 1
        duration: 300
        easing.type: Easing.InOutQuad
    }

    Rectangle{
        id: burgerMenu
        width: Math.min(dfltWidth, dfltHeight) / 3 * 2
        height: parent.height
        color: navigationDrawer.biruzoviu


        Rectangle {
            id: rectangle
            width: Math.min(dfltWidth, dfltHeight) / 3 * 2
            height: 60
            color: noColor

            Rectangle {
                id: rectangle1
                width: 60
                height: 60
                color: noColor
                //            radius: 30


                Rectangle {
                    id: rectangle5
                    x: 8
                    y: 8
                    width: 44
                    height: 44
                    color: "#ffffff"
                    radius: rectangle5.width / 2

                    Image {
                        id: imgAvatar
                        x: 8
                        y: 8
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectCrop
                        source: "qrc:/resourses/avatar/cop.tif"
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 0
                        anchors.topMargin: 0

                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: parent
                        }
                    }
                }
            }

            Rectangle {
                id: buttonSettings
                x: 277
                y: 0
                width: 60
                height: 60
                color: noColor
                z: 10
                Image {
                    x: 17
                    y: 18
                    width: 26
                    height: 25

                    source: "qrc:/resourses/shtorka/nastroiki.tif"
                    //                fillMode: Image.PreserveAspectFit
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        loader.sourceComponent = settingsNav;
                        navDrawer.closeNavDrawer()
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
                    id: tbName
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    color: "#ffffff"
                    text: currentUser.getName()
                    font.pixelSize: fontSize
                    verticalAlignment: Text.AlignVCenter
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
                    id: tbLogin
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    color: "#ffffff"
                    text: currentUser.getLogin()
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                }

            }
        }

        Rectangle {
            id: lineCuka
            x: 35
            y: 66
            width: 267
            height: 1
            color: "#ffffff"
        }

        Column {
            id: columnMenu
            anchors.top: lineCuka.bottom
            anchors.topMargin: 15
            anchors.right: parent.right
            anchors.left: parent.left
            width: parent.width
            height: 4 * (columnMenu.spacing * repMenu.height)
            spacing: 5


            Repeater{
                id: repMenu
                anchors.fill: parent

                model: 4

                property int sizeHeightMenuElement: 60
                MenuElement {


                }
            }
        }

        Rectangle {
            id: lineCuka1
            x: 35
            y: 354
            width: 267
            height: 1
            color: "#ffffff"
        }

        Rectangle {
            id: lineCuka2
            x: 35
            y: 693
            width: 267
            height: 1
            color: "#ffffff"
        }

        Column {
            id: helpColumn
            anchors.top: lineCuka2.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left

            spacing: 10
            width: parent.width
            height: repHelp.model * (helpColumn.spacing + repHelp.height)

            Repeater{
                id: repHelp
                anchors.fill: parent
                model: 3

                property int sizeHelpHeight: 60
                HelpMenu {

                }
            }
        }
    }

    Rectangle {
        id: rectangle7
        width: 169
        height: parent.height
        anchors.right: parent.right
        anchors.left: burgerMenu.right
        color: "black" // black
        opacity: 0.3

        MouseArea{
            anchors.fill: parent

            onClicked: {
                closeNavDrower.start()
            }
        }
    }

//    Component.onCompleted: {
//        openNavDrawer.start()
//    }
}


