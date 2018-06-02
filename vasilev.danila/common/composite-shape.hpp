#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP
#include "shape.hpp"
#include <memory>
namespace vasilev
{
class CompositeShape :
    public Shape
{
public:
  CompositeShape(std::shared_ptr<Shape> figure);
  CompositeShape(const CompositeShape &figure);
  CompositeShape(CompositeShape &&figure);
  Shape &operator[](size_t n) const;
  CompositeShape &operator=(CompositeShape &&figure);
  CompositeShape &operator=(const CompositeShape &figure);
  void addShape(std::shared_ptr<Shape> newshape);
  void deleteShape(size_t n);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double dx, const double dy) override;
  void move(const point_t &point) override;
  void scale(const double mult) override;
  size_t getQuantity() const;
  std::shared_ptr<Shape> getShape(size_t number) const;
  void getInfo() const override;
private:
  std::unique_ptr<std::shared_ptr<Shape>[]> arr_;
  size_t quant_;
};
}
#endif // COMPOSITESHAPE_HPP
