#ifndef HPP_CIRCLE
#define HPP_CIRCLE

#include "shape.hpp"
#include <memory>

namespace astafev
{
  class Circle :
    public Shape
  {
  public:
    Circle(const point_t &centre, double radius);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void scale(double koeficent) override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t &newcentre) noexcept override;
    void rotate(const double degrees) noexcept override;
    void printInfo() const noexcept override;
    size_t getSize() const noexcept override;

  private:
    point_t centre_;
    double radius_;
  };
}

#endif

