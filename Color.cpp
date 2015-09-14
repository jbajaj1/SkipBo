#include "Color.hpp"

using std::ostream;

//makes the output have the correct formatiing so the color of the text is changed
ostream& operator<<(ostream& os, const ColorModifier& mod) {
  return os << "\033[" << mod.getColor() << "m";
}
