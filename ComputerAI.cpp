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

#include "ComputerAI.hpp"
#include "Computer.hpp"
#include "DiscardPile.hpp"
#include "StockPile.hpp"
#include "Card.hpp"
#include "Deck.hpp"
#include <vector>
#include <algorithm>

using std::sort;
using std::vector;
using std::string;

//default constructor, calls Computer constructor, sets first three discard piles as like piles (same value cards on pile), and last discard pile as solitaire pile(i.e. 5-4-3-2-1)
ComputerAI::ComputerAI(string initName, int initPlayerNum, int initStockSize): Computer(initName, initPlayerNum, initStockSize){
  discardPiles[0].setLike(true);
  discardPiles[1].setLike(true);
  discardPiles[2].setLike(true);
  discardPiles[3].setSolitaire(true);
}

//chooses aggression level depending upon your stock pile size and the opponent's stock pile size
void ComputerAI::doMove(vector<Deck> &buildPiles, const StockPile oppStock) {
  
  int stockSize = stock.getSize();
  int oppSize = oppStock.getSize();

  if(stockSize == 1){
    aggresionNeg2(buildPiles, oppStock);
  }
  else if(oppSize == 1){
    aggresion2(buildPiles, oppStock);
  }
  else if(stockSize - oppSize >= 5){
    if(oppSize < 5){
      //aggresion = 2
      aggresion2(buildPiles, oppStock);
    }
    else {
      //agression = 1
      aggresion1(buildPiles, oppStock);
    }
  }
  else if(stockSize < 5 &&  stockSize < oppSize){
    //aggresion = -2
    aggresionNeg2(buildPiles, oppStock);
  }
  else if(stockSize - oppSize > -5 && stockSize - oppSize < 5){
    //agression = 0
    aggresion0(buildPiles, oppStock);
  }
  else{
    //aggresion = -1
    aggresionNeg1(buildPiles, oppStock);
  }
}

//discards 1) checks like piles and solitaire piles, if build accordingly
//2) if empty, starts pile
//3) else, looks for closest match
void ComputerAI::discard() {
  for(int i = 0; i<4; i++){
    if(discardPiles[i].getSize() != 0){
      if(discardPiles[i].isLike()){
	for(int j = 0; j<playerHand.getSize(); j++){
	  if(discardPiles[i].getCard().getValue() == playerHand.getCard(j).getValue()){
	    //Discard in same-card pile
	    discardPiles[i].add(playerHand.draw(j+1));
	    return;
	  }
	}
      }
      else if(discardPiles[i].isSolitaire()){
	for(int j = 0; j<playerHand.getSize(); j++){
	  if(discardPiles[i].getCard().getValue()-1 == playerHand.getCard(j).getValue()){
	    //discard in Soltaire Pile
	    discardPiles[i].add(playerHand.draw(j+1));
	    return;
	  }
	}
      }
    }
  }

  for(int i = 0; i<4; i++){
    if(discardPiles[i].getSize() == 0){
      if(discardPiles[i].isLike()){
	for(int j = 0; j<playerHand.getSize() -1; j++){
	  for(int k = j+1; k<playerHand.getSize();k++){
	    if(playerHand.getCard(j).getValue() == playerHand.getCard(k).getValue()){
	      //starting a "like" pile  (A like pile is a similar-card pile)
	      discardPiles[i].add(playerHand.draw(j+1));
	      return;
	    }
	  }
	}
      }
      else{
	int greatest = 0;
	int position = -1;
	for(int j = 0; j<playerHand.getSize() -1; j++){
	  if(playerHand.getCard(j).getValue() > greatest){
	    position = j;

	    greatest = playerHand.getCard(j).getValue();
	  }
	}
	//Adding to a solitaire pile
	discardPiles[i].add(playerHand.draw(position +1));
	return;
      }
    }
  }
  
  int distance = 13;
  int discardPosition = -1;
  int handPosition = -1;
  for(int i = 0; i<4; i++){
    for(int j = 0; j <playerHand.getSize(); j++){
      if(playerHand.getCard(j).getValue() - discardPiles[i].getCard().getValue() < distance){
	discardPosition = i;
	handPosition = j;
      }
    }
  }
  
  discardPiles[discardPosition].add(playerHand.draw(handPosition +1));
}

