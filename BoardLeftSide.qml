import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3

Item {
    id: left

    EndOfGameDialog {
        id: endOfGame
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
            bknd.restartGame()
            mystack.replace("GamePage.qml")
        }
        onRejected: restartAlert.close()
    }

    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            id: leftSide
            source: "qrc:/Assets/Images/Wood5.png"
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
                Image {
                    source: "qrc:/Assets/Images/wood1.png"
                    width: parent.width - 2
                    height: parent.height - 2
                    anchors.centerIn: parent
                }
                Column {
                    id: gamenamecol
                    anchors.centerIn: parent
                    width: gameNameRec.width
                    height: gameNameRec.height * 0.9
                    spacing: gamenamecol.height * 0.02
                    Text {
                        id: gameNameText
                        text: persian.checked ? "نام بازی" : "Game name"
                        font.bold: true
                        color: "#aa882a"
                        anchors.horizontalCenter: gamenamecol.horizontalCenter
                        width: gamenamecol.width * 0.8
                        height: gamenamecol.height * 0.45
                        textFormat: Text.StyledText
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 3
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Text {
                        id: gameName
                        text: bknd.getGameName()
                        color: "#e2d29d"
                        anchors.horizontalCenter: gamenamecol.horizontalCenter
                        width: gamenamecol.width * 0.8
                        height: gamenamecol.height * 0.45
                        textFormat: Text.StyledText
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 3
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            //buttons
            Column {
                id: orderCol
                anchors.bottom: leftSide.bottom
                anchors.bottomMargin: parent.height * 0.05
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                //undo
                Rectangle {
                    id: undoRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width * 0.8
                    height: leftSide.height * 0.07
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: undoRec.width - 2
                        height: undoRec.height - 2
                        source: "qrc:/Assets/Images/wood1.png"
                        Button {
                            id: undo
                            anchors.fill: parent
                            flat: true
                            onClicked: {
                                bknd.undo()
                                //                                mystack.replace("GamePage.qml")
                            }
                            Text {
                                text: persian.checked ? "بازگشت" : "Undo"
                                color: "#aa882a"
                                anchors.centerIn: parent
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 15
                                height: parent.height * 0.9
                                width: parent.width * 0.9
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }

                //restart
                Rectangle {
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width * 0.8
                    height: leftSide.height * 0.07
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: undoRec.width - 2
                        height: undoRec.height - 2
                        source: "qrc:/Assets/Images/wood1.png"
                        Button {
                            id: restart
                            anchors.fill: parent
                            flat: true
                            Text {
                                text: persian.checked ? "شروع مجدد" : "Restart"
                                color: "#aa882a"
                                anchors.centerIn: parent
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 15
                                height: parent.height * 0.9
                                width: parent.width * 0.9
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            onPressed: restartAlert.open()
                        }
                    }
                }
                //save & Exit Rec
                Rectangle {
                    id: saveExitRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width * 0.8
                    height: leftSide.height * 0.07
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: cancelRec.width - 2
                        height: cancelRec.height - 2
                        source: "qrc:/Assets/Images/wood1.png"
                        Button {
                            anchors.fill: parent
                            flat: true
                            onClicked: {
                                bknd.saveAndExit()
                                mystack.pop()
                            }
                            Text {
                                text: persian.checked ? "ذخیره و خروج" : "Save & Exit"
                                color: "#aa882a"
                                anchors.centerIn: parent
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 15
                                height: parent.height * 0.9
                                width: parent.width * 0.9
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }

                //cancel
                Rectangle {
                    id: cancelRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: leftSide.width * 0.8
                    height: leftSide.height * 0.07
                    anchors.horizontalCenter: orderCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: cancelRec.width - 2
                        height: cancelRec.height - 2
                        source: "qrc:/Assets/Images/wood1.png"
                        Button {
                            anchors.fill: parent
                            flat: true
                            onClicked: {
                                bknd.setCanceler()
                                endOfGame.open()
                            }
                            Text {
                                text: persian.checked ? "تسلیم" : "Surrend"
                                color: "#aa882a"
                                anchors.centerIn: parent
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 15
                                height: parent.height * 0.9
                                width: parent.width * 0.9
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
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

