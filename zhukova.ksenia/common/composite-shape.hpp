
#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>
#include <boost/shared_array.hpp>

namespace zhukova
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(std::shared_ptr <Shape> element);
    CompositeShape(const CompositeShape & compShape);

    CompositeShape & operator = (const CompositeShape & rhs);
    std::shared_ptr <Shape> operator [] (int i) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t & point) override;
    void scale(double coefficient) override;
    void rotate(double deg) override;

    void addElement(std::shared_ptr <Shape> element);
    int getCount() const;

  private:
    int count_;
    boost::shared_array< std::shared_ptr <Shape> > shapeList_;

    point_t calcCenter() const;
  };
}

#endif // COMPOSITE_SHAPE_HPP
