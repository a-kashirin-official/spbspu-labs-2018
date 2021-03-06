#ifndef BASE_TYPES_HPP_INCLUDED
#define BASE_TYPES_HPP_INCLUDED

namespace turgunov
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width, height;
  };
}

#endif
