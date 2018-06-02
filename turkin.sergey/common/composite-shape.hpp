//
// Created by 811432 on 06.05.2018.
//

#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace turkin
{
  class CompositeShape : public turkin::Shape
  {
  public:
    explicit CompositeShape(std::shared_ptr<turkin::Shape> NewSh);
    CompositeShape(const CompositeShape &ShapeArray);
    CompositeShape(CompositeShape &&ShapeArray) noexcept;

    CompositeShape &operator=(const CompositeShape &ShapeArray);
    CompositeShape &operator=(CompositeShape &&ShapeArray) noexcept;

    std::shared_ptr<turkin::Shape> operator[](unsigned int i) const;
    void add(std::shared_ptr<turkin::Shape> NewSh);
    void del(size_t i);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &center) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    void printInfo() override;
    void rotate(double angle) override ;
    size_t getSize()const;
    point_t getCenter() const override ;


  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> array_;
    size_t size_;

  };
}

#endif
