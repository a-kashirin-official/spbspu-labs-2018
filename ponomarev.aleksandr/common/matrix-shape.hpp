#ifndef MATRIX_SHAPE_HPP
#define MATRIX_SHAPE_HPP

#include <iostream>
#include <memory>

#include "shape.hpp"

namespace ponomarev
{
  class MatrixShape
  {
  public:

    MatrixShape();

    MatrixShape(const MatrixShape &matrixShape);

    MatrixShape(MatrixShape &&matrixShape) noexcept;

    ~MatrixShape();

    const std::shared_ptr<Shape> operator()(unsigned int row, unsigned int column) const;

    MatrixShape &operator=(const MatrixShape &rhs);

    MatrixShape &operator=(MatrixShape &&rhs) noexcept;

    friend std::ostream &operator<<(std::ostream &out, const MatrixShape &matrix);

    void addShape(const std::shared_ptr<Shape> &shape);

    size_t getNumberOfColumns() const;
    size_t getNumberOfRows() const;

    bool checkForIntersection(const std::shared_ptr<Shape> &firstShape,
      const std::shared_ptr<Shape> &secondShape) const;

  private:

    std::unique_ptr <std::shared_ptr <Shape>[]> matrix_;
    size_t numberOfColumns_;
    size_t numberOfRows_;

  };

  std::ostream &operator<<(std::ostream &out, const MatrixShape &matrix);

}

#endif

