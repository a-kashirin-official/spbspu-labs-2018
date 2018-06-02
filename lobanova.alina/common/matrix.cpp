#include "matrix.hpp"
#include <algorithm>
#include <cmath>


using namespace lobanova;

Matrix::Matrix()
{
  elements_ = new Shape *[widthCapacity_ * heightCapacity_];
  sizeOfLayer_ = new int[heightCapacity_]();
}


void Matrix::addToLayer(int i, Shape *shape)
{
  if (sizeOfLayer_[i] == widthCapacity_) {
    doubleWidthCapacity();
  }
  (*this)[i][sizeOfLayer_[i]++] = shape;
  width_ = std::max(sizeOfLayer_[i], width_);
}

void Matrix::add(Shape *shape)
{

  if (shape == nullptr) {
    throw std::invalid_argument("Null pointer!");
  }

  for (int i = 0; i < height_; ++i) {
    bool good = true;
    for (int j = 0; j < sizeOfLayer_[i]; ++j) {
      if (not overlapping(shape, (*this)[i][j])) {
        good = false;
        break;
      }
    }

    if (good) {
      addToLayer(i, shape);
      return;
    }
  }

  if (height_ == heightCapacity_) {
    doubleHeightCapacity();
  }

  addToLayer(height_++, shape);

}

void Matrix::doubleWidthCapacity()
{
  int newWidthCapacity = 2 * widthCapacity_;
  auto newElements = new Shape *[heightCapacity_ * newWidthCapacity];

  for (int i = 0; i < height_; ++i) {

    std::copy(elements_ + widthCapacity_ * i,
              elements_ + widthCapacity_ * i + sizeOfLayer_[i],
              newElements + newWidthCapacity * i);
  }
  delete[] elements_;
  elements_ = newElements;
  widthCapacity_ = newWidthCapacity;
}

void Matrix::doubleHeightCapacity()
{
  int newHeightCapacity = 2 * heightCapacity_;
  auto newElements = new Shape *[widthCapacity_ * newHeightCapacity];
  auto *newSizes = new int[newHeightCapacity]();
  std::copy(elements_, elements_ + height_ * widthCapacity_, newElements);
  std::copy(sizeOfLayer_, sizeOfLayer_ + height_, newSizes);
  delete[] elements_;
  delete[] sizeOfLayer_;
  elements_ = newElements;
  sizeOfLayer_ = newSizes;
  heightCapacity_ = newHeightCapacity;
}

const Shape **Matrix::operator[](int index) const
{

  if (index > height_) {
    throw std::out_of_range("Index out of range.");
  }
  return const_cast<const Shape **>(elements_ + index * widthCapacity_);

}

void Matrix::clear()
{
  for (int i = 0; i < height_; ++i) {
    sizeOfLayer_[i] = 0;
  }
  height_ = 0;
  width_ = 0;
}


bool Matrix::overlapping(const Shape *shape1, const Shape *shape2) noexcept
{
  rectangle_t r1 = shape1->getFrameRect();
  rectangle_t r2 = shape2->getFrameRect();
  return ((std::abs(r1.pos.x - r2.pos.x) > (r1.width + r2.width))
          or (std::abs(r1.pos.y - r2.pos.y) > (r1.height + r2.height)));
}

int Matrix::getWidth() const noexcept
{
  return width_;
}

int Matrix::getHeight() const noexcept
{
  return height_;
}

int Matrix::getSizeOfLayer(int i) const
{

  if (i > height_) {
    throw std::out_of_range("Index of layer out of range.");
  }
  return sizeOfLayer_[i];
}

Matrix::Matrix(const Matrix &matrix)
{
  elements_ = new Shape *[matrix.heightCapacity_ * matrix.widthCapacity_];
  std::copy(matrix.elements_, matrix.elements_ + matrix.heightCapacity_ * matrix.widthCapacity_, elements_);
  height_ = matrix.height_;
  width_ = matrix.width_;
  widthCapacity_ = matrix.widthCapacity_;
  heightCapacity_ = matrix.heightCapacity_;
  sizeOfLayer_ = new int[width_];
  std::copy(matrix.sizeOfLayer_, matrix.sizeOfLayer_ + width_, sizeOfLayer_);
}

namespace lobanova {
  std::ostream &operator<<(std::ostream &out, const Matrix &m)
  {
    out << "--------" << std::endl;
    for (int i = 0; i < m.getHeight(); i++) {
      for (int j = 0; j < m.getSizeOfLayer(i); j++) {
        rectangle_t rect = m[i][j]->getFrameRect();
        out << "[" << "{" << rect.pos.x << ", " << rect.pos.y << "} " <<
            rect.height << ", " << rect.width << "]\t";

      }
      out << std::endl;
    }
    out << "--------" << std::endl;
    return out;
  }

  Matrix::~Matrix()
  {
    delete[] elements_;
    delete[] sizeOfLayer_;
    elements_ = nullptr;
    sizeOfLayer_ = nullptr;
  }
}
