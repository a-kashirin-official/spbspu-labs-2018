#include "triangle.hpp"

#include <algorithm>
#include <math.h>
#include <stdexcept>

using namespace hvetsckovich;

hvetsckovich::Triangle::Triangle(const point_t & vertexA, const point_t & vertexB, const point_t & vertexC):
  vertexA_(vertexA),
  vertexB_(vertexB),
  vertexC_(vertexC),
  angle_(0.0)
{

}

point_t hvetsckovich::Triangle::getVertex(const int index) const
{
  switch (index) {
    case 0: return vertexA_;
    case 1: return vertexB_;
    case 2: return vertexC_;
    default: throw std::invalid_argument("Index is out of bounds");
  }
}

point_t hvetsckovich::Triangle::getPos() const
{
  double x = (vertexA_.x + vertexB_.x + vertexC_.x) / 3;
  double y = (vertexA_.y + vertexB_.y + vertexC_.y) / 3;

  return { x, y };
}

double hvetsckovich::Triangle::getArea() const
{
  double aLineX = vertexB_.x - vertexA_.x;
  double aLineY = vertexB_.y - vertexA_.y;
  double aLineLength = sqrt(aLineX * aLineX + aLineY * aLineY);

  double bLineX = vertexC_.x - vertexB_.x;
  double bLineY = vertexC_.y - vertexB_.y;
  double bLineLength = sqrt(bLineX * bLineX + bLineY * bLineY);

  double cLineX = vertexC_.x - vertexA_.x;
  double cLineY = vertexC_.y - vertexA_.y;
  double cLineLength = sqrt(cLineX * cLineX + cLineY * cLineY);

  double semiPerimeter = (aLineLength + bLineLength + cLineLength)/2;

  return sqrt(semiPerimeter * (semiPerimeter - aLineLength) *
    (semiPerimeter - bLineLength) * (semiPerimeter - cLineLength));
}

rectangle_t hvetsckovich::Triangle::getFrameRect() const
{
  auto xMinMax = std::minmax({ vertexA_.x, vertexB_.x, vertexC_.x });
  double start = xMinMax.first;
  double end = xMinMax.second;

  auto yMinMax = std::minmax({ vertexA_.y, vertexB_.y, vertexC_.y });
  double bottom = yMinMax.first;
  double top = yMinMax.second;

  double width = end - start;
  double height = top - bottom;

  return { { start + (width / 2), bottom + (height / 2) }, width, height };
}

void hvetsckovich::Triangle::move(const point_t & pos)
{
  point_t currentPosition = getPos();

  vertexA_.x += pos.x - currentPosition.x;
  vertexA_.y += pos.y - currentPosition.y;
  vertexB_.x += pos.x - currentPosition.x;
  vertexB_.y += pos.y - currentPosition.y;
  vertexC_.x += pos.x - currentPosition.x;
  vertexC_.y += pos.y - currentPosition.y;
}

void hvetsckovich::Triangle::move(const double dx, const double dy)
{
  vertexA_.x += dx;
  vertexA_.y += dy;
  vertexB_.x += dx;
  vertexB_.y += dy;
  vertexC_.x += dx;
  vertexC_.y += dy;
}

void hvetsckovich::Triangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Scale factor must be > 0");
  }

  point_t pos = getPos();
  vertexA_.x = (vertexA_.x - pos.x) * factor + pos.x;
  vertexA_.y = (vertexA_.y - pos.y) * factor + pos.y;
  vertexB_.x = (vertexB_.x - pos.x) * factor + pos.x;
  vertexB_.y = (vertexB_.y - pos.y) * factor + pos.y;
  vertexC_.x = (vertexC_.x - pos.x) * factor + pos.x;
  vertexC_.y = (vertexC_.y - pos.y) * factor + pos.y;
}

void hvetsckovich::Triangle::rotate(const double degrees)
{
  angle_ += degrees;

  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }

  const double sina = sin(degrees * M_PI / 180.0); // degrees -> radians
  const double cosa = cos(degrees * M_PI / 180.0);
  const hvetsckovich::point_t center = this->getPos();

  double x = vertexA_.x;
  double y = vertexA_.y;
  vertexA_ = { (x - center.x) * cosa - (y - center.y) * sina + center.x,
     (x - center.x) * sina - (y - center.y) * cosa + center.y };
  
  x = vertexB_.x;
  y = vertexB_.y;
  vertexB_ = { (x - center.x) * cosa - (y - center.y) * sina + center.x,
     (x - center.x) * sina - (y - center.y) * cosa + center.y };

  x = vertexC_.x;
  y = vertexC_.y;
  vertexC_ = { (x - center.x) * cosa - (y - center.y) * sina + center.x,
     (x - center.x) * sina - (y - center.y) * cosa + center.y };
}
