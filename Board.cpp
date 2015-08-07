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

#include "Board.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "ComputerAI.hpp"
#include "MasterPile.hpp"
#include "Deck.hpp"
#include "Color.hpp"
#include <string>
#include <fstream>
#include <cstdio>

using std::setw; using std::setfill;
using std::cout; using std::endl;
using std::vector; using std::string;
using std::stringstream; using std::cin;
using std::ofstream; using std::ifstream;

//constucts a new Board based on the player-submitted stock size,
//number of players, and number of human players
Board::Board(int initStock, int numPlayers, int numHumans, bool difficulty){

  hard = difficulty;
  for(int i = 0; i < numHumans; i++){
    string name;
    cout << "Name of player " << i+1 << " (one word): ";
    cin >> name;
    numOfHumans = numHumans;
    Player *humanPlayer = new Human(name,initStock,i);
    p.push_back(humanPlayer);
  }
  for(int i = numHumans; i<numPlayers; i++){
    stringstream ss;
    ss << "Computer ";
    ss << i-numHumans+1;
    string name = ss.str();
    //    Player *computerPlayer = new Computer(name, i, initStock);
    Player *computerPlayer = new ComputerAI(name, i, initStock);
    p.push_back(computerPlayer);
  }
  numOfPlayers = numPlayers;
  MasterPile temp1(162);
  temp1.create();
  temp1.shuffle();
  master = temp1;
    
  for(int i = 0; i< 4; i++){
    Deck buildPile(12);
    buildPiles.push_back(buildPile);
  }
  for(int i = 0; i<numOfPlayers; i++){
    dealToHand(i);
    StockPile& stockTmp = p[i]->getStock();
    while(stockTmp.add(master.getCard())){
      master.draw();
    }
  }

  turn = 0;
  
}

Board::Board(const Board &other){
  master = other.master;
  imaginaryDeck = other.imaginaryDeck;
  turn = other.turn;
  buildPiles = other.buildPiles;
  numOfPlayers = other.numOfPlayers;
  numOfHumans = other.numOfHumans;
  hard = other.hard;

  for(int i = 0; i < other.numOfPlayers; i++){
    Player *playerTemp = other.p[i];
    if(playerTemp->isHuman()){
      Player *human = new Human(*playerTemp);
      p.push_back(human);
    }
    else{
      //      Player *human = new Computer(*playerTemp);
      Player *human = new ComputerAI(*playerTemp);
      p.push_back(human);
    }
  }
}

Board::~Board(){
  std::vector<Player*>::iterator it = p.begin();
  
  while(it != p.end()){
    if (*it != NULL){
    delete *it;
    *it = NULL;
    }
    it++;
  }
  p.clear();
}

//saves all the information about the game and prints it to SaveFile.txt
void Board::save(){

  ifstream ifs("SaveFile.txt", std::ios::app);
  if(ifs.good()){

    bool good = false;
    char choice;
    while(!good){
      try{
	cout << "Are you sure to want to save (Saving while override any previously saved data)? (y)es or (n)o: " << endl;
	cin >> choice;
	choice = tolower(choice);
	if(choice != 'y' && choice != 'n'){
	  throw choice;
	}
	good = true;
      }
      catch(char){
	cin.clear();
	string ignoreStr;
	getline(cin, ignoreStr);
	cout << "Invalid input! Input 'y' or 'n'" << endl;
      }
    }
    if(choice == 'n'){
      return;
    }
  }

  ofstream of("SaveFile.txt", std::ofstream::out);
  of << master.getSize() << " ";
  for(int i = 0 ;i < master.getSize(); i++){
    of << master.getCard(master.getSize() -1-i).getValue() << " ";
  }
  of << " ";
  of << imaginaryDeck.getSize() << " ";
  for(int i = 0 ;i < imaginaryDeck.getSize(); i++){
    of << imaginaryDeck.getCard(imaginaryDeck.getSize() -1 -i).getValue() << " ";
  }
  of << " ";
  for(int j = 0; j < 4; j++){
    of << buildPiles[j].getSize() << " ";
    for(int i = 0 ;i < buildPiles[j].getSize(); i++){
      if(buildPiles[j].getCard(buildPiles[j].getSize()-1-i).getIsSkipBo()){
	of << "13 ";
      }
      else{
	of << buildPiles[j].getCard(buildPiles[j].getSize()-1-i).getValue() << " ";
      }
    } 
  }

  of << " ";
  of << numOfPlayers;
  of << " ";
  of << numOfHumans;
  of << " ";
  for(int i = 0 ; i < numOfPlayers; i++){
    if(p[i]->isHuman()){
      of << "Human ";
      of << p[i]->getName() << " ";
    }
    else{
      of << "Computer ";
      of << p[i]->getPlayerNum() - numOfHumans + 1;
      of << " ";
    }
    of << p[i]->getPlayerNum();
    of << " ";

    StockPile playerStock  = p[i] ->getStock();
    of << playerStock.getSize() << " ";
    for(int j = 0; j < playerStock.getSize(); j++){
      of << playerStock.getCard(playerStock.getSize()-1-j).getValue() << " ";
    }
    of << " ";
    
    Hand playerHand  = p[i] ->getHand();
    of << playerHand.getSize() << " ";
    for(int j = 0; j < playerHand.getSize(); j++){
      of << playerHand.getCard(playerHand.getSize()-1-j).getValue() << " ";
    }

    for(int k = 0; k < 4; k++){
      DiscardPile playerDiscard = p[i]->getDiscardPile(k);
      of << playerDiscard.getSize() << " ";
      for(int j = 0; j < playerDiscard.getSize(); j++){
	of << playerDiscard.getCard(playerDiscard.getSize()-1-j).getValue() << " ";
      }
    }
  }

  if(hard){
    of << 1 << " ";
  }
  else{
    of << 0 << " ";
  }
  of.close();
}

