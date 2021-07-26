import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: board
    Dialog {
        id: wrongChoose
        title: persian.checked ? "خطا" : "Error"
        Text {
            id: errText
            text: "An error!"
        }
    }
    Dialog {
        id: promotion
        title: persian.checked ? "ارتقا" : "Promotion"
        width: boardImage.width * 0.4
        height: boardImage.height * 0.4
        contentItem: Rectangle {
            id: promotionRec
            border.color: "#7c6d43"
            border.width: 2
            anchors.centerIn: parent
            Image {
                id: name
                source: "qrc:/Assets/Images/Wood2.jpg"
                width: promotionRec.width - 2
                height: promotionRec.height - 2
                anchors.centerIn: promotionRec
            }
            Text {
                id: promotionText
                text: persian.checked ? "به کدام یک میخواهید ارتقا پیدا کنید؟" : "Which one you want promote to?"
                color: "white"
                textFormat: Text.StyledText
                fontSizeMode: Text.Fit
                minimumPixelSize: 5
                font.pixelSize: 18
                width: promotionRec.width * 0.9
                height: promotionRec.height * 0.3
                anchors.horizontalCenter: promotionRec.horizontalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Grid {
                id: promotionGrid
                height: promotionRec.height * 0.7
                width: promotionRec.width * 0.9
                anchors.top: promotionText.bottom
                anchors.horizontalCenter: promotionRec.horizontalCenter
                anchors.bottom: promotionRec.bottom
                anchors.bottomMargin: height * 0.1
                rows: 2
                columns: 2
                horizontalItemAlignment: Grid.AlignHCenter
                verticalItemAlignment: Grid.AlignVCenter
                columnSpacing: this.width * 0.1
                rowSpacing: this.height * 0.1
                Rectangle {
                    id: queenRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: promotionGrid.width * 0.45
                    height: promotionGrid.height * 0.45
                    Image {
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        width: parent.width - 2
                        height: parent.height - 2
                        anchors.centerIn: parent
                    }
                    Button {
                        id: promoteToQueen
                        flat: true
                        icon.source: "qrc:/Assets/Icons/WQueen.png"
                        icon.width: this.width * 0.9
                        icon.height: this.height * 0.9
                        icon.color: "#9c843c"
                        width: queenRec.width - 2
                        height: queenRec.height - 2
                        onClicked: {
                            bknd.promote(4)
                            mystack.replace("GamePage.qml")
                        }
                    }
                }
                Rectangle {
                    id: rookRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: promotionGrid.width * 0.45
                    height: promotionGrid.height * 0.45
                    Image {
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        width: parent.width - 2
                        height: parent.height - 2
                        anchors.centerIn: parent
                    }
                    Button {
                        id: promoteToRook
                        flat: true
                        icon.source: "qrc:/Assets/Icons/WRook.png"
                        icon.width: this.width * 0.9
                        icon.height: this.height * 0.9
                        icon.color: "#9c843c"
                        width: rookRec.width - 2
                        height: rookRec.height - 2

                        onClicked: {
                            bknd.promote(3)
                            mystack.replace("GamePage.qml")
                        }
                    }
                }
                Rectangle {
                    id: bihopRec
                    color: "#00000000"
                    border.color: "#9c843c"
                    width: promotionGrid.width * 0.45
                    height: promotionGrid.height * 0.45
                    Image {
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        width: parent.width - 2
                        height: parent.height - 2
                        anchors.centerIn: parent
                    }
                    Button {
                        id: promoteToBishop
                        flat: true
                        icon.source: "qrc:/Assets/Icons/WBishop.png"
                        icon.width: this.width * 0.9
                        icon.height: this.height * 0.9
                        icon.color: "#9c843c"
                        width: bihopRec.width - 2
                        height: bihopRec.height - 2
                        onClicked: {
                            bknd.promote(1)
                            mystack.replace("GamePage.qml")
                        }
                    }
                }
                Rectangle {
                    id: knightRec
                    color: "#00000000"
                    border.color: "#7c6d43"
                    width: promotionGrid.width * 0.45
                    height: promotionGrid.height * 0.45
                    Image {
                        source: "qrc:/Assets/Images/wood1.jpeg"
                        width: parent.width - 2
                        height: parent.height - 2
                        anchors.centerIn: parent
                    }
                    Button {
                        id: promoteToKnight
                        flat: true
                        icon.source: "qrc:/Assets/Icons/WKnight.png"
                        icon.width: this.width * 0.9
                        icon.height: this.height * 0.9
                        icon.color: "#9c843c"
                        width: knightRec.width - 2
                        height: knightRec.height - 2
                        onClicked: {
                            bknd.promote(2)
                            mystack.replace("GamePage.qml")
                        }
                    }
                }
            }
        }
    }
    //??
    Connections {
        target: bknd
        onPromotion: {
            promotion.open()
        }
    }
    Image {
        id: boardImage
        anchors.fill: parent
        source: "qrc:/Assets/Images/Board.jpg"

        //a grid of buttons for move source
        GridView {
            interactive: false
            id: src
            anchors.centerIn: boardImage
            width: boardImage.width - boardImage.width * 0.096
            height: boardImage.height - boardImage.height * 0.097
            cellWidth: width / 8
            cellHeight: height / 8
            model: 64

            delegate: Rectangle {
                id: cellRec

                width: src.width / 8
                height: src.height / 8
                border.width: bknd.isMoved(index) ? 3.4 : 0.5

                border.color: bknd.isMoved(index) ? "#42e7ac" : "black"
                color: "#00000000"
                Button {
                    id: srcCell
                    anchors.fill: parent
                    flat: true
                    onClicked: {
                        promotion.open()
                        switch (bknd.choose(index)) {
                            //OK
                        case 2:
                            //used "Connections" to prevent crowdness
                            break

                            //unaccessable
                        case 1:
                            errText.text = persian.checked ? "نوبت این رنگ نیست!" : "It's not turn of this color!"
                            wrongChoose.open()
                            break

                            //empty
                        case 0:
                            errText.text
                                    = persian.checked ? "این خانه خالی است!" : "This tile is empty!"
                            wrongChoose.open()
                            break
                        }
                    }

                    //highlight canGo and canHit cells on choose
                    Connections {
                        target: bknd
                        onChoosen: {

                            //shows second choose buttons
                            srcCell.visible = false
                            dest.visible = true

                            switch (bknd.cellState(index)) {
                                //is selected
                            case 3:

                                cellRec.color = "#bca972"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //can hit
                            case 2:

                                cellRec.color = "#811717"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //can go
                            case 1:

                                cellRec.color = "#a4883d"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //unavailable
                            case 0:
                                //can set a color for unavailabe squares
                            }
                        }
                    }

                    //unchoose the piece
                    Connections {
                        target: bknd
                        onUnchoosen: {
                            srcCell.visible = true
                            dest.visible = false
                            cellRec.color = "#00000000"

                            cellRec.border.color = bknd.isMoved(
                                        index) ? "#42e7ac" : "balck"

                            cellRec.border.width = bknd.isMoved(
                                        index) ? 3.4 : 0.5
                        }
                    }
                }
                Image {
                    id: chessmanIcon
                    source: bknd.getIcon(index)
                    anchors.centerIn: parent
                    width: parent.width * 0.85
                    height: parent.height * 0.85
                }
            }
        }

        //for setting colors
        Rectangle {
            id: colorTest
            color: "#9c843c"
            width: 0
            height: 0
        }
        //new grid buttons for destination
        GridView {
            interactive: false
            id: dest
            visible: false
            anchors.centerIn: boardImage
            width: boardImage.width - 60
            height: boardImage.height - 60
            cellWidth: width / 8
            cellHeight: height / 8
            model: 64

            delegate: Button {
                id: destCell
                width: dest.width / 8
                height: dest.height / 8
                flat: true
                onClicked: {

                    //if piece can go there
                    if (bknd.move(index)) {
                        mystack.replace("GamePage.qml")
                    } else {
                        //if piece can't go there and it's not its current square
                        if (!bknd.unchoosePiece(index)) {
                            errText.text
                                    = persian.checked ? "نمیتوان به آنجا رفت!" : "Can't move there!"
                            wrongChoose.open()
                        }
                    }
                }
            }
        }
    }
}
