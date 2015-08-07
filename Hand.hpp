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
