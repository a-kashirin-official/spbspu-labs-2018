#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include "shape.hpp"
#include <memory>

namespace lyachko
{

  class CompositeShape : public Shape
  {

  public:

    CompositeShape( Shape * new_shape );
    CompositeShape( const CompositeShape & new_cmp );
    CompositeShape & operator=(const CompositeShape & new_cmp);

    virtual double getArea() const noexcept override;
    virtual rectangle_t getFrameRect() const noexcept override;
    virtual void move(const point_t & new_center) noexcept override;
    virtual void move(double dx, double dy) noexcept override;
    virtual void scale(double scale_coef) override;

    void remove( int index );
    void add( Shape * new_shape );

  private:

    std::unique_ptr<Shape * []> m_shapelist;
    int m_size;

  };
}

#endif 
