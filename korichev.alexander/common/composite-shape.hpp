#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "shape.hpp"
#include "matrix.hpp"
#include <memory>

namespace korichev
{
  class CompositeShape : public Shape
  {
    public:
      CompositeShape();
      CompositeShape(const CompositeShape & rhs);
      CompositeShape( CompositeShape && rhs );

      CompositeShape & operator=(const CompositeShape & rhs);
      CompositeShape & operator=(CompositeShape && rhs);
      std::shared_ptr< korichev::Shape > operator[]( const size_t index ) const;

      virtual double getArea() const noexcept override;
      virtual rectangle_t getFrameRect() const noexcept override;
      virtual void move(const point_t & point) noexcept override;
      virtual void move(double dx, double dy) noexcept override;
      virtual void scale(double ratio) override;
      virtual void rotate(double angle) noexcept override;

      Matrix getMatrix() const;
      void add(std::shared_ptr < korichev::Shape> shape);
      void dispose(size_t index);
      void clean() noexcept;
      size_t getListSize() const noexcept;
    private:
      size_t size_;
      std::unique_ptr< std::shared_ptr < korichev::Shape> [] > items_;
  };
}
#endif
