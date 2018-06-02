#include <iostream>
#include "../common/composite-shape.hpp"

using std::cout;
using std::endl;
using namespace razuvaev;

CompositeShape::CompositeShape() :
  arr(new Shape *[0]),
  size_(0)
{
}

CompositeShape::CompositeShape(Shape *obj) :
  arr(new Shape *[1]),
  size_(1)
{
  if (obj == nullptr) {
    throw std::invalid_argument("Wrong pointer!");
  }
  arr[0] = obj;
}

double CompositeShape::getArea() const {
  double summArea = 0;
  for (int i = 0; i < size_; i++) {
    summArea += arr[i]->getArea();
  }
  return summArea;
}

rectangle_t CompositeShape::getFrameRect() const {
  rectangle_t rect = arr[0]->getFrameRect();
  double maxX = rect.pos.x + rect.width/2;
  double minX = rect.pos.x - rect.width/2;
  double maxY = rect.pos.y + rect.height/2;
  double minY = rect.pos.y - rect.height/2;
  
  for (int i = 1; i < size_; i++) {
    rect = arr[i]->getFrameRect();
    if ((rect.pos.x + rect.width/2) > maxX) {
      maxX = rect.pos.x + rect.width/2;
    }
    if ((rect.pos.x - rect.width/2) > minX) {
      minX = rect.pos.x - rect.width/2;
    } 
    if ((rect.pos.y + rect.height/2) > maxY) {
      maxY = rect.pos.y + rect.height/2;
    }
    if ((rect.pos.y - rect.height/2) > minY) {
      minY = rect.pos.y - rect.height/2;
    }     
  }
  point_t center;
  center.x = maxX - (maxX-minX)/2;
  center.y = maxY - (maxY-minY)/2;
  return {maxX-minX,maxY-minY,center}; 
}

void CompositeShape::move(point_t c) {
  for (int i = 0; i < size_; i++) {
    arr[i]->move(c);
  }
}

void CompositeShape::move(double dx, double dy) {
  for (int i = 0; i < size_; i++) {
    arr[i]->move(dx,dy);
  }
}

void CompositeShape::writeInfoOfObject() const {
  cout <<endl <<"COMPOSITE SHAPE:" <<endl 
    <<" Area: " <<getArea() <<endl
    <<" FRAME RECTANGLE:" <<endl 
    <<"  Height: " <<getFrameRect().height <<"; Width: " <<getFrameRect().width <<endl 
    <<"  cords (x, y): (" <<getFrameRect().pos.x <<", " <<getFrameRect().pos.y <<")" <<endl;
}

void CompositeShape::scale(double ratio) {
  if (ratio < 0.0) {
    throw std::invalid_argument("Ratio < 0!");
  }
  for (int i = 0; i < size_; i++) {
    arr[i]->scale(ratio);
  }
}

void CompositeShape::addShape(Shape* obj) {
  if (obj == nullptr) {
    throw std::invalid_argument("Wrong pointer!");
  }
  std::unique_ptr<Shape *[]> tempArr (new Shape*[size_+1]);
  for (int i = 0; i < size_; i++) {
    tempArr[i] = arr[i];
  }
  tempArr[size_] = obj;
  arr.swap(tempArr);
  size_++;
}

void CompositeShape::deleteShape(int index) {
  std::unique_ptr<Shape *[]> tempArr (new Shape*[size_-1]);
  for (int i = 0; i < size_; i++) {
    if (i != index) {
      if (i > index) {
        tempArr[i-1] = arr[i]; 
      } else {
        tempArr[i] = arr[i];
      }
    }
  }
  arr.swap(tempArr);
  size_--;
}

CompositeShape::~CompositeShape(){
}
