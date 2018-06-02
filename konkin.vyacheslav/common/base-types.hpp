#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace konkin
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double height, width;
    point_t pos;
  };
}

#endif // BASE_TYPES_HPP
