#include "matrix.hpp"
#include <memory>
#include <stdexcept>

kahuanahil::Matrix::Matrix(const std::shared_ptr < kahuanahil::Shape > shape):
  matrixShape(nullptr),
  Lnumber_(0),
  Lsize_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Pointer empty");
  }
  addShape(shape);
}

kahuanahil::Matrix::Matrix(const kahuanahil::Matrix & matrix):
  matrixShape(new std::shared_ptr < kahuanahil::Shape > [matrix.Lnumber_ * matrix.Lsize_]),
  Lnumber_(matrix.Lnumber_),
  Lsize_(matrix.Lsize_)
{
  for (int i = 0; i < (Lnumber_ * Lsize_); ++i)
  {
    matrixShape[i] = matrix.matrixShape[i];
  }
}

kahuanahil::Matrix::Matrix(kahuanahil::Matrix && matrix):
  matrixShape(nullptr),
  Lnumber_(matrix.Lnumber_),
  Lsize_(matrix.Lsize_)
{
  matrixShape.swap(matrix.matrixShape);
  matrix.Lnumber_ = 0;
  matrix.Lsize_ = 0;
}

kahuanahil::Matrix::~Matrix()
{
  matrixShape.reset();
  matrixShape = nullptr;
  Lnumber_ = 0;
  Lsize_ = 0;
}

kahuanahil::Matrix & kahuanahil::Matrix::operator=(const kahuanahil::Matrix & matrix)
{
  if (this != & matrix)
  {
    Lnumber_ = matrix.Lnumber_;
    Lsize_ = matrix.Lsize_;
    std::unique_ptr < std::shared_ptr < kahuanahil::Shape > [] > newMatrixShape(new std::shared_ptr < kahuanahil::Shape > [Lnumber_ * Lsize_]);
    for (int i = 0; i < (Lnumber_ * Lsize_); ++i)
    {
      newMatrixShape[i] = matrix.matrixShape[i];
    }
    matrixShape.swap(newMatrixShape);
  }
  return *this;
}

kahuanahil::Matrix & kahuanahil::Matrix::operator=(kahuanahil::Matrix && matrix)
{
  if (this != & matrix)
  {
    Lnumber_ = matrix.Lnumber_;
    Lsize_ = matrix.Lsize_;
    matrixShape.reset();
    matrixShape.swap(matrix.matrixShape);
    matrix.Lnumber_ = 0;
    matrix.Lsize_ = 0;
  }
  return *this;
}

bool kahuanahil::Matrix::operator==(const kahuanahil::Matrix & matrix) const
{
  if((this->Lnumber_ != matrix.Lnumber_) || (this->Lsize_ != matrix.Lsize_))
  {
    return false;
  }
  for (int i = 0; i < (Lnumber_ * Lsize_); ++i)
  {
    if (this->matrixShape[i] != matrix.matrixShape[i])
    {
      return false;
    }
  }
  return true;
}

bool kahuanahil::Matrix::operator!=(const Matrix & matrix) const
{
  if((this->Lnumber_ != matrix.Lnumber_) || (this->Lsize_ != matrix.Lsize_))
  {
    return true;
  }
  for (int i = 0; i < (Lnumber_ * Lsize_); ++i)
  {
    if (this-> matrixShape[i] != matrix.matrixShape[i])
    {
      return true;
    }
  }
  return false;
}

std::unique_ptr < std::shared_ptr < kahuanahil::Shape > [] > kahuanahil::Matrix::operator[](const int Lnumber) const
{
  if ((Lnumber < 0) || (Lnumber >= Lnumber_))
  {
    throw std::out_of_range("Invalid Layer index");
  }
  std::unique_ptr < std::shared_ptr < kahuanahil::Shape > [] > layer(new std::shared_ptr < kahuanahil::Shape > [Lsize_]);
  for (int i = 0; i < Lsize_; ++i)
  {
    layer[i] = matrixShape[Lnumber * Lsize_ + i];
  }
  return layer;
}

