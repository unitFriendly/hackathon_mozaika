import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: hatAccountMask
    width: 506
    height: 50
    color: "#00000000"


    property var nameText: "Аккаунт"
    Text {
        id: text1
        x: 191
        y: 0
        width: 125
        height: 50
        color: "#ffffff"
        text: nameText
        font.pixelSize: 18
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        id: rectangle1
        x: 8
        y: 24
        width: 177
        height: 2
        color: "#ffffff"
    }

    Rectangle {
        id: rectangle2
        x: 322
        y: 24
        width: 177
        height: 2
        color: "#ffffff"
    }
}
