import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Dialogs 1.2

Dialog {
    id: endOfGame
    height: parent.height * 0.17
    title: persina.checked ? "پایان بازی" : "End of Game"
    width: parent.width * 0.3

    contentItem: Rectangle {

        border.color: "#7c6d43"
        anchors.fill: parent

        //BackGround
        Image {
            id: name
            source: "qrc:/Assets/Images/Wood2.jpg"
            width: parent.width - 2
            height: parent.height - 2
            anchors.centerIn: parent
        }

        Rectangle {
            width: parent.width * 0.6
            height: parent.height * 0.35
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.07
            border.color: "#7c6d43"
            color: "#00000000"
            Text {
                id: endGameText
                text: ""
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                height: parent.height - 2
                width: parent.width - 2
                font.pixelSize: this.width * 0.1
                Component.onCompleted: {
                    switch (bknd.winner()) {
                        //user 1
                    case 0:
                        endOfGame.title = persian.checked ? "کیش و مات" : "Checkmate"
                        this.text = persian.checked ? "برنده: " + bknd.getP1Name(
                                                          ) : "Winner: " + bknd.getP1Name()
                        break
                        //user 2
                    case 1:
                        endOfGame.title = persian.checked ? "کیش و مات" : "Checkmate"
                        this.text = persian.checked ? "برنده: " + bknd.getP2Name(
                                                          ) : "Winner: " + bknd.getP2Name()
                        break
                        //draw
                    case 2:
                        endOfGame.title = persian.checked ? "پات" : "Stalemate"
                        this.text = persian.checked ? "مساوی" : "Draw"
                        break
                    }
                }
            }
        }

        Row {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.07
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: this.width * 0.03

            width: parent.width * 0.9
            height: parent.height * 0.4

            Button {
                id: dialogUndoButton
                text: persian.checked ? "بازگشت" : "Undo"
                width: parent.width * 0.3
                height: parent.height
                font.pixelSize: this.width * 0.1
                onClicked: {
                    bknd.undo()
                    mystack.replace("GamePage.qml")
                }
            }
            Button {
                id: dialogEndGameButton
                text: persian.checked ? "اتمام بازی" : "End game"
                width: parent.width * 0.3
                height: parent.height
                font.pixelSize: this.width * 0.1
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
                font.pixelSize: this.width * 0.1
                onClicked: {
                    bknd.restartGame()
                    mystack.replace("GamePage.qml")
                }
            }
        }
    }
}
