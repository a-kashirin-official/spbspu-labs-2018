#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include "shape.hpp"
#include <memory>

namespace kashirin
{
  class CompositeShape: public Shape
  {
    public:
      CompositeShape(const std::shared_ptr<Shape> figure);
      ~CompositeShape();
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      point_t getCenter() const override;
      void move(const point_t &point) override;
      void move(const double dx, const double dy) override;
      void scale(const double coef) override;

      void addShape(const std::shared_ptr<Shape> figure);
      void removeFigure(const int index);
      void removeAll();
      int getCount() const;
    private:
      std::unique_ptr < std::shared_ptr<Shape> [] > figures_;
      int count_;
  };
}
#endif
