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
#ifndef _COLOR_MODIFIER
#define _COLOR_MODIFIER

#include <ostream>

//makes the name of a color equal to its number value in the console
enum Color {
  RED      = 31,
  GREEN    = 32,
  YELLOW   = 33,
  BLUE     = 34,
  CYAN     = 36,
  BOLD     = 1,
  UNDERLINE= 4,
  INVERT   = 7,
  BGBLACK  = 40,
  PINK     = 95, //9-12
  YELLOWLT = 93, //SB
  INDIGO   = 94, //1-4
  WHITE    = 97, //5-8
  DEFAULT  = 0
};

//Contains a color that is used to change the output color in the terminal for
//different players/cards
class ColorModifier {
  Color color; //a color

public:
  //constructor that creates a ColorModifier out of a color
  ColorModifier(Color pColor) : color(pColor) {}
  
  //returns the number value of the ColorModifier
  Color getColor()const{ return color; };

};

std::ostream& operator<<(std::ostream& , const ColorModifier&);

#endif
