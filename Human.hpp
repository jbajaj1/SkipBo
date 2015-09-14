#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "Player.hpp"
#include <iostream>

class Human: public Player{
 
public:
  Human(std::string initName, int initStock = 0, int initPlayerNum = 0):Player(initName,initStock,initPlayerNum){}; //inital contructor for a human player
  Human(const Player &h):Player(h){};
  ~Human(){};
  bool isHuman() const{return true;}; //inline boolean to check type of player
  bool move(const Card, Deck &); //humans move method, for actual play
};

#endif
