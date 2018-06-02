//
// Created by russk on 13.03.2018.
//

#ifndef A1_BASE_TYPES_HPP
#define A1_BASE_TYPES_HPP

namespace russkov
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
}

#endif //A1_BASE_TYPES_HPP
