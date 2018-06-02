#include <initializer_list>
#include <cmath>
#include <iomanip>
#include <iostream>
#include "polygon.hpp"

golyshev::Polygon::Polygon(const std::initializer_list<point_t> &list) :
  size_(list.size())
{
  int i = 0;
  points_ = boost::shared_array<point_t>(new point_t[size_]);
  for (std::initializer_list<point_t>::const_iterator itr = list.begin(); itr != list.end(); itr++) {
    points_[i++] = const_cast<point_t &>(*itr);
  }

  if (size_ < 3) {
    throw std::invalid_argument("The polygon must contain at least 3 points!");
  }

  if (getArea() == 0) {
    throw std::invalid_argument("The area of a polygon is equal to zero!");
  }

  if (!Convex()) {
    throw std::invalid_argument("The polygon is not convex");
  }

}

golyshev::point_t golyshev::Polygon::operator[](size_t index) const
{
  if (index >= size_) {
    throw std::invalid_argument("No item with this number!");
  }
  return points_[index];
}

double golyshev::Polygon::getArea() const
{
  double sum_area = 0;
  for (size_t i = 0; i < size_ - 1; i++) {
    sum_area += (points_[i].x + points_[i + 1].x) * (points_[i].y - points_[i + 1].y);
  }
  sum_area += (points_[size_ - 1].x + points_[0].x) * (points_[size_ - 1].y - points_[0].y);
  return abs(sum_area) / 2;
}

golyshev::rectangle_t golyshev::Polygon::getFrameRect() const
{
  double min_x = points_[0].x;
  double max_x = points_[0].x;
  double min_y = points_[0].y;
  double max_y = points_[0].y;
  for (size_t i = 1; i < size_; i++) {
    if (points_[i].x < min_x) {
      min_x = points_[i].x;
    }

    if (points_[i].x > max_x) {
      max_x = points_[i].x;
    }

    if (points_[i].y < min_y) {
      min_y = points_[i].y;
    }

    if (points_[i].x > max_y) {
      max_y = points_[i].y;
    }
  }
  double width = max_x - min_x;
  double height = max_y - min_y;
  point_t p = {max_x - (max_x - min_x) / 2, max_y - (max_y - min_y) / 2};
  return {width, height, p};

}

void golyshev::Polygon::move(double Ox, double Oy)
{
  for (size_t i = 0; i < size_; i++) {
    points_[i].x += Ox;
    points_[i].y += Oy;
  }
}

void golyshev::Polygon::move(const golyshev::point_t &point)
{
  point_t OldCenter = getCentre();
  move(point.x - OldCenter.x, point.y - OldCenter.y);
}

void golyshev::Polygon::scale(double coeff)
{
  if (coeff < 0) {
    throw std::invalid_argument("Scale coefficient of the circle must be > 0!");
  }
  point_t centre = getCentre();
  for (size_t i = 0; i < size_; ++i) {
    points_[i] = {centre.x + (points_[i].x - centre.x) * coeff,
                  centre.y + (points_[i].y - centre.y) * coeff};
  }

}

void golyshev::Polygon::rotate(const double angle)
{
  point_t center_ = getCentre();
  for (size_t i = 0; i < 4; i++) {
    points_[i] = {center_.x + (points_[i].x - center_.x) * cos((angle * M_PI) / 180) -
                  (points_[i].y - center_.y) * sin((angle * M_PI) / 180),
                  center_.y + (points_[i].y - center_.y) * cos((angle * M_PI) / 180) +
                  (points_[i].x - center_.x) * sin((angle * M_PI) / 180)};
  }
}

void golyshev::Polygon::OutInf() const
{
  std::cout << "_________________________________________________________" << std::endl;
  std::cout << "Size:   " << std::setprecision(3) << std::fixed << size_ << std::endl;
  std::cout << "Area:   " << getArea() << std::endl;
  std::cout << "Width:  " << getFrameRect().width << std::endl;
  std::cout << "Height: " << getFrameRect().height << std::endl;
  std::cout << "Pos(x): " << getFrameRect().pos.x << std::endl;
  std::cout << "Pos(y): " << getFrameRect().pos.y << std::endl;
  std::cout << "_________________________________________________________" << std::endl;
}

size_t golyshev::Polygon::getSize() const
{
  return size_;
}

golyshev::point_t golyshev::Polygon::getCentre() const
{
  double sum_x = 0;
  double sum_y = 0;
  for (size_t i = 0; i < size_; i++) {
    sum_x += points_[i].x;
    sum_y += points_[i].y;
  }
  return {sum_x / size_, sum_y / size_};
}

bool golyshev::Polygon::Convex() const
{
  for (size_t i = 0; i < (size_ - 1); i++) {
    double line_pos1 = (points_[i + 1].y - points_[i].y) * (points_[0].x - points_[i].x)
                       - (points_[i + 1].x - points_[i].x) * (points_[0].y - points_[i].y);
    double line_pos2 = 0;
    for (size_t j = 1; j < size_; j++) {
      line_pos2 = (points_[i + 1].y - points_[i].y) * (points_[j].x - points_[i].x)
                  - (points_[i + 1].x - points_[i].x) * (points_[j].y - points_[i].y);
      if (line_pos2 * line_pos1 >= 0) {
        line_pos1 = line_pos2;
      } else {
        return false;
      }
    }
  }
  return true;
}
