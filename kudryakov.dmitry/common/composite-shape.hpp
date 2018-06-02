#ifndef KUDRYAKOV_DMITRY_LABS_COMPOSITESHAPE_HPP
#define KUDRYAKOV_DMITRY_LABS_COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace kudryakov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
  
    CompositeShape(Shape* newShape);
  
    CompositeShape(const CompositeShape& other);
  
    CompositeShape(CompositeShape&& other);
  
    void operator= (const CompositeShape& other);
  
    void operator= (CompositeShape&& other);
  
    Shape* operator[] (int index) const;
    
    void addShape(Shape* newShape);
    
    double getArea() const override;
    
    rectangle_t getFrameRect() const override;
    
    void move(const point_t &newCenterPoint) override;
    
    void move(const double dx, const double dy) override;
    
    void scale(const double factor) override;
    
  private:
    std::unique_ptr<Shape *[]> arr_;
    int size_;
  };
}
#endif
