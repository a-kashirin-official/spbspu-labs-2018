#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

// Point structure
struct point_t
{
  // X coordinate
  double x;
  // Y coordinate
  double y;
};

// Rectangle structure
struct rectangle_t
{
  // Position of the center
  point_t pos;
  // Width
  double width;
  // Height
  double height;
};

#endif //BASE_TYPES_HPP

