import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12

Rectangle{
    color: "transparent"
    width: 300
    height: 200
    //    opacity: 0.3
    property int sizeVideo: videoMessage.duration / 10 / 60
    property real procentVideo: videoMessage.duration / 100
    property int secondVideo: videoMessage.duration / 1000 / 60 / 100
    property int minuteVideo: 0
    property int minuteSizeVideo: sizeVideo / 100
    property int secondSizeVideo: sizeVideo % 100

    property int countTimer: 1
    property int secondsVideoDurationINT: testMap.getSizeSeconds(videoMessage.duration) % 60

    Rectangle {
        id: mask
        x: 0
        y: 0
        width: 300
        height: 200
        color: "transparent"

        Image {
            id: startstop
            x: 125
            y: 75
            width: 50
            height: 50
            source: "qrc:/picture/button/play.png"
            fillMode: Image.PreserveAspectFit
            scale: mouseStartstop.containsPress ? 1.2 : 1

            MouseArea{
                id: mouseStartstop
                anchors.fill: parent
                onClicked: {
                    if (!isPlay)
                    {
                        videoMessage.pause()
                        timerVideo.stop()
                        startstop.source = "qrc:/picture/button/play.png"
                        isPlay = !isPlay
                    }
                    else
                    {
                        videoMessage.play()
                        timerVideo.start()
                        startstop.source = "qrc:/picture/button/pause.png"
                        isPlay = !isPlay
                    }
                }
            }
        }

        Image {
            id: zoom
            x: 250
            y: 0
            width: 50
            height: 50
            source: "qrc:/picture/button/scale.png"
            fillMode: Image.PreserveAspectFit
            scale: mouseZoom.containsPress ? 1.2 : 1

            MouseArea{
                id: mouseZoom
                anchors.fill: parent

                hoverEnabled: true

                onClicked: {

                }
            }

        }

        Timer{
            id: timerVideo
            interval: 1000;
            running: false;
            repeat: true
            onTriggered: {
                progressBar.value += videoMessage.duration / secondsVideoDurationINT
                secondVideo +=1
//                console.log(progressBar.value)

                if (countTimer == secondsVideoDurationINT)
                {
                    timerVideo.stop()

                }
                countTimer++
//                console.log(videoMessage.duration /1000 /60, videoMessage.duration /1000 %60,)

                if (secondVideo == 60)
                {
                    minuteVideo++;
                    secondVideo = 0;
                }
            }
        }


        ProgressBar {
            id: progressBar
            x: 35
            y: 184
            width: 230
            height: 8
            value: 0
            from: 0
            to: videoMessage.duration

            background: Rectangle {
                     color: "white"
                     radius: 3
                 }

            contentItem: Rectangle{
                width: progressBar.visualPosition * parent.width
                height: parent.width
                color: Qt.darker("gray")
                radius: 2
            }

        }

        Text {
            id: text1
            x: 0
            y: 168
            width: 42
            height: 17
            text:
            {
                if (secondVideo < 10)
                {
                    minuteVideo + ":0" + secondVideo
                }
                else
                {
                    minuteVideo + ":" + secondVideo
                }
            }

            font.pixelSize: 12
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: text2
            x: 250
            y: 168
            width: 42
            height: 17
            text: testMap.getSizeMinuts(videoMessage.duration) + ":" + testMap.getSizeSeconds(videoMessage.duration)
            font.pixelSize: 12
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            anchors.right: parent.right
        }
    }

    Component.onCompleted: {


    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}D{i:8}
}
##^##*/
