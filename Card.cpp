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

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Card.hpp"

using std::string;

//constructs a Card based on the 0-13 value given
//if its 13 then the Card becomes a Skip Bo card
//if its 0 then the Card becomes an empty Card slot
Card::Card(int input){
  value = input;
  isSB = false;
  if(value == 13){
    isSB = true;
  }
}

//returns the string representation of a card, which is the value if it is 1-12
// and SB for a 13 and two spaces for a 0, all outputs are 2 characters wide 
string Card::toString() const{
  switch(this->getValue()){
  case 0:
    return "  ";
    break;
  case 1: 
    return "01";
    break;
  case 2: 
    return "02";
    break;
  case 3: 
    return "03";
    break;
  case 4: 
    return "04";
    break;
  case 5: 
    return "05";
    break;
  case 6: 
    return "06";
    break;
  case 7: 
    return "07";
    break;
  case 8: 
    return "08";
    break;
  case 9: 
    return "09";
    break;
  case 10: 
    return "10";
    break;
  case 11: 
    return "11";
    break;
  case 12: 
    return "12";
    break;
  case 13: 
    return "SB";
    break;
  }
  return "  ";
}

//returns the ColorModifier for the Card's assigned color
//indigo for 1-4
//white for 5-8
//pink for 9-12
//light yellow for Skip Bo
ColorModifier Card::getColor() const{
  ColorModifier indigo(INDIGO);
  ColorModifier white(WHITE);
  ColorModifier pink(PINK);
  ColorModifier yellowLt(YELLOWLT);

  switch(this->getValue()){
  case 0:
    break;
  case 1:
  case 2:
  case 3:
  case 4:
    return indigo;
    break;
  case 5:
  case 6:
  case 7:
  case 8:
    return white;
    break;
  case 9:
  case 10:
  case 11:
  case 12:
    return pink;
    break;
  case 13:
    return yellowLt;
    break;
    }
  return pink;
}

