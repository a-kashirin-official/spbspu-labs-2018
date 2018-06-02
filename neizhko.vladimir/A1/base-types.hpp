//  This file contains definitions of point and rectangle structures
#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
//  A point on the flatness
struct point_t
{
  double x;

  double y;
};
//  A rectangle on the flatness
struct rectangle_t
{
  double width;

  double height;
  //  Center point of rectangle
  point_t pos;
};

#endif
