#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

namespace lashchenov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t & center);
    Rectangle(double width, double height, double x, double y);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & NewCenter) override;
    void move(double dx, double dy) override;
    void scale(double multiplier) override;
    void rotate(double degrees) override;
    std::unique_ptr<Shape> getCopy() const override;
    void printInfo() const override;

  private:
    point_t vertices_[4];
    double calcDistance(const point_t & p1, const point_t & p2) const;
    point_t getCenter() const;
  };
}
#endif //A1_RECTANGLE_HPP
