#ifndef REACTANGLE_HPP
#define REACTANGLE_HPP
#include "shape.hpp"

namespace egorov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t &rectangle);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &point) noexcept override;

    void move(const double deltaX, const double deltaY) noexcept override;

    void scale(const double coefficent) override;

    void rotate(double angle) noexcept override;

    std::string getName() const noexcept;

  private:
    rectangle_t rectangle_;
    point_t points_[4];
  };
}
#endif
