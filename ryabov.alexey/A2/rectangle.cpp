#include "rectangle.hpp"
#include <stdexcept>

using namespace ryabov;

void checkRectForErrs(double width, double height)
{
  if ((width <= 0) || (height <= 0)) {
    throw std::invalid_argument("Error: Invalid argument: Width and height must be > 0.");
  }
}

Rectangle::Rectangle(double width, double height, const point_t &pos) :
  frame_({width, height, pos})
{
  checkRectForErrs(width, height);
}

Rectangle::Rectangle(const rectangle_t &frame) :
  frame_(frame)
{
  checkRectForErrs(frame.width, frame.height);
}

double Rectangle::getArea() const
{
  return frame_.width * frame_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return frame_;
}

point_t Rectangle::move(const point_t &coords)
{
  frame_.pos = coords;
  return coords;
}

point_t Rectangle::move(double dx, double dy)
{
  frame_.pos.x += dx;
  frame_.pos.y += dy;
  return frame_.pos;
}

void Rectangle::scale(double factor)
{
  if (factor <= 0) {
    throw std::invalid_argument("Error: Invalid argument: factor must be > 0.");
  } else {
    frame_.width *= factor;
    frame_.height *= factor;
  } 
}
