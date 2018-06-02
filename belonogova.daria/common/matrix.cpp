#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>

using namespace belonogova;

Matrix::Matrix() :
  m_layers(0),
  m_maxInLayer(0),
  m_matrix(nullptr)
{

}

Matrix::Matrix(const Matrix & other) :
  m_layers(other.m_layers),
  m_maxInLayer(other.m_maxInLayer),
  m_matrix(new std::shared_ptr <Shape> [m_layers * m_maxInLayer])
{
  for (int i = 0; i < (m_layers * m_maxInLayer); i++) {
    m_matrix[i] = other.m_matrix[i];
  }
}

Matrix::Matrix(Matrix && other) :
  m_layers(other.m_layers),
  m_maxInLayer(other.m_maxInLayer),
  m_matrix(std::move(other.m_matrix))
{
  other.m_layers = 0;
  other.m_maxInLayer = 0;
  other.m_matrix.reset();
}

Matrix & Matrix::operator= (const Matrix & other)
{
  if (this != &other)
  {
    m_layers = other.m_layers;
    m_maxInLayer = other.m_maxInLayer;
    m_matrix.reset(new std::shared_ptr<Shape> [m_layers * m_maxInLayer] );
    for(int i = 0; i < (m_layers * m_maxInLayer); i++)
    {
      m_matrix[i] = other.m_matrix[i];
    }
  }
  return *this;
}

Matrix & Matrix::operator= (Matrix && other)
{
  m_layers = other.m_layers;
  m_maxInLayer = other.m_maxInLayer;
  m_matrix = std::move(other.m_matrix);
  other.m_layers = 0;
  other.m_maxInLayer = 0;

  return *this;
}

std::unique_ptr<std::shared_ptr<Shape>[]> Matrix::operator[](const int index) const
{
  if ((index < 0) || (index >= m_layers))
  {
    throw std::out_of_range("Invalid index");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> layer(new std::shared_ptr<Shape>[m_maxInLayer]);
  for (int i = 0; i < m_maxInLayer; i++)
  {
    layer[i] = m_matrix[index * m_maxInLayer + i];
  }
  return layer;
}

void Matrix::addShapeToLayer(const std::shared_ptr <Shape> & shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("Shape is nullptr");
  }
  if ((m_layers == 0) && (m_maxInLayer == 0)) {
    std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix(new std::shared_ptr<Shape>[1]);
    m_maxInLayer++;
    m_layers++;
    newMatrix[0] = shape;
    m_matrix.swap(newMatrix);
    return;
  }
  int i = 0;
  for (; i < m_layers; i++) {
    int j = 0;
    for(; j < m_maxInLayer; j++) {
      if (m_matrix[i * m_maxInLayer + j] == nullptr) {
        m_matrix[i * m_maxInLayer + j] = shape;
        return;
      }
      if (isIntersected(m_matrix[i * m_maxInLayer + j], shape)) {
        break;
      }
    }
    if (j == m_maxInLayer) {
      std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix(new std::shared_ptr <Shape> [m_layers * (m_maxInLayer + 1)]);
      for (int k = 0; k < m_layers; k++) {
        for (j = 0; j < m_maxInLayer; j++) {
          newMatrix[k * m_maxInLayer + j + k] = m_matrix[k * m_maxInLayer + j];
        }
      }
      ++m_maxInLayer;
      newMatrix[(i + 1) * m_maxInLayer - 1] = shape;
      m_matrix.swap(newMatrix);
      return;
    }
  }
  if (i == m_layers) {
    std::unique_ptr< std::shared_ptr<Shape>[] > newMatrix(new std::shared_ptr <Shape> [(m_layers+1) * (m_maxInLayer)]);
    for (int k = 0; k < m_layers * m_maxInLayer; k++) {
      newMatrix[k] = m_matrix[k];
    }
    newMatrix[m_layers * m_maxInLayer] = shape;
    m_layers++;
    m_matrix.swap(newMatrix);
  }
}

bool Matrix::isIntersected(const std::shared_ptr <Shape> & shape1, const std::shared_ptr <Shape> & shape2) const
{

  double firstRectLeft = shape1->getFrameRect().pos.x - shape1->getFrameRect().width / 2.0;
  double firstRectRight = shape1->getFrameRect().pos.x + shape1->getFrameRect().width / 2.0;
  double firstRectTop = shape1->getFrameRect().pos.y + shape1->getFrameRect().height / 2.0;
  double firstRectBottom = shape1->getFrameRect().pos.y - shape1->getFrameRect().height / 2.0;

  double secondRectLeft = shape2->getFrameRect().pos.x - shape2->getFrameRect().width / 2.0;
  double secondRectRight = shape2->getFrameRect().pos.x + shape2->getFrameRect().width / 2.0;
  double secondRectTop = shape2->getFrameRect().pos.y + shape2->getFrameRect().height / 2.0;
  double secondRectBottom = shape2->getFrameRect().pos.y - shape2->getFrameRect().height / 2.0;

  if ((firstRectLeft >= secondRectRight) || (firstRectRight <= secondRectLeft)
    || (firstRectTop <= secondRectBottom) || (firstRectBottom >= secondRectTop)) {
    return false;
  } else {
    return true;
  }

}


int Matrix::getLayers() const
{
  return m_layers;
}
int Matrix::getMaxInLayer() const
{
  return m_maxInLayer;
}
