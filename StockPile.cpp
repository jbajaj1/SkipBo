#include "Deck.hpp"
#include "Card.hpp"
#include <iostream>
#include <vector>
#include "StockPile.hpp"

//adds a card to the stockpile
bool StockPile::add(const Card c){
  if(this->getSize() == this->getCapacity()){
    return false;
  }
  pile.push_back(c);
  return true;
}//end sotckpile add
