#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

//Point structure 
struct point_t
{
  //Coordinates of the point
  double x, y;
};

//Rectangle structure
struct rectangle_t
{
  //Coordinates of center 
  point_t pos;

  //Rectangle's width and height
  double width, height;
};

#endif 
