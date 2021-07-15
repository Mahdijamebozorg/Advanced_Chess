import QtQuick 2.9

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"
        Image {
            width: board.width - 2
            height: 128
            id: wood4
            anchors.centerIn: parent
            source: "qrc:/Assets/Images/Wood5.jpg"
        }
    }
}
