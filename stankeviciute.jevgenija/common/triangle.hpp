#ifndef TRIANGLE_HPP_INCLUDED
#define TRIANGLE_HPP_INCLUDED
#include "shape.hpp"

namespace stankeviciute
{
  class Triangle:
    public Shape
  {
  public:
    Triangle(const point_t &, const point_t &, const point_t &);
    friend bool stankeviciute::operator==(const Triangle &, const Triangle &);
    point_t getCenter() const;
    std::string getName() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void printFeatures() const override;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double k) override;
    void rotate(double angle) override;

  private:
    point_t corners_[3];
  };

  bool operator==(const Triangle &, const Triangle &);
}

#endif
