#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace gremiachenskii
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    point_t pos;
    double height, width;
  };
}

#endif // BASE_TYPES_HPP
