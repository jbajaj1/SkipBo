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
