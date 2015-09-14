#include <cassert>
#include <iostream>
#include "Card.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Deck.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "Hand.hpp"
#include "MasterPile.hpp"
#include "DiscardPile.hpp"
#include "StockPile.hpp"
#include "Color.hpp"
#include "ComputerAI.hpp"
#include <vector>
#include "Game.hpp"

using std::vector;

//This is the main testing file that will be turned in
//card test start
void cardTest() {
  Card c0(0); //card with value 0 <-blank space
  Card c3(3); //"" 3
  Card c5(5); //"" 5
  Card c10(10); //"" 10
  Card c13(13); //"" 13 <-skipbo
 
  //test if value correct, test getter
  assert(c0.getValue() == 0);
  assert(c3.getValue() == 3);
  assert(c5.getValue() == 5);
  assert(c10.getValue() == 10);
  assert(c13.getValue() == 13);
  
  //test if card is a skipbo
  assert(!c0.getIsSkipBo());
  assert(!c3.getIsSkipBo());
  assert(!c5.getIsSkipBo());
  assert(!c10.getIsSkipBo());
  assert(c13.getIsSkipBo());
  
  //test tostring of cards, 0 is blank space, 0-12 actual umber, 13 is SB
  assert(c0.toString() == "  ");
  assert(c3.toString() == "03");
  assert(c5.toString() == "05");
  assert(c10.toString() == "10");
  assert(c13.toString() == "SB");
  
  //test if color correct, first get color returns colormodifier, second color returns actual number code
  assert(c0.getColor().getColor() == 95);
  assert(c3.getColor().getColor() == 94);
  assert(c5.getColor().getColor() == 97);
  assert(c10.getColor().getColor() == 95);
  assert(c13.getColor().getColor() == 93);
}//end cardtest

//start deck test
void deckTest() {
  //construct various cards
  Card c0(0);
  Card c3(3);
  Card c5(5);
  Card c10(10);
  Card c13(13);

  Deck d(12); //deck of size 12
  
  assert(d.getSize() == 0); //no cards should be in it
  assert(d.getCapacity() == 12); //has a capcity of 12 total cards

  assert(!d.add(c0)); //can't add blank card
  
  //additional cards
  Card c1(1);
  Card c2(2);
  Card c6(6);
  
  //need to add in numerical order, for build piles
  assert(d.add(c1));
  assert(!d.add(c10));
  assert(d.add(c2));
  assert(d.add(c3));
  assert(!d.add(c5));
  assert(d.add(c13));
  assert(d.add(c5));
  assert(!d.add(c5));
  assert(!d.add(c2));
  assert(d.add(c6));

  //check sizes and make sure cpaapctiy is still 12
  assert(d.getSize() == 6);
  assert(d.getCapacity() == 12);

  //check values of cards, test if draw removes a card, check if skipbo as well
  assert(!d.getCard().getIsSkipBo());
  assert(d.getCard().getValue() == 6);
  assert(d.draw(1).getValue() == 6);
  assert(!d.getCard().getIsSkipBo());
  assert(d.getCard().getValue() == 5);
  assert(d.draw(1).getValue() == 5);
  
  assert(d.getCard().getIsSkipBo());
  assert(d.getCard().getValue() == 4);
  assert(d.getCard().getIsSkipBo());
  
  assert(d.draw(1).getValue() == 4);
  assert(!d.getCard().getIsSkipBo());
  assert(d.draw(1).getValue() == 3);
  assert(!d.getCard().getIsSkipBo());
  assert(d.getSize() == 2);
}//end decktest

