#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace hvetsckovich
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> shape);
    CompositeShape(const CompositeShape & compShape);
    CompositeShape(CompositeShape && compShape);
    ~CompositeShape();
    CompositeShape & operator=(const CompositeShape & compShape);
    CompositeShape & operator=(CompositeShape && compShape);
    const std::shared_ptr<Shape> & operator[](int index) const;
    point_t getPos() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
    void rotate(const double degrees) override;

    void deleteAllShapes();
    int getSize() const;
    void addShape(std::shared_ptr<Shape> shape);
    void deleteShape(const int index);

  private:
    std::unique_ptr <std::shared_ptr <Shape>[]> items_;
    int size_;
    double angle_;
  };
}

#endif
