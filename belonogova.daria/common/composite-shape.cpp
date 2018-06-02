#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <cmath>
#include <algorithm>
#include <numeric>


using namespace belonogova;

belonogova::CompositeShape::CompositeShape(std::shared_ptr <Shape> & newComponent) :
  m_size(0),
  m_array(nullptr)
{
  if (newComponent == nullptr) {
    throw std::invalid_argument("New component is empty");
  }
  addComponent(newComponent);
}

CompositeShape::CompositeShape(const CompositeShape & other) :
  m_size(other.m_size),
  m_array(new std::shared_ptr<Shape> [other.m_size])
{
  for (int i = 0; i < m_size; i++) {
    m_array[i] = other.m_array[i];
  }
}

CompositeShape::CompositeShape(CompositeShape && other):
  m_size(other.m_size),
  m_array(std::move(other.m_array))
{
  other.m_size = 0;
  other.m_array.reset();
}

CompositeShape & CompositeShape::operator= (const CompositeShape & other)
{
  if (this != &other)
  {
    m_size = other.m_size;
    m_array.reset(new std::shared_ptr<Shape> [m_size]);
    for(int i = 0; i < m_size; i++)
    {
      m_array[i] = other.m_array[i];
    }
  }
  return *this;
}

CompositeShape & CompositeShape::operator= (CompositeShape && other)
{
  m_size = other.m_size;
  m_array = std::move(other.m_array);
  other.m_size = 0;

  return *this;
}

std::shared_ptr <Shape> & CompositeShape::operator[] (int index) const
{
  if (index >= m_size) {
    throw std::out_of_range("Wrong index");
  }
  return m_array[index];
}

double CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < m_size; i++) {
    area += m_array[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (m_size == 0) {
    return {0.0, 0.0, {0.0, 0.0}};
  }
  point_t pos_left, pos_right;
  pos_left.x = m_array[0]->getFrameRect().pos.x - (m_array[0]->getFrameRect().width / 2.0);
  pos_left.y = m_array[0]->getFrameRect().pos.y + (m_array[0]->getFrameRect().height / 2.0);

  pos_right.x = m_array[0]->getFrameRect().pos.x + (m_array[0]->getFrameRect().width / 2.0);
  pos_right.y = m_array[0]->getFrameRect().pos.y - (m_array[0]->getFrameRect().height / 2.0);

  double current;
  for (int i = 1; i < m_size; i++) {
    current = m_array[i]->getFrameRect().pos.x - (m_array[i]->getFrameRect().width / 2.0);
    if (current < pos_left.x) {
      pos_left.x = current;
    }
    current = m_array[i]->getFrameRect().pos.y + (m_array[i]->getFrameRect().height / 2.0);
    if (current > pos_left.y) {
      pos_left.y = current;
    }

    current = m_array[i]->getFrameRect().pos.x + (m_array[i]->getFrameRect().width / 2.0);
    if (current > pos_right.x) {
      pos_right.x = current;
    }
    current = m_array[i]->getFrameRect().pos.y - (m_array[i]->getFrameRect().height / 2.0);
    if (current < pos_right.y) {
      pos_right.y = current;
    }
  }

  rectangle_t frameRect;
  frameRect.width = pos_right.x - pos_left.x;
  frameRect.height = pos_left.y - pos_right.y;
  frameRect.pos.x = (pos_right.x + pos_left.x) / 2.0;
  frameRect.pos.y = (pos_left.y + pos_right.y) / 2.0;

  return frameRect;
}

void CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < m_size; i++) {
    m_array[i]->move(dx, dy);
  }
}

void CompositeShape::move(const point_t & newPos)
{
  double dx = newPos.x - getFrameRect().pos.x;
  double dy = newPos.y - getFrameRect().pos.y;
  move(dx, dy);
}

void CompositeShape::scale(const double coef)
{
  point_t compositeCenter = getFrameRect().pos;
  for (int i = 0; i < m_size; i++) {
    double dx = m_array[i]->getFrameRect().pos.x - compositeCenter.x;
    double dy = m_array[i]->getFrameRect().pos.y - compositeCenter.y;

    point_t newPos;
    newPos.x = compositeCenter.x + coef*dx;
    newPos.y = compositeCenter.y + coef*dy;
    m_array[i]->move(newPos);

    m_array[i]->scale(coef);
  }
}

void CompositeShape::addComponent(std::shared_ptr <Shape> & newComponent)
{
  if (newComponent == nullptr) {
    throw std::invalid_argument("New component is empty");
  }
  for (int i = 0; i < m_size; i++) {
    if (newComponent == m_array[i]) {
      throw std::invalid_argument("This component has been already added");
    }
  }
  std::unique_ptr <std::shared_ptr <Shape> []> tempArray(new std::shared_ptr <Shape> [m_size+1]);
  for (int i = 0; i < m_size; i++) {
    tempArray[i] = m_array[i];
  }
  tempArray[m_size] = newComponent;
  m_size++;
  m_array.swap(tempArray);
}

void CompositeShape::removeComponent(const int index)
{
  if ((index >= m_size) || (index < 0)) {
    throw std::invalid_argument("Wrong index");
  }
  if (m_size == 1){
    m_array.reset();
    m_size = 0;
  }
  else {
    std::unique_ptr < std::shared_ptr <Shape> []> tempArray (new std::shared_ptr <Shape> [m_size-1]);
    for (int i = 0; i < index; i++) {
      tempArray[i] = m_array[i];
    }
    for (int i = index; i < m_size - 1; i++) {
      tempArray[i] = m_array[i+1];
    }
    m_array.swap(tempArray);
    m_size--;
  }
}

void CompositeShape::rotate(const double alfa)
{
  point_t compositePos = getFrameRect().pos;

  for (int i = 0; i < m_size; i++) {
    point_t detailPos = m_array[i]->getFrameRect().pos;
    detailPos.x -= compositePos.x;
    detailPos.y -= compositePos.y;
    double new_x = detailPos.x * cos(alfa * M_PI / 180) - detailPos.y * sin(alfa * M_PI / 180);
    double new_y = detailPos.x * sin(alfa * M_PI / 180) + detailPos.y * cos(alfa * M_PI / 180);

    m_array[i]->move({(new_x + compositePos.x), (new_y + compositePos.y)});
    m_array[i]->rotate(alfa);
  }
}

Matrix CompositeShape::formMatrix() const
{
  Matrix newMatrix;
  for (int i = 0; i < m_size; i++) {
    newMatrix.addShapeToLayer(m_array[i]);
  }
  return newMatrix;
}

int CompositeShape::getSize() const
{
  return m_size;
}
