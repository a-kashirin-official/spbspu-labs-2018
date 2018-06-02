#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"
namespace isaev 
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &centre, double width, double height);
    virtual double getArea() const override;
    virtual rectangle_t getFrameRect() const override;
    virtual void move(const point_t &point) override;
    virtual void move(const double dx,const double dy) override;
    virtual void scale(const double ratio) override;
    virtual void printShapeInfo() const override;
  private:
    point_t pos_;
    double width_;
    double height_;
  };
}
#endif

