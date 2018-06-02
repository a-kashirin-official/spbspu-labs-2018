#include "circle.hpp"

#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

pashin::Circle::Circle(const point_t& center, double radius):
  center_(center),
  radius_(radius)
{
  if (!(radius >= 0.0)) {
    throw invalid_argument("Invalid radius");
  }
}

pashin::point_t pashin::Circle::getCenter() const
{
  return center_;
}

double pashin::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

pashin::rectangle_t pashin::Circle::getFrameRect() const
{
  return {center_, radius_ * 2, radius_ * 2};
}

string pashin::Circle::getInfo() const
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

void pashin::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void pashin::Circle::move(const point_t& new_center)
{
  center_ = new_center;
}

void pashin::Circle::scale(double k)
{
  if (!(k >= 0)) {
    throw invalid_argument("Invalid coefficient");
  }
  radius_ *= k;
}

void pashin::Circle::rotate(double /* angle */)
{}

double pashin::Circle::getRadius() const
{
  return radius_;
}
