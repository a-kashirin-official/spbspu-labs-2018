#include "rectangle.hpp"
#include <stdexcept>
#include <sstream>

using namespace std;

Rectangle::Rectangle(const point_t& center, double width, double height):
  center_(center),
  width_(width),
  height_(height)
{
  if (width < 0.0) {
    throw invalid_argument("Invalid width");
  }
  if (height < 0.0) {
    throw invalid_argument("Invalid height");
  }
}

string Rectangle::getInfo() const
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

double Rectangle::getArea() const
{
  return width_ * height_;
};

rectangle_t Rectangle::getFrameRect() const 
{
  return {center_, width_, height_};
}

void Rectangle::move(const point_t& new_center)
{
  center_ = new_center;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
