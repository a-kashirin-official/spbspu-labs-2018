#include "composite-shape.hpp"

#include <stdexcept>

// Default class constructor
hvatov::CompositeShape::CompositeShape() :
  size_(0),
  array_(nullptr)
{
}

// Fill class constructor with shared_ptr
hvatov::CompositeShape::CompositeShape(const std::shared_ptr< Shape > & ptr) :
  size_(1),
  array_(new std::shared_ptr< Shape >[1])
{
  array_[0] = ptr;
}

// Copying class constructor
hvatov::CompositeShape::CompositeShape(const CompositeShape & other) :
  size_(other.size_),
  array_(new std::shared_ptr< Shape >[size_])
{
  // Copy elements of the arrays
  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = other.array_[i];
  }
}

// Moving class constructor
hvatov::CompositeShape::CompositeShape(CompositeShape && other) :
  size_(other.size_)
{
  // Move unique pointer
  array_ = std::move(other.array_);

  // Set other array_ to null:
  other.array_ = nullptr;
  other.size_ = 0;
}

// Class destructor
hvatov::CompositeShape::~CompositeShape()
{
  // noting to be done because of the smart pointers
}

// Copying operator = overload
hvatov::CompositeShape & hvatov::CompositeShape::operator=(const CompositeShape & other)
{
  // if it is itself
  if (this == &other)
  {
    return *this;
  }

  // Deep copying the object
  size_ = other.size_;  // set size
  array_.reset(new std::shared_ptr< Shape >[size_]);  // allocate array

                                                      // Copy array
  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = other.array_[i];
  }

  return *this;
}

// Moving operator = overload
hvatov::CompositeShape & hvatov::CompositeShape::operator=(CompositeShape && other)
{
  // if it is itself
  if (this == &other)
  {
    return *this;
  }

  // Deep copying the object
  size_ = other.size_;  // set size
  array_.reset(new std::shared_ptr< Shape >[size_]);  // allocate array

                                                      // Move array
  array_ = std::move(other.array_);

  // Set other array_ to null:
  other.array_ = nullptr;
  other.size_ = 0;

  return *this;
}

// Operator + overload
hvatov::CompositeShape hvatov::CompositeShape::operator+(const CompositeShape & other)
{
  // Buffer
  CompositeShape buf;

  // Copy from this one
  for (size_t i = 0; i < size_; i++)
  {
    buf.addElement(array_[i]);
  }
  // Copy from other one
  for (size_t i = 0; i < size_; i++)
  {
    buf.addElement(other[i]);
  }

  buf.size_ = size_ + other.size_;

  // Return result
  return buf;
}

// Operator [] overload
const std::shared_ptr<hvatov::Shape> & hvatov::CompositeShape::operator[](size_t index) const
{
  // Check this
  if (index >= size_)
  {
    throw std::invalid_argument("Array index must be < size of the container!");
  }

  return array_[index];
}

std::shared_ptr<hvatov::Shape> & hvatov::CompositeShape::operator[](size_t index)
{
  // Check this
  if (index >= size_)
  {
    throw std::invalid_argument("Array index must be < size of the container!");
  }

  return array_[index];
}

// Get total area method
double hvatov::CompositeShape::getArea() const noexcept
{
  // buffer var
  double area = 0;

  for (size_t i = 0; i < size_; i++)
  {
    area += array_[i]->getArea();
  }

  return area;
}

// Get total frame rect
hvatov::rectangle_t hvatov::CompositeShape::getFrameRect() const noexcept
{
  // if container is empty then return zero rect
  if (size_ == 0)
  {
    return rectangle_t{ 0, 0, 0, 0 };
  }

  // looking for the corners of the rectangle
  rectangle_t buf_rect = array_[0]->getFrameRect();
  double left = buf_rect.pos.x - buf_rect.width / 2;
  double right = buf_rect.pos.x + buf_rect.width / 2;
  double top = buf_rect.pos.y + buf_rect.height / 2;
  double bottom = buf_rect.pos.y - buf_rect.height / 2;

  for (size_t i = 1; i < size_; i++)
  {
    // compare with other shapes and find the least
    buf_rect = array_[i]->getFrameRect();
    double buf_left = buf_rect.pos.x - buf_rect.width / 2;
    double buf_right = buf_rect.pos.x + buf_rect.width / 2;
    double buf_top = buf_rect.pos.y + buf_rect.height / 2;
    double buf_bottom = buf_rect.pos.y - buf_rect.height / 2;

    if (buf_left < left)
    {
      left = buf_left;
    }
    if (buf_right > right)
    {
      right = buf_right;
    }
    if (buf_top > top)
    {
      top = buf_top;
    }
    if (buf_bottom < bottom)
    {
      bottom = buf_bottom;
    }
  }
  // return result
  return rectangle_t{ { ((left + right) / 2.0), ((top + bottom) / 2.0) }, (right - left), (top - bottom) };
}

