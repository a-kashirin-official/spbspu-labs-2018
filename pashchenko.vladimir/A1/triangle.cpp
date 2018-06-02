#include <math.h>
#include "triangle.hpp"

Triangle::Triangle(const point_t fPoint, const point_t sPoint, const point_t tPoint) : 
  vertices_{ fPoint, sPoint, tPoint }
{
}

void Triangle::move(const point_t &newP)
{
  const point_t centre = getFrameRect().pos;

  for (int i = 0; i < 3; ++i)
  {
    vertices_[i].x += newP.x - centre.x;
    vertices_[i].y += newP.y - centre.y;
  }
}

void Triangle::move(const double &nX, const double &nY)
{
  for (int i = 0; i < 3; ++i)
    vertices_[i].x += nX;
  for (int i = 0; i < 3; ++i)
    vertices_[i].y += nY;
}

double Triangle::getArea() const
{
  return ((fabs(((vertices_[0].x - vertices_[2].x) * (vertices_[1].y - vertices_[2].y)) -
    ((vertices_[0].y - vertices_[2].y) * (vertices_[1].x - vertices_[2].x)))) / 2);
}

rectangle_t Triangle::getFrameRect() const
{
  double top = vertices_[0].y;
  double bottom = vertices_[0].y;
  double left = vertices_[0].x;
  double right = vertices_[0].x;

  for (int i = 1; i < 3; ++i)
  {
    if (vertices_[i].x < left)
      left = vertices_[i].x;
    if (vertices_[i].x > right)
      right = vertices_[i].x;
    if (vertices_[i].y < bottom)
      bottom = vertices_[i].y;
    if (vertices_[i].y > top)
      top = vertices_[i].y;
  }

  double centreX = 0;
  double centreY = 0;

  for (int i = 0; i < 3; ++i)
    centreX += vertices_[i].x;
  for (int i = 0; i < 3; ++i)
    centreY += vertices_[i].y;

  return { { centreX / 3, centreY / 3 }, right - left, top - bottom };
}
