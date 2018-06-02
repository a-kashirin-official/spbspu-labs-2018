#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <iostream>

using namespace tseptsov;

Polygon::Polygon(const std::initializer_list < point_t > &pts)
{
  if (pts.size() < 3) {
    throw std::range_error("Vertices should be 3 or more");
  }
  count_ = pts.size();

  std::unique_ptr < point_t[] > temp(new point_t[count_]);
  int i = 0;

  for (std::initializer_list < point_t >::const_iterator point = pts.begin(); point != pts.end(); point++) {
    temp[i] = *point;
    i++;
  }
  pts_.swap(temp);
  if (!convexity()) {
    throw std::invalid_argument("Polygon is unconvex");
  }
  if (getArea() == 0) {
    throw std::invalid_argument("Polygon area should be > 0");
  }
}

point_t Polygon::operator[](std::size_t numb) const
{
  if (numb > count_) {
    throw std::out_of_range("Point does not exist");
  }

  return pts_[numb];
}

void Polygon::move(double Ox, double Oy)
{
  for (std::size_t i = 0; i < count_; i++) {
    pts_[i].x += Ox;
    pts_[i].y += Oy;
  }
}

void Polygon::move(const point_t &pos)
{
  point_t pos_ = getCenter();
  double Ox = pos.x - pos_.x;
  double Oy = pos.y - pos_.y;

  move(Ox, Oy);
}

void Polygon::scale(double coef)
{
  if (coef <= 0) {
    throw std::invalid_argument("Coefficient should be > 0");
  }
  point_t pos_ = getCenter();
  double Ox = 0;
  double Oy = 0;

  for (std::size_t i = 0; i < count_; ++i) {
    Ox = (pts_[i].x - pos_.x) * coef;
    Oy = (pts_[i].y - pos_.y) * coef;
    pts_[i].x = pos_.x + Ox;
    pts_[i].y = pos_.y + Oy;
  }
}

void Polygon::rotate(double deg)
{
  point_t temp_point = {0, 0};
  point_t pos_ = getCenter();

  deg = deg * M_PI / 180.0;
  for (std::size_t i = 0; i < count_; i++) {
    temp_point.x = pts_[i].x - pos_.x;
    temp_point.y = pts_[i].y - pos_.y;

    pts_[i].x = temp_point.x * cos(deg) - temp_point.y * sin(deg) + pos_.x;
    pts_[i].y = temp_point.y * cos(deg) + temp_point.x * sin(deg) + pos_.y;
  }
}

void Polygon::OutData() const
{
  std::cout << "Polygon. Coords: " << std::ends;
  for (std::size_t i = 0; i < count_; i++) {
    std::cout << "(" << pts_[i].x << ", " << pts_[i].y << ") " << std::ends;
  }
  std::cout << std::endl << "Centre: (" << getCenter().x << ", " << getCenter().y << ")" << std::endl;
}

double Polygon::getArea() const
{
  double area = 0;
  for (std::size_t i = 0; i < count_ - 1; i++) {
    area += pts_[i].x * pts_[i + 1].y - pts_[i].y * pts_[i + 1].x;
  }
  area += pts_[count_ - 1].x * pts_[0].y - pts_[count_ - 1].y * pts_[0].x;

  return fabs(area) / 2.0;
}

rectangle_t Polygon::getFrameRect() const
{
  double min_x = pts_[0].x;
  double max_x = pts_[0].x;
  double min_y = pts_[0].y;
  double max_y = pts_[0].y;
  rectangle_t frame = {0, 0, {0, 0}};

  for (std::size_t i = 1; i < count_; i++) {
    min_x = std::min(min_x, pts_[i].x);
    min_y = std::min(min_y, pts_[i].y);
    max_x = std::max(max_x, pts_[i].x);
    max_y = std::max(max_y, pts_[i].y);
  }
  frame.pos.x = min_x + (max_x - min_x) / 2.0;
  frame.pos.y = min_y + (max_y - min_y) / 2.0;
  frame.width = max_x - min_x;
  frame.height = max_y - min_y;

  return frame;
}

point_t Polygon::getCenter() const
{
  point_t pos = {0, 0};

  for (std::size_t i = 0; i < count_; i++) {
    pos.x += pts_[i].x;
    pos.y += pts_[i].y;
  }
  pos.x /= count_;
  pos.y /= count_;

  return pos;
}

bool Polygon::convexity() const
{
  double pair_1 = (pts_[0].x - pts_[count_ - 1].x) * (pts_[1].y - pts_[0].y)
                  - (pts_[1].x - pts_[0].x) * (pts_[0].y - pts_[count_ - 1].y);
  double pair_2 = 0;

  for (std::size_t i = 0; i < count_ - 2; i++) {
    pair_2 = (pts_[i + 1].x - pts_[i].x) * (pts_[i + 2].y - pts_[i + 1].y)
             - (pts_[i + 2].x - pts_[i + 1].x) * (pts_[i + 1].y - pts_[i].y);

    if (pair_1 * pair_2 >= 0) {
      pair_1 = pair_2;
    } else {
      return false;
    }
  }
  pair_2 = (pts_[count_ - 1].x - pts_[count_ - 2].x) * (pts_[0].y - pts_[count_ - 1].y)
           - (pts_[0].x - pts_[count_ - 1].x) * (pts_[count_ - 1].y - pts_[count_ - 2].y);

  return (pair_1 * pair_2 >= 0);
}