//finds pile which is closest to stock pile card and finds distance to it, creates temps and checks if it is possible to put cards down such that the stock pile card will be played, if so, saves changes
bool ComputerAI::helpStock(vector<Deck> &buildPiles) {

  //look for stock closest to stock pile card
  int distance = 13;
  int position = -1;
  for(int i = 0; i <4; i++){
    int a =-( buildPiles[i].getCard().getValue() - stock.getCard().getValue()); 
    if(a > 0 && a < distance){
      distance = a;
      position = i;
    }
  }

  //if none found, look for pile with greatest value
  if(position == -1){
    int greatest = -1;
    for(int i = 0; i < 4; i++){
      if(buildPiles[i].getCard().getValue() > greatest){
	greatest = buildPiles[i].getCard().getValue();
	position = i;
      }
    }
    distance = 12 - buildPiles[position].getCard().getValue() + stock.getCard().getValue();
  }

  if(buildPiles[position].getCard().getValue() == stock.getCard().getValue() || position == -1){
    return false;
  }
  
  //create temps
  vector<Deck> buildPilesTemp = buildPiles;
  vector<DiscardPile> discardPilesTemp = discardPiles;
  Hand handTemp = playerHand;

  //add to temps to test if stock pile card can be played
  bool done = false;
  bool add = false;
  for(int i = 0; i < distance-1; i++){
    if(buildPilesTemp[position].getCard().getValue() == 12){
      buildPilesTemp[position].clear();
    }
    int numberOfSkipBo = 0;
    for(int j = 0; j < handTemp.getSize(); j++){
      if(handTemp.getCard(j).getValue() == 13){
	numberOfSkipBo++;
	add = false;
	continue;
      }
      if(buildPilesTemp[position].add(handTemp.getCard(j))){
	handTemp.draw(j+1);
	add = true;
	break;
      }
    }
    if(add){
      add = false;
      continue;
    }
    for(int j = 0; j < 4; j++){
      if(discardPilesTemp[j].getSize() == 0){
	add = false;
	continue;
      }

      if(buildPilesTemp[position].add(discardPilesTemp[j].getCard())){

	discardPilesTemp[j].draw();
	add = true;
	break;
      }
    }
    if(add){
      add = false;
      continue;
    }
    if(numberOfSkipBo == 0){
      break;
    }
    for(int j = 0; j < handTemp.getSize(); j++){
      if(buildPilesTemp[position].add(handTemp.getCard(j))){
	handTemp.draw(j+1);
	add = true;
	break;
      }
    }
    if(i == distance - 1){
      done = true;
    }
    if(!add){
      done = false;
      break;
    }
  }
  if(buildPilesTemp[position].getCard().getValue() == 12){
    buildPilesTemp[position].clear();
  }
  if(buildPilesTemp[position].add(stock.getCard())){
    done = true;
    stock.draw();
  }

  //save changes
  if(done == true || distance == 1){
    playerHand = handTemp;
    buildPiles = buildPilesTemp;
    discardPiles = discardPilesTemp;
    return true;
  }
  return false;
}

//finds pile which is closest to opponent's stock pile card and finds distance to it, creates temps and checks if it is possible to put cards down such that the opponent's stock pile card will be blocked, if so, saves changes
bool ComputerAI::helpBlock(vector<Deck>& buildPiles, const StockPile oppStock) {

  //look for stock closest to opponent's stock pile card
  int distance = 13;
  int position = -1;
  for(int i = 0; i < 4; i++){
    int a = -(buildPiles[i].getCard().getValue() - oppStock.getCard().getValue()); 
    if(a > 0 && a < distance){
      distance = a;
      position = i;
    }
  }

  //if none found, look for greatest build pile
  if(position == -1){
    int greatest = -1;
    for(int i = 0; i < 4; i++){
      if(buildPiles[i].getCard().getValue() > greatest){
	greatest = buildPiles[i].getCard().getValue();
	position = i;
      }
    }
    distance = 12 - buildPiles[position].getCard().getValue() + oppStock.getCard().getValue();
  }

  if(buildPiles[position].getCard().getValue() == oppStock.getCard().getValue() || position == -1){
    return false;
  }
  
  //create temps
  vector<Deck> buildPilesTemp = buildPiles;
  vector<DiscardPile> discardPilesTemp = discardPiles;
  Hand handTemp = playerHand;
  StockPile stockTemp = stock;
 
  //put cards on temps to see if blocked
  bool done = false;
  bool add = false;

  for(int i = 0; i < distance; i++){
    if(buildPilesTemp[position].getCard().getValue() == 12){
      buildPilesTemp[position].clear();
    }
    int numberOfSkipBo = 0;
    if(buildPilesTemp[position].add(stockTemp.getCard())){
      stockTemp.draw();
      add = true;
    }
    if(add){
      add =false;
      continue;
    }
    for(int j = 0; j < handTemp.getSize(); j++){
      if(handTemp.getCard(j).getValue() == 13){
	numberOfSkipBo++;
	add = false;
	continue;
      }
   
      if(buildPilesTemp[position].add(handTemp.getCard(j))){
      
	handTemp.draw(j+1);
	add = true;
	break;
      }
    }
    if(add){
      add = false;
      continue;
    }

    for(int j = 0; j < 4; j++){
      if(discardPilesTemp[j].getSize() == 0){
	add = false;
	continue;
      }
      if(buildPilesTemp[position].add(discardPilesTemp[j].getCard())){
	discardPilesTemp[j].draw();
	add = true;
	break;
      }
    }
    if(add){
      add = false;
      continue;
    }
    if(numberOfSkipBo == 0){
      break;
    }
    for(int j = 0; j < handTemp.getSize(); j++){
      if(buildPilesTemp[position].add(handTemp.getCard(j))){
	handTemp.draw(j+1);
	add = true;
	break;
      }
    }
    if(i == distance - 1){
      done = true;
    }
    if(!add){
      done = false;
      break;
    }
  }
  if(buildPilesTemp[position].getCard().getValue() == 12){
    buildPilesTemp[position].clear();
  }
  if(buildPilesTemp[position].getCard().getValue() == oppStock.getCard().getValue()){
    done = true;
  }

  //save changes
  if(done == true){
    playerHand = handTemp;
    buildPiles = buildPilesTemp;
    discardPiles = discardPilesTemp;
    return true;
  }
  return false;
}

