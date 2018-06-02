#include "circle.hpp"

#include <stdexcept>

// Class constructor
hvatov::Circle::Circle(const point_t& center, double radius) :
  center_(center)
{
  // check if argument is invalid
  if (radius < 0)
  {
    // if so throw an exception
    throw std::invalid_argument("Radius of the circle must be >= 0");
  }
  // otherwise init radius
  radius_ = radius;
}

// Class constructor
hvatov::Circle::Circle(double x, double y, double radius) :
  center_({ x, y })
{
  // check if argument is invalid
  if (radius < 0)
  {
    // if so throw an exception
    throw std::invalid_argument("Radius of the circle must be >= 0");
  }
  // otherwise init radius
  radius_ = radius;
}

// Scale method:
void hvatov::Circle::scale(double k)
{
  // check if argument is invalid
  if (k < 0)
  {
    // throw an exception
    throw std::invalid_argument("Scale coefficient must be >= 0");
  }
  // otherwise scale the figure
  radius_ *= k;
}

// Rotate method
void hvatov::Circle::rotate(double /* angle */) noexcept
{
}

// Get area method
double hvatov::Circle::getArea() const noexcept
{
  // return area of the circle
  return M_PI * radius_ * radius_;
}

// Get the frame rectangle
hvatov::rectangle_t hvatov::Circle::getFrameRect() const noexcept
{
  return rectangle_t{ center_, 2 * radius_, 2 * radius_ };
}

// Move circle to the point method
void hvatov::Circle::move(const point_t & center) noexcept
{
  // set position to the given one
  center_ = center;
}

// Move circle by dx and dy method
void hvatov::Circle::move(double dx, double dy) noexcept
{
  // move by dx and dy
  center_.x += dx;
  center_.y += dy;
}

// Operator << override
std::ostream& hvatov::operator<<(std::ostream & stream, const Circle & circle)
{
  // use std::endl
  using std::endl;

  // buffer variable
  rectangle_t rect = circle.getFrameRect();

  // write to the stream
  stream << "Circle object with following parameters:" << endl
    << "Position of the center: (" << circle.center_.x << ";" << circle.center_.y << ")" << endl
    << "Radius of the circle: " << circle.radius_ << endl
    << "Area of the circle: " << circle.getArea() << endl
    << "Rectangle Frame has following parameters:" << endl
    << "\t Position of the center: (" << rect.pos.x << ";" << rect.pos.x << ")" << endl
    << "\t Width and height are: " << rect.width << " and " << rect.height << endl;
  return stream;
}

// Get radius method
double hvatov::Circle::getRadius() const noexcept
{
  return radius_;
}

// Get the coordinates of current position method
hvatov::point_t hvatov::Circle::getPosition() const noexcept
{
  return center_;
}

// Get the information of about shape
std::ostream & hvatov::Circle::getInfo(std::ostream & stream) const noexcept
{
  // use std::endl
  using std::endl;

  // write to the stream
  stream << *this << endl;

  return stream;
}

