#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <cstring>
#include "shape.hpp"

namespace maikenova
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape & newShape);
    CompositeShape(CompositeShape && newShape);
    ~CompositeShape();

    Shape * operator[](size_t index) const;
    CompositeShape & operator= (const CompositeShape & newShape);
    CompositeShape & operator= (CompositeShape && newShape);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newPos) override;
    void move(const double dx, const double dy) override;
    void scale(const double ratio) override;
    void rotate(double phi) override;

    void pushBack(Shape * newShape);
    void remove(Shape * thisShape);
    point_t getPos() const;
    size_t getAmount() const;
    size_t getSize() const;

  private:
    size_t amount_;
    Shape ** complexShape_;
    point_t pos_;
  };
}

#endif //COMPOSITE_SHAPE_HPP
