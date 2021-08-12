import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Window 2.3

Page {
    id: gamePage
    title: persian.checked ? "صفحه ی بازی" : "Game Page"
    anchors.fill: parent

    background: Image {
        source: "qrc:/Assets/Images/Wood2.jpg"
    }

    Board {
        id: board
        height: parent.height * 0.55
        width: parent.height * 0.55
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
    }

    //orders
    BoardLeftSide {
        id: leftSide
        anchors.right: board.left
        anchors.rightMargin: 8
        width: parent.width * 0.125
        height: board.height
        anchors.verticalCenter: board.verticalCenter
    }

    //scores
    BoardRightSide {
        id: rightSide
        anchors.left: board.right
        anchors.leftMargin: 8
        anchors.right: gamePage.right
        width: parent.width * 0.125
        height: board.height
        anchors.verticalCenter: board.verticalCenter
    }

    //P1 outs
    BoardBottomSide {
        id: outs1
        anchors.top: board.bottom
        anchors.topMargin: 8
        width: board.width
        height: parent.height * 0.13
        anchors.horizontalCenter: board.horizontalCenter
    }

    //P2 outs
    BoardTopSide {
        id: outs2
        anchors.bottom: board.top
        anchors.bottomMargin: 8
        width: board.width
        height: parent.height * 0.13
        anchors.horizontalCenter: board.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

