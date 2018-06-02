#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace lyachko
{

  class Rectangle : public Shape
  {

  public:

    Rectangle(const rectangle_t & new_center);
    virtual double getArea() const override;
    virtual rectangle_t getFrameRect() const override;
    virtual void move(const point_t & new_center) override;
    virtual void move(double dx, double dy) override;
    virtual void scale(double scale_coef) override;

  private:

    rectangle_t m_rectangle;
    
  };

}

#endif
