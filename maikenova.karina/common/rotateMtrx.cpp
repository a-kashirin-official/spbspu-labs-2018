#include "rotateMtrx.hpp"
#include <cmath>

maikenova::point_t rotateMtrx(const maikenova::point_t & center, const maikenova::point_t & point, double phi)
{
  maikenova::point_t newPoint;
  double dx, dy, radAngle;
  radAngle = (phi*M_PI) / 180.0;
  dx = point.x - center.x;
  dy = point.y - center.y;
  newPoint.x = center.x + dx*cos(radAngle) - dy*sin(radAngle);
  newPoint.y = center.y + dx*sin(radAngle) + dy*cos(radAngle);
  return newPoint;
}

