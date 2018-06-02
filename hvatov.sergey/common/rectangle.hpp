#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

#include <array>

namespace hvatov {

  // Rectangle class
  class Rectangle :
    public Shape
  {
    // Public members
  public:
    // Constructors of the class
    Rectangle(const point_t & center, double w, double h);

    Rectangle(double x, double y, double w, double h);

    // Scale method
    virtual void scale(double k);

    // Rotate method
    virtual void rotate(double angle) noexcept override;

    // Get area method
    virtual double getArea() const noexcept override;

    // Get frame rectangle method
    virtual rectangle_t getFrameRect() const noexcept override;

    // Move to the point method
    virtual void move(const point_t & center) noexcept override;

    // Move by dx and dy
    virtual void move(double dx, double dy) noexcept override;

    // Get the coordinates of current position
    virtual point_t getPosition() const noexcept;

    // Get the width method
    double getWidth() const noexcept;

    // Get height method
    double getHeight() const noexcept;

    // Get the info about object method:
    friend std::ostream & operator<<(std::ostream &stream, const Rectangle &rect);

    // Get the information of about shape
    virtual std::ostream & getInfo(std::ostream & stream) const noexcept override;

    // Private members
  private:
    // Width of the rect
    double width_;
    // Height of the rect
    double height_;
    // Position of the center
    std::array<point_t, 4> vertices_;
  };

  std::ostream & operator<<(std::ostream &stream, const Rectangle &rect);
}

#endif // RECTANGLE_HPP

