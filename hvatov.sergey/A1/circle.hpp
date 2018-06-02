#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

// Circle class
class Circle :
  public Shape
{
  // Public members
public:
  // Constructors of the class
  Circle(const point_t & pos, double radius);
  Circle(double x, double y, double radius);

  // Get area method
  virtual double getArea() const override ;

  // Get frame rectangle method
  virtual rectangle_t getFrameRect() const override ;

  // Move to the point method
  virtual void move(const point_t & pos) override ;

  // Move by dx and dy
  virtual void move(double dx, double dy) override ;

  // Operator << override
  friend std::ostream & operator<<(std::ostream & stream, const Circle & circle);

  // Private members
private:
  // Radius of the circle
  double radius_;
  // Position of the center
  point_t pos_;
};

#endif // CIRCLE_H

