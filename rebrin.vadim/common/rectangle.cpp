#include <stdexcept>
#include <iostream>
#include "rectangle.hpp"


rebrin::Rectangle::Rectangle(const rectangle_t& parameters) :  parameters_(parameters)
{
  if (parameters.width < 0.0)
  {
    throw std::invalid_argument("Width must be >= 0");
  }
  if (parameters.height < 0.0)
  {
    throw std::invalid_argument("Height must be >= 0");
  }
}

double rebrin::Rectangle::getArea () const
{
  return parameters_.width * parameters_.height;
}

rebrin::rectangle_t rebrin::Rectangle::getFrameRect() const
{
  return parameters_;
}

void rebrin::Rectangle::move(const double dx, const double dy)
{
  parameters_.pos.x += dx;
  parameters_.pos.y += dy;
}

void rebrin::Rectangle::move(const point_t& pos)
{
  parameters_.pos = pos;
}

void rebrin::Rectangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Factor must be >= 0");
  }

  parameters_.width *= factor;
  parameters_.height *= factor;
}
