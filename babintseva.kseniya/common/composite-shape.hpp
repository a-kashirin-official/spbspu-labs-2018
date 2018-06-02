#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include "shape.hpp"
#include <memory>
#include <string>

namespace babintseva
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(const std::shared_ptr<Shape> &shape);
    CompositeShape(const CompositeShape &compShape);
    CompositeShape &operator=(const CompositeShape &compShape);
    friend bool babintseva::operator==(const CompositeShape &compShape1, const CompositeShape &compShape2);

    std::string getName() const override;

    void addShape(const std::shared_ptr<Shape> &shape);

    double getArea() const override;
    virtual point_t getPos() const override;
    rectangle_t getFrameRect() const override;

    void move(const point_t &pos) override;
    void move(const double dx, const double dy) override;
    void scale(double ratio) override;
    void rotate(double angle) override;

  private:
    std::unique_ptr <std::shared_ptr<Shape>[]> shapes_;
    size_t size_;
  };

  bool operator==(const CompositeShape &, const CompositeShape &);
}

#endif