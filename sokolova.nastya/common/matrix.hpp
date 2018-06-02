#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

#include "shape.hpp"
#include "composite-shape.hpp"

namespace sokolova
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      Layer(int size, const std::unique_ptr<std::shared_ptr<sokolova::Shape>[]>::pointer & arrayOfShapes);
      sokolova::Shape & operator[](int j);

    private:
      int size_;
      std::unique_ptr<std::shared_ptr<sokolova::Shape>[]> arrayOfShapes_;
    };

    Matrix();
    Matrix(const Matrix & matrix);
    Matrix(Matrix && matrix) noexcept;
    ~Matrix() = default;

    Matrix & operator=(const Matrix & matrix);
    Matrix & operator=(Matrix && matrix) noexcept;
    Layer operator[](int i) const;

    void addElementsFromCompSh(const sokolova::CompositeShape & compSh);
    void add(const std::shared_ptr<sokolova::Shape> shape);
    int getLayerCount() const;
    int getLayerSize(int i) const;

    void printInfo() const;

  private:
    int LayerCount_;
    int MaxLayerSize_;
    std::unique_ptr<int[]> LayerSize_;
    std::unique_ptr<std::shared_ptr<sokolova::Shape>[]> arrayOfShapes_;

    bool IsSuitableLayer(int LayerNumber, const std::shared_ptr<sokolova::Shape> shape) const;
    void resizeLayer(int NewLayerSize);
    void addLayer();
  };
}



#endif // MATRIX_HPP
