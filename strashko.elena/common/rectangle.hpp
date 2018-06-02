#ifndef HPP_RECTANGLE
#define HPP_RECTANGLE

#include <memory>

#include "shape.hpp"

namespace strashko
{
  class Rectangle : public strashko::Shape
  {
  public:
    Rectangle(const strashko::point_t &centre, double width, double height);

    double getArea() const noexcept override;
    strashko::rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const strashko::point_t &newcentre) noexcept override;
    void scale(double const factor) override;
    void rotate(const double angle) noexcept override;
    std::unique_ptr<strashko::Shape> getCopy() const noexcept override;
    void printInfo() const override;

  private:
    double width_;
    double height_;
    double angle_;
  };
}

#endif
