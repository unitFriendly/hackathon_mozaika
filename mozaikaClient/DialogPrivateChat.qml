import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle
{
    id: background

    anchors.fill: parent
    enabled: true
    color: "#88000000" // black

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    MouseArea{
        anchors.fill: parent
        onClicked: {
            console.log("background")
        }
    }

    Rectangle {
        id: window

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        width: 300
        height: 200
        color: "#ffffff"
        radius: 25


        Rectangle {
            id: rectangle
            x: 8
            y: 63
            width: 284
            height: 54
            color: "#00000000"

            Text {
                id: text1
                x: 82
                y: 0
                width: 203
                height: 54
                text: qsTr(privateCharReqName + " приглашает вас в приватный чат")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.Wrap
            }

            Rectangle{
                id: maskImage
                x: -5
                y: -12
                width: 88
                height: 81

                Rectangle {
                    id: rectangle3
                    x: 7
                    y: 14
                    width: 60
                    height: 60
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 2
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    radius: 35
                    border.width: 1
                    border.color: "#068d9d"
                    clip: true

                    color: "#ffffff"

                    Image {
                        id: image
                        x: 0
                        y: 8
                        width: 60
                        height: 44
                        source: "qrc:/resourses/avatar/baba.tif"
                        fillMode: Image.PreserveAspectFit

                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: parent
                        }
                    }

                    MouseArea {
                        id: mouseOpenProfile
                        anchors.fill: parent

                        onClicked: {
                            console.log("Открыть профиль")
                        }
                    }
                }
            }
        }

        Rectangle {
            id: buttonYes
            x: 57
            y: 136
            width: 71
            height: 23
            color: mouseButtonYes.containsPress ? Qt.lighter(biruzoviu) : biruzoviu
            radius: 5

            Text {
                id: text2
                anchors.fill: parent
                text: qsTr("Да")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }

            MouseArea {
                id: mouseButtonYes
                anchors.fill: parent

                onClicked: {
                    client.getReqPrivateChat(privateCharReqLogin,true)
                    console.log("Да")
                }
            }
        }

        Rectangle {
            id: buttonNo
            x: 164
            y: 136
            width: 71
            height: 23
            color: mouseButtonNo.containsPress ? Qt.lighter(biruzoviu) : biruzoviu
            radius: 5

            Text {
                id: text3
                anchors.fill: parent
                text: qsTr("Нет")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }

            MouseArea {
                id: mouseButtonNo
                anchors.fill: parent

                hoverEnabled: true

                onClicked: {
                    client.getReqPrivateChat(privateCharReqLogin,false)
                    console.log("Нет")
                }
            }
        }

        Rectangle {
            id: rectangle1
            x: 0
            y: 0
            width: 300
            height: 49
            color: biruzoviu
            radius: 15

            Text {
                id: text4
                x: 0
                y: 11
                width: 300
                height: 27
                color: "#ffffff"

                text: qsTr("Приглашение")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
            }
        }

        Rectangle {
            id: rectangle2
            x: 0
            y: 36
            width: 300
            height: 27
            color: "#ffffff"
        }






    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/
