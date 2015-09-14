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

