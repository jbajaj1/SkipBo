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

#include "Game.hpp"
#include <iostream>
#include "Card.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <cctype>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include "Color.hpp"

using std::cout;
using std::exception;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;
using std::getline;
using std::list;
using std::endl;
using std::cin;

Game::Game() {
  Board board2(printStartMenu());
  board2.dealToHand();  
  board = board2;
  i = 0;
  it = boardList.begin();
}

Game::~Game() {
  
}
  
//What do you want to do(0 - 9 choose card, e, s)
//if e - save or quit
//if 0-9 - move to where (5-9 A-D)
Board Game::createNewBoard(){
  bool good = false;
  char difficultLevel;
  while(!good){
    try{
      cout << "(e)asy or (h)ard: ";
      cin >> difficultLevel;
      difficultLevel = tolower(difficultLevel);
      if(difficultLevel != 'e' && difficultLevel != 'h'){
	throw difficultLevel;
      }
      good = true;
    }
    catch(char){
      cin.clear();
      string ignoreStr;
      getline(cin, ignoreStr);
      cout << "Invalid input! Input 'e' or 'h'" << endl;
    }
  }

  int players;
  good = false;
  //keep asking number of players until valid input
  while(!good){
    try{
      cout << "How many players? ";
      cin >> players;
      if(players < 2 || players > 6){
	throw players;
      }
      good = true;
    }
    catch(int){
      cin.clear();
      string ignoreStr;
      getline(cin, ignoreStr);
      cout << "Invalid Input\nPlease enter 2, 3, 4, 5, or 6\n" << endl;
    }
  }

  int humanNum;

  good = false;
  
  //keep asking number of human players until valid input
  while(!good){
    try{
      cout << "How many human players? ";
      cin >> humanNum;
      if(humanNum < 1 || humanNum > players){
	throw humanNum;
      }
      good = true;
    }
    catch(int & humanNum){
      cin.clear();
      string ignoreStr;
      getline(cin, ignoreStr);
      cout << "Input needs to be greater than zero and less than number of players\nPlease enter in integer format\n" << endl;
    }
  }

  //create stock size max dependent on number of players
  int stockSize;
  int stockSizeMax = 30;
  if(players > 4){
    stockSizeMax = 20;
  }
  good = false;

  //keeps asking number of stock size until valid input
  while(!good){
    try{
      cout << "Choose a stock size (5-" << stockSizeMax << ") ";
      cin >> stockSize;
      if(stockSize > stockSizeMax  || stockSize < 5){
	throw stockSize;
      }
      good = true;
    }
    catch(int){
      cin.clear();
      string ignoreStr;
      getline(cin, ignoreStr);
      cout << "Stock size needs to be greater than 5 and less than " << stockSizeMax <<endl;
      cout << "Please enter in integer format\n" << endl;
    }
  }

  //return board;
  Board board2(stockSize, players, humanNum);
  if(difficultLevel == 'e'){
    board2.setDifficulty(false);
  }
  else{
    board2.setDifficulty(true);
  }
  //board = board2;
  return board2;
}

//loads the board, check if board is created, else creates new board
Board Game::load(){
  Board board2(1,2,0);
  if(board2.load()){
    return board2;
  }
  cout << "Load failed " << endl;
  cout << "You can save a game during your turn in a game by inputting 's', you can also save while exitting" << endl;
  return createNewBoard();
}

//prints menu (new game or load 
Board Game::printStartMenu(){
  bool good = false;
  int choice;
  
  //keeps asking input until valid input
  while(!good){
    cout << "1. New Game \n2. Load Game \n3. Help \n4. Exit\nEnter choice: ";
    try{
      cin >> choice;
      if(choice < 1 || choice > 4){
	throw choice;
      }
      good = true;
    }
    catch(int & choice){
      cin.clear();
      string ignoreStr;
      getline(cin, ignoreStr);
      cout << "Invalid Input\nPlease enter 1, 2, or 3\n" << endl;
    }
  }
  if(choice == 2){
    return load();
  }
  if(choice == 4){
    cout << "Good-Bye!" << endl;
    board.~Board();
    exit(EXIT_SUCCESS);
  }
  if(choice == 3){
    cout << endl << endl;
    cout << "To play Skip-Bo, the goal is to get rid of your stock pile cards (denoted by 0). Each player has a hand of five cards (0-4) and four discard piles (5-9). In the center of the field, there are four build piles (A-D). A Skip-Bo deck contains cards 1-12, 12 of each, plus 18 Skip-Bo cards. This deck is used to give players their cards. At the start of a turn, a player receives cards until they have five cards in their hand. Players do moves by sequentially building piles by using cards from either their hand, discard piles, or stock pile. Skip-Bo (SB) cards are wild cards and can be used to represent any number 1-12. If all five cards are used in a single turn, then five new cards are given to the player.  Whenever a build pile reaches 12 cards, it is taken off the field. A player ends their turn by moving a card from their hand to a discard pile. (Note: Discard piles are stackable). The winner is the player who uses all their stock pile cards first.\nYou can choose easy or hard AI's (note: you can't the see the moves of hard AI's to add an extra challenge)" << endl << endl;
    return printStartMenu();
  }

  return createNewBoard();
}

