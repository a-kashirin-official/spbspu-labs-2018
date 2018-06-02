#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace suslov
{
  class CompositeShape:
    public suslov::Shape
  {
  public:
    CompositeShape(const std::shared_ptr < suslov::Shape > shape);
    CompositeShape(const CompositeShape & compositeShape);
    CompositeShape(CompositeShape && compositeShape);
    ~CompositeShape();
    CompositeShape & operator = (const CompositeShape & compositeShape);
    CompositeShape & operator = (CompositeShape && compositeShape);
    bool operator == (const CompositeShape & compositeShape) const;
    bool operator != (const CompositeShape & compositeShape) const;
    suslov::rectangle_t getFrameRect() const noexcept override;
    double getArea() const noexcept override;
    double getAngle() const override;

    void move(const double dx, const double dy) noexcept override;
    void move(const suslov::point_t & newPoint) noexcept override;

    void scale(const double coef) override;
    void rotate(const double angle) noexcept override;

    void addShape(std::shared_ptr < suslov::Shape > shape);
    void deleteShape(const int shapeNumber);
    void deleteAllShapes() noexcept;


  private:
    std::unique_ptr < std::shared_ptr < suslov::Shape > [] > shapes_;
    int size_;
    double angle_;
  };
}

#endif
