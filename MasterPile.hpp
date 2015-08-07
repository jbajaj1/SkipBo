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
