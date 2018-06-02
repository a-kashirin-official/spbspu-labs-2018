#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "matrix.hpp"
#include <memory>

namespace belonogova
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape(std::shared_ptr <Shape> & newComponent);
    CompositeShape(const CompositeShape & other);
    CompositeShape(CompositeShape && other);
    CompositeShape & operator= (const CompositeShape & other);
    CompositeShape & operator= (CompositeShape && other);
    std::shared_ptr <Shape> & operator[] (int index) const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & newPos) override;
    void scale(const double coef) override;
    void addComponent(std::shared_ptr <Shape> & newComponent);
    void removeComponent(const int index);
    void rotate(const double alfa) override;
    Matrix formMatrix() const;
    int getSize() const;

  private:
    int m_size;
    std::unique_ptr <std::shared_ptr <Shape> []> m_array;
  };
}

#endif //COMPOSITE_SHAPE_HPP
