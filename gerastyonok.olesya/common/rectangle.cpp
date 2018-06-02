#include "rectangle.hpp"
#include <iostream>

using namespace gerastyonok; 

gerastyonok::Rectangle::Rectangle(const rectangle_t & rect) :
  rect_(rect)
{
  if (rect.height < 0.0 || rect.width < 0.0)
  {
    throw std::invalid_argument("Error! Invalid height or width");
  }
}

double gerastyonok::Rectangle::getArea() const
{
  return rect_.height * rect_.width;
}

rectangle_t gerastyonok::Rectangle::getFrameRect() const
{
  return rect_;
}

void gerastyonok::Rectangle::move(const point_t & pos)
{
  rect_.pos = pos;
}

void gerastyonok::Rectangle::move(double px, double py)
{
  rect_.pos.x += px;
  rect_.pos.y += py;
}

void gerastyonok::Rectangle::scale(const double k)
{
  if (k < 0.0)
  {
   
    throw std::invalid_argument("Error!");

  }
 
  rect_.height *= k;
  rect_.width *= k;
}

point_t gerastyonok::Rectangle::getCenter() const
{
  return rect_.pos;
}
