#include <iostream>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"

//adds a card to current deck
bool Deck::add(Card addCard){
  Card topCard = getCard();
  if(this->getSize() == this->getCapacity()){
    return false;
  }
  if(addCard.getValue() - 1 == topCard.getValue()){
    pile.push_back(addCard);
    return true;
  }
  else if(addCard.getValue() == 13){
    int tempValue = topCard.getValue();
    addCard.changeValue( tempValue +1);
    pile.push_back(addCard);
    return true;
  }
  return false;
}

//empty a deck
void Deck::clear(){
  Card a = getCard();
  if(a.getValue() == 12){
    pile.clear();
  }
}//end clear

//get card value
Card Deck::getCard(int i) const {
  int j = this->getSize() - i - 1;
  if(i < 0 || j<0){
    Card nullCard(0);
    return nullCard;
  }
  return pile.at(j);
}//end get card

//draws card from deck
Card Deck::draw(int i){
  int j = this->getSize() - i;
  
  if(i < 0 || j<0){
    Card nullCard(0);
    return nullCard;
  }
  
  Card topCard = *(pile.end() - i);
  pile.erase(pile.end() - i);
  return topCard;
}//end draw

//copy
Deck::Deck(const Deck &d){
  capacity = d.getCapacity();
  pile = d.pile;
}//end copy
