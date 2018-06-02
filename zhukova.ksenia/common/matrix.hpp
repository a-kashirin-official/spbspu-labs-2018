
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include "composite-shape.hpp"

namespace zhukova
{
  class Matrix
  {
  public:
    struct matrixIndex 
    {
      int layer;
      int shape;
    };

    Matrix(const CompositeShape & arg);
    Matrix(const Matrix & arg);

    std::shared_ptr <zhukova::Shape> operator [] (matrixIndex i);
    std::shared_ptr <zhukova::Shape> * operator [] (int i);
    Matrix & operator = (const Matrix & rhs);

    std::string getInfo() const;

  private:
    int countLayer_;
    int layersLength_;
    boost::shared_array< std::shared_ptr<Shape> > shapeMatrix_;

    bool checkCross(const rectangle_t & r1, const rectangle_t & r2) const;
  };

}


#endif // MATRIX_HPP
