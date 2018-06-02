#include "rectangle.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

pashin::Rectangle::Rectangle(const point_t& center, double width, double height, double angle):
  center_(center),
  width_(width),
  height_(height),
  angle_(angle)
{
  if (!(width >= 0.0)) {
    throw invalid_argument("Invalid width");
  }
  if (!(height >= 0.0)) {
    throw invalid_argument("Invalid height");
  }
}

pashin::point_t pashin::Rectangle::getCenter() const
{
  return center_;
}

double pashin::Rectangle::getArea() const
{
  return width_ * height_;
};

pashin::rectangle_t pashin::Rectangle::getFrameRect() const
{
  point_t vertices[4];
  vertices[0] = {center_.x - (width_ / 2), center_.y - (height_ / 2)};
  vertices[1] = {center_.x - (width_ / 2), center_.y + (height_ / 2)};
  vertices[2] = {center_.x + (width_ / 2), center_.y - (height_ / 2)};
  vertices[3] = {center_.x + (width_ / 2), center_.y + (height_ / 2)};
  
  double angle_in_radians = angle_ * M_PI / 180;
  for (point_t& vertex: vertices) {
    vertex.x = center_.x + (vertex.x - center_.x) * cos(angle_in_radians)
                         - (vertex.y - center_.y) * sin(angle_in_radians);
    vertex.y = center_.y + (vertex.x - center_.x) * sin(angle_in_radians)
                         + (vertex.y - center_.y) * cos(angle_in_radians);
  }
  
  double min_x = vertices[0].x;
  double max_x = vertices[0].x;
  double min_y = vertices[0].y;
  double max_y = vertices[0].y;
  for (const point_t& vertex: vertices) {
    if (vertex.x < min_x) {
      min_x = vertex.x;
    } else if (vertex.x > max_x) {
      max_x = vertex.x;
    }
    if (vertex.y < min_y) {
      min_y = vertex.y;
    } else if (vertex.y > max_y) {
      max_y = vertex.y;
    }
  }
  
  return {center_, (max_x - min_x), (max_y - min_y)};
}

string pashin::Rectangle::getInfo() const
{
  stringstream info;
  
  rectangle_t frame_rect = getFrameRect();
  info << "Type: Rectangle" << endl
      << "Center coordinates: (" << center_.x << "; " << center_.y << ")" << endl
      << "Width: " << width_ << endl
      << "Height: " << height_ << endl
      << "Area: " << getArea() << endl
      << "Frame Rectangle:" << endl
      << "\t" << "Center coordinates: ("
      << frame_rect.pos.x << "; "
      << frame_rect.pos.y << ")" << endl
      << "\t" << "Width: " << frame_rect.width << endl
      << "\t" << "Height: " << frame_rect.height << endl;
  
  return info.str();
}

void pashin::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void pashin::Rectangle::move(const point_t& new_center)
{
  center_ = new_center;
}

void pashin::Rectangle::scale(double k)
{
  if (!(k >= 0)) {
    throw invalid_argument("Invalid coefficient");
  }
  width_ *= k;
  height_ *= k;
}

void pashin::Rectangle::rotate(double angle)
{
  angle_ = angle;
  while (angle_ >= 360.0) {
    angle_ -= 360.0;
  }
}

double pashin::Rectangle::getWidth() const
{
  return width_;
}

double pashin::Rectangle::getHeight() const
{
  return height_;
}

