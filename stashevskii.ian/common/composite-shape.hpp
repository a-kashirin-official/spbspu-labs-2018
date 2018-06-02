#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace stashevskii
{
  class CompositeShape : public Shape
    {
    public:
      CompositeShape();
      CompositeShape(const std::shared_ptr< Shape > &shape);
      CompositeShape(const CompositeShape & copyShape);
      CompositeShape(CompositeShape && moveShape);
      CompositeShape & operator = (const CompositeShape & copyShape);
      CompositeShape & operator = (CompositeShape && moveShape);
      ~CompositeShape() =default;

      rectangle_t getFrameRect() const override;
      double getArea() const override;

      void move(const double dx, const double dy) override;
      void move(const point_t &Point) override;
      void scale(const double k) override;
      void printf() const;
      point_t getPosition() const override;

      void addShape(const std::shared_ptr < Shape > new_shape);
      void deleteShape(const int number);
      void deleteAll();

      std::shared_ptr<Shape> & operator[](int size);
      int getArraySize() const;
      void rotate(const double angle) override;
  
    private:
      std::unique_ptr < std::shared_ptr < Shape > [] > shapes_;

      int amount_;
    };
}

#endif
