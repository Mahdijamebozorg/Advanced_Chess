import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3

Dialog {
    id: infoDialog
    title: persian.checked ? "Info" : "اطلاعات"
    standardButtons: Dialog.Close
    width: Screen.width * 0.5
    height: Screen.height * 0.4
    contentItem: Rectangle {
        color: "black"
        ScrollView {
            anchors.fill: parent
            clip: true
            Text {
                id: info
                color: "white"
                text: "
This game is a modified 2P chess with all chess rules plus some features:\n
Score:\n
\t Score is the key to win in this game, some movement have score:\n
\t Hit: Pawn->+3 , Queen->+15 , others->+8 (you can't hit king!)\n
\t Move: Pawn pass away half of board ->+3 , Check enemy king ->+10 , checkmate ->+50\n
\t Extra move: if you have 30 scores, you can make an extram move!\n\n
Negative score:\n
\t Some works add your negatice score , if your negative score reachs 15 , you will have a random move.\n
\t Undo: return last moved piece and adds 5 negative scores\n
\t Touch piece: if you choose a moveable piece and reselct in this turn, you'll get 5 negative scores\n\n
***Important notes***\n
\t Game has auto save and you can continue crashed or closed games\n
\t Negative scores won't be saved in file\n
\t For game name, if a file exists with the same name, file will be overwriten\n
\t In promotion, if you don't choose any chessman, game will crash\n
\t Canceling game will delete save file and restarting will clear move history in file\n
\t Saved Files with free spaces or unreadable moves, won't be opened\n
"
            }
        }
    }
}
