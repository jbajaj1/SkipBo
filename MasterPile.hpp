#ifndef MASTERPILE_HPP
#define MASTERPILE_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "Deck.hpp"
#include "Card.hpp"

class MasterPile: public Deck{
  
public:
  MasterPile(int size = 162):Deck(size){}; //constructor, creates a master pile with a default size of 162
  MasterPile(const MasterPile &m):Deck(m){}; //copy constructor

  bool add(const Card addCard);
  bool addDeck(Deck addDeck);
  void shuffle();
  void clear();
  void create();
};

#endif
