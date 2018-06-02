#include "rectangle.hpp"

// Class constructor
Rectangle::Rectangle(const point_t & pos, double w, double h) :
  pos_(pos)
{
  // check if arguments are invalid
  if (w <= 0 || h <= 0)
  {
    // if so throw exception
    throw std::invalid_argument("Width and height of the rectangle must be > 0!");
  }
  // otherwise
  width_ = w;
  height_ = h;
}

// Class constructor
Rectangle::Rectangle(double x, double y, double w, double h) :
  width_(w),
  height_(h),
  pos_({x, y})
{
  // check if arguments are invalid
  if (w <= 0 || h <= 0)
  {
    // if so throw exception
    throw std::invalid_argument("Width and height of the rectangle must be > 0!");
  }
}

// Get area method
double Rectangle::getArea() const
{
  return width_ * height_;
}

// Get frame rectangle method
rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{pos_, width_, height_};
}

// Move rect to the point method
void Rectangle::move(const point_t & pos)
{
  this->pos_ = pos;
}

// Move rect by dx and dy method
void Rectangle::move(double dx, double dy)
{
  // move by dx and dy
  pos_.x += dx;
  pos_.y += dy;
}

// Operator << override
std::ostream & operator<<(std::ostream & stream, const Rectangle & rect)
{
  // use std::endl
  using std::endl;

  // buffer variable
  rectangle_t r = rect.getFrameRect();

  // write to the stream
  stream << "Rectangle object with following parameters:" << endl
      << "Position of the center: (" << rect.pos_.x << ";" << rect.pos_.y << ")" << endl
      << "Width and height of the rectangle are " << rect.width_ << " and " << rect.height_ << endl
      << "Area of the circle: " << rect.getArea() << endl
      << "Rectangle Frame has following parameters:" << endl
      << "\t Position of the center: (" << r.pos.x << ";" << r.pos.x << ")" << endl
      << "\t Width and height are: " << r.width << " and " << r.height << endl;
  return stream;
}

