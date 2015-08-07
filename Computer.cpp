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
#include "Computer.hpp"
#include <iostream>
#include "Player.hpp"
#include <ctime>
#include <cstdlib>

using std::string;
using std::vector;
using std::cout;
using std::endl;

//the computers moves for the turn, they try to get rid of the stock pile first
//and then their hand and lastly they discard a card
void Computer::doTurn(vector<Deck>& buildPiles){
  if(stock.getSize() == 0){
    return;
  }
  for(int i = 0; i<4; i++){
    if(buildPiles[i].add(stock.getCard())){
      cout << "(Stock)" <<stock.getCard().toString() << " moved to build pile " << i+1 << endl;
      stock.draw();
      doTurn(buildPiles);
    }
  }
  if(playerHand.getSize() == 0){
    return;
  }
  for(int i = 0; i<playerHand.getSize(); i++){
    for(int j = 0; j<4; j++){
      if(buildPiles[j].add(playerHand.getCard(i))){
	cout << "(Hand)" << playerHand.getCard(i).toString() << " moved to build pile " << j+1 << endl;
	playerHand.draw(i);
	doTurn(buildPiles);
	break;
      }
    }
  }
  for(int i = 0; i<4; i++){
    for(int j = 0; j<4; j++){
      if(buildPiles[j].add(discardPiles[i].getCard())){
	cout << "(Discard)" <<discardPiles[i].getCard().toString() << " moved to build pile " << j+1 << endl;
	discardPiles[i].draw();
	doTurn(buildPiles);
	break;
      }
    }
  }  
}

//discards the first card in their hand to a random discard pile
void Computer::discard(){
  srand(time(NULL));
  int randomValue = rand() % 4;
  discardPiles[randomValue].add(playerHand.getCard());
  cout << "(Hand)" << playerHand.getCard().toString() << " discarded to discard pile " << randomValue + 1;
  playerHand.draw();
}
