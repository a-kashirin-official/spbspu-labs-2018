#include <stdexcept>
#include "composite-shape.hpp"

using namespace zagorodniy;

CompositeShape::CompositeShape(std::shared_ptr< zagorodniy::Shape > shape):
  list_(nullptr),
  count_(0) {
  if (!shape) {
    throw std::invalid_argument("Wrong pointer");
  }
  else {
    addShape(shape);
  }
}

CompositeShape::~CompositeShape()
{
  list_.reset();
  list_ = nullptr;
  count_ = 0;
}

double CompositeShape::getArea() const {
  double area = 0.0;
  for (int i = 0; i < count_; ++i) {
    area += list_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const {
  if (count_ == 0.0) {
    return {{0.0, 0.0}, 0.0, 0.0};
  }
  else {
    double x = list_[0]->getFrameRect().pos.x;
    double y = list_[0]->getFrameRect().pos.y;
    double width = list_[0]->getFrameRect().width;
    double height = list_[0]->getFrameRect().height;
    for (int i = 1; i < count_; ++i) {
      point_t leftUpCorner = {x - width / 2.0, y + height / 2.0};
      point_t rightDownCorner = {x + width / 2.0, y - height / 2.0};
      point_t leftUpCorneri = {list_[i]->getFrameRect().pos.x - list_[i]->getFrameRect().width / 2.0,
                       list_[i]->getFrameRect().pos.y + list_[i]->getFrameRect().height / 2.0};
      point_t rightDownCorneri = {list_[i]->getFrameRect().pos.x + list_[i]->getFrameRect().width / 2.0,
                       list_[i]->getFrameRect().pos.y - list_[i]->getFrameRect().height / 2.0};
      if (leftUpCorner.x > leftUpCorneri.x) {           //if new shape is to the left
        width = rightDownCorner.x - leftUpCorneri.x;
        x = (2 * leftUpCorneri.x + width) / 2.0;
      }
      if (rightDownCorner.x < rightDownCorneri.x) {           //if new shape is to the right
        width = leftUpCorner.x - rightDownCorneri.x;
        x = (2 * leftUpCorner.x + width) / 2.0;
      }
      if (leftUpCorner.y < leftUpCorneri.y) {           //if new shape is above
        height = rightDownCorner.y - leftUpCorneri.y;
        y = (2 * rightDownCorner.y + height) / 2.0;
      }
      if (rightDownCorner.y > rightDownCorneri.y) {           //if new shape is below
        height = leftUpCorner.y - rightDownCorneri.y;
        y = (2 * rightDownCorneri.y + height) / 2.0;
      }
    }
    return {{x, y}, width, height};
  }
}

void CompositeShape::move(const point_t &newCenter) {
  point_t currPos = getFrameRect().pos;
  move(newCenter.x - currPos.x, newCenter.y - currPos.y);
}

void CompositeShape::move(double dx, double dy) {
  for (int i = 0; i < count_; ++i) {
    list_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(double coef) {
  if (coef < 0.0) {
    throw std::invalid_argument("Wrong coefficient");
  }
  point_t currPos = getFrameRect().pos;
  for (int i = 0; i < count_; ++i) {
    list_[i]->move((coef - 1) * (list_[i]->getFrameRect().pos.x - currPos.x), (coef - 1) * (list_[i]->getFrameRect().pos.y - currPos.y));
    list_[i]->scale(coef);
  }
}

int CompositeShape::getCount() const {
  return count_;
}

void CompositeShape::addShape(const std::shared_ptr< Shape > shape) {
  if (!shape)
  {
    throw std::invalid_argument("Not a shape");
  }
  std::unique_ptr< std::shared_ptr< zagorodniy::Shape >[] > newList(new std::shared_ptr < zagorodniy::Shape >[count_ + 1]);
  for (int i = 0; i < count_; ++i) {
    newList[i] = list_[i];
  }
  newList[count_] = shape;
  count_++;
  list_.swap(newList);
}

void CompositeShape::removeShape(const int index) {
  if ((index > count_) || (index <= 0)) {
    throw std::invalid_argument("Out of range");
  }
  else if (count_ == 0) {
    throw std::invalid_argument("List is empty");
  }
  else {
    std::unique_ptr<std::shared_ptr<zagorodniy::Shape>[]> newList(new std::shared_ptr<zagorodniy::Shape>[count_ - 1]);
    for (int i = 0; i < (index - 1); ++i) {
      newList[i] = list_[i];
    }
    for (int i = index; i < count_; ++i) {
      newList[i - 1] = list_[i];
    }
    list_.swap(newList);
    count_--;
  }
}
