#include "circle.hpp"
#include <stdexcept>
#include <sstream>
#include <math.h>

using namespace std;

Circle::Circle(const point_t& center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0.0) {
    throw invalid_argument("Invalid radius");
  }
}

string Circle::getInfo() const
{
  stringstream info;
  rectangle_t frame_rect = getFrameRect();
  info << "Type: Circle" << endl
      << "Center coordinates: (" << center_.x << "; " << center_.y << ")" << endl
      << "Radius: " << radius_ << endl
      << "Area: " << getArea() << endl
      << "Frame Rectangle:" << endl
      << "\t" << "Center coordinates: ("
      << frame_rect.pos.x << "; "
      << frame_rect.pos.y << ")" << endl
      << "\t" << "Width: " << frame_rect.width << endl
      << "\t" << "Height: " << frame_rect.height << endl;
  return info.str();
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {center_, radius_ * 2, radius_ * 2};
}

void Circle::move(const point_t& new_center)
{
  center_ = new_center;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
