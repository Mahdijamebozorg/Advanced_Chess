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
            anchors.horizontalCenter: parent.horizontalCenter
            id: errText
            text: "An error!"
        }
        standardButtons: Dialog.Close
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

            //Content
            delegate: Rectangle {
                id: cellRec

                width: src.width / 8
                height: src.height / 8
                border.width: bknd.isMoved(index) ? 3.4 : 0.5
                border.color: bknd.isMoved(index) ? "#42e7ac" : "black"
                color: "#00000000"

                //Cells
                Button {
                    id: srcCell
                    anchors.fill: parent
                    flat: true
                    onClicked: {
                        switch (bknd.choose(index)) {
                            //OK
                        case 2:
                            //highlight canGo and canHit
                            //Used "Connections" to prevent of crowdness here
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

                    //Highlight canGo and canHit cells on choose
                    Connections {
                        target: bknd
                        onChoosen: {

                            //Shows dest choose buttons
                            srcCell.visible = false
                            dest.visible = true

                            //Get destination cells state
                            switch (bknd.cellState(index)) {

                                //Is selected
                            case 3:

                                cellRec.color = "#bca972"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //Can hit
                            case 2:

                                cellRec.color = "#811717"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //Can go
                            case 1:

                                cellRec.color = "#a4883d"
                                cellRec.border.color = "black"
                                cellRec.border.width = 0.5
                                break

                                //Unavailable
                            case 0:
                                //Can set a color for unavailabe cells
                            }
                        }
                    }

                    //Unchoose the piece
                    Connections {
                        target: bknd
                        onUnchoosen: {
                            srcCell.visible = true
                            dest.visible = false
                            cellRec.color = "#00000000"

                            //Heighlight passed cells
                            cellRec.border.color = bknd.isMoved(
                                        index) ? "#42e7ac" : "balck"

                            cellRec.border.width = bknd.isMoved(
                                        index) ? 3.4 : 0.5
                        }
                    }
                }

                //Chessmen icons
                Image {

                    id: chessmanIcon
                    source: bknd.getIcon(index)
                    width: parent.width * 0.95
                    height: parent.height * 0.95

                    //_____________________moving animations
                    OpacityAnimator {
                        id: destOpasity
                        target: chessmanIcon
                        duration: 400
                        from: 1
                        to: 0
                    }
                    ParallelAnimation {
                        id: anim
                        animations: [
                            NumberAnimation {
                                id: pieceXAnim
                                target: chessmanIcon
                                property: "x"
                                from: chessmanIcon.x
                                duration: 400
                            },
                            NumberAnimation {
                                id: pieceYAnim
                                target: chessmanIcon
                                property: "y"
                                from: chessmanIcon.y
                                duration: 400
                            }
                        ]

                        onStopped: {
                            moveSound.play()
                            mystack.replace("GamePage.qml")
                        }
                    }
                    Connections {
                        target: bknd
                        onMoved: {

                            //____________________________________________________ unchoose
                            srcCell.visible = true
                            dest.visible = false
                            cellRec.color = "#00000000"

                            //Heighlight passed cells
                            cellRec.border.color = bknd.isMoved(
                                        index) ? "#42e7ac" : "balck"

                            cellRec.border.width = bknd.isMoved(
                                        index) ? 3.4 : 0.5

                            //___________________________________________________ animations
                            if (bknd.getDestIndex() === index)
                                destOpasity.start()

                            //did not word
                            //                            if (chessmanIcon.source === bknd.getHitPiece())
                            //                                mystack.pop()
                            if (bknd.getSrcIndex() === index) {
                                pieceXAnim.to = (bknd.getDestJ() - bknd.getSrcJ(
                                                     )) * cellRec.width
                                pieceYAnim.to = (bknd.getDestI() - bknd.getSrcI(
                                                     )) * cellRec.height
                                anim.start()
                            }
                        }
                    }
                } //Image End
            } //CellRec End
        } //GridView End

        //New grid buttons for move destination
        GridView {
            id: dest
            //Not scrollable
            interactive: false
            visible: false
            anchors.centerIn: boardImage

            //Ignoring edges of board photo
            width: boardImage.width - boardImage.width * 0.096
            height: boardImage.height - boardImage.height * 0.097
            cellWidth: this.width / 8
            cellHeight: this.height / 8
            model: 64

            //Content
            delegate: Rectangle {
                color: "#00000000"
                width: dest.width / 8
                height: dest.height / 8
                Button {
                    id: destCell
                    anchors.fill: parent
                    flat: true
                    onClicked: {
                        //If piece can go there
                        if (bknd.move(index)) {

                        } //If piece can't go to dest and dest is not its current cell
                        else if (!bknd.unchoosePiece(index)) {
                            errText.text
                                    = persian.checked ? "نمیتوان به آنجا رفت!" : "Can't move there!"
                            wrongChoose.open()
                        }
                    }
                }
            }
        }
    }
    Component.onCompleted: {
        switch (bknd.gameStatus()) {
            ////NORMAL
        case 0:
            bknd.checkRandomMove()
            break

            //CHECKED
        case 1:
            errText.text = persian.checked ? "شما کیش شدید!" : "You're checked!"
            wrongChoose.title = persian.checked ? "کیش" : "Checked"
            wrongChoose.open()
            bknd.checkRandomMove()
            break

            //STALEMATE
        case 2:

            //CHECKMATE
        case 3:
            endOfGame.open()
            break
        }
    }
}
