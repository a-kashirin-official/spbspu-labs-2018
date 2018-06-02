#ifndef HPP_CIRCLE
#define HPP_CIRCLE

#include <memory>

#include "shape.hpp"

namespace sokolova
{
  class Circle : public sokolova::Shape
  {
  public:
    Circle(const sokolova::point_t &centre, double radius);

    double getArea() const noexcept override;
    sokolova::rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const sokolova::point_t &newcentre) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
    std::unique_ptr<sokolova::Shape> getCopy() const noexcept override;
    void printInfo() const override;

  private:
    double radius_;
    double angle_;
  };
}

#endif
