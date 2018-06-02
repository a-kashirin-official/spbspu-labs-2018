#include "layer.hpp"

// Default constructor
hvatov::Layer::Layer() :
  array_(nullptr),
  size_(0)
{
}

// Copying constructor
hvatov::Layer::Layer(const Layer & l) :
  array_(new std::shared_ptr< Shape >[l.size_]),
  size_(l.size_)
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = l[i];
  }
}

// Moving constructor
hvatov::Layer::Layer(hvatov::Layer&& l) :
  array_(std::move(l.array_)),
  size_(l.size_)
{
  // set to null l
  l.array_ = nullptr;
  l.size_ = 0;
}

// Operator [] overload
std::shared_ptr< hvatov::Shape > hvatov::Layer::operator[](size_t index)
{
  // Check
  if (index >= size_)
  {
    // throw
    throw std::invalid_argument("Index must be < size!");
  }
  return array_[index];
}

const std::shared_ptr< hvatov::Shape > hvatov::Layer::operator[](size_t index) const
{
  // Check
  if (index >= size_)
  {
    // throw
    throw std::invalid_argument("Index must be < size!");
  }
  return array_[index];
}

// Operator = overload
hvatov::Layer & hvatov::Layer::operator=(const Layer & lhs)
{
  // check
  if (this == &lhs)
  {
    return *this;
  }

  // Create buffer
  std::unique_ptr< std::shared_ptr< Shape >[] > buf(new std::shared_ptr< Shape >[lhs.size_]);
  size_ = lhs.size_;
  
  // copy elements
  for (size_t i = 0; i < lhs.size_; i++)
  {
    buf[i] = lhs.array_[i];
  }

  // Move
  array_ = std::move(buf);

  return *this;
}

// Operator = overload
hvatov::Layer & hvatov::Layer::operator=(Layer && rhs)
{
  // check
  if (this == &rhs)
  {
    return *this;
  }

   // Move
  size_ = rhs.size_;
  array_ = std::move(rhs.array_);

  // Set to null
  rhs.size_ = 0;
  rhs.array_ = nullptr;

  return *this;
}

// Add element to the layer
void hvatov::Layer::addElement(const std::shared_ptr<Shape>& obj)
{
  // Check if nullptr
  if (obj == nullptr)
  {
    throw std::invalid_argument("Pointe must not be nullptr!");
  }

  // Create buffer
  size_++;
  std::unique_ptr< std::shared_ptr< Shape >[] > buf(new std::shared_ptr< Shape >[size_]);

  // copy elements
  for (size_t i = 0; i < size_ - 1; i++)
  {
    buf[i] = array_[i];
  }

  // add element
  buf[size_ - 1] = obj;

  // move arrays
  array_ = std::move(buf);
}

// operator << overload
std::ostream & hvatov::operator<<(std::ostream & stream, const Layer & l)
{
  for (size_t i = 0; i < l.size_; i++)
  {
    l[i]->getInfo(stream) << std::endl;
  }

  return stream;
}

