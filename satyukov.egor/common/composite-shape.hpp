#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"

#include <memory>

namespace satyukov
{
  class CompositeShape:
      public satyukov::Shape
  {
  public:
    CompositeShape(const std::shared_ptr < satyukov::Shape > newShape);
    CompositeShape(const CompositeShape & compositeShape);
    CompositeShape(CompositeShape && compositeShape);
    ~CompositeShape();

    CompositeShape & operator =(const CompositeShape & compositeShape);
    CompositeShape & operator =(CompositeShape && compositeShape);
    bool operator ==(const CompositeShape & compositeShape) const;
    bool operator !=(const CompositeShape & compositeShape) const;

    double getArea() const noexcept override;
    double getAngle() const noexcept override;
    satyukov::point_t getCoordinates() const noexcept override;
    satyukov::rectangle_t getFrameRect() const noexcept override;
    void move(const satyukov::point_t  & newCenter) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
    void addShape(const std::shared_ptr < satyukov::Shape > newShape);
    std::shared_ptr < satyukov::Shape > getShape(int const index) const;
    void removeShape(const int index);
    void clear() noexcept;
    int getSize() const noexcept;

  private:
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > list_;
    int size_;
    double angle_;
  };
}

#endif
