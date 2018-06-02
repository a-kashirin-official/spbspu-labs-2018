#ifndef BASETYPES_HPP
#define BASETYPES_HPP

namespace kostylev
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
