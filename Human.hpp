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