//reads SaveFile.txt and creates a new Board with the data
bool Board::load(){
  try{
    ifstream ifs("SaveFile.txt", std::ios::in);
    if(!ifs.good()){
      return false;
    }
    int masterSize;
    ifs >> masterSize;
    MasterPile masterDeck(162);
    for(int i = 0; i < masterSize; i++){
      int cardValue;
      ifs >> cardValue;
      Card masterCard(cardValue);
      masterDeck.add(masterCard);
    }
    
    ifs >> masterSize;
    MasterPile imaginary(162);
    for(int i = 0; i < masterSize; i++){
      int cardValue;
      ifs >> cardValue;
      Card masterCard(cardValue);
      imaginary.add(masterCard);
    }

    vector<Deck> buildPilesTemp;
    for(int i = 0; i< 4; i++){
      Deck buildPileTemp(12);
      int buildSize;
      ifs >> buildSize;
      for(int j = 0; j<buildSize; j++){
	int cardValue;
	ifs >> cardValue;
	Card buildCard(cardValue);
	buildPileTemp.add(cardValue);
      }
      buildPilesTemp.push_back(buildPileTemp);
    }
    
    ifs >> numOfPlayers;
    ifs >> numOfHumans;
    vector<Player*> playerTempList;
    for(int i = 0; i < numOfPlayers; i++){
      string isHuman;
      ifs >> isHuman;
      int stockPileSize;
      if(isHuman == "Human"){
	string name;
	ifs >> name;

	int playerNumTemp;
	ifs >> playerNumTemp;
       	ifs >> stockPileSize;
	Player * playerTemp = new Human(name,  stockPileSize, playerNumTemp);
	StockPile stockTemp(stockPileSize);
	for(int j = 0; j<stockPileSize; j++){
	  int cardValue;
	  ifs >> cardValue;
	  Card stockCard(cardValue);
	  stockTemp.add(stockCard);
	}
	
	int playerHandSize;
	ifs >> playerHandSize;
	Hand playerHand (playerHandSize);
	for(int j = 0; j<playerHandSize; j++){
	  int cardValue;
	  ifs >> cardValue;
	  Card handCard(cardValue);
	  playerHand.add(handCard);
	}
	
	vector<DiscardPile> discardPilesTemp;
	for(int k = 0; k < 4; k++){
	  int discardPileSize;
	  ifs >> discardPileSize;
	  DiscardPile discardPileTemp(discardPileSize);
	  for(int j= 0; j<discardPileSize; j++){
	    int cardValue;
	    ifs >> cardValue;
	    Card discardCard(cardValue);
	    discardPileTemp.add(discardCard);
	  }
	  discardPilesTemp.push_back(discardPileTemp);
	}
	
	Hand& oldHand = playerTemp->getHand();
	StockPile& oldStock = playerTemp->getStock();
	DiscardPile& oldDiscardPile0 = playerTemp->getDiscardPile(0); 
	DiscardPile& oldDiscardPile1 = playerTemp->getDiscardPile(1); 
	DiscardPile& oldDiscardPile2 = playerTemp->getDiscardPile(2); 
	DiscardPile& oldDiscardPile3 = playerTemp->getDiscardPile(3); 
	
	oldHand = playerHand;
	oldStock = stockTemp;
	oldDiscardPile0 = discardPilesTemp[0];
	oldDiscardPile1 = discardPilesTemp[1];
	oldDiscardPile2 = discardPilesTemp[2];
	oldDiscardPile3 = discardPilesTemp[3];
	
	playerTempList.push_back(playerTemp);
      }
      else{
	stringstream ss;
	string name;
	int computerNumber;
	ss << "Computer ";
	ifs >> computerNumber;
	ss  << computerNumber;
	name = ss.str();

	int playerNumTemp;
	ifs >> playerNumTemp;
	ifs >> stockPileSize;
	
	Player *playerTemp = new Computer(name, playerNumTemp, stockPileSize);
	StockPile stockTemp(stockPileSize);
	for(int j = 0; j<stockPileSize; j++){
	  int cardValue;
	  ifs >> cardValue;
	  Card stockCard(cardValue);
	  stockTemp.add(stockCard);
	}
	
	int playerHandSize;
	ifs >> playerHandSize;
	Hand playerHand (playerHandSize);
	for(int j = 0; j<playerHandSize; j++){
	  int cardValue;
	  ifs >> cardValue;
	  Card handCard(cardValue);
	  playerHand.add(handCard);
	}
	
	vector<DiscardPile> discardPilesTemp;
	for(int k = 0; k < 4; k++){
	  int discardPileSize;
	  ifs >> discardPileSize;
	  DiscardPile discardPileTemp(discardPileSize);
	  for(int j= 0; j<discardPileSize; j++){
	    int cardValue;
	    ifs >> cardValue;
	    Card discardCard(cardValue);
	    discardPileTemp.add(discardCard);
	  }
	  discardPilesTemp.push_back(discardPileTemp);
	}
	
	Hand& oldHand = playerTemp->getHand();
	StockPile& oldStock = playerTemp->getStock();
	DiscardPile& oldDiscardPile0 = playerTemp->getDiscardPile(0); 
	DiscardPile& oldDiscardPile1 = playerTemp->getDiscardPile(1); 
	DiscardPile& oldDiscardPile2 = playerTemp->getDiscardPile(2); 
	DiscardPile& oldDiscardPile3 = playerTemp->getDiscardPile(3); 
	
	oldHand = playerHand;
	oldStock = stockTemp;
	oldDiscardPile0 = discardPilesTemp[0];
	oldDiscardPile1 = discardPilesTemp[1];
	oldDiscardPile2 = discardPilesTemp[2];
	oldDiscardPile3 = discardPilesTemp[3];
	
	playerTempList.push_back(playerTemp);
      }
      if(i < 2){
	delete p[i];
	p[i] = playerTempList[i];
      }
      else{
	p.push_back(playerTempList[i]);
      }
    }
    buildPiles[0] = buildPilesTemp[0];
    buildPiles[1] = buildPilesTemp[1];
    buildPiles[2] = buildPilesTemp[2];
    buildPiles[3] = buildPilesTemp[3];

    master = masterDeck;
    imaginaryDeck = imaginary;

    int difficult;
    ifs >> difficult;
    if(difficult == 1){
      hard = true;
    }
    else{
      hard = false;
    }
    
    ifs.close();
    return true;
  }
  catch(std::exception &e){
    this->~Board();
    return false;
  }
  return false;
}