// Move all objects methods
void hvatov::CompositeShape::move(const point_t & pos) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(pos);
  }
}

void hvatov::CompositeShape::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(dx, dy);
  }
}

// Scale all objects
void hvatov::CompositeShape::scale(double k)
{
  point_t comp_pos = getPosition();
  for (size_t i = 0; i < size_; i++)
  {
    // Buffer position of the figure
    point_t shape_pos = array_[i]->getPosition();
    // New future position of the scaled figure
    point_t new_pos = { comp_pos.x + k * (shape_pos.x - comp_pos.x),
      comp_pos.y + k * (shape_pos.y - comp_pos.y) };
    // Move figure before scaling
    array_[i]->move(new_pos);
    // Scale figure
    array_[i]->scale(k);
  }
}

// Rotate method
void hvatov::CompositeShape::rotate(double angle) noexcept
{
  // get current position of the composite shape
  point_t cur_pos = getPosition();

  // Convert from degrees to radians
  angle = fromDegToRad(angle);

  // Transform coordinates and scale the shapes
  for (size_t i = 0; i < size_; i++) 
  {
    // Move the shapes
    array_[i]->move({ 
      cur_pos.x + (array_[i]->getPosition().x - cur_pos.x) * cos(angle) - (array_[i]->getPosition().y - cur_pos.y) * sin(angle),
      cur_pos.y + (array_[i]->getPosition().y - cur_pos.y) * cos(angle) + (array_[i]->getPosition().x - cur_pos.x) * sin(angle) 
    });

    // Rotate the shapes
    array_[i]->rotate(angle);
  }
}

// Get info method
std::ostream & hvatov::CompositeShape::getInfo(std::ostream & stream) const noexcept
{
  if (size_ == 0)
  {
    stream << std::endl << "Container is empty!" << std::endl;
  }
  else
  {
    for (size_t i = 0; i < size_; i++)
    {
      array_[i]->getInfo(stream) << std::endl;
    }
  }
  return stream;
}

// Get position method
hvatov::point_t hvatov::CompositeShape::getPosition() const noexcept
{
  return getFrameRect().pos;
}

// Add new element method
void hvatov::CompositeShape::addElement(const std::shared_ptr<Shape> & ptr)
{
  // Check if null pointer
  if (ptr == nullptr)
  {
    throw std::invalid_argument("Pointer must not be null!");
  }

  // Buffer pointer
  std::unique_ptr< std::shared_ptr< Shape >[] > buf;
  buf = std::move(array_);

  // Reset current data:
  array_.reset(new std::shared_ptr< Shape >[size_ + 1]);
  array_[size_] = ptr;
  size_++;
  // Copy data back
  for (size_t i = 0; i < size_ - 1; i++)
  {
    array_[i] = buf[i];
  }
}

// Delete element # index method
void hvatov::CompositeShape::deleteElement(size_t index)
{
  // Check this
  if (index >= size_)
  {
    throw std::invalid_argument("Array index must be < size of the container!");
  }

  // Delete object
  for (size_t i = index; i <= size_ - 2; i++)
  {
    array_[i] = array_[i + 1];
  }
  array_[size_ - 1] = nullptr;
  size_--;
}

// Get the size of the constainer method
size_t hvatov::CompositeShape::getSize() const noexcept
{
  return size_;
}

// Clear the container method
void hvatov::CompositeShape::clear() noexcept
{
  size_ = 0;
  array_ = nullptr;
}

// stream ouput operator override
std::ostream & hvatov::operator<<(std::ostream & stream, const hvatov::CompositeShape & container)
{
  if (container.size_ == 0)
  {
    stream << std::endl << "Container is empty!" << std::endl;
  }
  else
  {
    for (size_t i = 0; i < container.size_; i++)
    {
      container[i]->getInfo(stream) << std::endl;
    }
  }
  return stream;
}

