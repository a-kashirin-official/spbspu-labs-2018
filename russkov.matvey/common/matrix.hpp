//
// Created by matvey on 28.05.18.
//

#ifndef A3_MATRIX_HPP
#define A3_MATRIX_HPP
#include "shape.hpp"
#include "composite-shape.hpp"
#include <memory>

namespace russkov
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const std::shared_ptr<russkov::Shape> shape_ptr);
    Matrix(const russkov::Matrix & obj);
    Matrix(russkov::Matrix && obj);
    ~Matrix();

    Matrix &operator =(const russkov::Matrix & obj);
    Matrix &operator =(russkov::Matrix && obj);
    std::unique_ptr<std::shared_ptr<russkov::Shape>[]> operator [](const size_t index);

    void addShape(const std::shared_ptr <russkov::Shape> shape_ptr);

  private:
    std::unique_ptr<std::shared_ptr<russkov::Shape>[]> matrix_;
    size_t layersNumber_;
    size_t layersSize_;

    bool checkOverlapping(const int index, std::shared_ptr<russkov::Shape> obj) const;
  };
}

#endif //A3_MATRIX_HPP
