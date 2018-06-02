#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"

#include <memory>

namespace astafev
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape & other);
    CompositeShape(CompositeShape && other);
    CompositeShape(const std::shared_ptr<Shape> & shape);
    
    ~CompositeShape();
    
    CompositeShape & operator= (const CompositeShape & other);
    CompositeShape & operator= (CompositeShape && other);
    std::shared_ptr<Shape> & operator[] (size_t index);
    
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void scale(double koeficent) override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t &newcentre) noexcept override;
    void rotate(const double degrees) noexcept override;
    size_t getSize() const noexcept override;
    void printInfo() const noexcept override;
    void addElement(const std::shared_ptr<Shape> & shape);
    void deleteElement(size_t index);
    void clear() noexcept;
    
  private:
    size_t size_;
    std::unique_ptr<std::shared_ptr<Shape>[] > array_;
    double angle_;
  };
}

#endif

