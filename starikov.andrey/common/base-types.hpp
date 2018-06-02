#ifndef STARIKOV_ANDREY_LABS_BASE_TYPES_HPP
#define STARIKOV_ANDREY_LABS_BASE_TYPES_HPP

namespace starikov
{
  struct point_t
  {
    double x,y;
  };
  struct rectangle_t
  {
    double width,height;
    point_t pos;
  };
}

#endif //STARIKOV_ANDREY_LABS_BASE_TYPES_HPP
