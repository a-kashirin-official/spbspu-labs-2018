#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace aknazarova
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr <Shape> shape);
    CompositeShape(const CompositeShape &compositeShape);
    CompositeShape(CompositeShape &&compositeShape);
    CompositeShape &operator = (const CompositeShape &compositeShape);
    CompositeShape &operator = (CompositeShape &&compositeShape);
    std::shared_ptr <Shape> & operator[](int i) const;
    void removeShape(const int num);
    void addShape(const std::shared_ptr <Shape> shape);
    void deleteShapes();
    int getSize() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void scale(double kof) override;
    void move(const double dx, const double dy) override;
    void move(const point_t &pos) override;
    
  private:
    std::unique_ptr <std::shared_ptr <Shape> [] > shapes_;
    int size_;
  };
}
#endif
