#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

namespace ivanov
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t & vertexA, const point_t & vertexB, const point_t & vertexC);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & transferPoint) override;
    void move(const double dx, const double dy) override;
    void scale(const double scaleFactor) override;
    void printCurrentInfo() const override;
  private:
    point_t center_;
    point_t vertexA_;
    point_t vertexB_;
    point_t vertexC_;
  };
};

#endif