//decides what the computer should do for their turn:
//first tries to move from their stock pile
//then looks to play from their hand
//then discards the first card in its hand to a random discard pile
void Board::computerDoMove() {
  if(hard) {
    p[0]->doMove(buildPiles, p[1]->getStock());
    for(int i = 0; i<4; i++){
      Card buildPileCard = buildPiles[i].getCard();
      bool clear = false;
      if(buildPileCard.getValue() == 12){
	imaginaryDeck.addDeck(buildPiles[i]);
	buildPiles[i].clear();
	computerDoMove();
	clear = true;
      }
      if(clear){
	computerDoMove();
	return;
      }
    }
    if(master.getSize() <= 1){
      refresh();
    }
    if(p[0]->getHandSize() == 0){
      dealToHand();
      computerDoMove();
    }  
    else{
      p[0]->discard();
      turn++;
    }
  } else {
    p[0]->doTurn(buildPiles);
    for(int i = 0; i<4; i++){
      Card buildPileCard = buildPiles[i].getCard();
      bool clear = false;
      if(buildPileCard.getValue() == 12){
	imaginaryDeck.addDeck(buildPiles[i]);
	buildPiles[i].clear();
	computerDoMove();
	clear = true;
      }
      if(clear){
	computerDoMove();
	return;
      }
    }
    if(master.getSize() <= 1){
      refresh();
    }
    if(p[0]->getHandSize() == 0){
      dealToHand();
      computerDoMove();
    }  
    else{
      p[0]->discard();
      turn++;
    }
  }
}

//returns true if a player has no more cards in their stock pile
bool Board::isGameNotFinished() const{
  for(int i = 0; i<numOfPlayers; i++){
    if(p[i]->getStockLength() == 0){
      return false;
    }
  }
  return true;
}

//returns the size of the current player's hand
int Board::getPlayerHandSize() const{
  return p[0]->getHandSize();
}

//moves a card in slot a to slot b and checks to make sure the move is legal
bool Board::moveCard(char a, char b){
  bool moved = false;
  if(isdigit(b)){
    Hand& currentHand = p[0]->getHand();
    DiscardPile& moveDiscard = p[0]->getDiscardPile(b-'6');
    if(p[0]->move(currentHand.getCard(a-'1'),moveDiscard)){
      currentHand.draw(a-'0');
      moved = true;
    }
  }
  else{
    if(a == '0'){
      StockPile& currentStock = p[0]->getStock();
      b = toupper(b);
      if(p[0]->move(currentStock.getCard(),buildPiles[b-'A'])){
	currentStock.draw();
	moved = true;
      }
    }
    else if(a>= '1' && a<='5'){
      Hand& currentHand = p[0]->getHand();
      b = toupper(b);
      if(p[0]->move(currentHand.getCard(a-'1'), buildPiles[b-'A'])){
       	currentHand.draw(a-'0');
	moved = true;
      }
    }
    else {
      b = toupper(b);
      DiscardPile& currentDiscard = p[0]->getDiscardPile(a - '6');
      if(p[0]->move(currentDiscard.getCard(),buildPiles[b-'A'])){
	currentDiscard.draw();
	moved = true;
      }
    }
    
    Card buildPileCard = buildPiles[b-'A'].getCard();
    if(buildPileCard.getValue() == 12){
      imaginaryDeck.addDeck(buildPiles[b-'A']);
      buildPiles[b-'A'].clear();
      moved = true;
    }
  }
  if(getPlayerHandSize() == 0){
    dealToHand();
  }
  turn++;
  return moved;
}

