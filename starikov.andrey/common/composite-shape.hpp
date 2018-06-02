#ifndef STARIKOV_ANDREY_LABS_COMPOSITE_SHAPE_HPP
#define STARIKOV_ANDREY_LABS_COMPOSITE_SHAPE_HPP

#include <iostream>
#include <memory>
#include "shape.hpp"

namespace starikov
{
  class CompositeShape: public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> shape);
    CompositeShape();

    const Shape & operator [](int index) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &centre) override;
    void move(const double offsetAxisX, const double offsetAxisY) override;
    void scale(const double ratio) override;
    void addShape(const std::shared_ptr<Shape> newShape);
    rectangle_t getShapeInfo() const;
    void rotate(const double angleDeg) override;
  private:
    rectangle_t modelComposite_;
    int sizeArray_;
    double angleDeg_;
    std::unique_ptr <std::shared_ptr <Shape> []> arrayShape_;
  };
}

#endif //STARIKOV_ANDREY_LABS_COMPOSITE_SHAPE_HPP
