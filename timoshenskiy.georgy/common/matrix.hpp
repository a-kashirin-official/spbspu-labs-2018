//
//  matrix.hpp
//  A4 
//
//  Created by Георгий Тимошенский on 27.05.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <memory>
#include <sstream>
#include "shape.hpp"

namespace timoshenskiy
{
  class Matrix
  {
  public:
    Matrix(const std::shared_ptr < timoshenskiy::Shape > shape);
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix);
  
    Matrix & operator = (const Matrix & matrix);
    bool operator == (const Matrix & matrix) const;
    bool operator != (const Matrix & matrix) const;
    std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] > operator [] (const int layerNumber) const;

    void addShape(const std::shared_ptr < timoshenskiy::Shape > shape) ;
    std::string printInformation(const Shape & shape) const;
    bool areIntersected(const int index, std::shared_ptr < timoshenskiy::Shape > shape) const ;
  private:
    std::unique_ptr < std::shared_ptr < timoshenskiy::Shape > [] > matrixShapes_;
    int layersNumber_;
    int layerSize_;
  };
}
#endif 