//if a buildpile's state can be replicated by putting cards onto another buildPile, do not put card on other buildPile
bool ComputerAI::canReplicate(vector<Deck>& buildPiles) {
  
  vector<int> buildVal;
  for(int j = 0; j < 4; j++){
    buildVal.push_back(buildPiles[j].getCard().getValue());
  }
  sort(buildVal.begin(), buildVal.end());

  int j = 0;
  while(j < (int)buildVal.size()-1){
    for(int i = j+1; i < (int)buildVal.size(); i++){
      if(buildVal[i]-buildVal[j] == 1){
	buildVal.erase(buildVal.begin() + j);
	j--;
	break;
      }
    }
    j++;
 }

  if(buildVal.size() == 1){
    for(int j = 0; j<4; j++){
      if(buildPiles[j].getCard().getValue() == buildVal[0]){
	buildPiles[j].add(stock.draw());
	return true;
      }
    }
  }


  for(int m = 0; m < (int)buildVal.size()-1; m++){
    for(int n = m+1; n<(int)buildVal.size(); n++){
     
      int distance = buildVal[n]-buildVal[m];
      Deck buildPileM;
      for(int i = 1; i <= buildVal[m]; i++){
	Card addCard(i);
	buildPileM.add(addCard);
      }
     

      vector<DiscardPile> discardPilesTemp = discardPiles;
      Hand handTemp = playerHand;
      
      bool done = false;
      bool add = false;
      for(int i = 0; i < distance; i++){
	if(buildPileM.getCard().getValue() == 12){
	  buildPileM.clear();
	}
	int numberOfSkipBo = 0;
	for(int j = 0; j < handTemp.getSize(); j++){
	  if(handTemp.getCard(j).getValue() == 13){
	    numberOfSkipBo++;
	    add = false;
	    continue;
	  }
	  if(buildPileM.add(handTemp.getCard(j))){
	    handTemp.draw(j+1);
	    add = true;
	    break;
	  }
	}
	if(add){
	  add = false;
	  continue;
	}
	for(int j = 0; j < 4; j++){
	  if(discardPilesTemp[j].getSize() == 0){
	    add = false;
	    continue;
	  }
	  if(buildPileM.add(discardPilesTemp[j].getCard())){
	    discardPilesTemp[j].draw();
	    add = true;
	    break;
	  }
	}
	if(add){
	  add = false;
	  continue;
	}
	if(numberOfSkipBo == 0){
	  break;
	}
	for(int j = 0; j < handTemp.getSize(); j++){
	  if(buildPileM.add(handTemp.getCard(j))){
	    handTemp.draw(j+1);
	    add = true;
	    break;
	  }
	}
	if(i == distance - 1){
	  done = true;
	}
	if(!add){
	  done = false;
	  break;
	}
      }
      if(buildPileM.getCard().getValue() == 12){
	buildPileM.clear();
      }
      if(buildPileM.getCard().getValue() == buildVal[n]){
	done = true;
      }

      if(done == true){
	buildVal.erase(buildVal.begin() + m);
	m--;
      }
    }
  }
  
  for(int j = 0; j<4; j++){
    if(buildPiles[j].getCard().getValue() == buildVal[0]){
      buildPiles[j].add(stock.draw());
      return true;
    }
  }
  return false;
}

