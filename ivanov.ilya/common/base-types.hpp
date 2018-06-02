#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace ivanov
{
struct point_t
{
  double x;
  double y;
};

struct rectangle_t
{
  point_t pos;
  double width, height;
};
}
#endif // BASE_TYPES_HPP
