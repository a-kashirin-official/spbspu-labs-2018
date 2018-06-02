#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace gremiachenskii
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> & object);
    CompositeShape(const CompositeShape & object);
    CompositeShape(CompositeShape && object);

    std::shared_ptr<Shape> operator[] (size_t index) const;
    CompositeShape & operator= (const CompositeShape & object);
    CompositeShape & operator= (CompositeShape && object);
    void addElement(const std::shared_ptr<Shape> & object);
    void removeElement(size_t index);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(const point_t & pos) noexcept override;
    void scale(double ratio) override;
    size_t getSize() const noexcept;

  private:
    size_t size_;
    std::unique_ptr< std::shared_ptr<Shape>[] > elements_;
  };
}

#endif // COMPOSITE_SHAPE_HPP
