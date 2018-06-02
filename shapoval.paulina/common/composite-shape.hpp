#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace shapoval
{
  class CompositeShape:
    public shapoval::Shape
  {
  public:
    CompositeShape(const std::shared_ptr <shapoval::Shape> new_shape);
    CompositeShape(const shapoval::CompositeShape &copy);
    CompositeShape(shapoval::CompositeShape &&move) = default;
    CompositeShape & operator=(const shapoval::CompositeShape &copy);
    CompositeShape & operator=(shapoval::CompositeShape &&move);
    double getArea() const noexcept override;
    double getAngle() const noexcept;
    shapoval::rectangle_t getFrameRect() const noexcept override;
    void move(const shapoval::point_t & new_centre) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double k) override;
    void rotate(const double a) noexcept override;
    void addShape(std::shared_ptr <shapoval::Shape> new_shape);
    std::shared_ptr < shapoval::Shape > getShape(int const shapeNumber) const;
    void removeShape(const int shapeNumber);
    void deleteShapes() noexcept;
    int getSize() const noexcept;
  private:
    std::unique_ptr <std::shared_ptr <shapoval::Shape>[] > parts_;
    int size_;
    double angle_;
  };
}

#endif
