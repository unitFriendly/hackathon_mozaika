import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Window {
    id: errorDialog
    width: 300
    height: 200
    color: "#00000000"


    flags: Qt.FramelessWindowHint


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
                text: qsTr("Error")
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
                x: 90
                y: 0
                width: 210
                height: 76
                text: qsTr("Вход в аккаунт невозможен неправильный логин или пароль Попробуйте снова")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.Wrap
            }

            Rectangle {
                id: forgotPassword
                x: 29
                y: 92
                width: 130
                height: 31
                color: mouseForgotPassword.containsPress ? Qt.darker("#068d9d") : "#068d9d"
                radius: 5

                Text {
                    id: text3
                    anchors.fill: parent
                    color: "#ffffff"
                    text: qsTr("Забыли пароль?")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseForgotPassword
                    anchors.fill: parent

                    hoverEnabled: true

                    onClicked: {
                        errorDialog.clicked()
                        console.log("Здесь происходит заявку в службу ЗГТ")
                    }
                }
            }

            Rectangle {
                id: buttonOk
                x: 189
                y: 92
                width: 84
                height: 31
                color: mouseButtonOk.containsPress ? Qt.darker("#068d9d") : "#068d9d"
                radius: 5

                Text {
                    id: text4
                    anchors.fill: parent
                    color: "#ffffff"
                    text: qsTr("Ок")
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseButtonOk
                    anchors.fill: parent

                    hoverEnabled: true

                    onClicked: {
//                        loader.sourceComponent =
                        errorDialog.close()
                        console.log("Попробовать еще раз");
                    }
                }
            }

            Image {
                id: image
                x: 8
                y: 8
                width: 82
                height: 68
                source: "qrc:/qtquickplugin/images/template_image.png"
                fillMode: Image.PreserveAspectFit
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}D{i:9}
}
##^##*/
