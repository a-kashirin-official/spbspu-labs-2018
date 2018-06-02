#ifndef A2_BASE_TYPES_HPP
#define A2_BASE_TYPES_HPP

namespace khmyrov
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
}

#endif //A2_BASE_TYPES_HPP
