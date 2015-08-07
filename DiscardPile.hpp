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
#ifndef DISCARDPILE_HPP
#define DISCARDPILE_HPP

#include <iostream>
#include <vector>
#include "Deck.hpp"
#include "Card.hpp"

//discard pile to end turns
class DiscardPile: public Deck{

  //for AI
  bool likeCard;
  bool solitaire;
public:
  DiscardPile(int initSize = 12, bool like = false, bool sol = false):Deck(initSize), likeCard(like), solitaire(sol){}; //constructor
  DiscardPile(const DiscardPile &d): Deck(d){likeCard = d.likeCard; solitaire = d.solitaire;}; //copy
  bool add(const Card c); //adds card
  bool isLike(){return likeCard;};
  bool isSolitaire(){return solitaire;};
  void setLike(bool like){likeCard = like;};
  void setSolitaire(bool sol){solitaire = sol;};
};

#endif
