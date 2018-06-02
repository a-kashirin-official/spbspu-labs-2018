#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

namespace isaev
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t &point1, const point_t &point2, const point_t &point3);
    void setPoints(const point_t &point1, const point_t &point2, const point_t &point3);
    virtual double getArea() const override;
    virtual rectangle_t getFrameRect() const override;
    virtual void move(const point_t &point) override;
    virtual void move(double dx, double dy) override;
    virtual void scale(double ratio) override;
    virtual void printShapeInfo() const override;
    point_t getVertex1() const;
    point_t getVertex2() const;
    point_t getVertex3() const;
    point_t getCenter() const;
  private:
    point_t pos_;
    point_t point1_;
    point_t point2_;
    point_t point3_;
    static double getMax(const double &point1, const double &point2, const double &point3);
    static double getMin(const double &point1, const double &point2, const double &point3);
  };
}
#endif

