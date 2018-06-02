#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace volkov
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width; 
    double height;
  };
}

#endif
