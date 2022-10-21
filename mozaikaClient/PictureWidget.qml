import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: image

    property var sourcePicture: "qrc:/resourses/avatar/kloun.tif"
    property color fontMsgColor

    width: 300
    height: 170

//    border.width: 1
//    border.color: "white"
    radius: 10

    color: fontMsgColor

    Image {
        anchors.fill: parent
        source: sourcePicture
        anchors.rightMargin: 54
        anchors.bottomMargin: 23
        anchors.leftMargin: 54
        anchors.topMargin: 23
    }

//    Separator{
//        anchors.top: parent.bottom
//    }
}
