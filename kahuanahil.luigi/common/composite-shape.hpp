#ifndef COMPOSITE_SHAPE
#define COMPOSITE_SHAPE

#include "shape.hpp"
#include <memory>

namespace kahuanahil
{
  class CompositeShape: public kahuanahil::Shape
  {
  public:
  CompositeShape(const std::shared_ptr < kahuanahil::Shape > nshape);
  CompositeShape(const CompositeShape & compositeShape);
  CompositeShape(CompositeShape && compositeShape);
  ~CompositeShape();
  CompositeShape & operator = (const CompositeShape & compositeShape);
  CompositeShape & operator = (CompositeShape && compositeShape);
  bool operator == (const CompositeShape & compositeShape) const;
  bool operator != (const CompositeShape & compositeShape) const;
  double getArea() const noexcept override;
  double getAngle() const override;
  kahuanahil::rectangle_t getFrameRect() const noexcept override;
  void move(const double dx, const double dy) noexcept  override;
  void move(const kahuanahil::point_t &pos) noexcept override;
  void scale(const double factor) override;
  void rotate(const double angle) noexcept override;
  kahuanahil::point_t getCenter() const noexcept override;
  void addShape(std::shared_ptr < kahuanahil::Shape > nshape);
  void deleteShape(const int index);
  void deleteAllShape() noexcept;
  private:
    std::unique_ptr < std::shared_ptr < kahuanahil::Shape > [] > list_;
    int size_;
    double angle_;
  };
}

#endif
