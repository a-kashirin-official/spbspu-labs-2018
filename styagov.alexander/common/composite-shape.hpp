#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace styagov
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape() noexcept;
    CompositeShape(const std::shared_ptr <styagov::Shape> shape);
    CompositeShape(const styagov::CompositeShape & object) noexcept;
    CompositeShape(styagov::CompositeShape && object) noexcept;
    ~CompositeShape() noexcept;
    styagov::CompositeShape & operator=(const styagov::CompositeShape & object);
    styagov::CompositeShape & operator=(styagov::CompositeShape && object) noexcept;
    styagov::CompositeShape operator+(const CompositeShape & object) noexcept;
    const std::shared_ptr <styagov::Shape> & operator[](size_t index) const;
    
    std::unique_ptr <std::shared_ptr <styagov::Shape>[]> getShapes() const;
    styagov::point_t getPos() const noexcept override;
    double getArea() const noexcept override;
    styagov::rectangle_t getFrameRect() const noexcept override;
    void move(const styagov::point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double ratio) override;
    void rotate(const double alpha) noexcept override; // alpha - angle in degrees

    void clearShapes() noexcept;
    size_t getSize() const noexcept;
    void add(std::shared_ptr< styagov::Shape > shape);
    void remove(const size_t index);

  private:
    std::unique_ptr <std::shared_ptr <styagov::Shape>[]> shapes_;
    size_t size_;
    double angle_;
  };
}

#endif
