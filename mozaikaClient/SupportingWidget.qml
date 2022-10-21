import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Image {
    id: supporting
    width: 506
    height: 900
    source: "qrc:/picture/phone.tif"
//    color: "#80000000"

    //    flags: Qt.FramelessWindowHint

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    signal clicked

    MouseArea{
        anchors.fill: parent

        onClicked: {
            loader.sourceComponent = listDialog
        }
    }

    Rectangle {
        id: maskError
        x: 103
        y: 345
        width: 300
        height: 210
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
                text: qsTr("Поддержка")
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                minimumPointSize: 16
                minimumPixelSize: 16
            }
        }

        Rectangle {
            id: rectangle1
            x: 0
            y: 48
            width: 300
            height: 100
            color: "#ffffff"

            Text {
                id: text2
                x: 8
                y: 43
                width: 300
                height: 76
                text: qsTr("По вопросам обращаться в 5 роту (научную) ВИТ «ЭРА».

Адрес: Краснодарский край, город Анапа, Пионерский проспект, д. 41

Телефон: 21-55
")
                font.pixelSize: 15
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.Wrap
            }
        }
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {
            loader.sourceComponent = listDialog
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
