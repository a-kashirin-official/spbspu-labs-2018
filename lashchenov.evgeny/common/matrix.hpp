#ifndef STUDY_LABS_MATRIX_HPP
#define STUDY_LABS_MATRIX_HPP

#include "shape.hpp"
#include "composite-shape.hpp"

namespace lashchenov
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      Layer(size_t size, const std::unique_ptr<std::shared_ptr<Shape>[]>::pointer & list);
      Shape & operator[](size_t j);

    private:
      size_t size_;
      std::unique_ptr<std::shared_ptr<Shape>[]> list_;
    };

    Matrix();
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix) noexcept;
    ~Matrix() = default;

    Matrix & operator=(const Matrix & matrix);
    Matrix & operator=(Matrix && matrix) noexcept;
    Layer operator[](size_t i) const;

    void remove(size_t i, size_t j);
    void addElementsFromCShape(const CompositeShape & cShape);
    void add(const Shape & shape);
    size_t getLayerCount() const;
    size_t getLayerSize(size_t i) const;
    void printInfo() const;

  private:
    size_t LayerCount_;
    size_t MaxLayerSize_;
    std::unique_ptr<size_t[]> LayerSize_;
    std::unique_ptr<std::shared_ptr<Shape>[]> list_;

    bool IsSuitableLayer(size_t LayerNumber, const Shape & shape) const;
    void resizeLayer(size_t NewLayerSize);
    void addLayer();
  };
}


#endif //STUDY_LABS_MATRIX_HPP
