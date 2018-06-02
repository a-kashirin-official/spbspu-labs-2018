#include "matrix.hpp"

#include <string>

// Default constructor
hvatov::Matrix::Matrix() :
  layers_(nullptr),
  shapes_num_(0),
  layers_num_(0)
{
  layers_size_.push_back(0);
}

// Copying constructor
hvatov::Matrix::Matrix(const Matrix & obj) :
  layers_(
    new layer_type[obj.shapes_num_]
  ),
  shapes_num_(obj.shapes_num_),
  layers_num_(obj.layers_num_),
  layers_size_(obj.layers_size_)
{
  // Share pointers with another object
  for (size_t i = 0; i < shapes_num_; i++)
  {
    layers_[i] = obj.layers_[i];
  }
}

// Moving constructor
hvatov::Matrix::Matrix(Matrix && obj) :
  shapes_num_(obj.shapes_num_),
  layers_num_(obj.layers_num_),
  layers_size_(obj.layers_size_)
{
  // move unique ptr
  layers_ = std::move(obj.layers_);
  // Set to null other object
  obj.layers_ = nullptr;
  obj.layers_num_ = 0;
  obj.layers_size_ = { 0 };
  obj.shapes_num_ = 0;
}

// Matrix constructor using array of shapes
hvatov::Matrix::Matrix(const std::initializer_list<std::shared_ptr<Shape>>& collection) :
  Matrix()
{
  // For all objects add them to the matrix
  for (auto& obj : collection)
  {
    addElement(obj);
  }
}
// Matrix constructor using list of shapes
hvatov::Matrix::Matrix(const ArrayType<Shape>& collection, size_t size) :
  Matrix()
{
  for (size_t i = 0; i < size; i++)
  {
    addElement(collection[i]);
  }
}

// // Matrix constructor from composite shape
hvatov::Matrix::Matrix(const CompositeShape & comp_shape) :
  Matrix()
{
  for (size_t i = 0; i < comp_shape.getSize(); i++)
  {
    addElement(comp_shape[i]);
  }
}

// Copying operator =
hvatov::Matrix & hvatov::Matrix::operator=(const Matrix & other)
{
  // Check self
  if (this == &other)
  {
    return *this;
  }

  // Set numbers
  layers_num_ = other.layers_num_;
  layers_size_ = other.layers_size_;
  shapes_num_ = other.shapes_num_;

  // reallocate memory
  layers_.reset(new layer_type[shapes_num_]);

  // Copy array
  for (size_t i = 0; i < shapes_num_; i++)
  {
    layers_[i] = other.layers_[i];
  }

  return *this;
}

// Moving operator = 
hvatov::Matrix & hvatov::Matrix::operator=(Matrix && other)
{
  // Check self
  if (this == &other)
  {
    return *this;
  }

  // Set numbers
  layers_num_ = other.layers_num_;
  layers_size_ = other.layers_size_;
  shapes_num_ = other.shapes_num_;

  // Set to null other's numbers
  other.layers_num_  = 0;
  other.layers_size_ = { 0 };
  other.shapes_num_  = 0;

  // Move array
  layers_ = std::move(other.layers_);

  return *this;
}

// Get layer method
hvatov::Layer hvatov::Matrix::getLayer(size_t index)
{
  // check index
  if (index > layers_num_)
  {
    throw std::invalid_argument("No layer with such index!");
  }

  // buffer vector of shapes
  Layer layer;

  // Set vector of shapes in i layer
  for (size_t k = 0; k < shapes_num_; k++)
  {
    // if shape is in this layer
    if (layers_[k].second.first == index)
    {
      // add it to the vec
      layer.addElement(layers_[k].first);
    }
  }

  return layer;
}

