#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

// Rectangle class
class Rectangle :
  public Shape
{
  // Public members
public:
  // Constructors of the class
  Rectangle(const point_t & pos, double w, double h);
  Rectangle(double x, double y, double w, double h);

  // Get area method
  virtual double getArea() const override ;

  // Get frame rectangle method
  virtual rectangle_t getFrameRect() const override ;

  // Move to the point method
  virtual void move(const point_t & pos) override ;

  // Move by dx and dy
  virtual void move(double dx, double dy) override ;

  // Get the info about object method:
  friend std::ostream & operator<<(std::ostream & stream, const Rectangle & rect);

  // Private members
private:
  // Width of the rect
  double width_;
  // Height of the rect
  double height_;
  // Position of the center
  point_t pos_;
};

#endif // RECTANGLE_HPP

