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
#include <iostream>
#include <vector>
#include "Deck.hpp"
#include "Card.hpp"
#include "DiscardPile.hpp"

//adds a card to the discard pile
bool DiscardPile::add(const Card c){
  pile.push_back(c);
  return true;
}//end add
