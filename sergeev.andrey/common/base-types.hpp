#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace sergeev
{
  struct point_t
  {
    double x, y;
    void rotate(double angle);
  };

  struct rectangle_t
  {
    point_t pos;
    double width, height;
    bool intersection(const rectangle_t & rhs);
  };
}

#endif // BASE_TYPES_HPP
