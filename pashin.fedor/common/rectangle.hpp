#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <string>

#include "shape.hpp"
#include "base-types.hpp"

namespace pashin {
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& center, double width, double height, double angle=0);
    
    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    std::string getInfo() const override;
    void move(double dx, double dy) override;
    void move(const point_t& new_center) override;
    void scale(double k) override;
    void rotate(double angle) override;
    double getWidth() const;
    double getHeight() const;
    
  private:
    point_t center_;
    double width_;
    double height_;
    double angle_;
  };
}

#endif  // RECTANGLE_HPP
