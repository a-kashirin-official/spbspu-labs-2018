#ifndef WORK_COMPOSITESHAPE_HPP
#define WORK_COMPOSITESHAPE_HPP

#include "shape.hpp"

#include <memory>

namespace ivanov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();

    CompositeShape(const std::shared_ptr <Shape> & newShape);
    CompositeShape(const CompositeShape & Obj);
    CompositeShape(CompositeShape && Obj);

    CompositeShape & operator = (const CompositeShape & Obj);
    CompositeShape & operator = (CompositeShape && Obj);
    ~ CompositeShape();

    std::shared_ptr<Shape> operator [] (const unsigned int index);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & newCentrePoint) override;
    void move(const double dx, const double dy) override;
    void scale(const double ratio) override;
    void addShape(const std::shared_ptr<Shape> & newShape);
    void deleteShape(const unsigned int index);
    void printInfo();
    size_t getSize() const;

  private:
    size_t size_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;

  };
}

#endif
