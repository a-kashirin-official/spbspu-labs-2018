#ifndef HPP_RECTANGLE
#define HPP_RECTANGLE

#include <memory>

#include "shape.hpp"

namespace sokolova
{
  class Rectangle : public sokolova::Shape
  {
  public:
    Rectangle(const sokolova::point_t &centre, double width, double height);

    double getArea() const noexcept override;
    sokolova::rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const sokolova::point_t &newcentre) noexcept override;
    void scale(double const factor) override;
    void rotate(const double angle) noexcept override;
    std::unique_ptr<sokolova::Shape> getCopy() const noexcept override;
    void printInfo() const override;

  private:
    double width_;
    double height_;
    double angle_;
  };
}

#endif
