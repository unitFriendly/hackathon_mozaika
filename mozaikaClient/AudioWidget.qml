import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtMultimedia 5.12

Rectangle {
    width: 300
    height: 50
     property var fontMsgColor
    color: fontMsgColor
    radius: 10

    //    border.width: 1
    //    border.color: "white"

    property var filePath


    property bool flagMusic: false

    property int countAudio: 1
    property int secondsAudioDurationINT: testMap.getSizeSeconds(playMusic.duration) % 60

    property int sizeSong: playMusic.duration / 10 / 60
    property real procentSong: playMusic.duration / 100
    property int secondSong: playMusic.duration / 1000 / 60 / 100
    property int minuteSong: 0
    property int minuteSizeSong: sizeSong / 100
    property int secondSizeSong: sizeSong % 100

    Audio{
        id: playMusic
        source: filePath
    }

    Timer{
        id: timer
        interval: 1000;
        running: false;
        repeat: true
        onTriggered: {
            progressBar.value += 1/( playMusic.duration /1000)/// secondsAudioDurationINT
            console.log(playMusic.duration," ",secondsAudioDurationINT, playMusic.duration / secondsAudioDurationINT, progressBar.value)
            secondSong +=1
            //            console.log(progressBar.value)


            if (secondSong == playMusic.duration /1000)
            {
                timer.stop()
            }
            countAudio++

            if (secondSong%60 == 0)
            {
                minuteSong++;
                //secondSong = 0;
            }

        }
    }

    Text {
        id: text1
        x: 224
        y: 33
        width: 56
        height: 17
        text: testMap.getSizeMinuts(playMusic.duration) + ":" + testMap.getSizeSeconds(playMusic.duration)
        font.pixelSize: 12
        anchors.right: parent.right
    }

    ProgressBar {
        id: progressBar
        x: 48
        y: 21
        width: 232
        height: 8
        from: 0
        to: 1
        value: 0//playMusic.duration

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


        id: text2
        x: 48
        y: 33
        width: 56
        height: 17
        text:
        {
            if (secondSong%60 < 10)
            {
                minuteSong + ":0" + secondSong%60
            }
            else
            {
                minuteSong + ":" + secondSong%60
            }
        }


        font.pixelSize: 12
    }

    Rectangle{
        x: 12
        y: 8
        width: 34
        height: 34
        radius: width/2
        color: "white"
        Image {
            id: playerAudio
            x: 0
            y: 0
            width: 34
            height: 34
            source: "qrc:/picture/button/play.png"
            fillMode: Image.PreserveAspectFit
            scale: mousePlayerAudio.containsPress ? 1.1 : 1

            MouseArea{
                id: mousePlayerAudio
                anchors.fill: parent

                hoverEnabled: true

                onClicked: {
                    if (!flagMusic)
                    {
                        playerAudio.source = "qrc:/picture/button/pause.png"
                        timer.start()
                        playMusic.play()
                    }
                    else
                    {
                        playMusic.pause()
                        timer.stop()
                        playerAudio.source = "qrc:/picture/button/play.png"
                    }
                    flagMusic = !flagMusic
                }


            }
        }
    }

    //    Separator{
    //        anchors.top: parent.bottom
    //    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:6}
}
##^##*/
