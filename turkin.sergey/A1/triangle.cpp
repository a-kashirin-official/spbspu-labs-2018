//
// Created by 811432 on 05.04.2018.
//
#include "triangle.hpp"
#include <iostream>
#include <cmath>


Triangle::Triangle(const point_t &pos1, const point_t &pos2, const point_t &pos3) :
  pos1_(pos1),
  pos2_(pos2),
  pos3_(pos3)
{
  center_ = {(pos1.x + pos2.x + pos3.x) / 3, (pos1.y + pos2.y + pos3.y) / 3};
}

double Triangle::getArea() const
{
  return fabs((pos1_.x * (pos2_.y - pos3_.y) + pos2_.x * (pos3_.y - pos1_.y) + pos3_.x * (pos1_.y - pos2_.y))) * 0.5;
}

rectangle_t Triangle::getFrameRect() const
{
  double maxX = pos1_.x > pos2_.x ? (pos1_.x > pos3_.x ? pos1_.x : pos3_.x) : (pos2_.x > pos3_.x ? pos2_.x : pos3_.x);
  double minX = pos1_.x < pos2_.x ? (pos1_.x < pos3_.x ? pos1_.x : pos3_.x) : (pos2_.x < pos3_.x ? pos2_.x : pos3_.x);
  double maxY = pos1_.y > pos2_.y ? (pos1_.y > pos3_.y ? pos1_.y : pos3_.y) : (pos2_.y > pos3_.y ? pos2_.y : pos3_.y);
  double minY = pos1_.y < pos2_.y ? (pos1_.y < pos3_.y ? pos1_.y : pos3_.y) : (pos2_.y < pos3_.y ? pos2_.y : pos3_.y);
  return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
};

void Triangle::move(const point_t &pos)
{

  pos1_.x += pos.x - center_.x;
  pos2_.x += pos.x - center_.x;
  pos3_.x += pos.x - center_.x;
  pos1_.y += pos.y - center_.y;
  pos2_.y += pos.y - center_.y;
  pos3_.y += pos.y - center_.y;
  center_ = pos;
}

void Triangle::move(double Ox, double Oy)
{
  pos1_.x += Ox;
  pos2_.x += Ox;
  pos3_.x += Ox;
  pos1_.y += Oy;
  pos2_.y += Oy;
  pos3_.y += Oy;
  center_.x += Ox;
  center_.y += Oy;
}

void Triangle::printInfo()
{
  std::cout << "TRIANGLE:" << std::endl;
  std::cout << "A: " << "(" << pos1_.x << ", " << pos1_.y << ")" << std::endl;
  std::cout << "B: " << "(" << pos2_.x << ", " << pos2_.y << ")" << std::endl;
  std::cout << "C: " << "(" << pos3_.x << ", " << pos3_.y << ")" << std::endl;
}
