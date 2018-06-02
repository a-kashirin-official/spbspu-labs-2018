#include <iostream>
#include <cmath>
#include "triangle.hpp"
#include <iomanip>

Triangle::Triangle(const point_t &A, const point_t &B, const point_t &C) :
  A_(A),
  B_(B),
  C_(C)
{
  A_ = A;
  B_ = B;
  C_ = C;
  center_ = {(A_.x + B_.x + C_.x) / 3, (A_.y + B_.y + C_.y) / 3};
}

double Triangle::getArea() const
{
  double s = (0.5) * (A_.x * (B_.y - C_.y) + B_.x * (C_.y - A_.y) + C_.x * (A_.y - B_.y));
  if (s < 0) {
    s *= -1;
  }
  return s;
}

rectangle_t Triangle::getFrameRect() const
{
  double maxX = A_.x > B_.x ? (A_.x > C_.x ? A_.x : C_.x) : (B_.x > C_.x ? B_.x : C_.x);
  double minX = A_.x < B_.x ? (A_.x < C_.x ? A_.x : C_.x) : (B_.x < C_.x ? B_.x : C_.x);
  double maxY = A_.y > B_.y ? (A_.y > C_.y ? A_.y : C_.y) : (B_.y > C_.y ? B_.y : C_.y);
  double minY = A_.y < B_.y ? (A_.y < C_.y ? A_.y : C_.y) : (B_.y < C_.y ? B_.y : C_.y);
  return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
}

void Triangle::move(const point_t &poss)
{
  move(poss.x - (A_.x + B_.x + C_.x) / 3, poss.y - (A_.y + B_.y + C_.y) / 3);
  center_ = poss;
}

void Triangle::move(double Ox, double Oy)
{
  A_ = {A_.x + Ox, A_.y + Oy};
  B_ = {B_.x + Ox, B_.y + Oy};
  C_ = {C_.x + Ox, C_.y + Oy};
  center_.x += Ox;
  center_.y += Oy;
}

void Triangle::OutInf() const
{
  std::cout << "A( " << std::setprecision(2) << A_.x << " ; " << A_.y << " )" << std::endl;
  std::cout << "B( " << std::setprecision(2) << B_.x << " ; " << B_.y << " )" << std::endl;
  std::cout << "C( " << std::setprecision(2) << C_.x << " ; " << C_.y << " )" << std::endl;
  std::cout << "Center( " << std::setprecision(2) << center_.x << " ; " << center_.y << " )" << std::endl;
  std::cout << "Width:  " << std::setprecision(2) << getFrameRect().width << std::endl;
  std::cout << "Height: " << std::setprecision(2) << getFrameRect().height << std::endl;
  std::cout << "Area:   " << std::setprecision(2) << getArea() << std::endl;
  std::cout << "_____________________ " << std::endl;
}





