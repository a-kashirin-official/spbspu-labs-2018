#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <string>

#include "shape.hpp"
#include "base-types.hpp"

namespace pashin {
  class Circle : public Shape
  {
  public:
    Circle(const point_t& center, double radius);

    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    std::string getInfo() const override;
    void move(double dx, double dy) override;
    void move(const point_t& new_center) override;
    void scale(double k) override;
    void rotate(double /* angle */) override;
    double getRadius() const;

  private:
    point_t center_;
    double radius_;
  };
}

#endif  // CIRCLE_HPP
