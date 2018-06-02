#ifndef CRICLE_HPP
#define CRICLE_HPP

#include "shape.hpp"

namespace korichev
{
  class Circle : public Shape
  {
  public:
    // Constructor of Circle
    Circle(const point_t & new_coord, double new_radius);
    // Get area of Circle method
    virtual double getArea() const override;
    // Get frame of Circle method
    virtual rectangle_t getFrameRect() const override;
    // Move Circle by dx and dy method
    virtual void move(double dx, double dy) override;
    // Move to a point method
    virtual void move(const point_t & pos) override;
    // Scale circle
    virtual void scale(double ratio) override;
    // Rotate
    virtual void rotate(double angle) override;
  private:
    // Center coordinates
    point_t coord_;
    // Radius
    double radius_;
    // Rotation angle
    double angle_;
  };
}

#endif
