#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace kulikov
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