//deals from the masterPile to the current players hand until they have 5 cards
void Board::dealToHand(int i ){
  Hand& currentHand = p[i]->getHand();
  
  while(currentHand.add(master.getCard())){
    if(master.getSize() <= 1){
      refresh();
    }
    master.draw();
  }
}

//rotates the vector of players so that the next player is now the current player
void Board::rotate() {
  Player *tmp;
  tmp = p[0];
  for(int i = 0; i < numOfPlayers-1; i++){
    p[i] = p[i+1];
  }
  p[numOfPlayers-1] = tmp;
} //end rotate                                                                  

//shuffles the imaginary deck, moves the cards to the master deck, then erases the imaginary deck
void Board::refresh() {
  if(imaginaryDeck.getSize() == 0){
    master.create();
    master.shuffle();
  }
  else{
    imaginaryDeck.shuffle();
    master = imaginaryDeck;
    imaginaryDeck.clear();
  }
}//end refresh                                                                 

//calls the correct print function for the given number of players
void Board::printBoard() const {
  ColorModifier white(WHITE);
  ColorModifier black(BGBLACK);

  cout << endl;
  switch(numOfPlayers){
  case 2:
    toString2p();
    break;
  case 3:
    toString3p();
    break;
  case 4:
    toString4p();
    break;
  case 5:
    toString5p();
    break;
  case 6:
    toString6p();
    break;
  default:
    cout << "can't have that now...\n";
  }
  cout << white << black;
  cout << endl;
} // end printBoard

//Prints the correct board for 2 players
void Board::toString2p() const {
  //ColorModifier red(RED);
  //ColorModifier green(GREEN);
  //ColorModifier blue(BLUE);
  ColorModifier yellow(YELLOW);
  //ColorModifier cyan(CYAN);
  ColorModifier black(BGBLACK);
  ColorModifier bold(BOLD);
  ColorModifier def(DEFAULT);

  cout << black << bold;
  cout << p[1]->getPlayerColor() << setw(41) << p[1]->getName() << endl;
  cout << setw(26) << p[1]->getStockLengthStr() <<  endl;
  cout << setw(28) << "------" << endl;
  cout << setw(48) << "|    | ---- ---- ---- ----" <<  endl;
  cout << setw(24) << "| " << p[1]->getStockCardString() << " | |" << p[1]->getDiscardPileString(0) << "| |"<< p[1]->getDiscardPileString(1) << "| |" << p[1]->getDiscardPileString(2) << "| |" << p[1]->getDiscardPileString(3) << "|" <<  endl;
  cout << setw(48) << "|    | ---- ---- ---- ----" << endl;
  cout << setw(28) << "------" <<  endl;
  cout << endl;
  cout << yellow << setw(22) << "------" << endl;
  cout << setw(54) << "|?  ?|  ------  ------  ------  ------" << endl;
  cout << setw(26) << "| ?? |  | " << buildPiles[0].getCard().toString() << " |  | " << buildPiles[1].getCard().toString() << " |  | " << buildPiles[2].getCard().toString() << " |  | " << buildPiles[3].getCard().toString() << " |" << endl;
  cout << setw(54) << "| ?? |  |    |  |    |  |    |  |    |" << endl;
  cout << setw(54) << "|?  ?|  ------  ------  ------  ------" << endl;  
  cout << setw(22) << "------" << setw(6) << "A" << setw(8) << "B" << setw(8) << "C" << setw(8) << "D" << endl;
  cout << endl;
  cout << p[0]->getPlayerColor() << setw(66) << p[0]->getStockLengthStr() << endl;;
  cout << "------ ------ ------ ------ ------" << setw(35) << "--------" << endl;
  cout << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << "| " << p[0]->getHandString(0) << " | | " << p[0]->getHandString(1) << " | | " << p[0]->getHandString(2) << " | | " << p[0]->getHandString(3) << " | | " << p[0]->getHandString(4) << " |";
  cout << setw(5) << "|" << p[0]->getDiscardPileString(0) << "| |" << p[0]->getDiscardPileString(1) << "| |" << p[0]->getDiscardPileString(2) << "| |" << p[0]->getDiscardPileString(3) << "|" << setw(5) << "|" << setw(4) << p[0]->getStockCardString() << "  |"  << endl;
  cout << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << "------ ------ ------ ------ ------      6    7    8    9     --------" << endl;
  cout << setw(3) << 1 << setw(7) << 2 << setw(7) << 3 << setw(7) << 4 << setw(7) << 5 << setw(34)<< 0 << endl;
  cout << setw(41) << p[0]->getName() << endl;
  cout << def;
}//end toString2p