//1. New Game 2. Load Game
//1 - How many players?
//How many human players?
//How many cards in stock pile?
bool Game::printGameMenu(){
  bool good = false;
  char choice;

  //keeps asking for valid card to move
  while(!good){
    try{
      cout << "Choose: 0-9,(e)xit,(s)ave, (u)ndo, (r)edo: ";
      cin >> choice;
      choice = tolower(choice);
      if(!(isdigit(choice) || choice == 'e' || choice == 's' || choice == 'u' || choice == 'r')){
	throw choice;
      }
      if(choice == 'r'){
	if(*it == boardList.back()){
	  throw choice;
	}
      }
      if(choice == 'u'){
	if(it == boardList.begin()){
	  throw choice;
	}
      }
      good = true;
    }
    catch(char){
      cout << "Invalid input, must be 0-9, 's', 'u', or 'r'" << endl;
      return printGameMenu();
    }
  }

  //if e, exit
  if(choice == 'e'){
    try{
      char saveChoice;
      cout << "Do you want to save? (y)es or (n)o: ";
      cin >> saveChoice;
      if(saveChoice != 'y'){
	throw saveChoice;
      }
    }
    catch(char){
      board.~Board();
      exit(EXIT_SUCCESS);
    }
    board.save();
    board.~Board();
    exit(EXIT_SUCCESS);
  }

  //if s, save
  if(choice == 's'){
    cout << "Save the game" << endl;
    board.save();
    return printGameMenu();
  }
  if(choice == 'u'){
    it--;
    board = *it;
    cout << "Undo!" << endl;
    board.printBoard();
    return printGameMenu();
  }
  if(choice == 'r'){
    it++;
    board = *it;
    cout << "Redo!" << endl;
    board.printBoard();
    return printGameMenu();
  }
  good = false;
  char moveChoice;

  //keeps asking for position to move
  while(!good){
    try{
      cout << "Move to where: (6-9 and A-D): ";
      cin >> moveChoice;
      if(moveChoice != '6' && moveChoice != '7'  && moveChoice != '8'  && moveChoice != '9'  && moveChoice != 'A'  && moveChoice != 'a'  && moveChoice != 'B'  && moveChoice != 'b'  && moveChoice != 'C'  && moveChoice != 'c'  && moveChoice != 'D'  && moveChoice != 'd'){
	throw moveChoice;
      }  
      if(choice >= '6' && choice<= '9'){
	if(moveChoice >= '6' && moveChoice <= '9'){
	  throw moveChoice;
	}
      }
      if(choice == '0'){
	if(moveChoice >= '6' && moveChoice <= '9'){
	  throw moveChoice;
	}
      }
      good = true;
    }
    catch(char){
      cout << "Invalid move" << endl;
      return printGameMenu();
    }
  }

  if(choice >= '1' && choice <= '5'){
    if(moveChoice >= '6' && moveChoice <= '9'){
      board.moveCard(choice, moveChoice);
      Board boardTemp(board);
      if(*it == boardList.back()){
	boardList.push_back(boardTemp);
	it++;
      }
      else{
	/*boardList.erase(++it,boardList.end());
	  it--;
	  boardList.push_back(boardTemp);
	  it++;*/
	
	it++;
	boardList.insert(it, boardTemp);
	it--;
	while(!(*it == boardList.back())){
	  boardList.pop_back();
	}
	boardList.pop_back();
	board = *it;
      }
      return false;
    }
  }
  if(!board.moveCard(choice, moveChoice)){
    board.printBoard();
    return printGameMenu();
  }
  return true;
}

void Game::play(){
  //creates board by asking information from player
  //keep playing until the game if finished
  while(board.isGameNotFinished()){
    //if player is human, deal cards to hand, and asks input from player
    if(board.getPlayerIsHuman()){
      board.dealToHand();
      board.printBoard();
      Board boardTemp(board);
      if(i != 0){
	boardList.push_back(boardTemp);
	it++;
      }
      else{
	boardList.push_back(boardTemp);
	it = boardList.begin();
	board = *it;
	i++;
      }
      while(printGameMenu()){
	board.printBoard();
	Board boardTemp(board);
	if(*it == boardList.back()){
	  boardList.push_back(boardTemp);
	  it++;
	}
	else{
	  
	  it++;
	  boardList.insert(it, boardTemp);
	  it--;
	  while(!(*it == boardList.back())){
	    boardList.pop_back();
	  }
	  boardList.pop_back();
	  board = *it;
	}
	if(!board.isGameNotFinished()){
	  cout << endl << board.getPlayerName() << " wins" << endl;
	  break;
	}
      }
    }
    else{
      //if player is computer, deal hand and then tell computer to do move
      cout << endl;
      board.dealToHand();
      board.computerDoMove();
      if(!board.isGameNotFinished()){
	cout << endl << board.getPlayerName() << " wins" << endl;
	break;
      }

      cout << endl << board.getPlayerName() << " finished turn" << endl << endl << endl;
    }
    board.rotate();
  }

  printGameOver();
}

