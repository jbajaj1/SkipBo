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
#ifndef _CARD_HPP
#define _CARD_HPP

#include <iostream>
#include <string>
#include "Color.hpp"

/*
Card represents the cards in the actual game, 1-12, the special Skip Bo card,
and an empty slot for a card
*/
class Card{
  int value;  //the value of the card, 13 if its a skip bo
  bool isSB;  //true if the card is a skip bo

public:
  Card(int input);
  Card(const Card &c):value(c.getValue()){isSB = c.getIsSkipBo();};
  void changeValue(int change){
    this->value = change;
    this->isSB = true;
  };
  int getValue() const{return value;};
  bool getIsSkipBo()const{return isSB;};
  std::string toString() const;
  ColorModifier getColor() const;
};
#endif

