#include "matrix.hpp"
#include <cmath>

sibikin::Matrix::Matrix() :
  count_(0),
  layerCount_(0),
  array_(new Shape*[0]),
  layer_(new size_t[0])
{
}

sibikin::Matrix::~Matrix()
{
  array_.reset();
  layer_.reset();
}

sibikin::Matrix::Matrix(std::initializer_list <Shape*> shapes)
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
  count_ = 1;
  layerCount_ = 1;
  iter++;
  for (;iter != shapes.end(); iter++)
  {
    addShape(*iter);
  }
}

sibikin::Matrix::Matrix(const Matrix & matrix) :
  count_(matrix.getSize()),
  layerCount_(matrix.getLayerCount()),
  array_(new Shape*[matrix.getSize()]),
  layer_(new size_t[matrix.getLayerCount()])

{
  for (size_t i = 0;i < count_; i++)
  {
    array_[i] = matrix.array_[i];
  }
  for (size_t i = 0;i < layerCount_; i++)
  {
    layer_[i] = matrix.layer_[i];
  }
}

sibikin::Matrix& sibikin::Matrix::operator=(const Matrix &matrix)
{
  if (this != & matrix)
  {
    boost::shared_array <Shape*> tempArray{ new Shape*[matrix.getSize()] };
    boost::shared_array <size_t> tempLay{ new size_t[matrix.getLayerCount()] };
    for (size_t i = 0;i < matrix.getSize();i++)
    {
      tempArray[i] = matrix.array_[i];
    }
    for (size_t i = 0;i < matrix.getLayerCount(); i++)
    {
      tempLay[i] = matrix.layer_[i];
    }
    count_ = matrix.getSize();
    layerCount_ = matrix.getLayerCount();
    array_.reset();
    layer_.reset();
    array_ = tempArray;
    layer_ = tempLay;
  }
  return *this;
}

void sibikin::Matrix::addShape(Shape* shape)
{
  size_t line;
  size_t pos = 0;
  line = searchPos(shape);
  if (line == layerCount_)
  {
    boost::shared_array <size_t> tempLay{ new size_t[layerCount_ + 1] };
    for (size_t i = 0;i < layerCount_; i++)
    {
      tempLay[i] = layer_[i];
    }
    tempLay[layerCount_] = 0;
    layer_.reset(new size_t[layerCount_ + 1]);
    layer_ = tempLay;
    layerCount_++;
  }
  for (size_t i = 0; i < line; i++)
  {
    pos += layer_[i];
  }
  pos += layer_[line];

  boost::shared_array <Shape*> tempArray{new Shape*[count_+1]};
  for (size_t i = 0; i < pos; i++)
  {
    tempArray[i] = array_[i];
  }
  for (size_t i = pos + 1; i < count_ + 1; i++)
  {
    tempArray[i] = array_[i-1];
  }
  tempArray[pos] = shape;
  array_.reset(new Shape*[count_+1]);
  array_ = tempArray;
  layer_[line]++;
  count_++;
}

sibikin::Matrix sibikin::Matrix::createMatrix(sibikin::CompositeShape& comp)
{
  if (comp.getSize() < 1)
  {
    throw std::invalid_argument("There are no shapes in compositeShape.");
  }
  size_t size = comp.getSize();
  Matrix myMatrix{&comp[0]};
  for (size_t i = 1; i < size; i++)
  {
    myMatrix.addShape(&comp[i]);
  }
  return myMatrix;
}


void sibikin::Matrix::resetMatrix()
{
  array_.reset();
  layer_.reset();
  count_ = 0;
  layerCount_ = 0;
}

size_t sibikin::Matrix::getLayerSize(size_t line) const
{
  if (line > layerCount_)
  {
    throw std::invalid_argument("This layer does not exist!");
  }
  return layer_[line];
}

size_t sibikin::Matrix::getLayerCount() const
{
  return layerCount_;
}

size_t sibikin::Matrix::getSize() const
{
  return count_;
}

sibikin::Shape* sibikin::Matrix::getShape(size_t line, size_t column) const
{
  if (line > layerCount_)
  {
    throw std::invalid_argument("This shape does not exist!");
  }
  if (column > layer_[line])
  {
    throw std::invalid_argument("This shape does not exist!");
  }
  size_t cur = 0;
  for (size_t i = 0; i < line; i++)
  {
    cur += layer_[i];
  }
  cur += column;
  return array_[cur];
}

size_t sibikin::Matrix::searchPos(const Shape* shape) const
{
  if (layerCount_ == 0)
  {
    return 0;
  }
  size_t line = layerCount_;
  if (layerCount_ == 1)
  {
    if (checkOverlapping(shape, 0))
    {
      return 1;
    }
    return 0;
  }
  for (size_t i = layerCount_ - 1; i >= 1; i--)
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

bool sibikin::Matrix::checkOverlapping(const Shape* shape, size_t line) const
{
  rectangle_t rect;
  rectangle_t rect1 = shape->getFrameRect();
  size_t pos = 0;
  for (size_t i = 0; i < line;i++)
  {
    pos += layer_[i];
  }
  double dx, dy, dh, dw;
  for (size_t i = 0; i < layer_[line];i++)
  {
    rect = array_[pos+i]->getFrameRect();
    dx = fabs((rect.pos.x) - (rect1.pos.x));
    dy = fabs((rect.pos.y) - (rect1.pos.y));
    dh = rect.height / 2 + rect1.height / 2;
    dw = rect.width / 2 + rect1.width / 2;
    if ((dx <= dw) & (dy <= dh))
    {
      return true;
    }
  }
  return false;
}
