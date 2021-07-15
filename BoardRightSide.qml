import QtQuick 2.9

Item {
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
                text: "Scores:"
                font.pixelSize: 20
                font.bold: true
                color: "#aa882a"
                anchors.top: rightSide.top
                anchors.topMargin: 30
                anchors.horizontalCenter: rightSide.horizontalCenter
            }
            Column {
                id: scoreCol
                anchors.centerIn: parent
                spacing: 20

                //P1 score
                Rectangle {
                    id: scores1Rec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width - 2
                    height: rightSide.height / 3
                    anchors.horizontalCenter: scoreCol.horizontalCenter

                    Column {
                        id: score1Col
                        anchors.centerIn: parent
                        spacing: 15
                        Rectangle {
                            anchors.horizontalCenter: score1Col.horizontalCenter
                            border.color: "#7c6d43"
                            border.width: 1
                            width: 100
                            height: 40
                            color: "#00000000"
                            Text {
                                id: p1
                                text: "P1 name"
                                font.bold: true
                                font.pixelSize: 18
                                color: "#e2d29d"
                                anchors.centerIn: parent
                            }
                        }
                        Text {
                            id: p1PositiveScoreText
                            text: "Positive score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }
                        Text {
                            id: p1PositiveScore
                            text: "0"
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }

                        Text {
                            id: p1NegativeScoreText
                            text: "Negative score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }
                        Text {
                            id: p1NegativeScore
                            text: "0"
                            color: "#aa882a"
                            anchors.horizontalCenter: score1Col.horizontalCenter
                        }
                    }
                }

                //P2 score
                Rectangle {
                    id: scores2Rec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: rightSide.width - 2
                    height: rightSide.height / 3
                    anchors.horizontalCenter: scoreCol.horizontalCenter
                    Column {
                        id: score2Col
                        anchors.centerIn: parent
                        spacing: 15
                        Rectangle {
                            anchors.horizontalCenter: score2Col.horizontalCenter
                            border.color: "#7c6d43"
                            border.width: 1
                            width: 100
                            height: 40
                            color: "#00000000"
                            Text {
                                id: p2
                                text: "P2 name"
                                font.bold: true
                                font.pixelSize: 18
                                color: "#e2d29d"
                                anchors.centerIn: parent
                            }
                        }
                        Text {
                            id: p2PositiveScoreText
                            text: "Positive score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }
                        Text {
                            id: p2PositiveScore
                            text: "0"
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }

                        Text {
                            id: p2NegativeScoreText
                            text: "Negative score:"
                            font.bold: true
                            font.pixelSize: 15
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }
                        Text {
                            id: p2NegativeScore
                            text: "0"
                            color: "#aa882a"
                            anchors.horizontalCenter: score2Col.horizontalCenter
                        }
                    }
                }
            }
        }
    }
}
