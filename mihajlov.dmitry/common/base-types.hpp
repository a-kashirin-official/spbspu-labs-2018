#ifndef A1_BASE_TYPES_HPP
#define A1_BASE_TYPES_HPP

namespace mihajlov
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    point_t pos;
    double height;
    double width;
  };
}

#endif //A1_BASE_TYPES_HPP
