import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0




Rectangle {
    id: rectangle1
    color: biruzoviu


    property int dfltWidth: 506
    property int dfltHeight: 838
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property int countIndexVessage: 0

    width: dfltWidth
    height: 900

    Rectangle {
        id: hatAccountMask
        width: dfltWidth
        height: 50
        color: "#00000000"


        property var nameText: "Аккаунт"
        x: 0
        y: 279
        Text {
            id: text1
            x: 191
            y: 0
            width: 125
            height: 50
            color: "#ffffff"
            text: "Аккаунт"
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {

            x: 8
            y: 24
            width: 177
            height: 2
            color: "#ffffff"
        }

        Rectangle {

            x: 322
            y: 24
            width: 177
            height: 2
            color: "#ffffff"
        }
    }


    Rectangle {
        id: separatorLine
        x: 0
        y: 60
        width: parent.width
        height: 1
        color: Qt.darker(biruzoviu)
    }

    Rectangle {
        id: toolBar
        width: parent.width
        height: 60
        color: biruzoviu
        Rectangle {
            id: rectangle
            x: 8
            y: 0
            width: 60
            height: 60
            color: "#00000000"
            Image {
                id: image
                x: 5
                y: 5
                width: 50
                height: 50
                source: "qrc:/picture/arrow.tif"
                fillMode: Image.PreserveAspectFit
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    loader.sourceComponent = contactsList
                }
            }
        }

        Rectangle {
            id: maskText
            x: 163
            y: 0
            width: 180
            height: 60
            color: "#00000000"
            Text {
                id: textSettings
                color: "#ffffff"
                text: qsTr("Профиль")
                anchors.fill: parent
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Rectangle {
        id: pictureMask
        x: 0
        y: 60
        width: 506
        height: 220
        color: "#ffffff"
        Image {
            id: avatar
            x: 0
            y: 0
            width: 506
            height: 220
            source: clientData.getPathAvatarContact(currentCharContactOpen, currentContactOpen) != ""
                    ?"file:///" +currentDir+"/" + clientData.getPathAvatarContact(currentCharContactOpen, currentContactOpen)
                    :"qrc:/resourses/avatar/lobkov.tif"
            fillMode: Image.PreserveAspectFit

            Rectangle {
                id: rectangle2
                x: 414
                y: 179
                width: 92
                height: 41
                color: "#ffffff"
            }
        }

        Rectangle {
            id: nameMask
            x: 0
            y: 180
            width: 506
            height: 40
            opacity: customOpacity
            color: biruzoviu

            Text {
                id: text3
                x: 414
                y: -1
                width: 92
                height: 41
                color: "#ffffff"
                text: qsTr("не в сети")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Text {
            id: tbName
            x: 0
            y: 180
            width: 415
            height: 40
            color: "#ffffff"
            text: clientData.getNameContact(currentCharContactOpen, currentContactOpen)
            font.pixelSize: 16
            verticalAlignment: Text.AlignVCenter
            minimumPixelSize: 16
            leftPadding: 15
        }
    }

    Rectangle {
        id: accountSettings
        x: 0
        y: 329
        width: parent.width
        height: 154
        color: biruzoviu
        Column {
            id: columnPointSettings
            spacing: 2
            Rectangle {
                id: login
                width: accountSettings.width / 2
                height: 50
                color: noColor
                Text {
                    id: text2
                    color: "#ffffff"
                    text: qsTr("Логин")
                    anchors.fill: parent
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                }
            }

            Rectangle {
                id: phone
                width: accountSettings.width / 2
                height: 50
                color: noColor
                Text {
                    id: text4
                    color: "#ffffff"
                    text: qsTr("Телефон")
                    anchors.fill: parent
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                }
            }

            Rectangle {
                id: birthDay
                width: accountSettings.width / 2
                height: 50
                color: noColor
                Text {
                    id: text6
                    color: "#ffffff"
                    text: qsTr("Дата рождения")
                    anchors.fill: parent
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                }
            }
        }

        Column {
            anchors.left: columnPointSettings.right
            spacing: 2
            Rectangle {
                id: loginAnswer
                width: accountSettings.width / 2
                height: 50
                color: noColor
                Text {
                    id: loginAnswerText
                    color: "#ffffff"
                    text: clientData.getLoginContact(currentCharContactOpen, currentContactOpen)
                    anchors.fill: parent
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                }
            }

            Rectangle {
                id: accountAnswerPhone
                width: accountSettings.width / 2
                height: 50
                color: noColor
                Text {
                    id: accountAnswerPhoneText
                    color: "#ffffff"
                    text: qsTr("8-915-169-04-52")
                    anchors.fill: parent
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                }
            }

            Rectangle {
                id: accountAnswerBirthDay
                width: accountSettings.width / 2
                height: 50
                color: noColor
                Text {
                    id: accountAnswerBirthDayText
                    color: "#ffffff"
                    text: clientData.getBirthDateContact(currentCharContactOpen, currentContactOpen)
                    anchors.fill: parent
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 10
                }
            }
        }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/