//Prints the correct board for 3 players
void Board::toString3p() const {
  //ColorModifier red(RED);
  //ColorModifier green(GREEN);
  //ColorModifier blue(BLUE);
  ColorModifier yellow(YELLOW);
  //ColorModifier cyan(CYAN);
  ColorModifier black(BGBLACK);
  ColorModifier bold(BOLD);
  ColorModifier def(DEFAULT);
  cout << black << bold;

  cout.width(20);
  cout << p[1]->getPlayerColor() << std::internal << p[1]->getName() << p[2]->getPlayerColor();
  cout.width(34);
  cout << std::internal << p[2]->getName() << endl;

  cout << p[1]->getPlayerColor() << setw(12) << p[1]->getStockLengthStr() << setw(34) << p[2]->getPlayerColor() << p[2]->getStockLengthStr() << endl;
  cout << p[1]->getPlayerColor() << setw(14) << "------" << setw(30) << p[2]->getPlayerColor() << "------" <<  endl;
  cout << p[1]->getPlayerColor() << setw(34) << "|    | ---- ---- ---- ----" << setw(10) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----" <<  endl;
  cout << p[1]->getPlayerColor() << setw(10) << "| " << p[1]->getStockCardString() << " | |" << p[1]->getDiscardPileString(0) << "| |"<< p[1]->getDiscardPileString(1) << "| |" << p[1]->getDiscardPileString(2) << "| |" << p[1]->getDiscardPileString(3) << "|" << setw(10); 
  cout << p[2]->getPlayerColor() << "| " << p[2]->getStockCardString() << " | |" << p[2]->getDiscardPileString(0) << "| |"<< p[2]->getDiscardPileString(1) << "| |" << p[2]->getDiscardPileString(2) << "| |" << p[2]->getDiscardPileString(3) << "|" << endl;
  cout << p[1]->getPlayerColor() << setw(34) << "|    | ---- ---- ---- ----" << setw(10) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----" << endl;
  cout << p[1]->getPlayerColor() << setw(14) << "------" << setw(30) << p[2]->getPlayerColor() <<"------" << endl;
  cout << endl;
  cout << yellow << setw(22) << "------" << endl;
  cout << setw(54) << "|?  ?|  ------  ------  ------  ------" << endl;
  cout << setw(26) << "| ?? |  | " << buildPiles[0].getCard().toString() << yellow  << " |  | " << buildPiles[1].getCard().toString() << yellow << " |  | " << buildPiles[2].getCard().toString() << " |  | " << buildPiles[3].getCard().toString() << " |" << endl;
  cout <<  setw(54) << "| ?? |  |    |  |    |  |    |  |    |" << endl;
  cout << setw(54) << "|?  ?|  ------  ------  ------  ------" << endl;  
  cout << setw(22) << "------" << setw(6) << "A" << setw(8) << "B" << setw(8) << "C" << setw(8) << "D" << endl;
  cout << endl;
  cout << p[0]->getPlayerColor() << setw(66) << p[0]->getStockLengthStr() << endl;;
  cout << "------ ------ ------ ------ ------" << setw(35) << "--------" << endl;
  cout << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << "| " << p[0]->getHandString(0) << " | | " << p[0]->getHandString(1) << " | | " << p[0]->getHandString(2) << " | | " << p[0]->getHandString(3) << " | | " << p[0]->getHandString(4) << " |";
  cout << setw(5) << "|" << p[0]->getDiscardPileString(0) << "| |" << p[0]->getDiscardPileString(1) << "| |" << p[0]->getDiscardPileString(2) << "| |" << p[0]->getDiscardPileString(3) << "|" << setw(5) << "|" << setw(4) << p[0]->getStockCardString() << "  |"  << endl;
  cout << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << "------ ------ ------ ------ ------      6    7    8    9     --------" << endl;
  cout << setw(3) << 1 << setw(7) << 2 << setw(7) << 3 << setw(7) << 4 << setw(7) << 5 << setw(34)<< 0 << endl;
  cout << setw(41) << p[0]->getName() << endl;
  cout << def;
}//end toString3p

