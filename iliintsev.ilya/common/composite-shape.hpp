#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace iliintsev
{
  class CompositeShape : 
    public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape & comp_shape);
    CompositeShape(CompositeShape && comp_shape); 
    CompositeShape(std::shared_ptr<Shape> & shape);
    ~CompositeShape();

    CompositeShape & operator= (const CompositeShape & comp_shape);
    CompositeShape & operator= (CompositeShape && comp_shape);
    std::shared_ptr<Shape> & operator[] (int index);

    double getArea() const noexcept;
    rectangle_t getFrameRect() const noexcept;
    void move(const point_t & new_center) noexcept;
    void move(const double dx, const double dy) noexcept;
    void scale(const double koef);
    point_t getCenter() const noexcept;

    void add(const std::shared_ptr< Shape > & shape);
    void remove(int index);
    int getSize() const noexcept;
    void clear() noexcept;
    
  private:
    int size_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
  };
}

#endif
