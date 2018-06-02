#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <string>

#include "shape.hpp"
#include "base-types.hpp"

namespace pashin {
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t vertices[3]);
    
    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    std::string getInfo() const override;
    void move(double dx, double dy) override;
    void move(const point_t& new_center) override;
    void scale(double k) override;
    void rotate(double angle) override;
    
  private:
    point_t vertices_[3];
  };
}

#endif  // TRIANGLE_HPP