void kahuanahil::Matrix::addShape(const std::shared_ptr < kahuanahil::Shape > shape)
{
  if (Lnumber_ == 0)
  {
    try
    {
    std::unique_ptr < std::shared_ptr < kahuanahil::Shape > [] > newMatrixShape(new std::shared_ptr < kahuanahil::Shape > [1]);
    Lnumber_++;
    Lsize_++;
    matrixShape.swap(newMatrixShape);
    matrixShape[0] = shape;
    }
    catch(const std::bad_alloc &a)
    {
      throw;
    }
  }
  else
  {
    bool addedShapes = false;
    for (int i = 0; !addedShapes; i++)
    {
      for (int j = 0; j < Lsize_; j++)
      {
        if(!matrixShape[i * Lsize_ + j])
        {
          matrixShape[i * Lsize_ + j] = shape;
          addedShapes = true;
          break;
        }
        else
        {
          if (this->Checkforoverlap(i * Lsize_ + j, shape))
          {
            break;
          }
        }
        if (j == (Lsize_ - 1))
        { 
          try{
          std::unique_ptr < std::shared_ptr < kahuanahil::Shape > [] > newMatrixShape(new std::shared_ptr < kahuanahil::Shape > [Lnumber_ * (Lsize_ + 1)]);
          Lsize_++;
         
          for (int n = 0; n < Lnumber_; n++)
          {
            for (int m = 0; m < (Lsize_ - 1); m++)
            {
              newMatrixShape[n * Lsize_ +m] = matrixShape[n * (Lsize_ - 1) + m];
            }
            newMatrixShape[(n + 1) * Lsize_ - 1] = nullptr;
          }
          newMatrixShape[(i + 1) * Lsize_ - 1] = shape;
          matrixShape.swap(newMatrixShape);
          addedShapes = true;
          break;
          }
          catch(const std::bad_alloc &a)
          {
            throw;
          }
        }
      }
      if ((i == (Lnumber_ - 1)) && !addedShapes)
      {
        try
        {
        std::unique_ptr < std::shared_ptr < kahuanahil::Shape > [] > newMatrixShape(new std::shared_ptr < kahuanahil::Shape > [(Lnumber_ + 1) * Lsize_]);
        Lnumber_++;
        for (int n = 0; n < ((Lnumber_ - 1 ) * Lsize_); n++)
        {
          newMatrixShape[n] = matrixShape[n];
        }
        for (int m = ((Lnumber_ - 1) * Lsize_); m < (Lnumber_ * Lsize_); m++)
        {
          newMatrixShape[m] = nullptr;
        }
        newMatrixShape[(Lnumber_ - 1) * Lsize_] = shape;
        matrixShape.swap(newMatrixShape);
        addedShapes = true;
        }
        catch(const std::bad_alloc &a)
        {
          throw;
        }
      }
    }
  }
}

bool kahuanahil::Matrix::Checkforoverlap(const int i, std::shared_ptr < kahuanahil::Shape > shape) const noexcept
{
  kahuanahil::rectangle_t nShapeFrameRect = shape->getFrameRect();
  kahuanahil::rectangle_t mShapeFrameRect = matrixShape[i]->getFrameRect();
  kahuanahil::point_t newShapePoints[4] = {
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0},
    {nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0}
  };

  kahuanahil::point_t matrixShapePoints[4] = {
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0},
    {mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0}
  };

  for (int i = 0; i < 4; ++i)
  {
    if (((newShapePoints[i].x >= matrixShapePoints[0].x) && (newShapePoints[i].x <= matrixShapePoints[2].x)
      && (newShapePoints[i].y >= matrixShapePoints[3].y) && (newShapePoints[i].y <= matrixShapePoints[1].y)) 
        || ((matrixShapePoints[i].x >= newShapePoints[0].x) && (matrixShapePoints[i].x <= newShapePoints[2].x)
          && (matrixShapePoints[i].y >= newShapePoints[3].y) && (matrixShapePoints[i].y <= newShapePoints[1].y)))
    {
      return true;
    }
  }
  return false;
}
