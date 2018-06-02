#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
#include <string>

namespace babintseva
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &position, const double width, const double height);

    friend bool babintseva::operator==(const Rectangle &rect1, const Rectangle &rect2);

    double getArea() const override;
    std::string getName() const override;

    rectangle_t getFrameRect() const override;
    point_t getPos() const override;

    void move(const point_t &pos) override;
    void move(const double dx, const double dy) override;

    void scale(double ratio) override;

    void rotate(double angle) override;

    double getHeight();
    double getWidth();

  private:
    point_t corners_[4];
    double width_, height_;
  };

  bool operator==(const Rectangle &rect1, const Rectangle &rect2);
}

#endif
