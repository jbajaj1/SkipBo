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
