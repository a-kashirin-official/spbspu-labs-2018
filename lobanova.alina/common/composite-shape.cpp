#include "composite-shape.hpp"
#include <algorithm>
#include <stdexcept>

using namespace lobanova;

CompositeShape::CompositeShape() : size_(0), capacity_(1), elements_(new Shape *[capacity_])
{
}


double CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < size_; i++) {
    area += elements_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (size_ == 0) {
    return {{0, 0}, 0, 0};
  } else {
    double l = std::numeric_limits<double>::max(), b = l;
    double r = -std::numeric_limits<double>::max(), t = r;

    for (int i = 0; i < size_; i++) {
      rectangle_t rect = elements_[i]->getFrameRect();
      l = std::min(l, rect.pos.x - (rect.width / 2));
      r = std::max(r, rect.pos.x + (rect.width / 2));
      t = std::max(t, rect.pos.y + (rect.height / 2));
      b = std::min(b, rect.pos.y - rect.height / 2);
    }
    return {{(l + (r - l) / 2), (b + (t - b) / 2)}, (r - l), (t - b)};
  }
}

void CompositeShape::move(const point_t &p)
{
  point_t vector = {(p.x - getCentre().x), (p.y - getCentre().y)};
  move(vector.x, vector.y);
}

void CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < size_; i++) {
    elements_[i]->move(dx, dy);
  }
}

point_t CompositeShape::getCentre() const
{
  return getFrameRect().pos;
}

void CompositeShape::scale(const double p)
{
  if (p <= 0) {
    throw std::invalid_argument("Invalid parameter, must be positive");
  }

  const point_t centre = getCentre();
  for (int i = 0; i < size_; i++) {

    const point_t shapePos = elements_[i]->getFrameRect().pos;
    elements_[i]->move({centre.x + p * (shapePos.x - centre.x),
                        centre.y + p * (shapePos.y - centre.y)});
    elements_[i]->scale(p);
  }
}


void CompositeShape::add(Shape *shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Invalid Pointer");
  }

  if (size_ == capacity_) {
    capacity_ *= 2;
    auto **newElements = new Shape *[capacity_];
    std::copy(elements_, elements_ + size_, newElements);
    delete[] elements_;
    elements_ = newElements;
  }

  elements_[size_] = shape;
  size_++;
}

void CompositeShape::clear()
{
  size_ = 0;
}

int CompositeShape::getSize() const
{
  return size_;
}

void CompositeShape::remove(const int index)
{
  if ((index >= size_) or (index < 0)) {
    throw std::out_of_range("Index out of range");
  }

  std::move(elements_ + index + 1, elements_ + size_, elements_ + index);
  size_--;
}


Shape *CompositeShape::operator[](const int index) const
{
  if ((index >= size_) or (index <= 0)) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[index];
}

CompositeShape &CompositeShape::operator=(CompositeShape b)
{
  std::swap(elements_, b.elements_);
  size_ = b.size_;
  capacity_ = b.capacity_;
  return *this;
}

CompositeShape::~CompositeShape()
{
  delete[] elements_;
  elements_ = nullptr;
}

CompositeShape::CompositeShape(const CompositeShape &b)
{
  elements_ = new Shape *[b.capacity_];
  std::copy(b.elements_, b.elements_ + b.capacity_, elements_);
  size_ = b.size_;
  capacity_ = b.capacity_;

}

Shape *&CompositeShape::operator[](int index)
{
  if ((index >= size_) or (index <= 0)) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[index];
}

void CompositeShape::rotate(double p)
{
  point_t c = getCentre();
  rotatePoint(c, p);
}

void CompositeShape::rotatePoint(const point_t &a, double p)
{
  for (int i = 0; i < size_; i++) {
    elements_[i]->rotatePoint(a, p);
  }
}


