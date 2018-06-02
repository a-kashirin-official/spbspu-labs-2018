#include "base-types.hpp"
#include <cmath>

using namespace sergeev;

void point_t::rotate(double angle)
{
  double tempX = x;
  double tempY = y;

  const double rad = angle * M_PI / 180;

  x = tempX * cos(rad) - tempY * sin(rad);
  y = tempX * sin(rad) + tempY * cos(rad);
}

bool rectangle_t::intersection(const rectangle_t & rhs)
{
  double lhsRight = pos.x + rhs.width/2;
  double lhsLeft = pos.x - rhs.width/2;
  double lhsBottom = pos.y - rhs.height/2;
  double lhsUp = pos.y + rhs.height/2;

  double rhsLeft = rhs.pos.x - rhs.width/2;
  double rhsRight = rhs.pos.x + rhs.width/2;
  double rhsUp = rhs.pos.y + rhs.height/2;
  double rhsBottom = rhs.pos.y - rhs.height/2;

  return !((lhsLeft > rhsRight) || (lhsRight < rhsLeft) || (lhsBottom > rhsUp) || (lhsUp < rhsBottom));
}