//tests for players
void playerTest() {
  //human players, with appropriaite identifiers
  Human h1("Never", 5, 10);
  assert(h1.getName() == "Never");
  assert(h1.isHuman());
  assert(h1.getPlayerColor().getColor() == 4); //check color

  Human h2("Gonna", 4, 20);
  assert(h2.getName() == "Gonna");
  assert(h2.isHuman());
  assert(h2.getPlayerColor().getColor() == 4); //check color

  Human h3("Give", 3, 30);
  assert(h3.getName() == "Give");
  assert(h3.isHuman());
  assert(h3.getPlayerColor().getColor() == 4); //check color

  Human h4("You", 2);
  assert(h4.getName() == "You");
  assert(h4.isHuman());
  assert(h4.getPlayerColor().getColor() == 36); //check color

  Human h5("Up");
  assert(h5.getName() == "Up");
  assert(h5.isHuman());
  assert(h5.getPlayerColor().getColor() == 36); //check color

  //make cards
  Card c0(0);
  Card c1(1);
  Card c2(2);
  Card c3(3);
  Card c5(5);
  Card c6(6);
  Card c10(10);
  Card c13(13);

  //create decks
  Deck d1(12);
  Deck d2(10);
  Deck d3(8);
  Deck d4(6);
  Deck d5(14);
  
  //check id moves moves cards to correctly
  assert(h1.move(c1,d1));
  assert(!h1.move(c0,d1));
  assert(h1.move(c2,d1));
  assert(!h1.move(c1,d1));
  assert(h1.move(c3,d1));
  assert(!h1.move(c1,d1));
  assert(h1.move(c13,d1));
  assert(!h1.move(c3,d1));
  assert(h1.move(c5,d1));
  assert(!h1.move(c5,d1));
  assert(h1.move(c6,d1));
  
  //h2 test
  assert(h2.move(c1,d2));
  assert(!h2.move(c0,d2));
  assert(h2.move(c2,d2));
  assert(!h2.move(c1,d2));
  assert(h2.move(c3,d2));
  assert(!h2.move(c1,d2));
  assert(h2.move(c13,d2));
  assert(!h2.move(c3,d2));
  assert(h2.move(c5,d2));
  assert(!h2.move(c5,d2));
  assert(h2.move(c6,d2));
  
  //h3 test
  assert(h3.move(c1,d3));
  assert(!h3.move(c0,d3));
  assert(h3.move(c2,d3));
  assert(!h3.move(c1,d3));
  assert(h3.move(c3,d3));
  assert(!h3.move(c1,d3));
  assert(h3.move(c13,d3));
  assert(!h3.move(c3,d3));
  assert(h3.move(c5,d3));
  assert(!h3.move(c5,d3));
  assert(h3.move(c6,d3));
  
  //h4 test
  assert(h4.move(c1,d4));
  assert(!h4.move(c0,d4));
  assert(h4.move(c2,d4));
  assert(!h4.move(c1,d4));
  assert(h4.move(c3,d4));
  assert(!h4.move(c1,d4));
  assert(h4.move(c13,d4));
  assert(!h4.move(c3,d4));
  assert(h4.move(c5,d4));
  assert(!h4.move(c5,d4));
  assert(h4.move(c6,d4));
  
  //h5 test
  assert(h5.move(c1,d5));
  assert(!h5.move(c0,d5));
  assert(h5.move(c2,d5));
  assert(!h5.move(c1,d5));
  assert(h5.move(c3,d5));
  assert(!h5.move(c1,d5));
  assert(h5.move(c13,d5));
  assert(!h5.move(c3,d5));
  assert(h5.move(c5,d5));
  assert(!h5.move(c5,d5));
  assert(h5.move(c6,d5));

  //testing computer players, with appropriate attributes
  //first computer
  Computer co1("Never", 2, 10);
  assert(co1.getName() == "Never");
  assert(!co1.isHuman()); //can't be human
  assert(co1.getPlayerColor().getColor() == 32); //test if correct color

  Computer co2("Gonna", 3, 20);
  assert(co2.getName() == "Gonna");
  assert(!co2.isHuman());
  assert(co2.getPlayerColor().getColor() == 34);

  Computer co3("Let", 4, 15);
  assert(co3.getName() == "Let");
  assert(!co3.isHuman());
  assert(co3.getPlayerColor().getColor() == 95);

  Computer co4("You", 5, 30);
  assert(co4.getName() == "You");
  assert(!co4.isHuman());
  assert(co4.getPlayerColor().getColor() == 97);

  Computer co5("Down", 1, 5);
  assert(co5.getName() == "Down");
  assert(!co5.isHuman());
  assert(co5.getPlayerColor().getColor() == 31);
  
}//end player test for humans and computers

