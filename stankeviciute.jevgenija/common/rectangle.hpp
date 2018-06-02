#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace stankeviciute
{
  class Rectangle:
    public Shape
  {
  public:
    Rectangle(const point_t &pos, double width, double height);
    friend bool stankeviciute::operator==(const Rectangle &, const Rectangle &);
    double getWidth() const;
    double getHeight() const;
    std::string getName() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printFeatures() const override;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double k) override;
    void rotate(double angle) override;

  private:
    point_t corners_[4];
    double width_, height_;
  };

  bool operator==(const Rectangle &, const Rectangle &);
}

#endif
