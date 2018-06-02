#include "triangle.hpp"

#include <algorithm>
#include <cmath>

Triangle::Triangle(const point_t & vertexA, const point_t & vertexB, const point_t & vertexC):
  vertexA_(vertexA),
  vertexB_(vertexB),
  vertexC_(vertexC)
{ }

double Triangle::getArea() const
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

rectangle_t Triangle::getFrameRect() const
{
  auto byX = std::minmax({ vertexA_.x, vertexB_.x, vertexC_.x });
  double start = byX.first;
  double end = byX.second;

  auto byY = std::minmax({ vertexA_.y, vertexB_.y, vertexC_.y });
  double bottom = byY.first;
  double top = byY.second;

  double width = end - start;
  double height = top - bottom;
  point_t pos = { start + (width / 2), bottom + (height / 2) };

  return { pos, width, height };
}

void Triangle::move(const point_t & pos)
{
  double x = (vertexA_.x + vertexB_.x + vertexC_.x) / 3;
  double y = (vertexA_.y + vertexB_.y + vertexC_.y) / 3;
  point_t currentPosition = { x, y };

  vertexA_.x += pos.x - currentPosition.x;
  vertexA_.y += pos.y - currentPosition.y;

  vertexB_.x += pos.x - currentPosition.x;
  vertexB_.y += pos.y - currentPosition.y;

  vertexC_.x += pos.x - currentPosition.x;
  vertexC_.y += pos.y - currentPosition.y;
}

void Triangle::move(const double dx, const double dy)
{
  vertexA_.x += dx;
  vertexA_.y += dy;

  vertexB_.x += dx;
  vertexB_.y += dy;

  vertexC_.x += dx;
  vertexC_.y += dy;
}
