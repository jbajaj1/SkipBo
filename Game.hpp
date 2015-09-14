#ifndef _GAME_HPP
#define _GAME_HPP

#include "Board.hpp"
#include <list>

class Game {

  Board board;
  std::list<Board> boardList;
  std::list<Board>::iterator it;
  int i;

  bool printGameMenu();
  Board load();
  Board createNewBoard();
  Board printStartMenu();
  void printGameOver();

public:
  Game();
  ~Game();
  void play();
  Board& getBoard() {return board;};
};

#endif
