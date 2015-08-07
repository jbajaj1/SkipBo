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

#ifndef _AI_H
#define _AI_H

#include "Deck.hpp"
#include "DiscardPile.hpp"
#include "StockPile.hpp"
#include "Card.hpp"
#include "Computer.hpp"
#include "Player.hpp"
#include <string>

//harder AI, looks at opponents stock pile
class ComputerAI: public Computer{
		  
public:  
  ComputerAI(std::string initName, int initPlayerNum, int initStockSize);
  ComputerAI(const Player &c):Computer(c){}; //copy constructor
  void doMove(std::vector<Deck> &, const StockPile);
  void discard();

private:
  bool helpStock(std::vector<Deck> &);
  bool helpBlock(std::vector<Deck> &,const StockPile);
  bool isHuman(){return false;}; //is not human
  void aggresion2(std::vector<Deck> &, const StockPile );
  void aggresion1(std::vector<Deck> &, const StockPile );
  void aggresion0(std::vector<Deck> &, const StockPile );
  void aggresionNeg1(std::vector<Deck> &, const StockPile );
  void aggresionNeg2(std::vector<Deck> &, const StockPile );
  void finishTurn(std::vector<Deck>& buildPiles);
  bool canFinishTurn(std::vector<Deck> buildPiles);
  bool canReplicate(std::vector<Deck> &);
  void aggresivePlay(std::vector<Deck> &buildPiles,const StockPile oppStock, int a);
  void buildStock(std::vector<Deck> &buildPiles);
  void block(std::vector<Deck> &buildPiles, const StockPile oppStock);
  bool checkBoundaryConditions(std::vector<Deck> buildPiles);

};

#endif