//Prints the correct board for 4 players
void Board::toString4p() const {
  //ColorModifier red(RED);
  //ColorModifier green(GREEN);
  //ColorModifier blue(BLUE);
  ColorModifier yellow(YELLOW);
  //ColorModifier cyan(CYAN);
  ColorModifier black(BGBLACK);
  ColorModifier bold(BOLD);
  ColorModifier def(DEFAULT);
  cout << black << bold;
  
  cout.width(16);
  cout << p[1]->getPlayerColor() << std::internal << p[1]->getName() << p[2]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[2]->getName() << p[3]->getPlayerColor() ;
  cout.width(30);
  cout << std::internal << p[3]->getName() << endl;

  cout << "  " << p[1]->getPlayerColor() << p[1]->getStockLengthStr() << setw(30) << p[2]->getPlayerColor() << p[2]->getStockLengthStr();
  cout << setw(30) << p[3]->getPlayerColor() << p[3]->getStockLengthStr() << endl;
  cout << p[1]->getPlayerColor() << "------" << setw(26) << p[2]->getPlayerColor() << "------" << setw(26) << p[3]->getPlayerColor() << "------" << endl;
  cout << p[1]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[3]->getPlayerColor() << "|    | ---- ---- ---- ----" << endl;
  cout << p[1]->getPlayerColor() << "| " << p[1]->getStockCardString() << " | |" << p[1]->getDiscardPileString(0) << "| |";
  cout << p[1]->getDiscardPileString(1) << "| |" << p[1]->getDiscardPileString(2) << "| |" << p[1]->getDiscardPileString(3) << "|" << setw(6); 
  cout << p[2]->getPlayerColor() << "| " << p[2]->getStockCardString() << " | |" << p[2]->getDiscardPileString(0) << "| |"; 
  cout << p[2]->getDiscardPileString(1) << "| |" << p[2]->getDiscardPileString(2) << "| |" << p[2]->getDiscardPileString(3) << "|" << setw(6); 
  cout << p[3]->getPlayerColor() << "| " << p[3]->getStockCardString() << " | |" << p[3]->getDiscardPileString(0) << "| |";
  cout << p[3]->getDiscardPileString(1) << "| |" << p[3]->getDiscardPileString(2) << "| |" << p[3]->getDiscardPileString(3) << "|" << endl; 
  cout << p[1]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[3]->getPlayerColor() << "|    | ---- ---- ---- ----" << endl;
  cout << p[1]->getPlayerColor() << "------" << setw(26) << p[2]->getPlayerColor() << "------" << setw(26) << p[3]->getPlayerColor() << "------" << endl;
  cout << endl;
  cout << yellow << setw(29) << "------" << endl;
  cout << setw(61) << "|?  ?|  ------  ------  ------  ------" << endl;
  cout << setw(33) << "| ?? |  | " << buildPiles[0].getCard().toString() << " |  | " << buildPiles[1].getCard().toString();
  cout << " |  | " << buildPiles[2].getCard().toString() << " |  | " << buildPiles[3].getCard().toString() << " |" << endl;
  cout << setw(61) << "| ?? |  |    |  |    |  |    |  |    |" << endl;
  cout << setw(61) << "|?  ?|  ------  ------  ------  ------" << endl;  
  cout << setw(29) << "------" << setw(6) << "A" << setw(8) << "B" << setw(8) << "C" << setw(8) << "D" << endl;
  cout << endl;
  cout << p[0]->getPlayerColor() << setw(66) << p[0]->getStockLengthStr() << endl;;
  cout << "------ ------ ------ ------ ------" << setw(35) << "--------" << endl;
  cout << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << "| " << p[0]->getHandString(0) << " | | " << p[0]->getHandString(1) << " | | " << p[0]->getHandString(2) << " | | "; 
  cout << p[0]->getHandString(3) << " | | " << p[0]->getHandString(4) << " |";
  cout << setw(5) << "|" << p[0]->getDiscardPileString(0) << "| |" << p[0]->getDiscardPileString(1) << "| |"; 
  cout << p[0]->getDiscardPileString(2) << "| |" << p[0]->getDiscardPileString(3) << "|";
  cout << setw(5) << "|" << setw(4) << p[0]->getStockCardString() << "  |"  << endl;
  cout << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << "------ ------ ------ ------ ------      6    7    8    9     --------" << endl;
  cout << setw(3) << 1 << setw(7) << 2 << setw(7) << 3 << setw(7) << 4 << setw(7) << 5 << setw(34)<< 0 << endl;
  cout << setw(41) << p[0]->getName() << endl;
  cout << def; 
}//end toString4p


