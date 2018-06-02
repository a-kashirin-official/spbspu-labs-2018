#include "composite-shape.hpp"
#include <stdexcept>
#include <math.h>
namespace lyachko
{

  CompositeShape::CompositeShape( Shape * new_shape ) : 
   m_size( 0 )
  {
    if ( new_shape == nullptr )
    {
      throw std::invalid_argument( "Trying to create CompositeShape through nullptr" );
    }
    m_shapelist.reset( new Shape * [1] );
    m_shapelist[0] = new_shape;
    m_size = 1;
  }

  CompositeShape::CompositeShape( const CompositeShape & new_cmp ) :
   m_size( new_cmp.m_size )
  {
    m_shapelist.reset(new Shape *  [new_cmp.m_size] );
    for ( int i = 0; i < m_size; i++ )
    {
      m_shapelist[i] = new_cmp.m_shapelist[i];
    }
  }

  CompositeShape & CompositeShape::operator=(const CompositeShape & new_cmp)
  {
    if( this == &new_cmp )
    {
      return * this;
    }
    m_shapelist.reset( new Shape* [new_cmp.m_size] );
    m_size = new_cmp.m_size;
    for ( int i = 0; i < m_size; i++ )
    {
      m_shapelist[i] = new_cmp.m_shapelist[i];
    }
    return * this;
  }

  void CompositeShape::add( Shape * new_shape )
  {
    if ( new_shape == nullptr )
    {
      throw std::invalid_argument( "Trying to add nullptr to CompositeShape" );
    }
    
    std::unique_ptr<Shape *[]> templist(new Shape * [m_size + 1]);
    
    for ( int i = 0; i<m_size; i++ )
    {
      templist[i] = m_shapelist[i];
    }

    templist[m_size] = new_shape;
    m_shapelist.swap( templist );
    m_size++;
  }

  double CompositeShape::getArea() const noexcept
  {
    double area = 0.0;
    for ( int i = 0; i < m_size; i++ )
    {
      area += m_shapelist[i]->getArea();
    }
    return area;
  }

  rectangle_t CompositeShape::getFrameRect() const noexcept
  { 
    double xleft = m_shapelist[0]->getFrameRect().pos.x - m_shapelist[0]->getFrameRect().width/2;
    double xright = m_shapelist[0]->getFrameRect().pos.x + m_shapelist[0]->getFrameRect().width/2;
    double ytop = m_shapelist[0]->getFrameRect().pos.x + m_shapelist[0]->getFrameRect().height/2;
    double ybottom = m_shapelist[0]->getFrameRect().pos.x - m_shapelist[0]->getFrameRect().height/2;

    for ( int i = 0; i < m_size; i++ )
    {
      if ( m_shapelist[i]->getFrameRect().pos.x + m_shapelist[i]->getFrameRect().width/2 > xright )
      {
        xright = m_shapelist[i]->getFrameRect().pos.x + m_shapelist[i]->getFrameRect().width/2;
      }
      if ( m_shapelist[i]->getFrameRect().pos.x - m_shapelist[i]->getFrameRect().width/2 < xleft )
      {
        xleft = m_shapelist[i]->getFrameRect().pos.x - m_shapelist[i]->getFrameRect().width/2;
      }
      if ( m_shapelist[i]->getFrameRect().pos.y + m_shapelist[i]->getFrameRect().height/2 > ytop )
      {
        ytop = m_shapelist[i]->getFrameRect().pos.y + m_shapelist[i]->getFrameRect().height/2;
      }
      if ( m_shapelist[i]->getFrameRect().pos.y - m_shapelist[i]->getFrameRect().height/2 < ybottom )
      {
        ybottom = m_shapelist[i]->getFrameRect().pos.x - m_shapelist[i]->getFrameRect().height/2;
      }
    }

    return { { xleft + ( xright - xleft )/2 , ybottom  + ( ytop - ybottom )/2 }, ( xright - xleft ), ( ytop - ybottom ) };
  }

  void CompositeShape::move( const lyachko::point_t & new_center ) noexcept
  {
    int dx = new_center.x - getFrameRect().pos.x;
    int dy = new_center.y - getFrameRect().pos.y;

    for ( int i = 0; i < m_size; i++ )
    {
      m_shapelist[i]->move( dx, dy );
    }
  }

  void CompositeShape::move( double dx, double dy ) noexcept
  {
    for ( int i = 0; i < m_size; i++ )
    {
      m_shapelist[i]->move( dx, dy );
    }
  }

  void CompositeShape::scale( double scale_coef ) 
  {
    if ( scale_coef < 0.0 )
    {
      throw std::invalid_argument( "scale_coeff mustn't be lower than 0" );
    }

    double x0 = getFrameRect().pos.x;
    double y0 = getFrameRect().pos.y;

    for ( int i = 0; i < m_size; i++ )
    {
      double new_x = 0.0;
      double new_y = 0.0;

      if ( m_shapelist[i]->getFrameRect().pos.x > x0 )
      {
        new_x = x0 + abs( ( m_shapelist[i]->getFrameRect().pos.x -  x0 ) * scale_coef );
      }else if ( m_shapelist[i]->getFrameRect().pos.x < x0 )
      {
        new_x = x0 - abs( ( m_shapelist[i]->getFrameRect().pos.x -  x0 ) * scale_coef );
      }

      if ( m_shapelist[i]->getFrameRect().pos.y > y0 )
      {
        new_y = y0 + abs( ( m_shapelist[i]->getFrameRect().pos.y -  y0 ) * scale_coef );
      }else if ( m_shapelist[i]->getFrameRect().pos.y < y0 )
      {
        new_y = y0 - abs( ( m_shapelist[i]->getFrameRect().pos.y -  y0 ) * scale_coef );
      }

      if ( (x0 != m_shapelist[i]->getFrameRect().pos.x) && (y0 != m_shapelist[i]->getFrameRect().pos.y) )
      {
        m_shapelist[i]->move( { new_x, new_y } );
      }
      m_shapelist[i]->scale( scale_coef ); 
    }
  }

  void CompositeShape::remove( int index )
  {
    if ( ( index > m_size ) || ( index <= 0 ) )
    {
      throw std::invalid_argument( "No such index" );
    }
    if ( m_size == 0 )
    {
      throw std::invalid_argument( "No elements to delete" );
    }
    std::unique_ptr<Shape *[]> templist( new Shape * [m_size - 1] );
    for ( int i = 0; i < index-1; i++ )
    {
      templist[i] = m_shapelist[i];
    }
    for ( int i = index; i<m_size; i++ )
    {
      templist[i - 1] = m_shapelist[i];
    }
    m_shapelist.swap( templist );
    m_size--;
  }
}
