#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "layer.hpp"

#include <memory>
#include <vector>
#include <utility>

namespace hvatov {

  // Matrix class
  class Matrix
  {
    // Public members
  public:

    // Default constructor
    Matrix();

    // Copying constructor
    Matrix(const Matrix& obj);

    // Moving constructor
    Matrix(Matrix&& obj);

    // Matrix constructor using list of shapes
    Matrix(const std::initializer_list<std::shared_ptr<Shape>>& collection);

    // Matrix constructor using list of shapes
    Matrix(const ArrayType<Shape>& collection, size_t size);

    // Matrix constructor from composite shape
    Matrix(const CompositeShape& comp_shape);

    // Matrix destructor
    ~Matrix() = default;

    // Copying operator = overload
    Matrix & operator=(const Matrix& other);

    // Moving operator = overload
    Matrix & operator=(Matrix&& other);

    // Get layer method
    Layer getLayer(size_t index);

    // Add element to the matrix
    void addElement(const std::shared_ptr< Shape >& obj);

    // Add elements of composite shape to the matrix
    void addElement(const CompositeShape& obj);

    // Add elements of array of shape to the matrix
    void addElement(const ArrayType<Shape>& collection, size_t size);

    // Get element method
    std::shared_ptr< Shape > & getElement(size_t i, size_t j) const;

    // Get number of the layers method
    size_t getLayersNum() const noexcept;

    // Get the number of elements in layer
    size_t getLayerSize(size_t i) const;
  
    // Cler matrix method
    void clear() noexcept;

    // output to the stream function
    friend std::ostream & operator<<(std::ostream & stream, const Matrix & matr);

    // Private members
  private:
    // Short name of the type
    using layer_type = 
      std::pair< std::shared_ptr< Shape >, std::pair< size_t, size_t > >;
    // Pointer to the array of pairs 
    // of pointers to the shapes and 
    // the numbers of position in the matrix
    std::unique_ptr< layer_type[] > layers_;
    // Current number of shapes
    size_t shapes_num_;
    // Current number of layers
    size_t layers_num_;
    // Current size of the each layer
    std::vector< size_t > layers_size_;

    // Check if two shapes cross each other method
    static bool checkOverlap(const std::shared_ptr<Shape> & s1, const std::shared_ptr<Shape> & s2) noexcept;
  };

  // output to the stream function
  std::ostream & operator<<(std::ostream & stream, const Matrix & matr);

}

#endif // !MATRIX_HPP