//masterpile test
void masterPileTest() {
  MasterPile mp1;
  MasterPile mp2;
  
  //test sizes
  assert(mp1.getSize() == 0);
  assert(mp2.getSize() == 0);
  assert(mp1.getCapacity() == 162);
  assert(mp2.getCapacity() == 162);
  
  //creates a whole deck with all cards
  mp2.create();

  //test size of mp1 and mp2
  assert(mp1.getSize() == 0);
  assert(mp2.getSize() == 162);
  assert(mp1.getCapacity() == 162);
  assert(mp2.getCapacity() == 162);
  
  //create cards 1 -12 and SkipBo Card
  Card one(1);
  Card two(2);
  Card three(3);
  Card four(4);
  Card five(5);
  Card six(6);
  Card seven(7);
  Card eight(8);
  Card nine(9);
  Card ten(10);
  Card eleven(11);
  Card twelve(12);
  Card thirteen(13);
  
  //creates mp1 similar to how .create() creates mp2
  for(int i = 0; i<12; i++){
    assert(mp1.add(one));
    assert(mp1.add(two));
    assert(mp1.add(three));
    assert(mp1.add(four));
    assert(mp1.add(five));
    assert(mp1.add(six));
    assert(mp1.add(seven));
    assert(mp1.add(eight));
    assert(mp1.add(nine));
    assert(mp1.add(ten));
    assert(mp1.add(eleven));
    assert(mp1.add(twelve));
    assert(mp1.add(thirteen));
  }
  
  for(int i = 0; i<6; i++){
    assert(mp1.add(thirteen));
  }

  //test size and capacity of mp1 and mp2
  assert(mp1.getSize() == 162);
  assert(mp2.getSize() == 162);
  assert(mp1.getCapacity() == 162);
  assert(mp2.getCapacity() == 162);

  //create mp3 of size 13
  MasterPile mp3(13);

  //test size and capacity of mp3
  assert(mp3.getSize() == 0);
  assert(mp3.getCapacity() == 13);

  //add one copy of each card into mp3
  assert(mp3.add(one));
  assert(mp3.add(two));
  assert(mp3.add(three));
  assert(mp3.add(four));
  assert(mp3.add(five));
  assert(mp3.add(six));
  assert(mp3.add(seven));
  assert(mp3.add(eight));
  assert(mp3.add(nine));
  assert(mp3.add(ten));
  assert(mp3.add(eleven));
  assert(mp3.add(twelve));
  assert(mp3.add(thirteen));

  //test size and capacity of mp3
  assert(mp3.getSize() == 13);
  assert(mp3.getCapacity() == 13);
  
  //copies mp3 into mp4
  MasterPile mp4 = mp3;

  //test size of mp4
  assert(mp4.getSize() == 13);
  assert(mp4.getCapacity() == 13);

  //tests values inside the mp3 deck
  for(int i = 13, j = 0; i>0 && j<13; i--, j++) {
    assert(mp3.getCard(j).getValue() == i);
  }

  //removes all the cards from mp3
  for(int i = 13; i>0; i--) {
    assert(mp3.draw(1).getValue() == i);
  }

  //tests the size and capacity of mp3
  assert(mp3.getSize() == 0);
  assert(mp3.getCapacity() == 13);

  //tests the size and capacity of mp4
  assert(mp4.getSize() == 13);
  assert(mp4.getCapacity() == 13);

  //removes all cards from mp4
  mp4.clear();

  //tests size and capacity
  assert(mp3.getSize() == 0);
  assert(mp3.getCapacity() == 13);

  //removes all cards from mp1 and tests size and capacity
  mp1.clear();
  assert(mp1.getSize() == 0);
  assert(mp1.getCapacity() == 162);

  //removes all cards from mp2 and tests size and capacity
  mp2.clear();
  assert(mp2.getSize() == 0);
  assert(mp2.getCapacity() == 162);
}

