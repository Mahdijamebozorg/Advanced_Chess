# Advanced Chess
Graphical 2P chess built with Qt Quick QML and C++

<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="Images/ScreenShots/icon.png" alt="Icon" width="80" height="80">
  </a>
</div>

## Game features:
- Save game
- View, load and delete saved games
- Auto save the game on crash or unprincipled closing
- Highlight cells the piece can go or hit
- Undo
- Positive and negative scores
- Random moves
- Extra moves
- Background music
- Full screen mode
- Bilingual (English and Persian)
- Animations
- ...

## Home Page
[![Home Screen Shot][Home]](Home)

## Login Page
[![Login Screen Shot][Login]](Login-url)
  
## Load Game
[![Load Screen Shot][Load]](Load-url)

## Game Page
[![Game Screen Shot][Game]](Game-url)

## Promotion Dialog
[![Promotion Screen Shot][Promotion]](Promotion-url)

## Game rules:
This game is a modified 2P chess with all chess rules plus some features:
### Winner:
If game ends by checkmate or stalemate, winner is player who has more scores,
but if a player presses Surrend, other player wins.
### Score:
Score is the key to win in this game, some movement have score:
Hit: Pawn->+3 , Queen->+15 , others->+8 (you can't hit king!)
Move: Pawn pass away half of board ->+3 , Check enemy king ->+10 , checkmate ->+50
Extra move: if you have 30 scores, you can make an extra move!
### Negative score:
Some works add your negatice score , if your negative score reachs 15 , you will have a random move.
Undo: return last moved piece and adds 5 negative scores
Touch piece: if you choose a moveable piece and reselct in this turn, you'll get 5 negative scores
### Important notes
- Game has auto save and you can continue crashed or closed games
- Negative scores won't be saved in file
- For game name, if a file exists with the same name, file will be overwriten
- In promotion, if you don't choose any chessman, game will crash, but you can continue game by laoding it
- Canceling game will delete save file and restarting will clear move history in file
- Saved Files with free spaces or unreadable moves, won't be opened

## Built With

* [![Qt][Qt.com]][Qt-url]
* [![C++][C++.com]][C++-url]

[Home]: Images/ScreenShots/home.PNG
[Login]: Images/ScreenShots/login.PNG
[Load]: Images/ScreenShots/load.PNG
[Game]: Images/ScreenShots/game.PNG
[Promotion]: Images/ScreenShots/promotion.PNG

[Home-url]: https://github.com/Mahdijamebozorg/Advanced_Chess/tree/main/Images/ScreenShots/home.PNG
[Login-url]: https://github.com/Mahdijamebozorg/Advanced_Chess/tree/main/Images/ScreenShots/login.PNG
[Load-url]: https://github.com/Mahdijamebozorg/Advanced_Chess/tree/main/Images/ScreenShots/load.PNG
[Game-url]: https://github.com/Mahdijamebozorg/Advanced_Chess/tree/main/Images/ScreenShots/game.PNG
[Promotion-url]: https://github.com/Mahdijamebozorg/Advanced_Chess/tree/main/Images/ScreenShots/promotion.PNG

[Qt-url]: https://www.qt.io/
[Qt.com]: https://img.shields.io/badge/qt-35495E?style=for-the-badge&logo=qt&logoColor=4FC08D
[C++-url]: https://cplusplus.com/
[C++.com]: https://img.shields.io/badge/C++-0769AD?style=for-the-badge&logo=cplusplus&logoColor=white
