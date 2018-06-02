

#include <stdexcept>
#include <cmath>
#include <iostream>
#include "base-types.hpp"
#include "polygon.hpp"

turkin::Polygon::Polygon(const std::unique_ptr<turkin::point_t[]> &array, size_t size) :
  size_(size),
  ver_(new turkin::point_t[size])
{
  if (size_ < 4) {
    throw std::invalid_argument("Size must be > 3");
  }
  for (size_t i = 0; i < size_; ++i) {
    ver_[i] = array[i];
  }
  if (!isConvex()) {
    throw std::invalid_argument("Polygon is  no convex");
  }
  if (getArea() == 0) {
    throw std::invalid_argument("Polygon area = 0");
  }

  center_ = getCenter();
}

double turkin::Polygon::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_ - 1; i++) {
    area += ((ver_[i].x + ver_[i + 1].x) * (ver_[i].y - ver_[i + 1].y));
  }
  area += ((ver_[size_ - 1].x + ver_[0].x) * (ver_[size_ - 1].y - ver_[0].y));
  return fabs(area) / 2;

}

turkin::rectangle_t turkin::Polygon::getFrameRect() const
{
  double maxX = ver_[0].x > ver_[1].x ? ver_[0].x : ver_[1].x;
  double maxY = ver_[0].y > ver_[1].y ? ver_[0].y : ver_[1].y;
  double minX = ver_[0].x < ver_[1].x ? ver_[0].x : ver_[1].x;
  double minY = ver_[0].y < ver_[1].y ? ver_[0].y : ver_[1].y;
  for (size_t i = 2; i < size_; ++i) {
    if (ver_[i].x > maxX) {
      maxX = ver_[i].x;
    } else if (ver_[i].x < minX) {
      minX = ver_[i].x;
    }
    if (ver_[i].y > maxY) {
      maxY = ver_[i].y;
    } else if (ver_[i].y < minY) {
      minY = ver_[i].y;
    }
  }
  return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
}

void turkin::Polygon::move(const turkin::point_t &pos)
{
  move(pos.x - getCenter().x, pos.y - getCenter().y);
}

void turkin::Polygon::move(double Ox, double Oy)
{
  for (size_t i = 0; i < size_; ++i) {
    ver_[i].x += Ox;
    ver_[i].y += Oy;
  }
  center_.x += Ox;
  center_.y += Oy;
}

void turkin::Polygon::printInfo()
{
  for (size_t i = 0; i < size_; ++i) {
    std::cout << "Ver[" << i << "] : {" << ver_[i].x << ", " << ver_[i].y << "}" << std::endl;
  }
  std::cout << "Center : " << center_.x << " " << center_.y << std::endl;
}

void turkin::Polygon::scale(double k)
{
  for (size_t i = 0; i < size_; ++i) {
    ver_[i].x = center_.x + k * (ver_[i].x - center_.x);
    ver_[i].y = center_.y + k * (ver_[i].y - center_.y);
  }
}

void turkin::Polygon::rotate(double angle)
{
  angle = angle * M_PI / 180;
  double r = 0;
  double angle2 = 0;
  point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; i++) {
    r = sqrt(pow((center.x - ver_[i].x), 2) + pow((center.y - ver_[i].y), 2));
    if (ver_[i].y > center.y) {
      angle2 = acos((ver_[i].x - center.x) / r);
    } else {
      angle2 = 2 * M_PI - acos((ver_[i].x - center.x) / r);
    }
    ver_[i].x += (cos(angle2 + angle) - cos(angle2)) * r;
    ver_[i].y += (sin(angle2 + angle) - sin(angle2)) * r;
  }

}


turkin::point_t turkin::Polygon::getCenter() const
{
  double xc = 0;
  double yc = 0;
  double p = 0;
  double l = 0;
  for (size_t i = 0; i < size_; ++i) {
    if (i != size_ - 1) {
      l = sqrt(pow(ver_[i].x - ver_[i + 1].x, 2) + pow(ver_[i].y - ver_[i + 1].y, 2));
      xc += l * ((ver_[i].x + ver_[i + 1].x) / 2);
      yc += l * ((ver_[i].y + ver_[i + 1].y) / 2);
      p += l;
    } else {
      l = sqrt(pow(ver_[i].x - ver_[0].x, 2) + pow(ver_[i].y - ver_[0].y, 2));
      xc += l * ((ver_[i].x + ver_[0].x) / 2);
      yc += l * ((ver_[i].y + ver_[0].y) / 2);
      p += l;
    }
  }
  return {xc / p, yc / p};
}

turkin::point_t &turkin::Polygon::operator[](unsigned int i) const
{
  if (i >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return ver_[i];
}

bool turkin::Polygon::isConvex() const
{
  for (size_t i = 0; i < size_ - 1; i++) {
    double line_pos1 = (ver_[i + 1].y - ver_[i].y) * (ver_[0].x - ver_[i].x)
                       - (ver_[i + 1].x - ver_[i].x) * (ver_[0].y - ver_[i].y);
    double line_pos2 = 0;
    for (size_t j = 1; j < size_; j++) {
      line_pos2 = (ver_[i + 1].y - ver_[i].y) * (ver_[j].x - ver_[i].x)
                  - (ver_[i + 1].x - ver_[i].x) * (ver_[j].y - ver_[i].y);
      if (line_pos2 * line_pos1 >= 0) {
        line_pos1 = line_pos2;
      } else {
        return false;
      }
    }
  }
  return true;

}