//Prints the correct board for 5 players
void Board::toString5p() const{
  //ColorModifier red(RED);
  //ColorModifier green(GREEN);
  //ColorModifier blue(BLUE);
  ColorModifier yellow(YELLOW);
  //ColorModifier cyan(CYAN);
  //ColorModifier pink(PINK);
  //ColorModifier lYellow(YELLOWLT);
  ColorModifier black(BGBLACK);
  ColorModifier bold(BOLD);
  ColorModifier def(DEFAULT);
  cout << black << bold;

  cout.width(16);
  cout << p[1]->getPlayerColor() << std::internal << p[1]->getName() << p[2]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[2]->getName() << p[3]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[3]->getName() << p[4]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[4]->getName() << endl;

  cout << "  " << p[1]->getPlayerColor() << p[1]->getStockLengthStr() << setw(30) << p[2]->getPlayerColor() << p[2]->getStockLengthStr();
  cout << setw(30) << p[3]->getPlayerColor() << p[3]->getStockLengthStr() << setw(30) << p[4]->getPlayerColor() << p[4]->getStockLengthStr() << endl;
  cout << p[1]->getPlayerColor() << "------" << setw(26) << p[2]->getPlayerColor() << "------";
  cout << setw(26) << p[3]->getPlayerColor() << "------" << setw(26) << p[4]->getPlayerColor() << "------" <<endl;
  cout << p[1]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[3]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[4]->getPlayerColor() << "|    | ---- ---- ---- ----" << endl;
  cout << p[1]->getPlayerColor() << "| " << p[1]->getStockCardString() << " | |" << p[1]->getDiscardPileString(0) << "| |";
  cout << p[1]->getDiscardPileString(1) << "| |" << p[1]->getDiscardPileString(2) << "| |" << p[1]->getDiscardPileString(3) << "|" << setw(6);
  cout << p[2]->getPlayerColor() << "| " << p[2]->getStockCardString() << " | |" << p[2]->getDiscardPileString(0) << "| |";
  cout << p[2]->getDiscardPileString(1) << "| |" << p[2]->getDiscardPileString(2) << "| |" << p[2]->getDiscardPileString(3) << "|" << setw(6);
  cout << p[3]->getPlayerColor() << "| " << p[3]->getStockCardString() << " | |" << p[3]->getDiscardPileString(0) << "| |";
  cout << p[3]->getDiscardPileString(1) << "| |" << p[3]->getDiscardPileString(2) << "| |" << p[3]->getDiscardPileString(3) << "|" << setw(6);
  cout << p[4]->getPlayerColor() << "| " << p[4]->getStockCardString() << " | |" << p[4]->getDiscardPileString(0) << "| |"; 
  cout << p[4]->getDiscardPileString(1) << "| |" << p[4]->getDiscardPileString(2) << "| |" << p[4]->getDiscardPileString(3) << "|" << endl;
  cout << p[1]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[3]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[4]->getPlayerColor() << "|    | ---- ---- ---- ----" << endl;
  cout << p[1]->getPlayerColor() << "------" << setw(26) << p[2]->getPlayerColor() << "------";
  cout << setw(26) << p[3]->getPlayerColor() << "------" << setw(26) << p[4]->getPlayerColor() << "------" << endl;
  cout << "\n";
  cout << yellow << setw(44) << "------" << endl;
  cout << "" << setw(76) << "|?  ?|  ------  ------  ------  ------" << endl;
  cout << setw(48) << "| ?? |  | " << buildPiles[0].getCard().toString() << " |  | " << buildPiles[1].getCard().toString();
  cout << " |  | " << buildPiles[2].getCard().toString() << " |  | " << buildPiles[3].getCard().toString() << " |" << endl;
  cout << setw(76) << "| ?? |  |    |  |    |  |    |  |    |" << endl;
  cout << setw(76) << "|?  ?|  ------  ------  ------  ------" << endl;  
  cout << setw(44) << "------" << setw(6) << "A" << setw(8) << "B" << setw(8) << "C" << setw(8) << "D" << endl;
  cout << "\n";
  cout << p[0]->getPlayerColor() << setw(88) << p[0]->getStockLengthStr() << endl;;
  cout << setw(56) << "------ ------ ------ ------ ------" << setw(35) << "--------" << endl;
  cout << setw(91) << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << setw(24) << "| " << p[0]->getHandString(0) << " | | " << p[0]->getHandString(1) << " | | " << p[0]->getHandString(2) << " | | "; 
  cout << p[0]->getHandString(3) << " | | " << p[0]->getHandString(4) << " |";
  cout << setw(5) << "|" << p[0]->getDiscardPileString(0) << "| |" << p[0]->getDiscardPileString(1) << "| |" << p[0]->getDiscardPileString(2) << "| |";
  cout << p[0]->getDiscardPileString(3) << "|" << setw(5) << "|" << setw(4) << p[0]->getStockCardString() << "  |"  << endl;
  cout << setw(91) << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << setw(91) << "------ ------ ------ ------ ------      6    7    8    9     --------" << endl;
  cout << setw(26) << 1 << setw(7) << 2 << setw(7) << 3 << setw(7) << 4 << setw(7) << 5 << setw(34)<< 0 << endl;
  cout << setw(62) << p[0]->getName() << endl;
  cout << def;
}

