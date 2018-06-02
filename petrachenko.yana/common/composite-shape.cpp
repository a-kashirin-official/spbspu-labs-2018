#include "composite-shape.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace petrachenko;

CompositeShape::CompositeShape(Shape *shp):
  figures_(new Shape *[1]),
  count_(1)
{
  if (shp == nullptr){
    throw std::invalid_argument("Invalid_figures");
  }
  figures_[0] = shp;
}

CompositeShape::CompositeShape(CompositeShape &&shp):
  figures_(nullptr),
  count_(0)
{
  *this = std::move(shp);
}

CompositeShape::CompositeShape(const CompositeShape &shp):
  figures_(new Shape *[shp.count_]),
  count_(shp.count_)
{
  for (size_t i = 0; i < count_; i++)
  {
    figures_[i] = shp.figures_[i];
  }
}

CompositeShape::~CompositeShape()
{
  for (size_t i = 0; i<count_; i++)
  {
    delete figures_[i];
  }
}

Shape *CompositeShape::operator[](size_t num) const
{
  if (num>count_)
  {
    throw std::invalid_argument("Invalid_value");
  }
  return figures_[num];
}

CompositeShape &CompositeShape::operator=(CompositeShape &shp)
{
  if(this!=&shp)
  {
    count_ = shp.count_;
    figures_.swap(shp.figures_);
  }
  return *this;
}

CompositeShape &CompositeShape::operator=(CompositeShape &&shp)
{
  if (this!=&shp)
  {
    count_ = shp.count_;
    figures_.swap(shp.figures_);
    shp.figures_ = nullptr;
    shp.count_ = 0;
  }
  return *this;
}

void CompositeShape::addShape(Shape *shp)
{
  if (shp == nullptr)
  {
    throw std::invalid_argument("Invalid_figures");
  }
  std::unique_ptr<Shape *[]> tmp (new Shape *[count_+1]);
  for (size_t i = 0; i<count_; i++)
  {
    tmp[i] = figures_[i];
  }
  tmp[count_] = shp;
  count_++;
  figures_.swap(tmp);
}

double CompositeShape::getArea() const
{
  double area = figures_[0]->getArea();
  for (size_t i = 1; i < count_; i++)
  {
    area += figures_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (count_ > 1)
  {
    double maxX = figures_[0]->getFrameRect().pos.x + figures_[0]->getFrameRect().width / 2;
    double maxY = figures_[0]->getFrameRect().pos.y + figures_[0]->getFrameRect().height / 2;
    double minX = figures_[0]->getFrameRect().pos.x - figures_[0]->getFrameRect().width / 2;
    double minY = figures_[0]->getFrameRect().pos.y - figures_[0]->getFrameRect().height / 2;

    for (size_t i = 1; i < count_; i++) {
      double width = figures_[i]->getFrameRect().width;
      double height = figures_[i]->getFrameRect().height;
      double posX = figures_[i]->getFrameRect().pos.x;
      double posY = figures_[i]->getFrameRect().pos.y;
      maxX = (posX + width / 2 > maxX) ? (posX + width / 2) : maxX;
      maxY = (posY + height / 2 > maxY) ? (posY + height / 2) : maxY;
      minX = (posX - width / 2 < minX) ? (posX - width / 2) : minX;
      minY = (posY - height / 2 < minY) ? (posY - height / 2) : minY;
    }
    return {maxX - minX, maxY - minY, {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}};
  }
  else
  {
    return figures_[0]->getFrameRect();
  }
}

void CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i<count_; i++)
  {
    figures_[i]->move(dx, dy);
  }
}

void CompositeShape::move(const point_t &p)
{
  point_t center = getFrameRect().pos;
  for (size_t i = 0; i<count_; i++)
  {
    figures_[i]->move(p.x-center.x,p.y-center.y);
  }
}

void CompositeShape::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid_scale_coefficient");
  }
  const point_t center = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++){
    figures_[i]->scale(coefficient);
    const point_t shape_center = figures_[i]->getFrameRect().pos;
    figures_[i]->move({center.x + (shape_center.x - center.x) * coefficient, center.y + (shape_center.y - center.y) * coefficient});
  }
}

size_t CompositeShape::getCount() const
{
  return count_;
}

void CompositeShape::rotate(double alpha)
{
  const point_t center = getFrameRect().pos;
  for (size_t i = 0; i < count_; ++i) {
    figures_[i]->rotate(alpha);
    figures_[i]->move(rotatePoint(center, figures_[i]->getFrameRect().pos, alpha));
  }
}

point_t CompositeShape::rotatePoint(const point_t &center, const point_t &p, double alpha)
{
  const double rad = alpha * M_PI / 180;
  const double newX = center.x + (p.x - center.x) * cos(rad) - (p.y - center.y) * sin(rad);
  const double newY = center.y + (p.x - center.x) * sin(rad) + (p.y - center.y) * cos(rad);
  return {newX, newY};
}

void CompositeShape::print() const
{
  std::cout << "There is(are) " << count_ << " figures." << std::endl;
  for (size_t i = 0; i <count_; i++)
  {
    figures_[i]->print();
    std::cout << std::endl;
  }
}

