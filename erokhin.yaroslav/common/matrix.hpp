//
// Created by Yaroslav on 28.05.2018.
//

#ifndef LABA1_MATRIX_HPP
#define LABA1_MATRIX_HPP

#include <memory>
#include <iostream>
#include "shape.hpp"

namespace erokhin
{
    class Matrix
    {
    public:
        Matrix();
        Matrix(const Matrix & rhs);
        Matrix(Matrix && rhs);
        ~Matrix() = default;
        Matrix& operator=(const Matrix & rhs);
        Matrix& operator=(Matrix && rhs);
        std::unique_ptr<std::shared_ptr<Shape>[]> operator[](const unsigned int index) const;
        void add(const std::shared_ptr<Shape> figure);
        unsigned int getRows() const;
        unsigned int getColumns() const;
        void viewMap() const;
    private:
        std::unique_ptr<std::shared_ptr<Shape> []> map_;
        unsigned int rows_;
        unsigned int columns_;
        inline bool controlCross(const std::shared_ptr<Shape> figure1, const std::shared_ptr<Shape> figure2);
    };
}
#endif //LABA1_MATRIX_HPP
