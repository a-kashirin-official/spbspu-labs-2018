#include <iostream>
#include <cmath>
#include "triangle.hpp"

Triangle::Triangle(const point_t &A, const point_t &B, const point_t &C) :
  A_(A),
  B_(B),
  C_(C) {
  center_ = {(A_.x + B_.x + C_.x) / 3, (A_.y + B_.y + C_.y) / 3};
}

double Triangle::getArea() const {
  return fabs((A_.x - C_.x) * (B_.y - C_.y) - (B_.x - C_.x) * (A_.y - C_.y)) / 2.0;
}

rectangle_t Triangle::getFrameRect() const {
  double maxX = A_.x > B_.x ? (A_.x > C_.x ? A_.x : C_.x) : (B_.x > C_.x ? B_.x : C_.x);
  double minX = A_.x < B_.x ? (A_.x < C_.x ? A_.x : C_.x) : (B_.x < C_.x ? B_.x : C_.x);
  double maxY = A_.y > B_.y ? (A_.y > C_.y ? A_.y : C_.y) : (B_.y > C_.y ? B_.y : C_.y);
  double minY = A_.y < B_.y ? (A_.y < C_.y ? A_.y : C_.y) : (B_.y < C_.y ? B_.y : C_.y);
  return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
}

void Triangle::move(const point_t &pos) {
  center_ = {pos.x, pos.y};
  move(pos.x - (A_.x + B_.x + C_.x) / 3, pos.y - (A_.y + B_.y + C_.y) / 3);
}

void Triangle::move(const double Ox, const double Oy) {
  A_ = {A_.x + Ox, A_.y + Oy};
  B_ = {B_.x + Ox, B_.y + Oy};
  C_ = {C_.x + Ox, C_.y + Oy};
  center_ = {(A_.x + B_.x + C_.x) / 3, (A_.y + B_.y + C_.y) / 3};
}

void Triangle::OutData() const {
  std::cout << "Point(A) : x=" << A_.x << " y=" << A_.y << std::endl;
  std::cout << "Point(B) : x=" << B_.x << " y=" << B_.y << std::endl;
  std::cout << "Point(C) : x=" << C_.x << " y=" << C_.y << std::endl;
}

point_t Triangle::spotofcenter() const {
  return center_;
}


