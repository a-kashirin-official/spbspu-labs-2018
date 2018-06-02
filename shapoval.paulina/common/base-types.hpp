#ifndef BASE_TYPES_HPP_
#define BASE_TYPES_HPP_

namespace shapoval
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width;
    double height;
  };
}

#endif 
