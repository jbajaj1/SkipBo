#ifndef HAND_HPP
#define HAND_HPP

#include <iostream>
#include "Deck.hpp"
#include "Card.hpp"

//inheirit from deck
class Hand : public Deck{
  
public:
  Hand(int = 5); //construct hand of default 5 cards, calls deck constructor
  Hand(const Hand& ); //copy
  bool add(const Card addCard); //adds a card to hand
};

#endif
