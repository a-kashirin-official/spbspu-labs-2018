#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include <ostream>
#include "composite-shape.hpp"
#include "base-types.hpp"
#include "shape.hpp"


namespace lobanova {

  class Matrix {
  public:
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

    Matrix(const Matrix &matrix);

    Matrix();

    ~Matrix();

    void add(Shape *shape);

    const Shape **operator[](int index) const;

    void clear();

    int getWidth() const noexcept;

    int getHeight() const noexcept;

    int getSizeOfLayer(int i) const;


  private:
    Shape **elements_;
    int width_ = 0;
    int height_ = 0;
    int *sizeOfLayer_;

    int widthCapacity_ = 1;
    int heightCapacity_ = 1;

    void doubleWidthCapacity();

    void doubleHeightCapacity();

    void addToLayer(int i, Shape *shape);

    static bool overlapping(const Shape *shape1, const Shape *shape2) noexcept;

  };


}


#endif //MATRIX_HPP
