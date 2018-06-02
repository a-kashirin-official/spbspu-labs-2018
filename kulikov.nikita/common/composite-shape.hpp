#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP
#include <memory>
#include "shape.hpp"

namespace kulikov
{
  class CompositeShape: public kulikov::Shape
  {
  public:
    CompositeShape();
    CompositeShape(const std::shared_ptr <kulikov::Shape> shape);
    CompositeShape(const kulikov::CompositeShape & compositeShape);
    CompositeShape & operator = (const kulikov::CompositeShape & compositeShape);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & p) override;
    void move(const double dx, const double dy) override;
    void scale(const double koeff) override;
    void addShape(const std::shared_ptr <kulikov::Shape> shape);
    void deleteShape(const int i);
    void clear();
    int getCounter() const;
  private:
    int counter_;
    std::unique_ptr < std::shared_ptr <kulikov::Shape>[] > array_;
  };
}

#endif // COMPOSITESHAPE_HPP
