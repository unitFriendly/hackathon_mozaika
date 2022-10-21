import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
 Image{
    id: supporting
    width: 506
    height: 900
//    color: "#80000000"
    source: "qrc:/picture/phone.tif"

    //    flags: Qt.FramelessWindowHint

    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"



    signal clicked


    Rectangle {
        id: maskError
        x: 47
        y: 77
        width: 400
        height: 700
        color: "#ffffff"
        radius: 25

        Rectangle {
            id: rectangle
            x: 0
            y: 0
            width: 400
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
                anchors.horizontalCenter: parent.horizontalCenter
                minimumPointSize: 16
                minimumPixelSize: 16
            }
        }

        Rectangle {
            id: rectangle1
            x: 0
            y: 48
            width: 400
            height: 100
            color: "#ffffff"

            Column {
                id: column
                x: 66
                y: 31
                width: 269
                height: 400
                spacing: 12
                padding: 0

                Text {
                    id: text2
                    text: "Бабушкин «yHorek» Игорь Юрьевич<br>(осталось " + "<font color=\"#068d9d\">" + dateLeft.getLeftDayFirstCall() + "</font>" + ") дня\n"

                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    textFormat: Text.RichText
                    minimumPixelSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: text3
                    text: "Горбунов «Sowl» Максим Сергеевич<br>(осталось " + "<font color=\"#068d9d\">" + dateLeft.getLeftDayFirstCall() + "</font>" + ") дня\n"
                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: text4
                    text: "Горбунов «herman» Сергей Александрович<br>(осталось " + "<font color=\"#068d9d\">" + dateLeft.getLeftDayFirstCall() + "</font>" + ") дня\n"
                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: text5
                    text: "Кирянов «IWIWI» Николай Олегович\n<br>(осталось " + "<font color=\"#068d9d\">" + dateLeft.getLeftDayFirstCall() + "</font>" + ") дня\n"
                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    textFormat: Text.RichText
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: text6
                    text: "Костриков «Voven» Владимир Владимирович<br>(осталось " + "<font color=\"#068d9d\">" + dateLeft.getLeftDayFirstCall() + "</font>" + ") дня\n"
                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: text7
                    text: "Назаров «unit.friendly» Алексей Иванович<br>(осталось " + "<font color=\"#068d9d\">" + dateLeft.getLeftDaySecondCall() + "</font>" + ") дня\n"
                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Image {
                    id: cyber_mandarin
                    width: 323
                    height: 189
                    source: "qrc:/picture/cyber_mandarin.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                }
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
    D{i:0;formeditorZoom:1.1}D{i:7}D{i:8}D{i:9}D{i:10}D{i:11}
}
##^##*/