//checks if player hand is not empty, stock is not empty, and a buildPile does not have 12 cards
bool ComputerAI::checkBoundaryConditions(vector<Deck> buildPiles){
  if(playerHand.getSize() == 0){
    return false;
  }
  if(stock.getSize() == 0){
    return false;
  }
  for(int i = 0; i<4; i++){
    Card buildPileCard = buildPiles[i].getCard();
    if(buildPileCard.getValue() == 12){
      return false;
    }
  }
  return true;
}

//calls helpBlock as many times as possible
void ComputerAI::block(vector<Deck> &buildPiles, const StockPile oppStock){
  if(oppStock.getCard().getValue() != 13){
    if(helpBlock(buildPiles, oppStock)){
      if(!checkBoundaryConditions(buildPiles)){
	return;
      }    
      block(buildPiles, oppStock);
    }

    if(!checkBoundaryConditions(buildPiles)){
      return;
    }
    
  }
}

//calls helpStock as many times as possible
//if stock card is skip bo, use can replicate to decide where to put card
void ComputerAI::buildStock(vector<Deck> &buildPiles){
  if(stock.getCard().getValue() != 13){
    if(helpStock(buildPiles)){
      if(!checkBoundaryConditions(buildPiles)){
	return;
      }
      buildStock(buildPiles);
    }
    
    if(!checkBoundaryConditions(buildPiles)){
      return;
    }
  }
  else{
    vector<int> buildVal;
    for(int j = 0; j < 4; j++){
      buildVal.push_back(buildPiles[j].getCard().getValue());
    }
    sort(buildVal.begin(), buildVal.end());
    int i = 0;
    bool added = false;
    while(i < 3){
      if(buildVal[i] == buildVal[i+1]){
	for(int j = 0; j < 3; j++){
	  if(buildVal[i] == buildPiles[j].getCard().getValue()){
	    buildPiles[j].add(stock.draw());
	    added = true;
	    break;
	  }
	}
	break;
      } 
      i++;
    }
    if(!added){
      canReplicate(buildPiles);
    }
    if(!checkBoundaryConditions(buildPiles)){
      return;
    }
    buildStock(buildPiles);
    return;
  }
}

//looks at opponent's stock pile, puts down cards up to opponent's stock pile card minus "a"
void ComputerAI::aggresivePlay(vector<Deck> &buildPiles,const StockPile oppStock, int a){
  bool done = false;
  int oppStockValue = oppStock.getCard().getValue();
  int testValue = oppStock.getCard().getValue()-a;
  bool add = false;
  if(testValue <= 0){
    testValue += 12;
  }
  
  for(int i = 0 ;i < 4; i++){
    if(testValue < oppStockValue){
      if(buildPiles[i].getCard().getValue() > testValue && buildPiles[i].getCard().getValue() < oppStockValue){
	testValue = buildPiles[i].getCard().getValue();
      }
    }
    else{
      if(buildPiles[i].getCard().getValue() < testValue && buildPiles[i].getCard().getValue() > oppStockValue){
	testValue = buildPiles[i].getCard().getValue();
      }
    }
  }

  for(int i = 0; i < playerHand.getSize(); i++){
    if(playerHand.getCard(i).getValue() == 13){
      continue;
    }
    if(playerHand.getCard(i).getValue() < testValue || playerHand.getCard(i).getValue() > oppStockValue){
      for(int j = 0; j < 4; j++){
	if(buildPiles[j].add(playerHand.getCard(i))){
	  playerHand.draw(i+1);
	  add = true;
	  i--;
	  break;
	}
      }
    }
  }


  while(!done){
    for(int i = 0; i < 4; i++){
      if(discardPiles[i].getCard().getValue() < testValue && discardPiles[i].getCard().getValue() > oppStockValue){
	for(int j = 0; j < 4; j++){
	  if(buildPiles[j].add(discardPiles[i].getCard())){
	    add = true;
	    discardPiles[i].draw();
	    done = true;
	  }
	}
      }
    }
    if(done){
      done = false;
    }
    else{
      done = true;
    }
  }

  if(!checkBoundaryConditions(buildPiles)){
    return;
  }
  
  for(int i = 0; i < playerHand.getSize(); i++){
    if(playerHand.getCard(i).getValue() == 13){
      for(int j = 0; j < 4; j++){
	if(testValue < oppStockValue){
	  if(buildPiles[j].getCard().getValue() < testValue || buildPiles[j].getCard().getValue() > oppStockValue){
	    buildPiles[j].add(playerHand.draw(i+1));
	    add = true;
	    break;
	  } 	  
	}
	else{
	  if(buildPiles[j].getCard().getValue() < testValue &&  buildPiles[j].getCard().getValue() > oppStockValue){
	    buildPiles[j].add(playerHand.draw(i+1));
	    add = true;
	    break;
	  } 
	} 
      }
      continue;
    }
    
    if(playerHand.getCard(i).getValue() < testValue || playerHand.getCard(i).getValue() > oppStockValue){
      for(int j = 0; j < 4; j++){
	if(buildPiles[j].add(playerHand.getCard(i))){
	  playerHand.draw(i+1);
	  add = true;
	  i--;
	  break;
	}
      }
    }
  }
  
  if(add){
    aggresivePlay(buildPiles, oppStock, a);
  }
}

