#ifndef COMPOSITESHAPE_HPP
#define COMPOSITEsHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace mordvintseva
{
  class CompositeShape : public Shape
  {
    public:
      CompositeShape(Shape* shape);
      CompositeShape(const CompositeShape & shape);
      CompositeShape(CompositeShape && shape);
      ~CompositeShape();

      double getArea() const noexcept override;
      rectangle_t getFrameRect() const noexcept override;
      void move(const point_t &point) noexcept override;
      void move(const double dx, const double dy) noexcept override;
      void scale(const double factor) override;

      int getCount() const noexcept;
      void add(Shape *shape);
      void remove(const int index);
      void clear();

      CompositeShape &operator=(CompositeShape &rhs);
      CompositeShape &operator=(CompositeShape &&rhs);
      Shape* operator[](const int index) const;

    private:
      std::unique_ptr<Shape *[]> list_;
      int count_;
  };
}

#endif //COMPOSITESHAPE_HPP
