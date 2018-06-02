#include "circle.hpp"

#include <cmath>

// Class constructor
Circle::Circle(const point_t& pos, double radius) :
  pos_(pos)
{
  // check if argument is invalid
  if (radius <= 0)
  {
    // if so throw an exception
    throw std::invalid_argument("Radius of the circle must be > 0");
  }
  // otherwise init radius
  radius_ = radius;
}

// Class constructor
Circle::Circle(double x, double y, double radius) :
  pos_({x, y})
{
  // check if argument is invalid
  if (radius <= 0)
  {
    // if so throw an exception
    throw std::invalid_argument("Radius of the circle must be > 0");
  }
  // otherwise init radius
  radius_ = radius;
}

// Get area method
double Circle::getArea() const
{
  // return area of the circle
  return M_PI * radius_ * radius_;
}

// Get the frame rectangle
rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{pos_, radius_, radius_};
}

// Move circle to the point method
void Circle::move(const point_t & pos)
{
  // set position to the given one
  pos_ = pos;
}

// Move circle by dx and dy method
void Circle::move(double dx, double dy)
{
  // move by dx and dy
  pos_.x += dx;
  pos_.y += dy;
}

// Operator << override
std::ostream & operator<<(std::ostream & stream, const Circle & circle)
{
  // use std::endl
  using std::endl;

  // buffer variable
  rectangle_t rect = circle.getFrameRect();

  // write to the stream
  stream << "Circle object with following parameters:" << endl
      << "Position of the center: (" << circle.pos_.x << ";" << circle.pos_.y << ")" << endl
      << "Radius of the circle: " << circle.radius_ << endl
      << "Area of the circle: " << circle.getArea() << endl
      << "Rectangle Frame has following parameters:" << endl
      << "\t Position of the center: (" << rect.pos.x << ";" << rect.pos.x << ")" << endl
      << "\t Width and height are: " << rect.width << " and " << rect.height << endl;
  return stream;
}