//checks if hand can be emptied
bool ComputerAI::canFinishTurn(std::vector<Deck> buildPiles){

  bool add = true;
  Hand handTemp = playerHand;
  StockPile stockTemp = stock;
  vector<DiscardPile> discardPilesTemp = discardPiles;

  while(add){
    add = false;
    for(int i = 0; i<4; i++){
      if(buildPiles[i].add(stockTemp.getCard())){
	stockTemp.draw();
	add = true;
      }
    }
    
    for(int i = 0; i<handTemp.getSize(); i++){
      for(int j = 0; j<4; j++){
	if(buildPiles[j].add(handTemp.getCard(i))){
	  handTemp.draw(i+1);
	  add = true;
	}
      }
    }

    if(handTemp.getSize() == 0){
      return true;
    }

    for(int i = 0; i<4; i++){
      for(int j = 0; j<4; j++){
	if(buildPiles[j].add(discardPilesTemp[i].getCard())){
	  discardPilesTemp[i].draw();
	  add = true;
	}
      }
    }
  }

  if(handTemp.getSize() == 0){
    return true;
  }
  return false;
}

//plays as many cards as possible
void ComputerAI::finishTurn(vector<Deck>& buildPiles){

  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  for(int i = 0; i<4; i++){
    if(buildPiles[i].add(stock.getCard())){
      stock.draw();
      finishTurn(buildPiles);
    }
  }
 
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  for(int i = 0; i<playerHand.getSize(); i++){
    for(int j = 0; j<4; j++){
      if(buildPiles[j].add(playerHand.getCard(i))){
	playerHand.draw(i+1);
	finishTurn(buildPiles);
      }
    }
  }
  for(int i = 0; i<4; i++){
    for(int j = 0; j<4; j++){
      if(buildPiles[j].add(discardPiles[i].getCard())){
	discardPiles[i].draw();
	finishTurn(buildPiles);
      }
    }
  }  
}

//very aggressive
void ComputerAI::aggresion2(vector<Deck> &buildPiles,  const StockPile oppStock) {
 
  block(buildPiles, oppStock);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  buildStock(buildPiles);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  aggresivePlay(buildPiles, oppStock, 4);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  } 

  if(canFinishTurn(buildPiles)){
    finishTurn(buildPiles);
  }
}

//aggressive
void ComputerAI::aggresion1(vector<Deck> &buildPiles, const StockPile oppStock) {
  
  block(buildPiles, oppStock);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }
  
  buildStock(buildPiles);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }
  
  aggresivePlay(buildPiles, oppStock, 3);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }
  
  if(canFinishTurn(buildPiles)){
    finishTurn(buildPiles);
  }
}

//a little aggressive
void ComputerAI::aggresion0(vector<Deck> &buildPiles,const StockPile oppStock) {

  buildStock(buildPiles);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  block(buildPiles, oppStock);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }
  
  aggresivePlay(buildPiles, oppStock, 2);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  if(canFinishTurn(buildPiles)){
    finishTurn(buildPiles);
  }
  
}

//passive
void ComputerAI::aggresionNeg1(vector<Deck> &buildPiles,  const StockPile oppStock) {

  buildStock(buildPiles);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  block(buildPiles, oppStock);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }
 
  finishTurn(buildPiles);
}

//like dumb AI
void ComputerAI::aggresionNeg2(vector<Deck> &buildPiles,  const StockPile oppStock) {

  buildStock(buildPiles);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  finishTurn(buildPiles);
  if(!checkBoundaryConditions(buildPiles)){
    return;
  }

  block(buildPiles,oppStock);
}