//tests creation of board
void boardTest() {
  //board has 20 stock pile cards, 6 players, and  0 humans players
  Board b1(20, 6, 0);
  
  //checks all players have 5 cards and no humans players
  for (int i=0; i<6; i++) {
    assert(!b1.getPlayerIsHuman());
    assert(b1.getPlayerHandSize() == 5);
    assert(b1.isGameNotFinished());
    b1.rotate();
  }

  //plays complete game
  while (b1.isGameNotFinished()) {
    b1.computerDoMove();
    assert(b1.getPlayerHandSize() <= 5);
    assert(!b1.getPlayerIsHuman());
  }

  //checks game is finished
  assert(!b1.isGameNotFinished());

  //creates another board with 5 stock pile cards, 2 players, and 2 human players
  Board b2(5, 2, 2);

  //checks all players are human
  for (int i=0; i<2; i++) {
    assert(b2.getPlayerIsHuman());
    assert(b2.getPlayerHandSize() == 5);
    assert(b2.isGameNotFinished());
    b2.rotate();
  }  
}

//tests a difficult situation for computerAI
void AITest(){

  ComputerAI computer("Achintya", 1, 26);
  Hand& handTemp = computer.getHand();
  StockPile& stockTemp = computer.getStock();
  DiscardPile& discardTemp0 = computer.getDiscardPile(0);
  DiscardPile& discardTemp1 = computer.getDiscardPile(1);
  DiscardPile& discardTemp2 = computer.getDiscardPile(2);
  DiscardPile& discardTemp3 = computer.getDiscardPile(3);

  Deck buildPile;
  for(int i = 1 ;i<=11; i++){
    buildPile.add(Card(i));
  }
  vector<Deck> buildPiles;
  buildPiles.push_back(buildPile);
  buildPiles.push_back(buildPile);
  buildPiles.push_back(buildPile);
  buildPiles.push_back(buildPile);

  Hand mainHand;
  mainHand.add(Card(2));
  mainHand.add(Card(2));
  mainHand.add(Card(2));
  mainHand.add(Card(2));
  mainHand.add(Card(2));
  handTemp = mainHand;

  StockPile mainStock;
  for(int i= 0; i < 25; i++){
    mainStock.add(Card(2));
  }
  mainStock.add(Card(1));
  stockTemp = mainStock;
  
  DiscardPile mainDiscard;
  mainDiscard.add(Card(5));
  DiscardPile mainDiscard2;
  mainDiscard2.add(Card(12));
  
  discardTemp0 = mainDiscard;
  discardTemp1 = mainDiscard;
  discardTemp2 = mainDiscard;
  discardTemp3 = mainDiscard2;

  StockPile oppStock;
  for(int i= 0; i < 25; i++){
    mainStock.add(Card(2));
  }
  mainStock.add(Card(13));

  computer.doMove(buildPiles, oppStock);

  assert(stockTemp.getCard().getValue() != 1);
}

void testSaveLoad(){
  std::remove("SaveFile.txt");
 
  Board board(1,2,0);
  Board board2(1,2,0);
  assert(!board.load());
  
  board.save();
  assert(board.load());
  assert(board == board2);
}

void testUndoRedo(){
  Game game;
  game.play();
  Game game2;
  game.play();
  assert(game.getBoard() == game2.getBoard());
}

int main(){
  cardTest();
  deckTest();
  playerTest();
  masterPileTest();
  boardTest();
  AITest();
  testSaveLoad();
  testUndoRedo();
}