// Add element to the matrix
void hvatov::Matrix::addElement(const std::shared_ptr<Shape>& obj)
{
  // Check if obj is null
  if (obj == nullptr)
  {
    throw std::invalid_argument("Object must not be null!");
  }

  // Check if matrix is empty
  if (layers_size_[0] == 0)
  {
    // if so 
    // allocate memory and
    // init matrix
    layers_ = std::move(std::unique_ptr< layer_type[] >(new layer_type[1]));
    // Increament numbers
    shapes_num_++;
    layers_num_++;
    layers_size_[0]++;
    // Set object and it's position 
    // in the matrix
    layers_[0].first = obj;
    layers_[0].second.first = 1;  // I
    layers_[0].second.second = 1; // J
  }
  // if matrix is not empty
  else
  {
    // Increament numbers
    shapes_num_++;
    // buffer array
    std::unique_ptr< layer_type[] > buffer(new layer_type[shapes_num_]);
    // copy data to buffer array
    for (size_t i = 0; i < shapes_num_ - 1; i++)
    {
      buffer[i] = layers_[i];
    }
    // add shape to the array
    buffer[shapes_num_ - 1].first = obj;

    // buffer position
    std::pair< size_t, size_t > cur_pos{1, 1};
    // get the position of the shape in the matrix
    for (size_t i = 0; i < shapes_num_ - 1; i++)
    {
      // if they dont overlap
      if (!checkOverlap(buffer[i].first, obj) &&
        buffer[i].second.first >= cur_pos.first)
      {
        // set position
        cur_pos.first = buffer[i].second.first;
        cur_pos.second = layers_size_[cur_pos.first - 1] + 1;
      }

      // if they overlap
      if (checkOverlap(buffer[i].first, obj) && 
        buffer[i].second.first == cur_pos.first)
      {
        // set position
        cur_pos.first++;
        cur_pos.second = 0;
      }
    }

    // if it needs a new layer
    if (!cur_pos.second)
    {
      // incr numbers
      layers_num_++;
      layers_size_.push_back(1);
      // place object
      buffer[shapes_num_ - 1].second.first = layers_num_;
      buffer[shapes_num_ - 1].second.second = 1;
    }
    else 
    {
      // place object
      buffer[shapes_num_ - 1].second = cur_pos;
      // incr number
      layers_size_[buffer[shapes_num_ - 1].second.first - 1]++;
    }

    // move buffer array 
    layers_ = std::move(buffer);
  }
}

// Add elements of composite shape to the matrix
void hvatov::Matrix::addElement(const CompositeShape & obj)
{
  for (size_t i = 0; i < obj.getSize(); i++)
  {
    addElement(obj[i]);
  }
}

// Add elements of array of shape to the matrix
void hvatov::Matrix::addElement(const ArrayType<Shape>& collection, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    addElement(collection[i]);
  }
}

// Gt element method
std::shared_ptr<hvatov::Shape>& hvatov::Matrix::getElement(size_t i, size_t j) const
{
  // go through the matrix
  for (size_t k = 0; k < shapes_num_; k++)
  {
    // if found
    if (layers_[k].second.first == i && layers_[k].second.second == j)
    {
      // return element
      return layers_[k].first;
    }
  }

  // if we didnt find => doesnt exist
  throw std::invalid_argument("No element with such coordinates in the matrix!");
}

// Get number of the layers method
size_t hvatov::Matrix::getLayersNum() const noexcept
{
  return layers_num_;
}

// Get the number of elements in layer
size_t hvatov::Matrix::getLayerSize(size_t i) const
{
  // check index
  if (i > layers_num_)
  {
    throw std::invalid_argument("No layer with such index!");
  }

  return layers_size_[i - 1];
}

// Cler matrix method:
void hvatov::Matrix::clear() noexcept
{
  layers_ = nullptr;
  layers_num_ = 0;
  shapes_num_ = 0;
  layers_size_ = { 0 };
}

// Check if two shapes cross each other method
bool hvatov::Matrix::checkOverlap(const std::shared_ptr<Shape> & s1, const std::shared_ptr<Shape> & s2) noexcept
{
  return fabs(s1->getFrameRect().pos.x - s2->getFrameRect().pos.x)
    < ((s1->getFrameRect().height / 2) + (s2->getFrameRect().height / 2)) && 
    abs(s1->getFrameRect().pos.y - s2->getFrameRect().pos.y)
      < ((s1->getFrameRect().width / 2) + (s2->getFrameRect().width / 2));
}

// output to the stream function
std::ostream & hvatov::operator<<(std::ostream & stream, const Matrix & matr)
{
  // go through the matrix
  for (size_t k = 0; k < matr.layers_num_; k++)
  {
    // Layer number
    stream << "Layer# " << k + 1 << std::endl;

    // go through all elements
    for (size_t j = 0; j < matr.layers_size_[k]; j++)
    {
      for (size_t i = 0; i < matr.shapes_num_; i++)
      {
        // buffer variable with the name of the figure
        std::string name;

        if (matr.layers_[i].second.first == k + 1 &&
          matr.layers_[i].second.second == j + 1)
        {
          // Using RTTI to get the type of the object
          // Check if object is Rectangle
          if (dynamic_cast<Rectangle *>(matr.layers_[i].first.get()) != nullptr)
          {
            name = "Rectangle";
          }
          // Check if object is Circle
          if (dynamic_cast<Circle *>(matr.layers_[i].first.get()) != nullptr)
          {
            name = "Circle";
          }

          // Output the results
          stream << "\t - " << name 
            << " ( " << matr.layers_[i].first->getPosition().x << " ; "
            << matr.layers_[i].first->getPosition().y << " )" << std::endl;
        }
      }
    }
  }

  return stream;
}

