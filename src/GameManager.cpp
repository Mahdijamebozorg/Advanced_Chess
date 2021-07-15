#include "GameManager.hpp"

#include "ChessBoard.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

#include <stdexcept>

using namespace std;

unique_ptr<GameManager> GameManager::game_manager = nullptr;

unique_ptr<GameManager>& GameManager::setGameManager()
{
  if(game_manager == nullptr)
    game_manager = unique_ptr<GameManager>(new GameManager());

  return game_manager;
}

unique_ptr<GameManager>& GameManager::getGameManager()
{
  return game_manager;
}

GameManager::GameManager()
{
  setChessman      (Chessman::WHITE);
  setChessman      (Chessman::BLACK);
  setChessBoardGame(               );
  chess_board->setCells(white_chessman, black_chessman);
}

void GameManager::setChessman(Chessman::Color color)
{
  white_chessman[0] = shared_ptr<Chessman>(new Rook  (color));
  white_chessman[1] = shared_ptr<Chessman>(new Knight(color));
  white_chessman[2] = shared_ptr<Chessman>(new Bishop(color));
  white_chessman[3] = shared_ptr<Chessman>(new Queen (color));
  white_chessman[4] = shared_ptr<Chessman>(new King  (color));
  white_chessman[5] = shared_ptr<Chessman>(new Bishop(color));
  white_chessman[6] = shared_ptr<Chessman>(new Knight(color));
  white_chessman[7] = shared_ptr<Chessman>(new Rook  (color));

  for(int i = 8; i < 16; i++)
  {
    white_chessman[i] = shared_ptr<Chessman>(new Pawn(color));
  }
}

void GameManager::setChessBoardGame()
{
  chess_board = ChessBoard::setChessBoard();
}

std::list<Chessman::Index> GameManager::getCanGo(Chessman::ID id, Chessman::Index index) const
{
  if(chess_board == nullptr)
    throw runtime_error("Chessboard not existed.");

  for(auto const &item: white_chessman)
  {
    if(item->getID() == id)
    {
      list<Chessman::Index> temp = item->getCellsCanGo(index);

      return chess_board->getCanGo(index, temp);
    }
  }

  for(auto const &item: black_chessman)
  {
    if(item->getID() == id)
    {
      list<Chessman::Index> temp = item->getCellsCanGo(index);

      return chess_board->getCanGo(index, temp);
    }
  }

  throw invalid_argument("Any Chessman with This Id not found.");
}

void GameManager::movePiece(Chessman::Index src, Chessman::Index dest)
{
  chess_board->moveChessman(src, dest);
}

void GameManager::hitPiece(Chessman::Index index)
{
  Chessman::ID temp = chess_board->hitChessman(index);

  for(size_t i = 0; i <= white_chessman.size(); i++)
    if(white_chessman[i]->getID() == temp)
      white_chessman[i] = nullptr;

  for(size_t i = 0; i <= black_chessman.size(); i++)
    if(black_chessman[i]->getID() == temp)
      black_chessman[i] = nullptr;
}
