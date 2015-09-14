#ifndef STOCKPILE_HPP
#define STOCKPILE_HPP

#include "Deck.hpp"
#include "Card.hpp"
#include <iostream>
#include <vector>

//stockpile is a deck
class StockPile: public Deck{

public:
  StockPile(int initSize = 30):Deck(initSize){}; //intial size is 30, use deck cosntructor
  StockPile(const StockPile &s):Deck(s){}; //copy
  bool add(const Card c); //add method to add a card to stockpile, only used in itial game cosntruction
};

#endif
