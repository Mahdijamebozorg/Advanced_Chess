import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: left
    Dialog {
        Text {
            id: alertCancelText
            text: "Data will be lost"
        }
        id: cancelAlert
        width: 150
        height: 100
        title: "Are you sure?"
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: mystack.pop()
        onRejected: cancelalert.close()
    }
    Dialog {
        Text {
            id: alertRestartText
            text: "Data will be lost"
        }
        id: restartAlert
        width: 150
        height: 100
        title: "Are you sure?"
        standardButtons: Dialog.Ok | Dialog.Cancel
        //        onAccepted:
        onRejected: restartAlert.close()
    }
    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            id: leftSide
            source: "qrc:/Assets/Images/Wood5.jpg"
            width: parent.width - 2
            height: parent.height - 2
            anchors.centerIn: parent

            //game name
            Rectangle {
                id: gameNameRec
                color: "#00000000"
                border.color: "#7c6d43"
                width: leftSide.width - 2
                height: leftSide.height * 0.15
                anchors.top: leftSide.top
                anchors.topMargin: 10
                anchors.horizontalCenter: leftSide.horizontalCenter

                Column {
                    id: gamenamecol
                    anchors.centerIn: parent
                    spacing: 20
                    Text {
                        id: gameNameText
                        text: "Game name:"
                        font.bold: true
                        color: "#aa882a"
                        anchors.horizontalCenter: gamenamecol.horizontalCenter
                    }

                    Text {
                        id: gameName
                        text: bknd.getGameName()
                        color: "#e2d29d"
                        anchors.horizontalCenter: gamenamecol.horizontalCenter
                    }
                }
            }

            //buttons
            Column {
                id: orderCol
                anchors.bottom: leftSide.bottom
                anchors.bottomMargin: 15
                anchors.horizontalCenter: leftSide.horizontalCenter
                spacing: 20

                //undo
                Rectangle {
                    id: undoRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width - 20
                    height: leftSide.height * 0.08
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Button {
                        id: undo
                        width: undoRec.width - 2
                        anchors.centerIn: parent
                        height: undoRec.height - 2
                        flat: true
                        Text {
                            text: "Undo"
                            color: "#aa882a"
                            anchors.centerIn: parent
                        }
                    }
                }

                //restart
                Rectangle {
                    id: restartRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width - 20
                    height: leftSide.height * 0.08
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Button {
                        id: restart
                        width: restartRec.width - 2
                        anchors.centerIn: parent
                        height: restartRec.height - 2
                        flat: true
                        Text {
                            text: "Restart"
                            color: "#aa882a"
                            anchors.centerIn: parent
                        }
                        onPressed: restartAlert.open()
                    }
                }

                //cancel
                Rectangle {
                    id: cancelRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width - 20
                    height: leftSide.height * 0.08
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Button {
                        id: cancel
                        width: cancelRec.width - 2
                        anchors.centerIn: parent
                        height: cancelRec.height - 2
                        flat: true
                        onClicked: {
                            cancelAlert.open()
                        }
                        Text {
                            text: "Cancel"
                            color: "#aa882a"
                            anchors.centerIn: parent
                        }
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

