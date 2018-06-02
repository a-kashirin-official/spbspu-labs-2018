#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace hvatov {

  // Circle class
  class Circle :
    public Shape
  {
    // Public members
  public:
    // Constructors of the class
    Circle(const point_t &center, double radius);

    Circle(double x, double y, double radius);

    // Scale method
    virtual void scale(double k) override;

    // Rotate method
    virtual void rotate(double /* angle */) noexcept override;

    // Get area method
    virtual double getArea() const noexcept override;

    // Get frame rectangle method
    virtual rectangle_t getFrameRect() const noexcept override;

    // Move to the point method
    virtual void move(const point_t &center) noexcept override;

    // Move by dx and dy
    virtual void move(double dx, double dy) noexcept override;

    // Get the coordinates of current position
    virtual point_t getPosition() const noexcept;

    // Get radius method
    double getRadius() const noexcept;

    // Operator << override
    friend std::ostream & operator<<(std::ostream &stream, const Circle &circle);

    // Get the information of about shape
    virtual std::ostream & getInfo(std::ostream & stream) const noexcept override;

    // Private members
  private:
    // Radius of the circle
    double radius_;
    // Position of the center
    point_t center_;
  };

  std::ostream & operator<<(std::ostream &stream, const Circle &circle);
}

#endif // CIRCLE_H

