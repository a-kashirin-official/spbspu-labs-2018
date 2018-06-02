#include "triangle.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

zhigalin::Triangle::Triangle(const point_t & point_a, const point_t & point_b, const point_t & point_c):
  Shape({(point_a.x + point_b.x + point_c.x) / 3.0, (point_a.y + point_b.y + point_c.y) / 3.0})
{
  double ab = sqrt(pow(point_b.x - point_a.x, 2.0) + pow(point_b.y - point_a.y, 2.0));
  double bc = sqrt(pow(point_c.x - point_b.x, 2.0) + pow(point_c.y - point_b.y, 2.0));
  double ac = sqrt(pow(point_c.x - point_a.x, 2.0) + pow(point_c.y - point_a.y, 2.0));

  if (ab + bc <= ac)
  {
    throw std::invalid_argument("Invalid point's of triangle! ab + bc <= ac");
  }
  else if (ab + ac <= bc)
  {
    throw std::invalid_argument("Invalid point's of triangle! ab + ac <= bc");
  }
  else if (ac + bc <= ab)
  {
    throw std::invalid_argument("Invalid point's of triangle! ac + bc <= ab");
  }
  point_a_ = point_a;
  point_b_ = point_b;
  point_c_ = point_c;
};

double zhigalin::Triangle::getArea() const
{
  return abs(0.5 * ((point_a_.x - point_c_.x) * (point_b_.y - point_c_.y) 
                   - (point_b_.x - point_c_.x) * (point_a_.y - point_c_.y)));
};

zhigalin::rectangle_t zhigalin::Triangle::getFrameRect() const
{
  double width = std::max(std::max(point_a_.x, point_b_.x), point_c_.x) 
                 - std::min(std::min(point_a_.x, point_b_.x), point_c_.x);
  double height = std::max(std::max(point_a_.y, point_b_.y), point_c_.y) 
                  - std::min(std::min(point_a_.y, point_b_.y), point_c_.y);
  double plusToX = width / 2.0 - (pos_.x - std::min(std::min(point_a_.x, point_b_.x), point_c_.x));
  double plusToY = height / 2.0 - (pos_.y - std::min(std::min(point_a_.y, point_b_.y), point_c_.y));
  return rectangle_t{width, height, {pos_.x + plusToX, pos_.y + plusToY}};
};

void zhigalin::Triangle::move(const point_t & pos)
{
  point_a_.x -= pos_.x - pos.x;
  point_a_.y -= pos_.y - pos.y;
  point_b_.x -= pos_.x - pos.x;
  point_b_.y -= pos_.y - pos.y;
  point_c_.x -= pos_.x - pos.x;
  point_c_.y -= pos_.y - pos.y;
  pos_ = pos;
};

void zhigalin::Triangle::move(const double dx, const double dy)
{
  point_a_.x += dx;
  point_a_.y += dy;
  point_b_.x += dx;
  point_b_.y += dy;
  point_c_.x += dx;
  point_c_.y += dy;
  pos_.x += dx;
  pos_.y += dy;
};

void zhigalin::Triangle::scale(const double coeff)
{
  if (coeff <= 0.0)
  {
    throw std::invalid_argument("Scale coefficient must be positive!");
  }
  (point_a_.x < pos_.x) ? point_a_.x = pos_.x - coeff * abs(pos_.x - point_a_.x): 
                          point_a_.x = pos_.x + coeff * abs(pos_.x - point_a_.x);
  (point_a_.y < pos_.y) ? point_a_.y = pos_.y - coeff * abs(pos_.y - point_a_.y):
                          point_a_.y = pos_.y + coeff * abs(pos_.y - point_a_.y);
  (point_b_.x < pos_.x) ? point_b_.x = pos_.x - coeff * abs(pos_.x - point_b_.x): 
                          point_b_.x = pos_.x + coeff * abs(pos_.x - point_b_.x);
  (point_b_.y < pos_.y) ? point_b_.y = pos_.y - coeff * abs(pos_.y - point_b_.y):
                          point_b_.y = pos_.y + coeff * abs(pos_.y - point_b_.y);
  (point_c_.x < pos_.x) ? point_c_.x = pos_.x - coeff * abs(pos_.x - point_c_.x): 
                          point_c_.x = pos_.x + coeff * abs(pos_.x - point_c_.x);
  (point_c_.y < pos_.y) ? point_c_.y = pos_.y - coeff * abs(pos_.y - point_c_.y):
                          point_c_.y = pos_.y + coeff * abs(pos_.y - point_c_.y);
};
