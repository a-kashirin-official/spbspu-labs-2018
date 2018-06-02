#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

namespace kudryakov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &center, const double width, const double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newCenterPoint) override;
    void move(const double dx, const double dy) override;
    void scale(const double factor) override;
  private:
    point_t center_;
    double width_;
    double height_;
  };
}
#endif //A1_RECTANGLE_HPP
