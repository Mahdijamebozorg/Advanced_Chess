import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    Dialog {
        id: extraMoveDialog
        title: persian.checked ? "حرکت اضافه" : "Extra Move"
        Text {
            id: extraMoveText
            text: ""
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
                textFormat: Text.StyledText
                fontSizeMode: Text.Fit
                minimumPixelSize: 3
                font.pixelSize: 20
                font.bold: true
                color: "#aa882a"
                anchors.top: rightSide.top
                height: rightSide.height * 0.04
                width: rightSide.width * 0.8
                anchors.topMargin: 10
                anchors.horizontalCenter: rightSide.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Column {
                id: scoreCol
                anchors.top: scoresSideText.bottom
                anchors.topMargin: rightSide.height * 0.04
                anchors.horizontalCenter: rightSide.horizontalCenter
                spacing: rightSide.height * 0.04

                //_________________________________________________________________________________ P2 score
                Rectangle {
                    id: scores2Rec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width - 10
                    height: rightSide.height * 0.3
                    anchors.horizontalCenter: scoreCol.horizontalCenter
                    Image {
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        width: parent.width - 2
                        height: parent.height - 2
                        anchors.centerIn: parent
                    }
                    Column {
                        id: score2Col
                        anchors.horizontalCenter: scores2Rec.horizontalCenter
                        anchors.top: scores2Rec.top
                        anchors.topMargin: scores2Rec.height * 0.05
                        Rectangle {
                            id: p2Rec
                            anchors.horizontalCenter: score2Col.horizontalCenter
                            border.color: "#7c6d43"
                            border.width: 1
                            width: scores2Rec.width * 0.6
                            height: scores2Rec.height * 0.22
                            color: "#00000000"
                            Text {
                                id: p2
                                text: bknd.getP2Name()
                                width: p2Rec.width - 2
                                height: p2Rec.height - 2
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 2
                                font.pixelSize: 18
                                font.bold: true
                                color: "#e2d29d"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                anchors.centerIn: parent
                            }
                        }
                        Text {
                            id: p2PositiveScoreText
                            text: persian.checked ? "امتیاز مثبت" : "Positive score:"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            width: scores2Rec.width * 0.6
                            height: scores2Rec.height * 0.19
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                            topPadding: scores2Rec.height * 0.05
                        }
                        Text {
                            id: p2PositiveScore
                            text: bknd.getP2_PScore()
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
                            horizontalAlignment: Text.AlignHCenter
                            height: scores2Rec.height * 0.18
                            width: scores2Rec.width * 0.6
                            color: "#e2d29d"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }

                        Text {
                            id: p2NegativeScoreText
                            text: persian.checked ? "امتیاز منفی" : "Negative score:"
                            horizontalAlignment: Text.AlignHCenter
                            height: scores2Rec.height * 0.18
                            width: scores2Rec.width * 0.6
                            font.bold: true
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                            topPadding: scores2Rec.height * 0.05
                        }
                        Text {
                            id: p2NegativeScore
                            horizontalAlignment: Text.AlignHCenter
                            height: scores2Rec.height * 0.18
                            width: scores2Rec.width * 0.6
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
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
                    height: rightSide.height * 0.3
                    anchors.horizontalCenter: scoreCol.horizontalCenter
                    Image {
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        width: parent.width - 2
                        height: parent.height - 2
                        anchors.centerIn: parent
                    }
                    Column {
                        id: score1Col
                        anchors.horizontalCenter: scores1Rec.horizontalCenter
                        anchors.top: scores1Rec.top
                        anchors.topMargin: scores1Rec.height * 0.05
                        Rectangle {
                            id: p1Rec
                            anchors.horizontalCenter: score1Col.horizontalCenter
                            border.color: "#7c6d43"
                            border.width: 1
                            width: scores1Rec.width * 0.6
                            height: scores1Rec.height * 0.22
                            color: "#00000000"
                            Text {
                                id: p1
                                text: bknd.getP1Name()
                                width: p1Rec.width - 2
                                height: p1Rec.height - 2
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 2
                                font.pixelSize: 18
                                font.bold: true
                                color: "#e2d29d"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                anchors.centerIn: parent
                            }
                        }
                        Text {
                            id: p1PositiveScoreText
                            text: persian.checked ? "امتیاز مثبت" : "Positive score:"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            width: scores1Rec.width * 0.6
                            height: scores1Rec.height * 0.18
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                            topPadding: scores1Rec.height * 0.05
                        }
                        Text {
                            id: p1PositiveScore
                            text: bknd.getP1_PScore()
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
                            horizontalAlignment: Text.AlignHCenter
                            height: scores1Rec.height * 0.18
                            width: scores1Rec.width * 0.6
                            color: "#e2d29d"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }

                        Text {
                            id: p1NegativeScoreText
                            text: persian.checked ? "امتیاز منفی" : "Negative score:"
                            horizontalAlignment: Text.AlignHCenter
                            height: scores1Rec.height * 0.18
                            width: scores1Rec.width * 0.6
                            font.bold: true
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                            topPadding: scores1Rec.height * 0.05
                        }
                        Text {
                            id: p1NegativeScore
                            text: bknd.getP1_NScore()
                            horizontalAlignment: Text.AlignHCenter
                            height: scores1Rec.height * 0.18
                            width: scores1Rec.width * 0.6
                            textFormat: Text.StyledText
                            fontSizeMode: Text.Fit
                            minimumPixelSize: 2
                            font.pixelSize: 15
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
                    width: rightSide.width * 0.8
                    height: rightSide.height * 0.07
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
                            onClicked: if (bknd.extraMove()) {
                                           extraMoveText.text = persian.checked ? "یک حرکت اضافه گرفتید" : "You got one extra move!"
                                           extraMoveDialog.open()
                                       } else {
                                           extraMoveText.text = persian.checked ? "امتیاز کافی ندارید!" : "Not enough scores!"
                                           extraMoveDialog.open()
                                       }

                            Text {
                                text: persian.checked ? "حرکت اضافه" : "Extra Move"
                                color: "#aa882a"
                                anchors.centerIn: parent
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 15
                                height: extraMove.height * 0.9
                                width: extraMove.width * 0.9
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
                //Random move
                Rectangle {
                    id: randomMoveRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width * 0.8
                    height: rightSide.height * 0.07
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
                                if (bknd.randomMove())
                                    mystack.replace("GamePage.qml")
                            }
                            Text {
                                text: persian.checked ? "حرکت تصادفی" : "Random Move"
                                color: "#aa882a"
                                anchors.centerIn: parent
                                textFormat: Text.StyledText
                                fontSizeMode: Text.Fit
                                minimumPixelSize: 3
                                font.pixelSize: 15
                                height: randomMove.height * 0.9
                                width: randomMove.width * 0.9
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
