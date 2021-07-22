import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: left

    Dialog {
        id: cancelAlert
        title: persian.checked ? "آیا مطمعنید؟" : "Are you sure?"
        Text {
            id: alertCancelText
            text: persian.checked ? "اطلاعات بازی حذف خواهند شد" : "Game data will be lost"
        }
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: mystack.pop()
        onRejected: cancelalert.close()
    }
    Dialog {
        id: restartAlert
        title: persian.checked ? "آیا مطمعنید؟" : "Are you sure?"
        Text {
            id: alertRestartText
            text: persian.checked ? "اطلاعات بازی حذف خواهند شد" : "Game data will be lost"
        }
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            mystack.replace("GamePage.qml")
        }
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
                width: leftSide.width - 10
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
                        text: persian.checked ? "نام بازی" : "Game name"
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
                    width: leftSide.width - 30
                    height: leftSide.height * 0.07
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: undoRec.width - 2
                        height: undoRec.height - 2
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        Button {
                            id: undo
                            anchors.fill: parent
                            flat: true
                            onClicked: {
                                bknd.undo()
                                mystack.replace("GamePage.qml")
                            }
                            Text {
                                text: persian.checked ? "بازگشت" : "Undo"
                                color: "#aa882a"
                                anchors.centerIn: parent
                            }
                        }
                    }
                }

                //restart
                Rectangle {
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width - 30
                    height: leftSide.height * 0.07
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: undoRec.width - 2
                        height: undoRec.height - 2
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        Button {
                            id: restart
                            anchors.fill: parent
                            flat: true
                            Text {
                                text: persian.checked ? "شروع مجدد" : "Restart"
                                color: "#aa882a"
                                anchors.centerIn: parent
                            }
                            onPressed: restartAlert.open()
                        }
                    }
                }
                //cancel
                Rectangle {
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width - 30
                    height: leftSide.height * 0.07
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: undoRec.width - 2
                        height: undoRec.height - 2
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        Button {
                            anchors.fill: parent
                            flat: true
                            onClicked: {
                                cancelAlert.open()
                            }
                            Text {
                                text: persian.checked ? "انصراف" : "Cancel"
                                color: "#aa882a"
                                anchors.centerIn: parent
                            }
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

