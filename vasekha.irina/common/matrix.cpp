#include "matrix.hpp"
#include <memory>
#include <stdexcept>

vasekha::Matrix::Matrix() noexcept:
  elements_(nullptr),
  cols_(0),
  rows_(0)
{}

vasekha::Matrix::Matrix(const Matrix & matrix):
  elements_((matrix.cols_*matrix.rows_)?std::make_unique<Shape::ptr_shape[]>(matrix.cols_*matrix.rows_):nullptr),
  cols_(matrix.cols_),
  rows_(matrix.rows_)
{
  for(size_t i=0;i<cols_*rows_;++i)
  {
    elements_[i]=matrix.elements_[i];
  }
}

vasekha::Matrix::Matrix(Matrix && matrix) noexcept:
  elements_(std::move(matrix.elements_)),
  cols_(matrix.cols_),
  rows_(matrix.rows_)
{
  matrix.cols_=0;
  matrix.rows_=0;
}

vasekha::Matrix & vasekha::Matrix::operator=(const Matrix & matrix)
{
  if(this==&matrix)
  {
    return *this;
  }
  elements_=(matrix.cols_*matrix.rows_)?std::make_unique<Shape::ptr_shape[]>(matrix.cols_*matrix.rows_):nullptr;
  for(size_t i=0; i<matrix.cols_*matrix.rows_;++i)
  {
    elements_[i]=matrix.elements_[i];
  } 
  cols_=matrix.cols_;
  rows_=matrix.rows_;
  return *this;
}

vasekha::Matrix & vasekha::Matrix::operator=(Matrix && matrix) noexcept
{
  if(this==&matrix)
  {
    return *this;
  }
  elements_=std::move(matrix.elements_);
  cols_=matrix.cols_;
  rows_=matrix.rows_;
  matrix.cols_=0;
  matrix.rows_=0;
  return *this;
}

std::unique_ptr<vasekha::Shape::ptr_shape[]> vasekha::Matrix::operator[](size_t index) const
{
  if(index>=rows_)
  {
    throw std::out_of_range("Invalid index");
  }
  std::unique_ptr<Shape::ptr_shape[]> matrix_layer=std::make_unique<Shape::ptr_shape[]>(cols_);
  for(size_t i=0;i<cols_;++i)
  {
    matrix_layer[i]=elements_[index*cols_+i];
  }
  return matrix_layer;
}

bool vasekha::Matrix::checkOverlapping(const size_t index, Shape::ptr_shape shape) const noexcept
{
  rectangle_t el_frame=elements_[index]->getFrameRect();
  rectangle_t sh_frame=shape->getFrameRect();
  point_t el_left_bottom = {el_frame.pos.x-el_frame.width/2.0,el_frame.pos.y-el_frame.height/2.0};
  point_t el_right_top ={el_frame.pos.x+el_frame.width/2.0,el_frame.pos.y+el_frame.height/2.0}; 
  point_t sh_left_bottom = {sh_frame.pos.x-sh_frame.width/2.0,sh_frame.pos.y-sh_frame.height/2.0};
  point_t sh_right_top = {sh_frame.pos.x+sh_frame.width/2.0,sh_frame.pos.y+sh_frame.height/2.0};
  return !(el_left_bottom.x>sh_right_top.x||el_right_top.x<sh_left_bottom.x
    ||sh_left_bottom.y>el_right_top.y||sh_right_top.y<el_left_bottom.y);
}

void vasekha::Matrix::add(const Shape::ptr_shape & shape)
{
  if(!shape)
  {
    throw std::invalid_argument("Invalid shape");
  }
  if(!rows_)
  {
    elements_= std::make_unique<Shape::ptr_shape[]>(1);
    elements_[0]=shape;
    cols_=1;
    rows_=1;
    return;
  }
  size_t j=0;
  size_t cur_cols=0;
  size_t cur_rows=0;
  bool isOverlapped=false;
  for(size_t i=rows_-1; i<rows_ && !isOverlapped; --i)
  {
    cur_cols=j;
    for(; j<cols_; ++j)
    {
      if(!elements_[i*cols_+j])
      {
        break;
      }
      if(checkOverlapping(i*cols_+j,shape))
      {
        if(i==rows_-1)
        {
          std::unique_ptr<Shape::ptr_shape[]> new_elements=std::make_unique<Shape::ptr_shape[]>(cols_*rows_+cols_);
          for(size_t m=0;m<rows_;++m)
          {
            for(size_t n=0;n<cols_;++n)
            {
              new_elements[m*cols_+n]=elements_[m*cols_+n];
            }
          }
          elements_=std::move(new_elements);
          elements_[rows_*cols_]=shape;
          rows_++;
          return;
        }
        isOverlapped=true;
        j=cur_cols;
        cur_rows=i;
        break;
      }
    }
  }

  if(isOverlapped)
  {
    cur_rows++;
  }
  if(cols_>j)
  {
    elements_[cur_rows*cols_+j]=shape;
    return;
  }
  else
  {
    ++cols_;
    std::unique_ptr<Shape::ptr_shape[]> new_elements=std::make_unique<Shape::ptr_shape[]>(cols_*rows_);
    for(size_t m=0;m<rows_;++m)
    {
      for(size_t n=0;n<cols_-1;++n)
      {
        new_elements[m*cols_+n]=elements_[m*(cols_-1)+n];
      }
    }
    elements_=std::move(new_elements);
    elements_[cur_rows*cols_+cols_-1]=shape;
    return;
  }
}

size_t vasekha::Matrix::getCols() const noexcept
{
  return cols_;
}

size_t vasekha::Matrix::getRows() const noexcept
{
  return rows_;
}
