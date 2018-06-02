#ifndef HPP_CIRCLE
#define HPP_CIRCLE

#include <memory>

#include "shape.hpp"

namespace strashko
{
  class Circle : public strashko::Shape
  {
  public:
    Circle(const strashko::point_t &centre, double radius);

    double getArea() const noexcept override;
    strashko::rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const strashko::point_t &newcentre) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;
    std::unique_ptr<strashko::Shape> getCopy() const noexcept override;
    void printInfo() const override;

  private:
    double radius_;
    double angle_;
  };
}

#endif
