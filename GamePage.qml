import QtQuick 2.9
import QtQuick.Controls 2.5

Page {
    anchors.fill: parent
    id: gamePage
    title: persian.checked ? "صفحه ی بازی" : "Game Page"
    Image {
        anchors.fill: parent
        source: "qrc:/Assets/Images/Wood2.jpg"

        Board {
            id: board
            height: 600
            width: 600
            x: gamePage.width / 2 - width / 2
            y: gamePage.height / 2 - height / 2
        }

        //orders
        BoardLeftSide {
            id: leftSide
            y: (gamePage.height - board.height) / 2 + board.height / 2 - height / 2
            anchors.right: board.left
            anchors.rightMargin: 8
            width: 200
            height: board.height
        }

        //scores
        BoardRightSide {
            id: rightSide
            y: (gamePage.height - board.height) / 2 + board.height / 2 - height / 2
            anchors.left: board.right
            anchors.leftMargin: 8
            width: 200
            height: board.height
        }

        //P1 outs
        BoardTopSide {
            id: outs2
            anchors.bottom: board.top
            anchors.bottomMargin: 8
            width: board.width
            height: 130
            x: (gamePage.width - board.width) / 2 + board.width / 2 - width / 2
        }

        //P2 outs
        BoardBottomSide {
            id: outs1
            anchors.top: board.bottom
            anchors.topMargin: 8
            width: board.width
            height: 130
            x: (gamePage.width - board.width) / 2 + board.width / 2 - width / 2
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

