#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace vlasov
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

#endif //VLASOV_DMITRY_LABS_BASE_TYPES_HPP
