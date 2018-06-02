#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace tseptsov
{
  class CompositeShape : public tseptsov::Shape
  {
  public:
    explicit CompositeShape(std::shared_ptr < tseptsov::Shape > NewSh);
    CompositeShape(const CompositeShape &ShapeArray);
    CompositeShape(CompositeShape &&ShapeArray) noexcept;

    CompositeShape &operator=(const CompositeShape &ShapeArray);
    CompositeShape &operator=(CompositeShape &&ShapeArray) noexcept;

    std::shared_ptr<tseptsov::Shape> operator[](unsigned int i) const;
    void add(std::shared_ptr < tseptsov::Shape > NewSh);
    void remove(size_t i);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &pos) override;
    void move(double Ox, double Oy) override;
    void scale(double coef) override;
    void OutData() const override;
    size_t getSize();
    void rotate(double deg) override;
    tseptsov::point_t rotatePoint(const point_t &center, const point_t &point, double deg);
    point_t getCenter() const override ;
  private:
    std::unique_ptr < std::shared_ptr < Shape >[] > list_;
    size_t size_;
  };
}


#endif
