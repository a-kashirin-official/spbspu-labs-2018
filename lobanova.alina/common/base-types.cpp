#include "base-types.hpp"
#include <cmath>

using namespace lobanova;

void point_t::rotate(const point_t a, double p)
{
  double xx = x;
  x = std::cos(p / 180 * M_PI) * (x - a.x) - std::sin(p / 180 * M_PI) * (y - a.y) + a.x;
  y = std::sin((p / 180 * M_PI)) * (xx - a.x) + std::cos((p / 180 * M_PI)) * (y - a.y) + a.y;
}
