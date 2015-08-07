/*
Paul Watson
pwatso14
pwatso14@jhu.edu
443-812-2302

Achintya Gopal
agopal2
agopal2@jhu.edu
520-508-1337

William Watson
wwatso13
wwatso13@jhu.edu
516-543-1131

Joshan Bajaj
jbajaj1
jbajaj1@jhu.edu
609-649-1214

Team 2A
600.120
Final Project
*/

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
