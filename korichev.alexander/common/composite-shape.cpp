#include "composite-shape.hpp"

#include <memory>
#include <math.h>
#include <stdexcept>

korichev::CompositeShape::CompositeShape():
  size_(0),
  items_(nullptr)
{}

korichev::CompositeShape::CompositeShape(const korichev::CompositeShape & rhs):
  size_(rhs.size_)
{
  items_.reset(new std::shared_ptr < korichev::Shape> [rhs.size_] );
  for (size_t i = 0; i<size_ ; i++) {
    items_[i] = rhs.items_[i];
  }
}

korichev::CompositeShape::CompositeShape( korichev::CompositeShape && rhs ):
  size_(rhs.size_)
{
  items_.reset(new std::shared_ptr < korichev::Shape> [rhs.size_] );
  for (size_t i = 0; i<size_ ; i++) {
    items_[i] = rhs.items_[i];
  }
  rhs.size_ = 0;
  rhs.items_.reset();
}

korichev::CompositeShape & korichev::CompositeShape::operator=(const korichev::CompositeShape & rhs)
{
  if(this == &rhs) {
    return *this;
  }

  items_ = std::make_unique< std::shared_ptr < korichev::Shape > []>(rhs.size_);
  size_ = rhs.size_;
  for (size_t i = 0; i<size_ ; i++) {
    items_[i] = rhs.items_[i];
  }
  return *this;
}

std::shared_ptr< korichev::Shape > korichev::CompositeShape::operator[]( const size_t index ) const
{
  if (index >= size_) {
    throw std::invalid_argument("Wrong index!");
  }

  return items_[index];
}

korichev::CompositeShape & korichev::CompositeShape::operator=( korichev::CompositeShape && rhs )
{
  items_ = std::make_unique< std::shared_ptr < korichev::Shape > []>(rhs.size_);
  size_ = rhs.size_;
  for (size_t i = 0; i<size_ ; i++) {
    items_[i] = rhs.items_[i];
  }
  rhs.size_ = 0;
  rhs.items_.reset();
  return *this;
}

double korichev::CompositeShape::getArea() const noexcept
{
  double result = 0.0;
  for(size_t i = 0; i < size_; i++) {
    result += items_[i]->getArea();
  }
  return result;
}

korichev::rectangle_t korichev::CompositeShape::getFrameRect() const noexcept
{
  if (size_ == 0) {
    korichev::rectangle_t zero = {0.0 , 0.0 , {0.0 , 0.0}};
    return zero;
  }

  korichev::rectangle_t rect = items_[0]->getFrameRect();
  double left,top,right,bottom;
  left = rect.pos.x - (rect.width / 2);
  top = rect.pos.y + (rect.height / 2);
  right = rect.pos.x + (rect.width / 2);
  bottom = rect.pos.y - (rect.height / 2);

  for(size_t i = 1; i < size_; i++) {
    rect = items_[i]->getFrameRect();
    left = std::min(left, rect.pos.x - (rect.width / 2));
    top = std::max(top, rect.pos.y + (rect.height / 2));
    right = std::max(right, rect.pos.x + (rect.width / 2));
    bottom = std::min(bottom, rect.pos.y - (rect.height / 2));
  }

  return {right - left, top - bottom,
          {left + ((right - left) / 2), bottom + ((top - bottom) / 2)}};
}

void korichev::CompositeShape::move(const korichev::point_t & point) noexcept
{
  korichev::point_t center = getFrameRect().pos;
  move(point.x - center.x, point.y - center.y);
}

void korichev::CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; i++) {
    items_[i]->move(dx, dy);
  }
}

void korichev::CompositeShape::scale(double ratio)
{
  if (ratio < 0.0) {
    throw std::invalid_argument("Wrong scaling ratio!");
  }
  korichev::point_t shape_pos = getFrameRect().pos;
  korichev::point_t item_pos{0.0,0.0};
  for(size_t i = 0; i < size_; i++) {
    item_pos = items_[i]->getFrameRect().pos;
    items_[i]->move(ratio * (item_pos.x - shape_pos.x),
                    ratio * (item_pos.y - shape_pos.y));
    items_[i]->scale(ratio);
  }
}

void korichev::CompositeShape::rotate(double angle) noexcept
{
  double x_new;
  double y_new;
  double temp_x, temp_y;
  double x0 = getFrameRect().pos.x;
  double y0 = getFrameRect().pos.y;
  for ( size_t i = 0; i < size_; i++ )
  {
    temp_x = items_[i]->getFrameRect().pos.x;
    temp_y = items_[i]->getFrameRect().pos.y;
    x_new = x0 + ( ( temp_x - x0 ) * cos( angle*M_PI/180 ) - ( temp_y - y0 ) * sin( angle*M_PI/180 ) );
    y_new = y0 + ( ( temp_x - x0 ) * sin( angle*M_PI/180 ) + ( temp_y - y0 ) * cos( angle*M_PI/180 ) );
    items_[i]->move( { x_new, y_new } );
    items_[i]->rotate( angle );
  }

}

korichev::Matrix korichev::CompositeShape::getMatrix() const
{
  Matrix matr;
  for (size_t i = 0; i < size_; i++) {
    matr.add(items_[i]);
  }
  return matr;
}

void korichev::CompositeShape::add(std::shared_ptr < korichev::Shape> shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Trying to add Nullptr");
  }
  std::unique_ptr< std::shared_ptr < korichev::Shape> [] > temp =
    std::make_unique< std::shared_ptr < korichev::Shape > []>(size_+1);

  for (size_t i = 0; i < size_; i++ ) {
    temp[i] = items_[i];
  }
  temp[size_] = shape;
  items_.swap(temp);
  size_++;
}

void korichev::CompositeShape::dispose(size_t index)
{
  if (index >= size_) {
    throw std::invalid_argument("Wrong Index of items of CompositeShape!");
  }
  if (size_ == 0 ) {
    throw std::invalid_argument("The CompositeShape is already empty");
  }
  std::unique_ptr< std::shared_ptr < korichev::Shape> [] > temp =
    std::make_unique< std::shared_ptr < korichev::Shape > []>(size_ - 1);

  if ( index != 0 ) {
    for ( size_t i = 0; i <= index-1; i++ ) {
      temp[i] = items_[i];
    }
  }
  for ( size_t i = index+1; i<size_; i++ ) {
    temp[i-1] = items_[i];
  }
  items_.swap(temp);
  size_--;
}


void korichev::CompositeShape::clean() noexcept
{
  items_.reset(nullptr);
  size_ = 0;
}

size_t korichev::CompositeShape::getListSize() const noexcept
{
  return size_;
}
