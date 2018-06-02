#ifndef BASE_HPP
#define BASE_HPP

namespace mordvintseva 
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
} //mordvintseva

#endif //BASE_HPP
