#include "shape.hpp"
#include <iostream>

std::ostream & operator<<(std::ostream & out, const Shape & shape)
{
  shape.print(out);
  return out;
}
