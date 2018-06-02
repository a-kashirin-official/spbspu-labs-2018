#include "matrix.hpp"
#include <cmath>
#include <iostream>

mihajlov::Matrix::Matrix():
  parts_(nullptr),
  layerCount_(0),
  layerSize_(0)
{
}

mihajlov::Matrix::Matrix(const Matrix& matrix):
  parts_(new std::shared_ptr<Shape>[matrix.layerCount_ * matrix.layerSize_]),
  layerCount_(matrix.layerCount_),
  layerSize_(matrix.layerSize_)
{
  for (int i = 0; i < layerCount_ * layerSize_; i++)
  {
    parts_[i] = matrix.parts_[i];
  }
}

mihajlov::Matrix::Matrix(Matrix&& matrix):
  parts_(std::move(matrix.parts_)),
  layerCount_(matrix.layerCount_),
  layerSize_(matrix.layerSize_)
{
  matrix.layerCount_ = 0;
  matrix.layerSize_ = 0;
}

mihajlov::Matrix& mihajlov::Matrix::operator=(const Matrix& matrix)
{
  if (this == &matrix)
  {
    return *this;
  }

  parts_.reset(new std::shared_ptr<Shape>[matrix.layerCount_ * matrix.layerSize_]);
  layerCount_ = matrix.layerCount_;
  layerSize_ = matrix.layerSize_;
  for (int i = 0; i < layerCount_ * layerSize_; i++)
  {
    parts_[i] = matrix.parts_[i];
  }
  return *this;
}

mihajlov::Matrix& mihajlov::Matrix::operator=(Matrix&& matrix)
{
  parts_ = std::move(matrix.parts_);
  layerCount_ = matrix.layerCount_;
  layerSize_ = matrix.layerSize_;
  for (int i = 0; i < layerCount_ * layerSize_; i++)
  {
    parts_[i] = matrix.parts_[i];
  }
  return *this;
}

std::unique_ptr<std::shared_ptr<mihajlov::Shape>[]> mihajlov::Matrix::operator[](const int index)
{
  if (index >= layerCount_ || index < 0)
  {
    throw std::out_of_range("Out of range! ");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> array(new std::shared_ptr<Shape>[layerSize_]);

  for (int i = 0; i < layerCount_; i++)
  {
    array[i] = parts_[index * layerCount_ * i];
  }
  return array;
}

void mihajlov::Matrix::addShape(const std::shared_ptr<mihajlov::Shape> figure)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("It can not be empty figure!");
  }
  if ((layerCount_ == 0) && (layerSize_ == 0))
  {
    parts_.reset(new std::shared_ptr<Shape>[1]);
    layerCount_ = 1;
    layerSize_ = 1;
    parts_[0] = figure;
    return;
  }
  int count1 = 0;
  for (int i = 0; i < layerCount_; i++)
  {
    int count2 = 0;
    for (int j = 0; j < layerSize_; j++)
    {
      if (parts_[i * layerSize_ + j] == nullptr)
      {
        parts_[i * layerSize_ + j] = figure;
        return;
      }
      if (controlCross(parts_[i * layerSize_ + j], figure))
      {
        count2 = j + 1;
        break;
      }
      count2 = j + 1;
    }
    if (count2 == layerSize_)
    {
      std::unique_ptr<std::shared_ptr<Shape> []> newmap(new std::shared_ptr<Shape>[layerCount_ * (layerSize_ + 1)]);
      for (int m = 0; m < layerCount_; m++)
      {
        for (int n = 0; n < layerSize_; n++)
        {
          newmap[m * layerSize_ + n + m] = parts_[m * layerSize_ + n];
        }
      }
      layerSize_++;
      newmap[(i + 1) * layerSize_ - 1] = figure;
      parts_ = std::move(newmap);
      return;
    }
    count1 = i + 1;
  }
  if (count1 == layerCount_)
  {
    std::unique_ptr<std::shared_ptr<Shape> []> newmap(new std::shared_ptr<Shape>[(layerCount_ + 1) * layerSize_]);
    for (int i = 0; i < layerCount_ * layerSize_; i++)
    {
      newmap[i] = parts_[i];
    }
    newmap[layerCount_ * layerSize_] = figure;
    layerCount_++;
    parts_ = std::move(newmap);
  }
}


int mihajlov::Matrix::getLayersCount() const
{
  return layerCount_;
}

int mihajlov::Matrix::getLayerSize() const
{
  return layerSize_;
}

void mihajlov::Matrix::view() const
{
  for (int i = 0; i < layerCount_; i++)
  {
    for (int j = 0; j < layerSize_; j++)
    {
      if (parts_[i * layerSize_ + j] != nullptr)
      {
        parts_[i * layerSize_ + j]->printName();
      }
    }
    std::cout << std::endl;
  }
}

bool mihajlov::Matrix::controlCross(const std::shared_ptr<Shape> shape1, const std::shared_ptr<Shape> shape2)
{
  {
    if (shape1 == nullptr || shape2 == nullptr)
    {
      throw std::invalid_argument("Shape expected, found nullptr !");
    }
    mihajlov::rectangle_t frame1 = shape1->getFrameRect();
    mihajlov::rectangle_t frame2 = shape2->getFrameRect();
    return ((fabs(frame1.pos.x - frame2.pos.x) < frame1.width / 2 + frame2.width / 2) &&
            fabs(frame1.pos.y - frame2.pos.y) < frame1.height / 2 + frame2.height / 2);
  }
}
