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
