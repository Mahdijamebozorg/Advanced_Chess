import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    id: board
    width: 600
    height: 600
    Image {
        id: boardImage
        anchors.fill: parent
        source: "qrc:/Images/Board.jpg"

        GridView {
            id: gridView
            anchors.centerIn: boardImage
            width: boardImage.width - 60
            height: boardImage.height - 60
            cellWidth: width / 8
            cellHeight: height / 8
            model: 64

            delegate: Button {
                width: gridView.width / 8
                height: gridView.height / 8
                flat: true
                onClicked: {
                    bknd.choose(index)
                }
                Text {
                    //                    source: ""
                    text: index + 1
                    color: "red"
                    anchors.centerIn: parent
                    width: parent.width * 0.85
                    height: parent.height * 0.85
                }
            }
        }
    }
}
