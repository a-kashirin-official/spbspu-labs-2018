#include "matrix.hpp"
#include <cmath>

maikenova::Matrix::Matrix() :
  size_(0),
  layNum_(0),
  array_(new Shape*[0]),
  layer_(new size_t[0])
{
}

maikenova::Matrix::~Matrix()
{
  array_.reset();
  layer_.reset();
}

maikenova::Matrix::Matrix(std::initializer_list <Shape*> shapes)
{
  std::initializer_list<Shape*>::const_iterator iter;
  for (iter = shapes.begin(); iter != shapes.end(); iter++)
  {
    if (* iter == nullptr)
    {
      throw std::invalid_argument("No shapes were added.");
    }
  }
  if (shapes.size() == 0)
  {
    throw std::invalid_argument("The list is empty.");
  }
  iter = shapes.begin();
  array_ = boost::shared_array<Shape*>{ new Shape*[1] };
  layer_ = boost::shared_array<size_t>{ new size_t[1] };
  array_[0] = *iter;
  layer_[0] = 1;
  size_ = 1;
  layNum_ = 1;
  iter++;
  for (;iter != shapes.end(); iter++)
  {
    addShape(*iter);
  }
}

maikenova::Matrix::Matrix(const Matrix & mtrx) :
  size_(mtrx.getSize()),
  layNum_(mtrx.getLayerNum()),
  array_(new Shape*[mtrx.getSize()]),
  layer_(new size_t[mtrx.getLayerNum()])

{
  for (size_t i = 0;i < size_; i++)
  {
    array_[i] = mtrx.array_[i];
  }
  for (size_t i = 0;i < layNum_; i++)
  {
    layer_[i] = mtrx.layer_[i];
  }
}

maikenova::Matrix& maikenova::Matrix::operator=(const Matrix & mtrx)
{
  if (this != & mtrx)
  {
    boost::shared_array <Shape*> tempArray{ new Shape*[mtrx.getSize()] };
    boost::shared_array <size_t> tempLay{ new size_t[mtrx.getLayerNum()] };
    for (size_t i = 0;i < mtrx.getSize();i++)
    {
      tempArray[i] = mtrx.array_[i];
    }
    for (size_t i = 0;i < mtrx.getLayerNum(); i++)
    {
      tempLay[i] = mtrx.layer_[i];
    }
    size_ = mtrx.getSize();
    layNum_ = mtrx.getLayerNum();
    array_.reset();
    layer_.reset();
    array_ = tempArray;
    layer_ = tempLay;
  }
  return *this;
}

void maikenova::Matrix::addShape(Shape* shape)
{
  size_t line;
  size_t pos = 0;
  line = searchPos(shape);
  if (line == layNum_) //new array of layers
  {
    boost::shared_array <size_t> tempLay{ new size_t[layNum_ + 1] };
    for (size_t i = 0;i < layNum_; i++)
    {
      tempLay[i] = layer_[i];
    }
    tempLay[layNum_] = 0;
    layer_.reset(new size_t[layNum_ + 1]);
    layer_ = tempLay;
    layNum_++;
  }
  for (size_t i = 0; i < line; i++)
  {
    pos += layer_[i];
  }
  pos += layer_[line];

  boost::shared_array <Shape*> tempArray{new Shape*[size_+1]};
  for (size_t i = 0; i < pos; i++)
  {
    tempArray[i] = array_[i];
  }
  for (size_t i = pos + 1; i < size_ + 1; i++)
  {
    tempArray[i] = array_[i-1];
  }
  tempArray[pos] = shape;
  array_.reset(new Shape*[size_+1]);
  array_ = tempArray;
  layer_[line]++;
  size_++;
}

maikenova::Matrix maikenova::Matrix::createMatrix(maikenova::CompositeShape& compShape)
{
  if (compShape.getAmount() < 1)
  {
    throw std::invalid_argument("There are no shapes in compositeShape.");
  }
  size_t size = compShape.getAmount();
  Matrix myMatrix{compShape[0]};
  for (size_t i = 1; i < size; i++)
  {
    myMatrix.addShape(compShape[i]);
  }
  return myMatrix;
}

void maikenova::Matrix::resetMatrix()
{
  array_.reset();
  layer_.reset();
  size_ = 0;
  layNum_ = 0;
}

size_t maikenova::Matrix::getLayerSize(size_t line) const
{
  if (line > layNum_)
  {
    throw std::invalid_argument("This layer does not exist.");
  }
  return layer_[line];
}

size_t maikenova::Matrix::getLayerNum() const
{
  return layNum_;
}

size_t maikenova::Matrix::getSize() const
{
  return size_;
}

maikenova::Shape* maikenova::Matrix::getShape(size_t line, size_t column) const
{
  if (line > layNum_)
  {
    throw std::invalid_argument("This shape does not exist");
  }
  if (column > layer_[line])
  {
    throw std::invalid_argument("This shape does not exist");
  }
  size_t curr = 0;
  for (size_t i = 0; i < line; i++)
  {
    curr += layer_[i];
  }
  curr += column;
  return array_[curr];
}

size_t maikenova::Matrix::searchPos(const Shape* shape) const
{
  if (layNum_ == 0)
  {
    return 0;
  }
  size_t line = layNum_;
  if (layNum_ == 1)
  {
    if (checkOverlapping(shape, 0))
    {
      return 1;
    }
    return 0;
  }
  for (size_t i = layNum_ - 1; i >= 1; i--)
  {
    if (checkOverlapping(shape, i))
    {
      return i + 1;
    }
    if (i == 1)
    {
      if (checkOverlapping(shape, 0))
      {
        return 1;
      }
      return 0;
    }
  }
  return line;
}

bool maikenova::Matrix::checkOverlapping(const Shape* shape, size_t line) const
{
  rectangle_t myRectangle;
  rectangle_t myRectangle1 = shape->getFrameRect();
  size_t pos = 0;
  double dx, dy, dh, dw;
  for (size_t i = 0; i < line;i++)
  {
    pos += layer_[i];
  }
  for (size_t i = 0; i < layer_[line];i++)
  {
    myRectangle = array_[pos+i]->getFrameRect();
    dx = std::abs((myRectangle.pos.x) - (myRectangle1.pos.x));
    dy = std::abs((myRectangle.pos.y) - (myRectangle1.pos.y));
    dh = myRectangle.height / 2 + myRectangle1.height / 2;
    dw = myRectangle.width / 2 + myRectangle1.width / 2;
    if ((dx <= dw) & (dy <= dh))
    {
      return true;
    }
  }
  return false;
}

