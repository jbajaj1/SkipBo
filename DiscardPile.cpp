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
