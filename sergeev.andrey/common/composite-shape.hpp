#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "matrix.hpp"
#include <memory>

namespace sergeev
{
  class CompositeShape : public Shape
  {
    public:
      using item_type = std::shared_ptr< Shape >;
      
      CompositeShape();
      CompositeShape(const CompositeShape & rhs);
      CompositeShape(CompositeShape && rhs);

      CompositeShape & operator=(const CompositeShape & rhs);
      CompositeShape & operator=(CompositeShape && rhs);
      item_type & operator[](int index);

      virtual double getArea() const;
      virtual rectangle_t getFrameRect() const;
      virtual void move(const point_t & point);
      virtual void move(double dx, double dy);
      virtual void scale(double factor);
      virtual void rotate(double angle) override;
      
      Matrix devide() const;
      void add(const item_type & shape);
      void dispose(int index);
      void clean();
      int getListSize() const;
    private:
      int size_;
      void checkIndex(int index);
      std::unique_ptr< item_type[] > items_;   
  };
}
#endif // COMPOSITE_SHAPE_HPP
