import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    Dialog {
        id: scoreError
        title: persian.checked ? "خطا" : "Error"
        Text {
            id: scoreErrorText
            text: persian.checked ? "امتیاز کافی ندارید!" : "Not enough scores!"
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            width: parent.width - 2
            height: parent.height - 2
            id: rightSide
            anchors.centerIn: parent
            source: "qrc:/Assets/Images/Wood5.jpg"

            Text {
                id: scoresSideText
                text: persian.checked ? "امتیاز ها" : "Scores:"
                font.pixelSize: 20
                font.bold: true
                color: "#aa882a"
                anchors.top: rightSide.top
                anchors.topMargin: 10
                anchors.horizontalCenter: rightSide.horizontalCenter
            }
            Column {
                id: scoreCol
                anchors.top: scoresSideText.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: rightSide.horizontalCenter
                spacing: 20

                //_________________________________________________________________________________ P2 score
                Rectangle {
                    id: scores2Rec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width - 10
                    height: rightSide.height / 3
                    anchors.horizontalCenter: scoreCol.horizontalCenter
                    Column {
                        id: score2Col
                        anchors.centerIn: parent
                        spacing: 15
                        Rectangle {
                            id: p2Rec
                            anchors.horizontalCenter: score2Col.horizontalCenter
                            border.color: "#7c6d43"
                            border.width: 1
                            width: 160
                            height: 40
                            color: "#00000000"
                            Text {
                                id: p2
                                text: bknd.getP2Name()
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 18
                                font.bold: true
                                color: "#e2d29d"
                                width: p2Rec.width - 5
                                horizontalAlignment: Text.AlignHCenter
                                anchors.centerIn: parent
                            }
                        }
                        Text {
                            id: p2PositiveScoreText
                            text: persian.checked ? "امتیاز مثبت" : "Positive score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }
                        Text {
                            id: p2PositiveScore
                            text: bknd.getP2_PScore()
                            color: "#e2d29d"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }

                        Text {
                            id: p2NegativeScoreText
                            text: persian.checked ? "امتیاز منفی" : "Negative score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }
                        Text {
                            id: p2NegativeScore
                            text: bknd.getP2_NScore()
                            color: "#e2d29d"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }
                    }
                }

                //______________________________________________________________________P1 score
                Rectangle {
                    id: scores1Rec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width - 10
                    height: rightSide.height / 3
                    anchors.horizontalCenter: scoreCol.horizontalCenter

                    Column {
                        id: score1Col
                        anchors.centerIn: parent
                        spacing: 15
                        Rectangle {
                            id: p1Rec
                            anchors.horizontalCenter: score1Col.horizontalCenter
                            border.color: "#7c6d43"
                            border.width: 1
                            width: 160
                            height: 40
                            color: "#00000000"
                            Text {
                                id: p1
                                text: bknd.getP1Name()
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 18
                                font.bold: true
                                color: "#e2d29d"
                                width: p1Rec.width - 5
                                horizontalAlignment: Text.AlignHCenter
                                anchors.centerIn: parent
                            }
                        }
                        Text {
                            id: p1PositiveScoreText
                            text: persian.checked ? "امتیاز مثبت" : "Positive score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }
                        Text {
                            id: p1PositiveScore
                            text: bknd.getP1_PScore()
                            color: "#e2d29d"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }

                        Text {
                            id: p1NegativeScoreText
                            text: persian.checked ? "امتیاز منفی" : "Negative score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }
                        Text {
                            id: p1NegativeScore
                            text: bknd.getP1_NScore()
                            color: "#e2d29d"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }
                    }
                }
                //extra move
                Rectangle {
                    id: extraMoveRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width - 50
                    height: rightSide.height * 0.06
                    anchors.horizontalCenter: scoreCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: extraMoveRec.width - 2
                        height: extraMoveRec.height - 2
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        Button {
                            id: extraMove
                            anchors.fill: parent
                            flat: true
                            onClicked: if (!bknd.extraMove())
                                           scoreError.open()

                            Text {
                                text: persian.checked ? "حرکت اضافه" : "Extra Move"
                                color: "#aa882a"
                                anchors.centerIn: parent
                            }
                        }
                    }
                }
                //Random move
                Rectangle {
                    id: randomMoveRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width - 50
                    height: rightSide.height * 0.06
                    anchors.horizontalCenter: scoreCol.horizontalCenter
                    Image {
                        anchors.centerIn: parent
                        width: randomMoveRec.width - 2
                        height: randomMoveRec.height - 2
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        Button {
                            id: randomMove
                            anchors.fill: parent
                            flat: true
                            onClicked: {

                            }
                            Text {
                                text: persian.checked ? "حرکت تصادفی" : "Random Move"
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
