#include "matrix.hpp"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <cmath>

bool kudryavtseva::Matrix::intersection(const kudryavtseva::Shape *obj1,const kudryavtseva::Shape *obj2)
{
  if((obj1 == nullptr)||(obj2 == nullptr))
  {
    return false;
  }
  return ((std::abs(obj1->getFrameRect().pos.x-obj2->getFrameRect().pos.x) < (obj1->getFrameRect().height/2.0 + obj2->getFrameRect().height/2.0))
      && ((std::abs(obj1->getFrameRect().pos.y-obj2->getFrameRect().pos.y) < (obj1->getFrameRect().width/2.0 + obj2->getFrameRect().width/2.0))));
}

kudryavtseva::Matrix::Matrix(const kudryavtseva::Shape *shape):
  shapes_(new const kudryavtseva::Shape*[1]),
  line_(1),
  column_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Object doesn't exist");
  }
  shapes_[0]=shape;
}

kudryavtseva::Matrix::Matrix (const kudryavtseva::Matrix &object):
  shapes_ (new const kudryavtseva::Shape*[object.getARow()*object.getAColumn()]),
  line_ (object.getARow()),
  column_ (object.getAColumn())
{
  for (size_t j = 0; j < (line_*column_); ++j)
  {
    shapes_[j] = object.shapes_[j];
  }
}

void kudryavtseva::Matrix::add(const kudryavtseva::Shape *shape)
{
  if(shape == nullptr)
  {
    throw std::invalid_argument("Address doesn't exist");
  }
  for (size_t j=0; j<column_*line_; j++)
  {
    if(shapes_[j]==shape)
    {
      throw std::invalid_argument("Matrix already contain this shape");
    }
  }
  size_t j=line_, i=column_-1;
  while((j!=0)&&(!intersection(shapes_[(j-1)*column_+i], shape)))
  {
    while(i!=0)
    {
      i--;
    }
    j--;
  }
  if(j==line_)
  {
    line_++;
    std::unique_ptr <const kudryavtseva::Shape*[]> new_matrix(new const kudryavtseva::Shape*[column_*line_]);
    j=0;
    while(j<(line_-1)*column_)
    {
      new_matrix[j]=shapes_[j];
      j++;
    }
    new_matrix[j++]=shape;
    while(j<column_*line_)
    {
      new_matrix[j++]=nullptr;
    }
    shapes_.swap(new_matrix);
  }
  else
  {
    i=0;
    while((i<column_)&&(shapes_[j*line_+i]!=nullptr))
    {
      i++;
    }
    if(i==column_)
    {
      ++column_;
      std::unique_ptr <const kudryavtseva::Shape*[]> new_matrix(new const kudryavtseva::Shape*[column_*line_]);
      i=0;
      size_t k=0;
      while(i<column_*line_)
      {
        if((i+1)%column_==0)
        {
          if((j+1)==((i+1)/column_))
          {
            new_matrix[i]=shape;
          }
          else
          {
            new_matrix[i]=nullptr;
          }
        }
        else
        {
          new_matrix[i]=shapes_[k++];
        }
        i++;
      }
      shapes_.swap(new_matrix);
    }
    else
    {
      shapes_[j*column_+i]=shape;
    }
  }
}

const kudryavtseva::Shape **kudryavtseva::Matrix::operator [](const size_t &i) const
{
  if (i>line_)
  {
    throw std::invalid_argument("Invalid value");
  }
  return(shapes_.get()+i*column_);
}

size_t kudryavtseva::Matrix::getARow() const
{
  return line_;
}

size_t kudryavtseva::Matrix::getAColumn() const
{
  return column_;
}

const kudryavtseva::Shape* kudryavtseva::Matrix::getShape(const size_t line, const size_t column) const
{
  if (line>line_)
  {
    throw std::invalid_argument("There are no shapes in this row");
  }
  if (column>column_)
  {
    throw std::invalid_argument("There are no shapes in this column");
  }
  return shapes_[line*column_+column];
}

void kudryavtseva::Matrix::print() const
{
  std::cout<<"There are "<<line_<<" lines and "<<column_<<" columns\n";
  for (size_t j=0; j<line_; j++)
  {
    std::cout<<"Layer "<<(j+1)<<":\n";
    for (size_t i=0; i<column_; i++)
    {
      if (shapes_[j*column_+i]!=nullptr)
      {
        std::cout<<"Position "<<(i+1)<<":\n";
        shapes_[j*column_+i]->printf();
      }
    }
  }
}
