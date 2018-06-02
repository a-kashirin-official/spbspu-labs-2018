#ifndef STUDY_LABS_COMPOSITE_SHAPE_HPP
#define STUDY_LABS_COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace lashchenov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    explicit CompositeShape(const Shape & shape);
    CompositeShape(const CompositeShape & ShapeArray);
    CompositeShape(CompositeShape && ShapeArray) noexcept;

    CompositeShape & operator=(const CompositeShape & ShapeArray);
    CompositeShape & operator=(CompositeShape && ShapeArray) noexcept;
    Shape & operator[](size_t i) const;

    void add(const Shape & shape);
    void remove(size_t i);
    void clear();
    size_t size() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & NewCenter) override;
    void move(double dx, double dy) override;
    void scale(double multiplier) override;
    void rotate(double degrees) override;
    point_t rotatePoint(const point_t & center, const point_t & point, double degrees);
    std::unique_ptr<Shape> getCopy() const override;
    void printInfo() const override;

  private:
    std::unique_ptr<std::shared_ptr<Shape>[]> list_;
    size_t size_;
  };
}
#endif //STUDY_LABS_COMPOSITE_SHAPE_HPP
