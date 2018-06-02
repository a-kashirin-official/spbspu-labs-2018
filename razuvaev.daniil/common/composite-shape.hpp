#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <memory>
#include "../common/base-types.hpp"
#include "../common/shape.hpp"

namespace razuvaev {
  class CompositeShape : public Shape {
  public:

    CompositeShape();
    CompositeShape(Shape *obj); 
    ~CompositeShape();
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t c) override;
    void move (double dx, double dy) override;
    void scale(double ratio) override;
    void addShape(Shape *obj);
    void deleteShape(int index);
    void writeInfoOfObject() const override;
    
  private:
    std::unique_ptr<Shape *[]> arr;
    int size_;
  };
}

#endif
