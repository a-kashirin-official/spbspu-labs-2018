//
// Created by 811432 on 05.04.2018.
//
#include <iostream>
#include "triangle.hpp"
#include <cmath>


turkin::Triangle::Triangle(const point_t &pos1, const point_t &pos2, const point_t &pos3) :
  pos1_(pos1),
  pos2_(pos2),
  pos3_(pos3)
{
  center_ = {(pos1.x + pos2.x + pos3.x) / 3, (pos1.y + pos2.y + pos3.y) / 3};
}

double turkin::Triangle::getArea() const
{
  return fabs((pos1_.x * (pos2_.y - pos3_.y) + pos2_.x * (pos3_.y - pos1_.y) + pos3_.x * (pos1_.y - pos2_.y))) * 0.5;
}

turkin::rectangle_t turkin::Triangle::getFrameRect() const
{
  double maxX = pos1_.x > pos2_.x ? (pos1_.x > pos3_.x ? pos1_.x : pos3_.x) : (pos2_.x > pos3_.x ? pos2_.x : pos3_.x);
  double minX = pos1_.x < pos2_.x ? (pos1_.x < pos3_.x ? pos1_.x : pos3_.x) : (pos2_.x < pos3_.x ? pos2_.x : pos3_.x);
  double maxY = pos1_.y > pos2_.y ? (pos1_.y > pos3_.y ? pos1_.y : pos3_.y) : (pos2_.y > pos3_.y ? pos2_.y : pos3_.y);
  double minY = pos1_.y < pos2_.y ? (pos1_.y < pos3_.y ? pos1_.y : pos3_.y) : (pos2_.y < pos3_.y ? pos2_.y : pos3_.y);
  return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
};

void turkin::Triangle::move(const point_t &pos)
{

  pos1_.x += pos.x - center_.x;
  pos2_.x += pos.x - center_.x;
  pos3_.x += pos.x - center_.x;
  pos1_.y += pos.y - center_.y;
  pos2_.y += pos.y - center_.y;
  pos3_.y += pos.y - center_.y;
  center_ = pos;
}

void turkin::Triangle::move(double Ox, double Oy)
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

void turkin::Triangle::printInfo()
{
  std::cout << "A: " << "(" << pos1_.x << ", " << pos1_.y << ")" << std::endl;
  std::cout << "B: " << "(" << pos2_.x << ", " << pos2_.y << ")" << std::endl;
  std::cout << "C: " << "(" << pos3_.x << ", " << pos3_.y << ")" << std::endl;
}

void turkin::Triangle::scale(double k)
{
  if (k < 0) {
    throw std::invalid_argument("K > 0!");
  }
  pos1_.x = center_.x + k * (pos1_.x - center_.x);
  pos2_.x = center_.x + k * (pos2_.x - center_.x);
  pos3_.x = center_.x + k * (pos3_.x - center_.x);
  pos1_.y = center_.y + k * (pos1_.y - center_.y);
  pos2_.y = center_.y + k * (pos2_.y - center_.y);
  pos3_.y = center_.y + k * (pos3_.y - center_.y);
}

void turkin::Triangle::rotate(double angle)
{
  double radians = angle * M_PI / 180;
  pos1_ = {
    center_.x + (pos1_.x - center_.x) * cos(radians) -
    (pos1_.y - center_.y) * sin(radians),
    center_.y + (pos1_.y - center_.y) * cos(radians) +
    (pos1_.x - center_.x) * sin(radians)
  };
  pos2_ = {
    center_.x + (pos2_.x - center_.x) * cos(radians) -
    (pos2_.y - center_.y) * sin(radians),
    center_.y + (pos2_.y - center_.y) * cos(radians) +
    (pos2_.x - center_.x) * sin(radians)
  };
  pos3_ = {
    center_.x + (pos3_.x - center_.x) * cos(radians) -
    (pos3_.y - center_.y) * sin(radians),
    center_.y + (pos3_.y - center_.y) * cos(radians) +
    (pos3_.x - center_.x) * sin(radians)
  };

}

turkin::point_t turkin::Triangle::getCenter() const
{
  return center_;
}




