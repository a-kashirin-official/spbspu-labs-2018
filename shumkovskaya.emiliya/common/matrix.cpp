#include "matrix.hpp"
#include <stdexcept>

using namespace shumkovskaya;

shumkovskaya::Matrix::Matrix(shumkovskaya::CompositeShape shapes):
  amount_(0),
  size_(0)
{
  if (shapes.getAmount()==0)
  {
    throw std::invalid_argument("Empty composite shape");
  }
  else
  {
    size_ = 1;
    amount_ = 1;
    std::unique_ptr<std::shared_ptr<shumkovskaya::Shape>[]> temp_array(
      new std::shared_ptr<shumkovskaya::Shape>[1]);
    temp_array[0] = shapes[0];
    shapes_.swap(temp_array);
    for (int i = 1; i < shapes.getAmount(); i++)
    {
      addShape(shapes[i]);
    }
  }
}

shumkovskaya::Matrix::Matrix(const shumkovskaya::Matrix & rhs) :
  amount_(rhs.amount_),
  size_(rhs.size_)
{
  std::unique_ptr<std::shared_ptr<shumkovskaya::Shape>[]> temp_array
    (new std::shared_ptr<shumkovskaya::Shape>[amount_ * size_]);
  for (int i = 0; i < amount_; i++)
  {
    temp_array[i] = rhs.shapes_[i];
  }
  shapes_.swap(temp_array);
}

shumkovskaya::Matrix & Matrix::operator = (const shumkovskaya::Matrix & rhs)
{
  amount_ = rhs.amount_;
  size_ = rhs.size_;
  std::unique_ptr<std::shared_ptr<shumkovskaya::Shape>[]> temp_array
    (new std::shared_ptr<shumkovskaya::Shape>[amount_ * size_]);
  for (int i = 0; i < amount_; i++)
  {
    temp_array[i] = rhs.shapes_[i];
  }
  shapes_.swap(temp_array);
  return *this;
}

std::shared_ptr<shumkovskaya::Shape> * shumkovskaya::Matrix::operator[](int index) const
{
  if (index > amount_)
  {
    throw std::invalid_argument("index out of range");
  }

  return & shapes_[index * size_];
}

bool shumkovskaya::Matrix::checkIntersection(std::shared_ptr<shumkovskaya::Shape> shape, const int index) const noexcept

{
  bool flag = false;
  double bottom1 = shape->getFrameRect().pos.y - (shape->getFrameRect().height / 2);
  double top1 = shape->getFrameRect().pos.y + shape->getFrameRect().height / 2;
  double left1 = shape->getFrameRect().pos.x - shape->getFrameRect().width / 2;
  double right1 = shape->getFrameRect().pos.x + shape->getFrameRect().width / 2;
  int i = index * size_;
  while (shapes_[i]!=nullptr && i < (index + 1)  * size_ )
  {
    double bottom2 = shapes_[i]->getFrameRect().pos.y - shapes_[i]->getFrameRect().height / 2;
    double top2 = shapes_[i]->getFrameRect().pos.y + shapes_[i]->getFrameRect().height / 2;
    double left2 = shapes_[i]->getFrameRect().pos.x - shapes_[i]->getFrameRect().width / 2;
    double right2 = shapes_[i]->getFrameRect().pos.x + shapes_[i]->getFrameRect().width / 2;
    if (((bottom1 <= top2 && top2 <= top1) || (bottom2 <= top1 && top1 <= top2))  
      && ((left1 <= left2 && left2 <= right1) || (left2 <= left1 && left1 <= right2)))
    {
      flag = true;
      break;
    }
    i++;
  }
  return flag;
}

void shumkovskaya::Matrix::addLayer(std::shared_ptr<shumkovskaya::Shape> shape)
{
  std::unique_ptr<std::shared_ptr<shumkovskaya::Shape>[]> temp_array(
      new std::shared_ptr<shumkovskaya::Shape>[size_ * (amount_ + 1)]);
  for (int i = 0; i < amount_ * size_; i++)
  {
    temp_array[i] = shapes_[i];
  }
  temp_array[amount_ * size_] = shape;
  shapes_.swap(temp_array);
  amount_++;
}

void shumkovskaya::Matrix::addShape(std::shared_ptr<shumkovskaya::Shape> shape) noexcept
{
  int layer_num = 0;
  while (checkIntersection(shape, layer_num) && layer_num < amount_ - 1)
  {
    layer_num++;
  }
  if (layer_num == amount_ - 1 && checkIntersection(shape, layer_num))
  {
    addLayer(shape);
  }
  else 
  {
    int i = layer_num * size_ ;
    while ((shapes_[i] != nullptr) && (i <= (layer_num + 1) * size_ - 1))
    {
      i++;
    }
    if ((i < (layer_num + 1) * size_)  &&  (shapes_[i] == nullptr))
    {
      shapes_[i] = shape;
    }
    else
    {
      std::unique_ptr<std::shared_ptr<shumkovskaya::Shape>[]> temp_array(
          new std::shared_ptr<shumkovskaya::Shape>[(size_ + 1) * amount_]);
      for (int i = 0; i < amount_; i++)
      {
        int j = 0;
        while (shapes_[j] != nullptr && j < size_)
        {
          temp_array[i * (size_ + 1) + j] = shapes_[i * size_ + j];
          j++;
        }
      }
      temp_array[(layer_num + 1) * (size_ + 1) - 1] = shape;
      shapes_.swap(temp_array);
      size_++;
    }
  }
}

int shumkovskaya::Matrix::getAmount()
{
  return amount_;
}

int shumkovskaya::Matrix::getSize()
{
  return size_;
}
