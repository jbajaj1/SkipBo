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
#include "Deck.hpp"
#include "Card.hpp"
#include "Hand.hpp"

Hand::Hand(int initSize): Deck(initSize) {} //inital construcotr for 5, calls deck constructor
Hand::Hand(const Hand& h): Deck(h){} //copy constructor

//adds a card to the vector of cards know as a hand
bool Hand::add(const Card addCard){
  if(this->getSize() == this->getCapacity()){
    return false;
  }
  pile.push_back(addCard);
  return true;
}//end add
