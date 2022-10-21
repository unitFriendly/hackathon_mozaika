import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Rectangle {
    id: pointUniversalSettings

    property int dfltWidth: 506
    property int dfltHeight: 400
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property int heightContentCustom: 50
    property int countIndex: 0

    width: dfltWidth
    height: (settingsData.getSizePointSettings(countIndex)+1) * (heightContentCustom + columnPointUniversalSettings.spacing)

    color: noColor

    Column{
        id: columnPointUniversalSettings
        anchors.fill: parent
        spacing: 10

        HatMask {
            id: hatAccountMask
            nameText: settingsData.getArrayPointSettings(countIndex)
        }

        Repeater{
            model: settingsData.getSizePointSettings(countIndex)

            Row{
                width: parent.width
                height: heightContentCustom

                Rectangle{
                    id: keyUniversal
                    width: parent.width / 2
                    height: heightContentCustom
                    color: noColor
//                    border.width: 1
//                    border.color: "black"

                    Text {
                        anchors.fill: parent
                        font.pixelSize: 14
//                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: settingsData.getPointSettings(countIndex, index)
                        wrapMode: Text.Wrap
                        color: "#ffffff"
                    }
                }

                Rectangle{
                    id: valueUniversal
                    width: parent.width / 2
                    height: heightContentCustom
                    anchors.left: keyUniversal.right
                    anchors.right: parent.right
                    color: noColor
//                    border.width: 1
//                    border.color: "black"

                    Text {
                        anchors.fill: parent
                        font.pixelSize: 14
//                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: settingsData.getAnswerSettings(countIndex, index)
                        wrapMode: Text.Wrap
                        color: "#ffffff"
                    }
                }
            }
        }
    }
}


