#ifndef SHAPES_PARTITION_HPP
#define SHAPES_PARTITION_HPP

#include <memory>

#include "shape.hpp"

namespace pashin {
  class ShapesPartition {
  public:
    ShapesPartition();
    
    ShapesPartition& operator=(const ShapesPartition& rhs);
    ShapesPartition& operator=(ShapesPartition&& rhs);
    std::unique_ptr<Shape*[]> operator[](int pos) const;
    Shape* getShape(int row, int column) const;
    int num_rows() const;
    int num_columns() const;
    void addShape(Shape& shape);
    void removeShape(Shape* shape);
    
  private:
    int num_rows_;
    int num_columns_;
    std::unique_ptr<pashin::Shape*[]> matrix_;
    
    bool areIntersecting(const Shape* shape_1, const Shape* shape_2) const;
    Shape** cell(int row, int column) const;
    void addRow();
    void addColumn();
  };
}

#endif  // SHAPES_PARTITION_HPP
