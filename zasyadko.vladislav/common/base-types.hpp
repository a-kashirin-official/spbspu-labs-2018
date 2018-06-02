#ifndef BASETYPES_HEADER
#define BASETYPES_HEADER

namespace zasyadko
{
struct point_t
{
  double x, y;
};

struct rectangle_t
{
  point_t pos;
  double height, width;
};
}

#endif
