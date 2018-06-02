#ifndef HPP_BASETYPES
#define HPP_BASETYPES

namespace strashko
{
  struct point_t{
    double x;
    double y;
  };

  struct rectangle_t{
    point_t pos;
    double width;
    double height;
  };
}

#endif
