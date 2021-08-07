import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2

Dialog {
    id: endOfGame
    title: persian.checked ? "پایان بازی" : "End game"
    height: parent.height * 0.17
    width: parent.width * 0.3

    contentItem: Rectangle {

        border.color: "#7c6d43"
        anchors.fill: parent

        //BackGround
        Image {
            id: name
            source: "qrc:/Assets/Images/Wood2.jpg"
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
        }

        Text {
            id: endGameText
            text: persian.checked ? "برنده: " + "ali" : "Winner: " + "ali"
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width * 0.8
            height: parent.height * 0.4
            font.pixelSize: this.height * 0.4
        }

        Row {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.1
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: this.width * 0.03

            width: parent.width * 0.9
            height: parent.height * 0.4

            Button {
                id: dialogUndoButton
                text: persian.checked ? "بازگشت" : "Undo"
                width: parent.width * 0.3
                height: parent.height
                font.pixelSize: this.height * 0.15
                onClicked: {
                    bknd.undo()
                    mystack.replace("GamePage.qml")
                }
            }
            Button {
                id: dialogEndGameButton
                text: persian.checked ? "پایان بازی" : "End game"
                width: parent.width * 0.3
                height: parent.height
                font.pixelSize: this.height * 0.15
                onClicked: {
                    endOfGame.close()
                    bknd.endGame()
                    mystack.pop()
                    window.width = Screen.width * 0.5
                    window.height = Screen.height * 0.75
                    fullScreen.checked = false
                }
            }
            Button {
                id: dialogRestartButton
                text: persian.checked ? "شروع مجدد" : "Restart"
                width: parent.width * 0.3
                height: parent.height
                font.pixelSize: this.height * 0.15
                onClicked: {
                    bknd.restartGame()
                    mystack.replace("GamePage.qml")
                }
            }
        }
    }
}
