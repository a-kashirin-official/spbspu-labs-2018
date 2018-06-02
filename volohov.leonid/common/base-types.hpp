#ifndef BASE_TYPES_HPP_
#define BASE_TYPES_HPP_

namespace volohov
{
  struct point_t
  {
    double x,y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width, height;
  };
}
#endif //BASE_TYPES_HPP_
