#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "MasterPile.hpp"
#include "Deck.hpp"
#include "Color.hpp"
#include <string>

/*
Board contains all elements of the game and organizes and prints the board
for each new turn, keeping track of the rules as well
*/
class Board{ 
  //data members

  bool hard; //true if hard AI
  
  std::vector<Player*> p;  //contains all the players in the game,
                      //p[0] is always the current player
  
  int numOfPlayers;  //the number of humans and computer in the game
  
  MasterPile master;  //the master deck that is dealt out to players at the
                      //beginning of their turns
  
  MasterPile imaginaryDeck;  //the deck that the finished build piles are put
                             //into, is shuffled and put into the master deck
                             //when the master deck runs out of cards
  
  std::vector<Deck> buildPiles;  //contains all the build piles in the center of
                            //the board, these are put into the imaginary deck
                            //once it reaches 12 cards
  
  int turn;  //keeps track of the number of turns (every player going once)
  
  int numOfHumans;  //stores the number of human players in the game

public:

  Board(int initStock = 1, int numPlayers = 2, int numHumans = 0, bool difficulty= false);
  Board(const Board &);
  ~Board();
  
  void setDifficulty(bool difficulty){hard = difficulty;};
  bool getPlayerIsHuman() const {return p[0]->isHuman();};
  std::string getPlayerName() const{ return p[0]->getName();};
  void computerDoMove();
  bool isGameNotFinished() const;
  bool moveCard(char, char);
  void dealToHand(int = 0);       //both automatically go to p[0] 
  int getPlayerHandSize() const; 
  int getMasterSize() const {return master.getSize();}; //return size of master deck
  void printBoard() const;
  void toString2p() const;
  void toString3p() const;
  void toString4p() const;
  void toString5p() const;
  void toString6p() const;
  void rotate();
  void refresh();
  void save();
  bool load();
  bool operator==(const Board &);
  Board& operator=(const Board &);
};

#endif
