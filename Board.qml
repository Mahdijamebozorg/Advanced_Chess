import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: board

    //Wrong Choose dialog
    Dialog {
        id: wrongChoose
        title: persian.checked ? "خطا" : "Error"
        Text {
            id: errText
            text: "An error!"
        }
    }

    //Promotion dialog
    PromotionDialog {
        id: promotion
    }
    //Promotion control
    Connections {
        target: bknd
        onPromotion: {
            promotion.open()
        }
    }

    //End of game dialog
    EndOfGameDialog {
        id: endOfGame
    }
    //End of game control
    Connections {
        target: bknd
        onEndOFGame: endOfGame.open()
    }

    //Board image
    Image {
        id: boardImage
        anchors.fill: parent
        source: "qrc:/Assets/Images/Board.jpg"

        //A grid of buttons for choosing move src
        GridView {
            id: src
            //Not scrollable
            interactive: false
            anchors.centerIn: boardImage

            //Ignoring edge of board photo
            width: boardImage.width - boardImage.width * 0.096
            height: boardImage.height - boardImage.height * 0.097
            cellWidth: width / 8
            cellHeight: height / 8
            model: 64

            //content
            delegate: Rectangle {
                id: cellRec

                width: src.width / 8
                height: src.height / 8
                border.width: bknd.isMoved(index) ? 3.4 : 0.5

                border.color: bknd.isMoved(index) ? "#42e7ac" : "black"
                color: "#00000000"

                //cells
                Button {
                    id: srcCell
                    anchors.fill: parent
                    flat: true
                    onClicked: {
                        switch (bknd.choose(index)) {
                            //OK
                        case 2:
                            //Used "Connections" to prevent crowdness
                            break

                            //Unaccessable
                        case 1:
                            errText.text = persian.checked ? "نوبت این رنگ نیست!" : "It's not turn of this color!"
                            wrongChoose.open()
                            break

                            //Empty
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

                            //shows dest choose buttons
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

                //Chessmen
                Image {
                    id: chessmanIcon
                    source: bknd.getIcon(index)
                    anchors.centerIn: parent
                    width: parent.width * 0.95
                    height: parent.height * 0.95
                }
            }
        }

        //new grid buttons for move destination
        GridView {
            id: dest
            //not scrollable
            interactive: false
            visible: false
            anchors.centerIn: boardImage

            //ignoring edge of board photo
            width: boardImage.width - boardImage.width * 0.096
            height: boardImage.height - boardImage.height * 0.097
            cellWidth: this.width / 8
            cellHeight: this.height / 8
            model: 64

            //content
            delegate: Button {
                id: destCell
                width: dest.width / 8
                height: dest.height / 8
                flat: true
                onClicked: {
                    //if piece can go there
                    if (bknd.move(index))
                        mystack.replace("GamePage.qml")
                    else //if piece can't go there and it's not its current square
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
