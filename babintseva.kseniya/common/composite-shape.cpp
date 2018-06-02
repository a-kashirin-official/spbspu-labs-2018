#include "composite-shape.hpp"
#include <stdexcept>
#include <cmath>
using namespace babintseva;

CompositeShape::CompositeShape(const std::shared_ptr<Shape> &shape):
    shapes_(new std::shared_ptr<Shape>[1]),
    size_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid shape!");
  }

  shapes_[0] = shape;
}

CompositeShape::CompositeShape(const CompositeShape &compShape)
{
  std::unique_ptr <std::shared_ptr<Shape>[]> shapesCopy(new std::shared_ptr<Shape>[compShape.size_]);
  size_ = compShape.size_;

  for (size_t i = 0; i < size_; i++)
  {
    shapesCopy[i] = compShape.shapes_[i];
  }

  shapes_.swap(shapesCopy);
}

CompositeShape &CompositeShape::operator=(const CompositeShape &compShape)
{
  if (this != &compShape)
  {
    std::unique_ptr <std::shared_ptr<Shape>[]> shapesCopy(new std::shared_ptr<Shape>[compShape.size_]);
    size_ = compShape.size_;

    for (size_t i = 0; i < size_; i++)
    {
      shapesCopy[i] = compShape.shapes_[i];
    }

    shapes_.swap(shapesCopy);
  }

  return *this;
}

bool babintseva::operator==(const CompositeShape &compShape1, const CompositeShape &compShape2)
{
  if (compShape1.size_ != compShape2.size_)
  {
    return false;
  }

  size_t i = 0;

  while (i < compShape1.size_)
  {
    if (compShape1.shapes_[i] == compShape2.shapes_[i])
    {
      i++;
    } else
    {
      return false;
    }
  }

  return true;
}

std::string CompositeShape::getName() const
{
  return "Composite shape";
}

void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid shape!");
  }

  std::unique_ptr <std::shared_ptr<Shape>[]> shapesTemp(new std::shared_ptr<Shape>[size_ + 1]);

  for (size_t i = 0; i < size_; i++)
  {
    shapesTemp[i] = shapes_[i];
  }

  shapesTemp[size_] = shape;
  size_++;
  shapes_.swap(shapesTemp);
}

double CompositeShape::getArea() const
{
  double sumOfAreas = 0;

  for (size_t i = 0; i < size_; i++)
  {
    sumOfAreas += shapes_[i]->getArea();
  }

  return sumOfAreas;
}

rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t shape_frame_rect = shapes_[0]->getFrameRect();

  double shape_frame_rect_top_left_x = shape_frame_rect.pos.x - shape_frame_rect.width / 2;
  double shape_frame_rect_top_left_y = shape_frame_rect.pos.y + shape_frame_rect.height / 2;

  double shape_frame_rect_bottom_right_x = shape_frame_rect.pos.x + shape_frame_rect.width / 2;
  double shape_frame_rect_bottom_right_y = shape_frame_rect.pos.y - shape_frame_rect.height / 2;

  point_t top_left = {shape_frame_rect_top_left_x, shape_frame_rect_top_left_y};
  point_t bottom_right = {shape_frame_rect_bottom_right_x, shape_frame_rect_bottom_right_y};

  for (size_t i = 1; i < size_; i++)
  {
    shape_frame_rect = shapes_[i]->getFrameRect();

    shape_frame_rect_top_left_x = shape_frame_rect.pos.x - shape_frame_rect.width / 2;
    shape_frame_rect_top_left_y = shape_frame_rect.pos.y + shape_frame_rect.height / 2;

    shape_frame_rect_bottom_right_x = shape_frame_rect.pos.x + shape_frame_rect.width / 2;
    shape_frame_rect_bottom_right_y = shape_frame_rect.pos.y - shape_frame_rect.height / 2;

    if (shape_frame_rect_top_left_x < top_left.x)
    {
      top_left.x = shape_frame_rect_top_left_x;
    }

    if (shape_frame_rect_top_left_y > top_left.y)
    {
      top_left.y = shape_frame_rect_top_left_y;
    }

    if (shape_frame_rect_bottom_right_x > bottom_right.x)
    {
      bottom_right.x = shape_frame_rect_bottom_right_x;
    }

    if (shape_frame_rect_bottom_right_y < bottom_right.y)
    {
      bottom_right.y = shape_frame_rect_bottom_right_y;
    }
  }

  point_t center = {(top_left.x + bottom_right.x) / 2, (top_left.y + bottom_right.y) / 2};

  return {center, bottom_right.x - top_left.x, top_left.y - bottom_right.y};
}

void CompositeShape::move(const point_t &pos)
{
  point_t centre = getFrameRect().pos;
  move(pos.x - centre.x, pos.y - centre.y);
}

void CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Scale can't be < 0!");
  }

  point_t centre = getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    point_t shapeCentre = shapes_[i]->getFrameRect().pos;
    shapes_[i]->move({centre.x + ratio * (shapeCentre.x - centre.x), centre.y + ratio * (shapeCentre.y - centre.y)});

    shapes_[i]->scale(ratio);
  }
}

point_t CompositeShape::getPos() const
{
  return getFrameRect().pos;
}

void CompositeShape::rotate(double angle)
{
  double angle_cos = cos(angle * M_PI / 180);
  double angle_sin = sin(angle * M_PI / 180);

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < size_; i++)
  {
    point_t shape_center = shapes_[i]->getFrameRect().pos;

    shapes_[i]->move({center.x + angle_cos * (shape_center.x - center.x) - angle_sin * (shape_center.y - center.y),
                      center.y + angle_cos * (shape_center.y - center.y) + angle_sin * (shape_center.x - center.x)});

    shapes_[i]->rotate(angle);
  }
}
