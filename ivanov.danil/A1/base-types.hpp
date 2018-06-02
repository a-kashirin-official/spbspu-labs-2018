#ifndef WORK_BASE_TYPES_HPP
#define WORK_BASE_TYPES_HPP

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
#endif
