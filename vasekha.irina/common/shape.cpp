#include "shape.hpp"
#include <iostream>

namespace vasekha
{
  std::ostream & operator<< (std::ostream & out, const Shape & shape) noexcept
  {
    shape.print(out);
    return out;
  }
}
