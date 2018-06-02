#ifndef LAYER_HPP
#define LAYER_HPP

#include "shape.hpp"

#include <memory>

namespace hvatov {

  class Matrix;

  // Layer class
  class Layer
  {
    // Public members
  public:

    friend Matrix;

    // Default constructor
    Layer();

    // Copying constructor
    Layer(const Layer& l);

    // Copying constructor
    Layer(Layer&& l);

    // Default destructor
    ~Layer() = default;

    // Operator [] overload
    std::shared_ptr< Shape > operator[](size_t index);
    const std::shared_ptr< hvatov::Shape > operator[](size_t index) const;

    // Operator = overload
    Layer& operator=(const Layer& lhs);
    Layer& operator=(Layer&& rhs);

    // operator << overload
    friend std::ostream& operator<<(std::ostream& stream, const Layer& l);

    // Private memebers:
  private:
    // Array of elements in the layer
    std::unique_ptr< std::shared_ptr< Shape >[] > array_;
    // Size of the array
    size_t size_;

    // Add element to the layer
    void addElement(const std::shared_ptr< Shape >& obj);
  };

  // operator << overload
  std::ostream& operator<<(std::ostream& stream, const Layer& l);
}

#endif // LAYER_HPP

