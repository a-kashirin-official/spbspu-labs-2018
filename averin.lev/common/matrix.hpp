#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace averin
{ 
class Matrix
{
public:
  
  Matrix(const std::shared_ptr<Shape>& shape);
  
  Matrix();
  
  Matrix & operator=(const Matrix& matrix);
  
  void addShape(const std::shared_ptr<Shape>& shape);
  
  int getRows() const;
  
  int getColumns() const;
  
  void printInfo() const;
    
private:
  
  bool checkIntersection(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2);
  
  std::unique_ptr<std::shared_ptr<Shape>[]> matrix_;
  
  int columns_;
  
  int rows_;
};
}
#endif
