#ifndef BASETYPES_HPP
#define BASETYPES_HPP

namespace sorvenkov
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
}
#endif 
