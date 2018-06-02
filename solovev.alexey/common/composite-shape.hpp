#ifndef COMPOSITE_SHAPE_HPP_INCLUDED
#define COMPOSITE_SHAPE_HPP_INCLUDED
#include <memory>
#include "shape.hpp"

namespace solovev {
  class CompositeShape:
    public Shape
  {
    public:
      CompositeShape();
      CompositeShape(const std::shared_ptr<Shape>& shape);
      CompositeShape(const CompositeShape& object);
      CompositeShape(CompositeShape&& object);

      CompositeShape& operator=(const CompositeShape& otherObj);
      std::shared_ptr<Shape> operator[](const unsigned int index) const;

      void addShape(const std::shared_ptr<Shape>& shape);
      void rmShape(const unsigned int index);
      size_t getCount() const;
      void move (const point_t newxy) override;
      void move (const double dx, const double dy) override;
      void scale(double factor) override;
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void clear();

    private:
      size_t countShapes_;
      std::unique_ptr <std::shared_ptr<Shape>[]> shapes_;
  };
}


#endif // COMPOSITE_SHAPE_HPP_INCLUDED
