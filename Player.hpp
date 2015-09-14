#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "DiscardPile.hpp"
#include "StockPile.hpp"
#include "Hand.hpp"

//an abstract base class of a player in the game, contains a hand, stockpile and discard piles
class Player {

protected:
  std::string name;  //the player's name
  std::vector<DiscardPile> discardPiles;  //the player's discard piles
  int playerNum;  //the number of the player (1-6)
  Hand playerHand;  //the player's hand
  StockPile stock;  //the player's stockpile
  
public:
  Player(std::string = "", int = 30, int = 0);
  Player(const Player &);
  virtual ~Player(){};
  
  //returns the player's name as a string
  std::string getName() const {return name;};

  //pure virtual function, true if the player is a human
  virtual bool isHuman() const = 0;

  //moves a card to a deck, always overriden
  virtual bool move(const Card, Deck&){return true;};
  virtual void doTurn(std::vector<Deck> &){};
  virtual void discard(){};

  //returns the player's hand
  Hand& getHand() {return playerHand;};

  //returns the player's discard piles
  DiscardPile& getDiscardPile(int i) {return discardPiles[i];}
  
  //returns the player's stock pile
  StockPile& getStock() {return stock;};

  //returns the sixe of the player's hand
  int getHandSize() const {return playerHand.getSize();};
  
  //returns the players number
  int getPlayerNum(){return playerNum;};

  //returns the string representation of the top card on the stock pile
  std::string getStockCardString() const {return stock.getCard(0).toString();};

  //returns the size of the player's stock pile
  int getStockLength() const {return stock.getSize();};
  
  //returns the initial size of the stock pile
  int getStockCapacity() const{return stock.getCapacity();};
  std::string getStockLengthStr() const;

  //returns the string representaion of the top card of the ith discard pile
  std::string getDiscardPileString(int i) const {return discardPiles[i].getCard(0).toString();};

  //returns the string representation of the ith card of the hand
  std::string getHandString(int i) const {Card cardTemp =  playerHand.getCard(i); return cardTemp.toString();};

  //returns the ColorModifier of the top card of the stock pile
  ColorModifier getStockCardColor() const {return stock.getCard(0).getColor();};
  
  //returns the ColorModifier of the top card of the ith discard pile
  ColorModifier getDiscardPileColor(int i) const {return discardPiles[i].getCard(0).getColor();};
  
  //returns the ColorModifier of the ith card of the hand
  ColorModifier getHandColor(int i) const {return playerHand.getCard(i).getColor();};
  
  ColorModifier getPlayerColor() const; //returns color based on playerNum

  virtual void doMove(std::vector<Deck> &,const StockPile){}; //save for ComputerAI

};

#endif
