#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "Deck.hpp"
#include "Card.hpp"
#include "MasterPile.hpp"

using std::vector;
using std::iter_swap;

//adds addCard to the masterPile, no error checking because a master deck can have 324 cards or more depending if master deck empties and master deck is empty
bool MasterPile::add(const Card addCard){
  pile.push_back(addCard);
  return true;
}

//create a master pile with 12 1's, 12 2's, 12 3's, 12 4's, 12 5's, 12 6's, 12 7's, 12 8's, 12 9's, 12 10's, 12 11's, 12 12's, and 18 SB's
void MasterPile::create(){
  /*Card one(1);
  Card two(2);
  Card three(3);
  Card four(4);
  Card five(5);
  Card six(6);
  Card seven(7);
  Card eight(8);
  Card nine(9);
  Card ten(10);
  Card eleven(11);
  Card twelve(12);
  Card thirteen(13);
  for(int i = 0; i<12; i++){
    add(one);
    add(two);
    add(three);
    add(four);
    add(five);
    add(six);
    add(seven);
    add(eight);
    add(nine);
    add(ten);
    add(eleven);
    add(twelve);
    add(thirteen);
    }*/
  for(int i = 0; i<6; i++){
    add(Card(13));
  }
  for(int i = 1; i <=13; i++){
    Card addThisCard(i);
    for(int j = 0 ; j<12;j++){
      add(addThisCard);
    }
  } 
}

//copies the addDeck into the masterPile
bool MasterPile::addDeck(Deck addDeck){
  vector<Card>& addVector = addDeck.getPile();
  vector<Card>::iterator it = addVector.begin();
  while(it != addVector.end()){
    Card temp = *it;
    if(temp.getIsSkipBo()){
      temp.changeValue(13);
    }
    add(temp);
    it++;
  }
  return true;
}

//shuffles the deck by switching cards at each position
void MasterPile::shuffle(){
  vector<Card>::iterator it = pile.begin();
  srand(time(NULL));
  while(it != pile.end()){
    int randomValue = rand() % this->getSize();
    iter_swap(it, pile.begin() + randomValue);
    it++;
  }
}

//deletes everything in master Pile
void MasterPile::clear(){
  pile.clear();

}
