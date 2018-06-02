#include "composite-shape.hpp"

#include <cmath>
#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;

pashin::CompositeShape::CompositeShape():
  angle_(0)
{}

pashin::CompositeShape& pashin::CompositeShape::operator=(const pashin::CompositeShape& rhs)
{
  if (this != &rhs) {
    angle_ = rhs.angle_;
    layers_ = rhs.layers_;
    shapes_.clear();
    for (const auto& shape: rhs.shapes_) {
      shapes_.push_back(shape);
    }
  }
  return *this;
}

pashin::point_t pashin::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

double pashin::CompositeShape::getArea() const
{
  double area = 0.0;
  for (const auto& shape: shapes_) {
    area += shape->getArea();
  }
  return area;
}

pashin::rectangle_t pashin::CompositeShape::getFrameRect() const
{
  if (shapes_.empty()) {
    return {{0, 0}, 0, 0};
  }
  
  auto frame_rect = shapes_[0]->getFrameRect();
  double min_x = frame_rect.pos.x - (frame_rect.width / 2);
  double max_x = frame_rect.pos.x + (frame_rect.width / 2);
  double min_y = frame_rect.pos.y - (frame_rect.height / 2);
  double max_y = frame_rect.pos.y + (frame_rect.height / 2);
  for (auto shape: shapes_) {
    auto frame_rect = shape->getFrameRect();
    if (frame_rect.pos.x < min_x) {
      min_x = frame_rect.pos.x;
    } else if (frame_rect.pos.x > max_x) {
      max_x = frame_rect.pos.x;
    }
    if (frame_rect.pos.y < min_y) {
      min_y = frame_rect.pos.y;
    } else if (frame_rect.pos.y > max_y) {
      max_y = frame_rect.pos.y;
    }
  }
  
  return {{(min_x + max_x) / 2, (min_y + max_y) / 2},
          (max_x - min_x), (max_y - min_y)};
}

std::string pashin::CompositeShape::getInfo() const
{
  stringstream info;
  
  point_t center = getCenter();
  rectangle_t frame_rect = getFrameRect();
  info << "Type: Composite Shape" << endl
      << "Center coordinates: (" << center.x << "; " << center.y << ")" << endl
      << "Area: " << getArea() << endl
      << "Frame Rectangle:" << endl
      << "\t" << "Center coordinates: ("
      << frame_rect.pos.x << "; "
      << frame_rect.pos.y << ")" << endl
      << "\t" << "Width: " << frame_rect.width << endl
      << "\t" << "Height: " << frame_rect.height << endl
      << "Components:" << endl;
  for (int i = 0; (i < layers_.num_rows()) && (layers_.getShape(i, 0) != nullptr); ++i) {
    for (int j = 0; (j < layers_.num_columns()) && (layers_.getShape(i, j) != nullptr); ++j) {
      info << "=== Layer number " << i + 1 << " | Shape number " << j + 1 << " ===" << endl;
      info << layers_.getShape(i, j)->getInfo();
    }
  }

  return info.str();
}

void pashin::CompositeShape::move(double dx, double dy)
{
  for (auto shape: shapes_) {
    shape->move(dx, dy);
  }
}

void pashin::CompositeShape::move(const pashin::point_t& new_center)
{
  auto center = getFrameRect().pos;
  double dx = new_center.x - center.x;
  double dy = new_center.y - center.y;
  move(dx, dy);
}

void pashin::CompositeShape::scale(double k)
{
  if (!(k >= 0)) {
    throw invalid_argument("Invalid coefficient");
  }
  
  auto center = getFrameRect().pos;
  for (auto shape: shapes_) {
    auto shape_center = shape->getFrameRect().pos;
    double dx = shape_center.x - center.x;
    double dy = shape_center.y - center.y;
    shape->move(dx * (k - 1), dy * (k - 1));
    shape->scale(k);
  }
}

void pashin::CompositeShape::rotate(double angle)
{
  double angle_in_radians = angle_ * M_PI / 180;
  const point_t& center = getCenter();
  for (const auto& shape: shapes_) {
    const point_t& old_shape_center = shape->getCenter();
    point_t new_shape_center;
    new_shape_center.x = center.x + (old_shape_center.x - center.x) * cos(angle_in_radians)
                                  - (old_shape_center.y - center.y) * sin(angle_in_radians);
    new_shape_center.y = center.y + (old_shape_center.x - center.x) * sin(angle_in_radians)
                                  + (old_shape_center.y - center.y) * cos(angle_in_radians);
    shape->move(new_shape_center);
    shape->rotate(angle);
  }
}

const pashin::detail::Array<pashin::Shape*>& pashin::CompositeShape::getShapes() const
{
  return shapes_;
}

const pashin::ShapesPartition& pashin::CompositeShape::getLayers() const
{
  return layers_;
}

void pashin::CompositeShape::addShape(pashin::Shape* shape)
{
  if (shape == nullptr) {
    throw invalid_argument("Nullptr");
  }
  
  if (find(shapes_.begin(), shapes_.end(), shape) != shapes_.end()) {
    throw invalid_argument("The shape is already added");
  }
  
  shapes_.push_back(shape);
  layers_.addShape(*shape);
}

void pashin::CompositeShape::removeShape(pashin::Shape* shape)
{
  if (shape == nullptr) {
    throw invalid_argument("Nullptr");
  }
  
  auto it = find(shapes_.begin(), shapes_.end(), shape);
  if (it == shapes_.end()) {
    throw invalid_argument("The shape not found");
  }
  
  shapes_.erase(it);
  layers_.removeShape(shape);
}
