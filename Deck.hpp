#ifndef DECK_HPP
#define DECK_HPP

#include <iostream>
#include <vector>
#include "Card.hpp"

//NOTE:Build Piles are just decks
class Deck{
  int capacity; //how much it can hold

protected:
  std::vector<Card> pile; //actual deck is a vector of card objects

public:
  Deck(int size = 12):capacity(size){}; //default constructor
  Deck(const Deck &); //copy
  int getSize() const{ //return size of deck
    return pile.size();
  };
 
  int getCapacity() const{ //return capacity of deck
    return capacity;
  };
  
  std::vector<Card>& getPile(){ //returns the actual deck
    return pile;
  };

  virtual bool add(Card addCard); //overrided by sub classes, add card to vector
  
  virtual Card getCard(int i = 0) const; //gets the card from deck
  virtual void clear(); //clears the pile, aka when buildpile reaches 12
  virtual Card draw(int = 1); //draw card
};

#endif
