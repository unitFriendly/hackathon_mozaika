import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: confidenceWidget
    width: 300
    height: 200
    color: "#00000000"

//    flags: Qt.FramelessWindowHint

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"



    signal clicked

    Rectangle {
        id: maskError
        x: 0
        y: 0
        width: 300
        height: 200
        color: "#ffffff"
        radius: 25

        Rectangle {
            id: rectangle
            x: 0
            y: 0
            width: 300
            height: 69
            color: biruzoviu
            radius: 25

            Text {
                id: text1
                x: 0
                y: 17
                width: 300
                height: 52
                color: "#ffffff"
                text: qsTr("Запрос")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
            }
        }

        Rectangle {
            id: rectangle1
            x: 0
            y: 48
            width: 300
            height: 127
            color: "#ffffff"

            Text {
                id: text2
                x: 45
                y: 8
                width: 210
                height: 76
                text: qsTr("Вы уверены, что хотите создать чат с " + name + " (" + login + ") ")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.Wrap
            }

            Rectangle {
                id: forgotPassword
                x: 45
                y: 92
                width: 85
                height: 31
                color: mouseArea1.containsPress ? Qt.darker("#068d9d") : "#068d9d"
                radius: 5

                Text {
                    id: text3
                    anchors.fill: parent
                    color: "#ffffff"
                    text: qsTr("Да")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea1
                    anchors.fill: parent

                    onClicked: {
//                        console.log("Не хочу с ним разговаривать")
                        client.
                        confidenceWidget.close()
                    }
                }
            }

            Rectangle {
                id: buttonOk
                x: 171
                y: 92
                width: 84
                height: 31
                color: mouseArea.containsPress ? Qt.darker("#068d9d") : "#068d9d"
                radius: 5

                Text {
                    id: text4
                    anchors.fill: parent
                    color: "#ffffff"
                    text: qsTr("Нет")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent

                    onClicked: {
                        console.log("Не против с ним поговорить")

                        loader.sourceComponent = profileMember
                        confidenceWidget.close()
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}D{i:9}
}
##^##*/
