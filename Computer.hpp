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
#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <vector>
#include <iostream>
#include "Player.hpp"

//a computer-controlled player
class Computer: public Player{
 
public:
  Computer(std::string initName, int initPlayerNum, int initStockSize): Player(initName, initStockSize, initPlayerNum){};
  Computer(const Player &c):Player(c){};
  ~Computer(){};
  bool isHuman() const{return false;}; //returns false because the computer is not a human
  virtual void discard();
  virtual void doMove(std::vector<Deck> &, const StockPile){}; //for computerAI
  void doTurn(std::vector<Deck> &);
};

#endif