void Game::printGameOver() {
  ColorModifier red(RED);
  ColorModifier bold(BOLD);
  ColorModifier def(DEFAULT);
  ColorModifier white(WHITE);

  cout << red << bold;  
  cout << endl << endl << endl << endl << endl;
  cout << "        GGGGGGGGGGGGG" << endl;                                                                   
  cout << "     GGG::::::::::::G" << endl;                                                                   
  cout << "   GG:::::::::::::::G" << endl;                                                                   
  cout << "  G:::::GGGGGGGG::::G" << endl;                                                                   
  cout << " G:::::G       GGGGGG   aaaaaaaaaaaaa       mmmmmmm    mmmmmmm        eeeeeeeeeeee" << endl;         
  cout << "G:::::G                 a::::::::::::a    mm:::::::m  m:::::::mm    ee::::::::::::ee" << endl;       
  cout << "G:::::G                 aaaaaaaaa:::::a  m::::::::::mm::::::::::m  e::::::eeeee:::::ee" << endl;     
  cout << "G:::::G    GGGGGGGGGG            a::::a  m::::::::::::::::::::::m e::::::e     e:::::e" << endl;     
  cout << "G:::::G    G::::::::G     aaaaaaa:::::a  m:::::mmm::::::mmm:::::m e:::::::eeeee::::::e" << endl;     
  cout << "G:::::G    GGGGG::::G   aa::::::::::::a  m::::m   m::::m   m::::m e:::::::::::::::::e" << endl;      
  cout << "G:::::G        G::::G  a::::aaaa::::::a  m::::m   m::::m   m::::m e::::::eeeeeeeeeee" << endl;       
  cout << " G:::::G       G::::G a::::a    a:::::a  m::::m   m::::m   m::::m e:::::::e" << endl;                
  cout << "  G:::::GGGGGGGG::::G a::::a    a:::::a  m::::m   m::::m   m::::m e::::::::e" << endl;               
  cout << "   GG:::::::::::::::G a:::::aaaa::::::a  m::::m   m::::m   m::::m  e::::::::eeeeeeee" << endl;       
  cout << "     GGG::::::GGG:::G  a::::::::::aa:::a m::::m   m::::m   m::::m   ee:::::::::::::e" << endl;       
  cout << "        GGGGGG   GGGG   aaaaaaaaaa  aaaa mmmmmm   mmmmmm   mmmmmm     eeeeeeeeeeeeee" << endl;       
    cout << endl;
  cout << "     OOOOOOOOO" << endl;                                                                          
  cout << "   OO:::::::::OO" << endl;                                                                        
  cout << " OO:::::::::::::OO" << endl;                                                                      
  cout << "O:::::::OOO:::::::O" << endl;                                                                     
  cout << "O::::::O   O::::::O vvvvvvv           vvvvvvv    eeeeeeeeeeee     rrrrr   rrrrrrrrr" << endl;       
  cout << "O:::::O     O:::::O  v:::::v         v:::::v   ee::::::::::::ee   r::::rrr:::::::::r" << endl;      
  cout << "O:::::O     O:::::O   v:::::v       v:::::v   e::::::eeeee:::::ee r:::::::::::::::::r" << endl;     
  cout << "O:::::O     O:::::O    v:::::v     v:::::v   e::::::e     e:::::e rr::::::rrrrr::::::r" << endl;    
  cout << "O:::::O     O:::::O     v:::::v   v:::::v    e:::::::eeeee::::::e  r:::::r     r:::::r" << endl;    
  cout << "O:::::O     O:::::O      v:::::v v:::::v     e:::::::::::::::::e   r:::::r     rrrrrrr" << endl;    
  cout << "O:::::O     O:::::O       v:::::v:::::v      e::::::eeeeeeeeeee    r:::::r" << endl;               
  cout << "O::::::O   O::::::O        v:::::::::v       e:::::::e             r:::::r" << endl;                
  cout << "O:::::::OOO:::::::O         v:::::::v        e::::::::e            r:::::r" << endl;                
  cout << " OO:::::::::::::OO           v:::::v          e::::::::eeeeeeee    r:::::r" << endl;                
  cout << "   OO:::::::::OO              v:::v            ee:::::::::::::e    r:::::r" << endl;                
  cout << "     OOOOOOOOO                 vvv               eeeeeeeeeeeeee    rrrrrrr" << endl;
  cout << endl << white;
  cout << "                                                              Powered by MathLens (c)2015" << endl << def;
}
