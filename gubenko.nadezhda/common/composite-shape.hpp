#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace gubenko
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(const std::shared_ptr <Shape> & newShape);
    CompositeShape(const CompositeShape &);
    CompositeShape & operator=(const CompositeShape &);
    void addShape( const std:: shared_ptr <Shape> & newShape);
    friend std::ostream & gubenko::operator <<(std::ostream & out, const CompositeShape & s);
    double getArea() const  override;
    rectangle_t getFrameRect() const  override;
    void move(const point_t & pos)  override;
    void move(double dx, double dy)  override;
    void scale(double n) override;

  private:
    std::unique_ptr <std::shared_ptr <Shape>[]> shapes_;
    size_t size_;
  };
  std::ostream & operator <<(std::ostream & out, const CompositeShape & s);
}

#endif //A3_COMPOSITE_SHAPE_HPP
