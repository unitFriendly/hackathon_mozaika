import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.2

Rectangle{
    id: root

    property int dfltWidth: 506
    property int dfltHeight: 900
    property color noColor: "#00000000"
    property real customOpacity: 0.7
    property color biruzoviu: "#068d9d"

    property int countIndexVessage: 0


    property color darkerBiruzoviu: "#414a4c" //слишком темный, использовать Qt.darker(biruzoviu)


                    //массивы для теста визуализации настроек через репитер
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    property int fontSize: 14

    width: dfltWidth
    height: dfltHeight
    color: "#00000000"

    property int heightToolSettings: 60


    FileDialog {
            id: fileOpenDialog
            title: "Select an image file"
            folder: shortcuts.documents
            nameFilters: [
                "Image files (*.png *.jpeg *.jpg)",
            ]
            onAccepted: {
                console.log(fileOpenDialog.fileUrl)
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

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    loader.sourceComponent = listDialog
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
                anchors.fill: parent
                color: "#ffffff"
                text: qsTr("Настройки")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

//    Rectangle {
//        id: pictureMask
//        x: 0
//        y: 60
//        width: 506
//        height: 220
//        color: "#ffffff"

//        Image {
//            id: avatar
//            x: 0
//            y: 0
//            width: 506
//            height: 220
//            source: "qrc:/resourses/avatar/lobkov.tif"
//            fillMode: Image.PreserveAspectFit
//        }

//        Rectangle {
//            id: nameMask
//            x: 0
//            y: 180
//            width: 506
//            height: 40
//            color: biruzoviu
//            opacity: customOpacity
//        }

//        Text {
//            id: nameText
//            x: 0
//            y: 180
//            width: 415
//            height: 40
//            color: "#ffffff"
//            text: "Рядовой Ефрейтор"
//            font.pixelSize: 16
//            verticalAlignment: Text.AlignVCenter
//            minimumPixelSize: 16
//            leftPadding: 15
//        }

//        Rectangle {
//            id: chooseAvatarButtonMask
//            x: 414
//            y: 160
//            width: 76
//            height: 60
//            color: "#00000000"

//            Image {
//                id: chooseAvatarImage
//                anchors.fill: parent
//                source: "qrc:/resourses/nastroiki/kopka_obovit`_photo.tif"
//                anchors.leftMargin: 0
//                anchors.topMargin: 0
//                fillMode: Image.PreserveAspectFit
//            }

//            MouseArea{
//                anchors.fill: parent

//                onClicked: {
//                    fileOpenDialog.open()
//                }
//            }
//        }
//    }
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
            source: lientData.getPathAvatar(index) != ""?"file:///" +currentDir+"/" + clientData.getPathAvatar(index):"qrc:/resourses/avatar/lobkov.tif"
//            source: "qrc:/resourses/avatar/lobkov.tif"
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            id: nameMask
            x: 0
            y: 180
            width: 506
            height: 40
            color: biruzoviu
            opacity: customOpacity
        }

        Text {
            id: tbName
            x: 0
            y: 180
            width: 415
            height: 40
            color: "#ffffff"
            text: currentUser.getName()
            font.pixelSize: 16
            verticalAlignment: Text.AlignVCenter
            minimumPixelSize: 16
            leftPadding: 15
        }

        Rectangle {
            id: chooseAvatarButtonMask
            x: 414
            y: 160
            width: 76
            height: 60
            color: "#00000000"

            Image {
                id: chooseAvatarImage
                anchors.fill: parent
                source: "qrc:/resourses/nastroiki/kopka_obovit`_photo.tif"
                anchors.leftMargin: 0
                anchors.topMargin: 0
                fillMode: Image.PreserveAspectFit
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    fileOpenDialog.open()
                }
            }
        }
    }

    Rectangle {
        id: scrollViewMask
        x: 0
        y: 60
        width: parent.width
        height: 840
        color: Qt.darker(biruzoviu)



        ScrollView{
            property int contentHeightSettings: 1040
            id: scrollSetting
            width: parent.width
            height: 840

            contentHeight: contentHeightSettings
            contentWidth: parent.width
            clip: true

            SettingsScrollView{

            }

//            Column{
//                id: columnSettings
//                anchors.fill: parent

//                //переделать нахер все!!!!!!! Полностью файл PointUniversalSettings.qml

//                Repeater{
//                    id: repeaterSettings
//                    anchors.fill: parent
//                    model: settingsData.getSizeArrayPointSettings()

//                    Component.onCompleted: {
//                        console.log("settingsData.getSizeArrayPointSettings()", settingsData.getSizeArrayPointSettings())
//                    }

//                    PointUniversalSettings {
//                        id: pointUniversalSettings
//                        countIndex: index
//                    }

//                    Rectangle {
//                        id: rectangle3
//                        x: 0
//                        y: 50
//                        width: 506
//                        height: 328
            //                        color: "#00000000"
            //                    }
        }
    }
}


