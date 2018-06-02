#include <iostream>
#include <stdexcept>
#include <memory>
#include "composite-shape.hpp"

using namespace vlasov;

CompositeShape::CompositeShape(std::shared_ptr<Shape> newShape) :
  amount_(0),
  shapes_(nullptr)
{
  if (!newShape) {
    throw std::invalid_argument("WARNIG: invalid parametr of Shape");
  }
  add(newShape);
}

CompositeShape::CompositeShape() :
  amount_(0),
  shapes_(nullptr)
{}

void CompositeShape::move(const point_t& point)
{
  double dx = point.x - getFrameRect().pos.x;
  double dy = point.y - getFrameRect().pos.y;

  for (int i = 0; i < amount_; i++) {
    shapes_[i] -> move(dx , dy);
  }
}

void CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < amount_; i++) {
    shapes_[i] -> move(dx, dy);
  }
}

void CompositeShape::scale(const double extender)
{
  if (extender < 0.0){
    throw std::invalid_argument("WARNING: invalid coefficient of scaling\n");
  }

  for (int i = 0; i < amount_; i++) {
    double dx = (shapes_[i] -> getFrameRect().pos.x -
      getFrameRect().pos.x) * (extender -1 );
    double dy = (shapes_[i] -> getFrameRect().pos.y -
      getFrameRect().pos.y) * (extender - 1);
    shapes_[i] -> move(dx, dy);
    shapes_[i] -> scale(extender);
  }
}

double CompositeShape::getArea() const
{
  double area = 0.0;

  for (int i = 0; i < amount_; i++) {
    area += shapes_[i] -> getArea();
  }

  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t shapeParameter;
  if (amount_ != 0){
    shapeParameter = shapes_[0] -> getFrameRect();
  } else shapeParameter = {{0.0, 0.0}, 0.0, 0.0};

  double leftEdge = shapeParameter.pos.x - shapeParameter.width / 2;
  double rightEdge = shapeParameter.pos.x + shapeParameter.width / 2;
  double topEdge = shapeParameter.pos.y + shapeParameter.height / 2;
  double bottomEdge = shapeParameter.pos.y - shapeParameter.height / 2;

  for (int i = 0; i < amount_; i++) {
    shapeParameter = shapes_[i] -> getFrameRect();

    if (leftEdge > shapeParameter.pos.x - shapeParameter.width / 2) {
      leftEdge = shapeParameter.pos.x - shapeParameter.width / 2;
    }

    if (rightEdge <  shapeParameter.pos.x + shapeParameter.width / 2) {
      rightEdge = shapeParameter.pos.x + shapeParameter.width / 2;
    }

    if (topEdge <  shapeParameter.pos.y + shapeParameter.height / 2) {
      topEdge =  shapeParameter.pos.y + shapeParameter.height / 2;
    }

    if (bottomEdge >  shapeParameter.pos.y - shapeParameter.height / 2) {
      bottomEdge =  shapeParameter.pos.y - shapeParameter.height / 2;
    }
  }

  double height = topEdge - bottomEdge;
  double width = rightEdge - leftEdge;
  point_t centre = {rightEdge - width / 2, topEdge - height / 2};

  return {centre, width, height};
}

void CompositeShape::add(const std::shared_ptr<Shape> newShape)
{
  if (!newShape) {
    throw std::invalid_argument("Adding null pointer?");
  }

  amount_++;
  std::unique_ptr<std::shared_ptr<Shape>[]> tmp(new std::shared_ptr<Shape>[amount_]);
  for (int i = 0; i < amount_ - 1; i++) {
    tmp[i] = shapes_[i];
  }
  tmp[amount_ - 1] = newShape;
  shapes_.swap(tmp);
  //setting a new center after adding a shape (even with null pointer)
  point_t lowPos = shapes_[0]->pos;
  point_t highPos = shapes_[0]->pos;
  for (int i = 1; i < amount_; i++){
    if (shapes_[i]->pos.x < lowPos.x){
      lowPos.x = shapes_[i]->pos.x;
    }
    if (shapes_[i]->pos.x > highPos.x){
      highPos.x = shapes_[i]->pos.x;
    }
    if (shapes_[i]->pos.y < lowPos.y){
      lowPos.y = shapes_[i]->pos.y;
    }
    if (shapes_[i]->pos.x > highPos.y){
      highPos.y = shapes_[i]->pos.y;
    }
  }
  pos.x = (lowPos.x + highPos.x)/2;
  pos.y = (lowPos.y + highPos.y)/2;
}

void CompositeShape::remove(const int index)
{
  if (index > amount_ - 1 || index < 0) {
    throw std::invalid_argument("WARNING: there is no such index or left only one shape in array\n");
  } else { //preventing undefined behaviour with else
    amount_--;
    std::unique_ptr<std::shared_ptr<Shape>[]> tmp(new std::shared_ptr<Shape>[amount_]);

    int n = 0;
    for (int i = 0; i < amount_ + 1; i++) {
      if (i != index) {
        tmp[n] = shapes_[i];
        n++;
      }
    }

    shapes_.swap(tmp);
    //setting a new center after removing a shape
    point_t lowPos = shapes_[0]->pos;
    point_t highPos = shapes_[0]->pos;
    for (int i = 1; i < amount_; i++) {
      if (shapes_[i]->pos.x < lowPos.x) {
        lowPos.x = shapes_[i]->pos.x;
      }
      if (shapes_[i]->pos.x > highPos.x) {
        highPos.x = shapes_[i]->pos.x;
      }
      if (shapes_[i]->pos.y < lowPos.y) {
        lowPos.y = shapes_[i]->pos.y;
      }
      if (shapes_[i]->pos.x > highPos.y) {
        highPos.y = shapes_[i]->pos.y;
      }
    }
    pos.x = (lowPos.x + highPos.x) / 2;
    pos.y = (lowPos.y + highPos.y) / 2;
  }
}

