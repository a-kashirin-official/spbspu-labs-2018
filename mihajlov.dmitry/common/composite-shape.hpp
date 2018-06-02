#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace mihajlov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const std::shared_ptr<Shape>& shape);
    const Shape& operator [](const int index) const;
    void addShape(const std::shared_ptr<Shape>& shape);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& centerPos);
    void move(const double shiftX, const double shiftY);
    void scale(double multiplier) override;
    void remove(const int index);
    void getInfo() const override;
    void printName() const override;
    void rotate(const double angle) override;
  private:
    int arrSize_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapeArr_;
    double angle_;
  };
}

#endif //A3_COMPOSITE_SHAPE_HPP