//Prints the correct board for 6 players
void Board::toString6p() const{
  //ColorModifier red(RED);
  //ColorModifier green(GREEN);
  //ColorModifier blue(BLUE);
  ColorModifier yellow(YELLOW);
  //ColorModifier cyan(CYAN);
  //ColorModifier pink(PINK);
  //ColorModifier white(WHITE);
  ColorModifier black(BGBLACK);
  ColorModifier bold(BOLD);
  ColorModifier def(DEFAULT);
  cout << black << bold;

  cout.width(16);
  cout << p[1]->getPlayerColor() << std::internal << p[1]->getName() << p[2]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[2]->getName() << p[3]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[3]->getName() << p[4]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[4]->getName() << p[5]->getPlayerColor();
  cout.width(30);
  cout << std::internal << p[5]->getName() << endl;

  cout << "  " << p[1]->getPlayerColor() << p[1]->getStockLengthStr() << setw(30) << p[2]->getPlayerColor() << p[2]->getStockLengthStr() << setw(30) << p[3]->getPlayerColor() << p[3]->getStockLengthStr() << setw(30) << p[4]->getPlayerColor() << p[4]->getStockLengthStr() << setw(30) << p[5]->getPlayerColor() << p[5]->getStockLengthStr() << endl;
  cout << p[1]->getPlayerColor() << "------" << setw(26) << p[2]->getPlayerColor() << "------" << setw(26) << p[3]->getPlayerColor() << "------" << setw(26) << p[4]->getPlayerColor() << "------" << setw(26) << p[5]->getPlayerColor() << "------" << endl;
  cout << p[1]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[3]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[4]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[5]->getPlayerColor() << "|    | ---- ---- ---- ----" << endl;
  cout << p[1]->getPlayerColor() << "| " << p[1]->getStockCardString() << " | |" << p[1]->getDiscardPileString(0) << "| |"<< p[1]->getDiscardPileString(1); 
  cout << "| |" << p[1]->getDiscardPileString(2) << "| |" << p[1]->getDiscardPileString(3) << "|" << setw(6); 
  cout << p[2]->getPlayerColor() << "| " << p[2]->getStockCardString() << " | |" << p[2]->getDiscardPileString(0) << "| |"<< p[2]->getDiscardPileString(1); 
  cout << "| |" << p[2]->getDiscardPileString(2) << "| |" << p[2]->getDiscardPileString(3) << "|" << setw(6);
  cout << p[3]->getPlayerColor() << "| " << p[3]->getStockCardString() << " | |" << p[3]->getDiscardPileString(0) << "| |"<< p[3]->getDiscardPileString(1); 
  cout << "| |" << p[3]->getDiscardPileString(2) << "| |" << p[3]->getDiscardPileString(3) << "|" << setw(6);
  cout << p[4]->getPlayerColor() << "| " << p[4]->getStockCardString() << " | |" << p[4]->getDiscardPileString(0) << "| |"<< p[4]->getDiscardPileString(1); 
  cout << "| |" << p[4]->getDiscardPileString(2) << "| |" << p[4]->getDiscardPileString(3) << "|" << setw(6);
  cout << p[5]->getPlayerColor() << "| " << p[5]->getStockCardString() << " | |" << p[5]->getDiscardPileString(0) << "| |"<< p[5]->getDiscardPileString(1); 
  cout << "| |" << p[5]->getDiscardPileString(2) << "| |" << p[5]->getDiscardPileString(3) << "|" << endl;
  cout << p[1]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[2]->getPlayerColor() << "|    | ---- ---- ---- ----"; 
  cout << setw(6) << p[3]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[4]->getPlayerColor() << "|    | ---- ---- ---- ----" << setw(6) << p[5]->getPlayerColor() << "|    | ---- ---- ---- ----" << endl;
  cout << p[1]->getPlayerColor() << "------" << setw(26) << p[2]->getPlayerColor() << "------" << setw(26) << p[3]->getPlayerColor() << "------" << setw(26) << p[4]->getPlayerColor() << "------" << setw(26) << p[5]->getPlayerColor() << "------" << endl;
  cout << "\n";
  cout << yellow << setw(60) << "------" << endl;
  cout << "" << setw(92) << "|?  ?|  ------  ------  ------  ------" << endl;
  cout << setw(64) << "| ?? |  | " << buildPiles[0].getCard().toString() << " |  | " << buildPiles[1].getCard().toString() << " |  | ";
  cout << buildPiles[2].getCard().toString() << " |  | " << buildPiles[3].getCard().toString() << " |" << endl;
  cout << setw(92) << "| ?? |  |    |  |    |  |    |  |    |" << endl;
  cout << setw(92) << "|?  ?|  ------  ------  ------  ------" << endl;  
  cout << setw(60) << "------" << setw(6) << "A" << setw(8) << "B" << setw(8) << "C" << setw(8) << "D" << endl;
  cout << "\n";
  cout << p[0]->getPlayerColor() << setw(108) << p[0]->getStockLengthStr() << endl;;
  cout << setw(76) << "------ ------ ------ ------ ------" << setw(35) << "--------" << endl;
  cout << setw(111) << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << setw(44) << "| " << p[0]->getHandString(0) << " | | " << p[0]->getHandString(1) << " | | " << p[0]->getHandString(2); 
  cout << " | | " << p[0]->getHandString(3) << " | | " << p[0]->getHandString(4) << " |";
  cout << setw(5) << "|" << p[0]->getDiscardPileString(0) << "| |" << p[0]->getDiscardPileString(1) << "| |" << p[0]->getDiscardPileString(2);
  cout << "| |" << p[0]->getDiscardPileString(3) << "|" << setw(5) << "|" << setw(4) << p[0]->getStockCardString() << "  |"  << endl;
  cout << setw(111) << "|    | |    | |    | |    | |    |    ---- ---- ---- ----    |      |" << endl;
  cout << setw(111) << "------ ------ ------ ------ ------      6    7    8    9     --------" << endl;
  cout << setw(46) << 1 << setw(7) << 2 << setw(7) << 3 << setw(7) << 4 << setw(7) << 5 << setw(34)<< 0 << endl;
  cout << setw(82) << p[0]->getName() << endl;
  cout << def;
}//end 6p to stirng ui

bool Board::operator==(const Board &other){
  if(turn == other.turn){
    return true;
  }
  return false;
}

Board& Board::operator=(const Board &other){
  //Board& mainBoard(other);
  master = other.master;
  imaginaryDeck = other.imaginaryDeck;
  turn = other.turn;
  buildPiles = other.buildPiles;
  numOfPlayers = other.numOfPlayers;
  numOfHumans = other.numOfHumans;
  hard = other.hard;
  
  for(int i = 0; i < other.numOfPlayers; i++){
    Player *playerTemp = other.p[i];
    if(playerTemp->isHuman()){
      Player *human = new Human(*playerTemp);
      if(i <2){
	delete p[i];
	p[i] = NULL;
	p[i] = human;
      }
      else{
	p.push_back(human);
      }
    }
    else{
      //      Player *human = new Computer(*playerTemp);
      Player *human = new ComputerAI(*playerTemp);
      if(i <2){
	delete p[i];
	p[i] = NULL;
	p[i] = human;
      }
      else{
	p.push_back(human);
      }
    }
  }
  return *this;
}
