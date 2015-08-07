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
