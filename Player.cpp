#include <iostream>
#include <vector>
#include <sstream>
#include "DiscardPile.hpp"
#include "StockPile.hpp"
#include "Hand.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "Color.hpp"

using std::string;
using std::vector;

//constructs a player based on a name, initial stock pile size, and player number
//sets up all the decks that the player owns
Player::Player(string initName, int initStock, int initPNum) {
  name = initName;
  playerNum = initPNum;
  Hand handTemp(5);
  playerHand = handTemp;
  DiscardPile discard1(12);
  DiscardPile discard2(12);
  DiscardPile discard3(12);
  DiscardPile discard4(12);
  discardPiles.push_back(discard1);
  discardPiles.push_back(discard2);
  discardPiles.push_back(discard3);
  discardPiles.push_back(discard4);
  StockPile tempStock(initStock);
  stock = tempStock;

  //stock = tempStock;
}

//copy constructor 
Player::Player(const Player &p){
  name = p.getName();
  playerNum = p.playerNum;
  playerHand = p.playerHand;
  stock = p.stock;
  discardPiles.push_back(p.discardPiles[0]);
  discardPiles.push_back(p.discardPiles[1]);
  discardPiles.push_back(p.discardPiles[2]);
  discardPiles.push_back(p.discardPiles[3]);
}

//returns the player's color based on their player number
//cyan for 0
//red for 1
//green for 2
//clue for 3
//pink for 4
//white for 5
ColorModifier Player::getPlayerColor()const {
  ColorModifier red(RED);
  ColorModifier green(GREEN);
  ColorModifier blue(BLUE);
  ColorModifier yellow(YELLOW);
  ColorModifier cyan(CYAN);
  ColorModifier pink(PINK);
  ColorModifier white(WHITE);
  ColorModifier underline(UNDERLINE);
  switch(playerNum){
  case 0:
    return cyan; 
    break;
  case 1:
    return red;
    break;
  case 2:
    return green;
    break;
  case 3:
    return blue; 
    break;
  case 4:
    return pink;
    break;
  case 5:
    return white;
    break;
  default:
    return underline;
    break;
  }
}

//returns the string representation of the size of the player's stock pile in 2 characters
string Player::getStockLengthStr() const{
  std::stringstream os;
  if(stock.getSize() < 10){
    os << "0" << stock.getSize();
    return os.str();
  }
  os << stock.getSize();
  return os.str();
}
