#include <iostream>
#include "Human.hpp"

//moves a card to a target deck, how human moves cards
bool Human::move(const Card card, Deck & target) {
  return target.add(card);
}//end human move
