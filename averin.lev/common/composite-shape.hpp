#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "base-types.hpp"
#include "shape.hpp"

namespace averin
{
class CompositeShape : public Shape
{
public:
  
  CompositeShape(Shape *obj); 
  
  CompositeShape();
  
  ~CompositeShape() = default;
  
  double getArea() const override;
  
  rectangle_t getFrameRect() const override;
  
  void move(point_t c) override;
  
  void move (double dx, double dy) override;
  
  void printInfo() const override;
  
  void scale(double ratio) override;
  
  void addShape(Shape *obj);
  
  void deleteShape(int index);
  
  void rotate(double deg) override;
  
  void printAngle() const override;
  
  void setAngle(double deg) override;
  
  void printName() const override;
  
private:
  
  std::unique_ptr<Shape *[]> arr_;
  
  int size_;
  
  double angle_;
  
};
}

#endif
