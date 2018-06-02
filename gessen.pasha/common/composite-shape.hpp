#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace gessen
{
  class CompositeShape: public Shape
  {
    public:
      CompositeShape();
      CompositeShape (Shape * shapeElement);
      
      CompositeShape(CompositeShape &&shp);
      CompositeShape(const CompositeShape &shp);
      ~CompositeShape();

      Shape *operator[](int num) const;
      CompositeShape &operator=(CompositeShape &shp);
      CompositeShape &operator=(CompositeShape &&shp);
      
      double getArea () const override;
      rectangle_t getFrameRect() const override;
      void move(const double dx, const double dy) override;
      void move(const point_t & newPoint) override;
      void scale(const double dk) override;
      void addShape(Shape * shapeElement);
      void removeShape(const int index);
      void printShapeName() const override;
      void rotate (const double angleRotate) override;
      point_t rotatePoint (const point_t &center, const point_t &p, double angleRotate);

    private:
      std::unique_ptr<Shape *[]> shapeList_;
      int shapeCounter_;
  };
}

#endif
