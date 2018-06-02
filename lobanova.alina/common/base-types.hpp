#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace lobanova {
  struct point_t {
    double x, y;

    void rotate(point_t a, double p);

  };

  struct rectangle_t {
    point_t pos;
    double width, height;
  };
}
#endif //BASE_TYPES_HPP
