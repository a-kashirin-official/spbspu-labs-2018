#ifndef BASETYPES_H
#define BASETYPES_H
namespace reznik
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

#endif // BASETYPES_H
