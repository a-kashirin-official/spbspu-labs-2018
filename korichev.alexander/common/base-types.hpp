#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace korichev
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t {
    bool cross( const rectangle_t & rect);
    double width, height;
    point_t pos;
  };
}

#endif
