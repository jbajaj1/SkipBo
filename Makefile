CC=g++
CXX= g++
CXXFLAGS = -ansi -pedantic -std=c++11 -Wall -Wextra -O -g

SkipBo:  SkipBo.o Game.o ComputerAI.o Board.o Player.o Human.o Computer.o Hand.o MasterPile.o DiscardPile.o StockPile.o Deck.o Card.o Color.o

SkipBo.o: SkipBo.cpp Game.o Board.o ComputerAI.o Player.o Human.o Computer.o Deck.o Hand.o MasterPile.o DiscardPile.o StockPile.o Card.o

Game.o: Game.cpp  Board.o Player.o DiscardPile.o StockPile.o Hand.o Deck.o Card.o MasterPile.o Color.o ComputerAI.o

Board.o: Board.cpp Player.o DiscardPile.o StockPile.o Hand.o Deck.o Card.o MasterPile.o Color.o ComputerAI.o

Computer.o: Computer.cpp Player.o DiscardPile.o StockPile.o Hand.o Deck.o Card.o

ComputerAI.o: ComputerAI.cpp Player.o DiscardPile.o StockPile.o Hand.o Deck.o Card.o


Human.o: Human.cpp Player.o DiscardPile.o StockPile.o Hand.o Deck.o Card.o

Player.o: Player.cpp DiscardPile.o StockPile.o Hand.o Deck.o Card.o

DiscardPile.o: DiscardPile.cpp Deck.o Card.o

StockPile.o: StockPile.cpp Deck.o Card.o

MasterPile.o: MasterPile.cpp Deck.o Card.o

Hand.o: Hand.cpp Deck.o Card.o

Deck.o: Deck.cpp Card.o

Card.o: Card.cpp Color.o

Color.o: Color.cpp

play:
	make
	./SkipBo

test: mainTest.cpp Game.cpp Board.cpp Player.cpp Human.cpp Computer.cpp Hand.cpp MasterPile.cpp DiscardPile.cpp StockPile.cpp Deck.cpp Card.cpp Color.cpp ComputerAI.cpp
	$(CC) $(CXXFLAGS) mainTest.cpp Game.cpp Board.cpp Player.cpp Human.cpp Computer.cpp Hand.cpp MasterPile.cpp DiscardPile.cpp StockPile.cpp Deck.cpp Card.cpp Color.cpp ComputerAI.cpp -o mainTest
	echo "Running tests..."
	./mainTest < mainTest.txt > mainTestOutput.txt
	echo "All tests passed! :)"

clean:
	rm -f a.out *~ *.o *.gcov *.gcda *.gcno gmon.out mainTest SkipBo  test
