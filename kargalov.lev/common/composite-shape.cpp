#include <iostream>
#include <stdexcept>
#include "composite-shape.hpp"

using namespace kargalov;

CompositeShape::CompositeShape(std::shared_ptr<Shape> newShape)
: size_(0),
list_(nullptr)
{
    if (!newShape) {
      throw std::invalid_argument("WARNIG: invalid parametr of Shape");
    }
    addShape(newShape);
}

CompositeShape::CompositeShape()
: size_(0),
list_(nullptr)
{}

void CompositeShape::move(const point_t& point)
{
    double dx = point.x - getFrameRect().pos.x;
    double dy = point.y - getFrameRect().pos.y;
    
    for (int i = 0; i < size_; i++) {
        list_[i] -> move(dx , dy);
    }
}

void CompositeShape::move(const double dx, const double dy)
{
    for (int i = 0; i < size_; i++) {
        list_[i] -> move(dx, dy);
    }
}

void CompositeShape::scale(const double increment)
{
    if (increment < 0.0){
        throw std::invalid_argument("WARNING: invalid coefficient of scaling\n");
    }
    
    
    for (int i = 0; i < size_; i++) {
        double dx = (list_[i] -> getFrameRect().pos.x -
                     getFrameRect().pos.x) * (increment -1 );
        double dy = (list_[i] -> getFrameRect().pos.y -
                     getFrameRect().pos.y) * (increment - 1);
        list_[i] -> move(dx, dy);
        list_[i] -> scale(increment);
    }
}

double CompositeShape::getArea() const
{
    double area = 0.0;
    for (int i = 0; i < size_; i++) {
        area += list_[i] -> getArea();
    }
    
    return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
    rectangle_t shapeParametr;
    if (size_ != 0){
        shapeParametr = list_[0] -> getFrameRect();
    } else shapeParametr = {0, 0, {0, 0}};
    

    double leftPoint = shapeParametr.pos.x - shapeParametr.width / 2;
    double rightPoint = shapeParametr.pos.x + shapeParametr.width / 2;
    double topPoint = shapeParametr.pos.y + shapeParametr.height / 2;
    double bottomPoint = shapeParametr.pos.y - shapeParametr.height / 2;
    
    for (int i = 0; i < size_; i++) {
        shapeParametr = list_[i] -> getFrameRect();
    
        if (leftPoint > shapeParametr.pos.x - shapeParametr.width / 2) {
            leftPoint = shapeParametr.pos.x - shapeParametr.width / 2;
        }
        
        if (rightPoint <  shapeParametr.pos.x + shapeParametr.width / 2) {
            rightPoint = shapeParametr.pos.x + shapeParametr.width / 2;
        }
        
        if (topPoint <  shapeParametr.pos.y + shapeParametr.height / 2) {
            topPoint =  shapeParametr.pos.y + shapeParametr.height / 2;
        }
        
        if (bottomPoint >  shapeParametr.pos.y - shapeParametr.height / 2) {
            bottomPoint =  shapeParametr.pos.y - shapeParametr.height / 2;
        }
    }
    
    double height = topPoint - bottomPoint;
    double width = rightPoint - leftPoint;
    point_t centre = {rightPoint - width / 2, topPoint - height / 2};
    
    return {width, height, centre};
}

void CompositeShape::addShape(const std::shared_ptr<Shape> newShape)
{
    if (!newShape) {
        throw std::invalid_argument("WARNIG: invalid parametr of Shape");
    }
    
    size_ ++;
    std::unique_ptr<std::shared_ptr <Shape> []> tmp(new std::shared_ptr<Shape> [size_]);
    for (int i = 0; i < size_ - 1; i++) {
        tmp[i] = list_[i];
    }
    tmp[size_ - 1] = newShape;
    list_.swap(tmp);
}

void CompositeShape::removeShape(const int index)
{
    if (index > size_ - 1 || index < 0 || size_ == 1) {
        throw std::invalid_argument("WARNING: there is no such index or left only one shape in array\n");
    }
    size_ --;
    std::unique_ptr<std::shared_ptr<Shape> []> tmp (new std::shared_ptr<Shape> [size_]);
    
    int n = 0;
    for (int i = 0; i < size_ + 1; i++) {
        if (i != index){
            tmp[n] = list_[i];
            n++;
        }
    }
    

    list_.swap(tmp);
}

