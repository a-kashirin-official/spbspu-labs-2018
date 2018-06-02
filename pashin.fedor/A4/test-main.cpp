#define BOOST_TEST_MAIN

#include <cmath>
#include <stdexcept>

#include <boost/test/included/unit_test.hpp>

#include "shapes-partition.hpp"
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace std;
using namespace pashin;
using namespace detail;

const double kTolerance = 1E-10;

const point_t kMovePoint = {-3, 44};
const double kMoveDx = 3;
const double kMoveDy = 8;

const double kScaleK = 1.5;
const double kInvalidScale = -2.3;

const double kRotateAngle = 32.1;

const point_t kCircleCenter = {8, 5};
const double kCircleRadius = 3;
const double kInvalidRadius = -1;

const point_t kRectangleCenter = {12, 15};
const double kWidth = 4;
const double kHeight = 5;
const double kInvaidWidth = -1;
const double kInvaidHeight = -1;

const point_t kVertices[3] = {{15, 21}, {32, 7}, {3, 80}};


BOOST_AUTO_TEST_SUITE(circle)

  BOOST_AUTO_TEST_CASE(constructor)
  {
    BOOST_CHECK_THROW(Circle circle(kCircleCenter, kInvalidRadius), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(move)
  {
    Circle circle(kCircleCenter, kCircleRadius);
    double area = circle.getArea();
    circle.move(kMovePoint);
    BOOST_CHECK_CLOSE(circle.getArea(), area, kTolerance);
    BOOST_CHECK_CLOSE(circle.getRadius(), kCircleRadius, kTolerance);
    circle.move(kMoveDx, kMoveDy);
    BOOST_CHECK_CLOSE(circle.getArea(), area, kTolerance);
    BOOST_CHECK_CLOSE(circle.getRadius(), kCircleRadius, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Circle circle(kCircleCenter, kCircleRadius);
    point_t center = circle.getCenter();
    double area = circle.getArea();
    circle.scale(kScaleK);
    BOOST_CHECK_EQUAL(circle.getCenter().x, center.x);
    BOOST_CHECK_EQUAL(circle.getCenter().y, center.y);
    BOOST_CHECK_CLOSE(circle.getArea(), area * pow(kScaleK, 2), kTolerance);
    BOOST_CHECK_THROW(circle.scale(kInvalidScale), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    Circle circle(kCircleCenter, kCircleRadius);
    const point_t& center = circle.getCenter();
    double area = circle.getArea();
    circle.rotate(kRotateAngle);
    BOOST_CHECK_EQUAL(circle.getCenter().x, center.x);
    BOOST_CHECK_EQUAL(circle.getCenter().y, center.y);
    BOOST_CHECK_EQUAL(circle.getArea(), area);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle)

  BOOST_AUTO_TEST_CASE(constructor)
  {
    BOOST_CHECK_THROW(Rectangle rectangle(kRectangleCenter, kInvaidWidth, kHeight), invalid_argument);
    BOOST_CHECK_THROW(Rectangle rectangle(kRectangleCenter, kWidth, kInvaidHeight), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(move)
  {
    Rectangle rectangle(kRectangleCenter, kWidth, kHeight);
    double area = rectangle.getArea();
    rectangle.move(kMovePoint);
    BOOST_CHECK_CLOSE(rectangle.getWidth(), kWidth, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getHeight(),kHeight, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area, kTolerance);
    rectangle.move(kMoveDx, kMoveDy);
    BOOST_CHECK_CLOSE(rectangle.getWidth(), kWidth, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), kHeight, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rectangle(kRectangleCenter, kWidth, kHeight);
    const point_t& center = rectangle.getCenter();
    double area = rectangle.getArea();
    rectangle.scale(kScaleK);
    BOOST_CHECK_EQUAL(rectangle.getCenter().x, center.x);
    BOOST_CHECK_EQUAL(rectangle.getCenter().y, center.y);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area * pow(kScaleK, 2), kTolerance);
    BOOST_CHECK_THROW(rectangle.scale(kInvalidScale), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    Rectangle rectangle(kRectangleCenter, kWidth, kHeight, 0);
    const point_t& center = rectangle.getCenter();
    double area = rectangle.getArea();
    rectangle.rotate(kRotateAngle);
    BOOST_CHECK_EQUAL(rectangle.getCenter().x, center.x);
    BOOST_CHECK_EQUAL(rectangle.getCenter().y, center.y);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area, kTolerance);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(triangle)

  BOOST_AUTO_TEST_CASE(move)
  {
    Triangle triangle(kVertices);
    double area = triangle.getArea();
    rectangle_t frame_rect = triangle.getFrameRect();
    triangle.move(kMovePoint);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, kTolerance);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, frame_rect.width, kTolerance);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, frame_rect.height, kTolerance);
    triangle.move(kMoveDx, kMoveDy);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Triangle triangle(kVertices);
    const point_t& center = triangle.getCenter();
    double area = triangle.getArea();
    triangle.scale(kScaleK);
    BOOST_CHECK_CLOSE(triangle.getCenter().x, center.x, kTolerance);
    BOOST_CHECK_CLOSE(triangle.getCenter().y, center.y, kTolerance);
    BOOST_CHECK_CLOSE(triangle.getArea(), area * pow(kScaleK, 2), kTolerance);
    BOOST_CHECK_THROW(triangle.scale(kInvalidScale), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    Triangle triangle(kVertices);
    const point_t& center = triangle.getCenter();
    double area = triangle.getArea();
    triangle.rotate(kRotateAngle);
    BOOST_CHECK_CLOSE(triangle.getCenter().x, center.x, kTolerance);
    BOOST_CHECK_CLOSE(triangle.getCenter().y, center.y, kTolerance);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, kTolerance);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(composite_shape)

  BOOST_AUTO_TEST_CASE(move)
  {
    CompositeShape composite_shape;
    Circle shape_1(kCircleCenter, kCircleRadius);
    composite_shape.addShape(&shape_1);
    Rectangle shape_2(kRectangleCenter, kWidth, kHeight);
    composite_shape.addShape(&shape_2);
    double area = composite_shape.getArea();
    rectangle_t frame_rect = composite_shape.getFrameRect();
    composite_shape.move(kMovePoint);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), area, kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, frame_rect.width, kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, frame_rect.height, kTolerance);
    composite_shape.move(kMoveDx, kMoveDy);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), area, kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, frame_rect.width, kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, frame_rect.height, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    CompositeShape composite_shape;
    Circle shape_1(kCircleCenter, kCircleRadius);
    composite_shape.addShape(&shape_1);
    Rectangle shape_2(kRectangleCenter, kWidth, kHeight);
    composite_shape.addShape(&shape_2);
    double area = composite_shape.getArea();
    point_t center = composite_shape.getCenter();
    composite_shape.scale(kScaleK);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), area * pow(kScaleK, 2), kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getCenter().x, center.x, kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getCenter().y, center.y, kTolerance);
    BOOST_CHECK_THROW(composite_shape.scale(kInvalidScale), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    CompositeShape composite_shape;
    vector<rectangle_t> frame_rects;
    Circle shape_1(kCircleCenter, kCircleRadius);
    composite_shape.addShape(&shape_1);
    frame_rects.push_back(shape_1.getFrameRect());
    Rectangle shape_2(kRectangleCenter, kWidth, kHeight);
    composite_shape.addShape(&shape_2);
    frame_rects.push_back(shape_2.getFrameRect());
    const point_t& center = composite_shape.getCenter();
    double area = composite_shape.getArea();
    composite_shape.rotate(kRotateAngle);
    BOOST_CHECK_CLOSE(composite_shape.getCenter().x, center.x, kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getCenter().y, center.y, kTolerance);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), area, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(manageShapes)
  {
    CompositeShape composite_shape;
    Array<Shape*> shapes;
    Circle shape_1(kCircleCenter, kCircleRadius);
    composite_shape.addShape(&shape_1);
    shapes.push_back(&shape_1);
    BOOST_CHECK(composite_shape.getShapes() == shapes);
    Rectangle removing_shape(kRectangleCenter, kWidth, kHeight);
    composite_shape.addShape(&removing_shape);
    shapes.push_back(&removing_shape);
    Triangle shape_3(kVertices);
    composite_shape.addShape(&shape_3);
    shapes.push_back(&shape_3);
    composite_shape.removeShape(&removing_shape);
    auto it = find(shapes.begin(), shapes.end(), &removing_shape);
    shapes.erase(it);
    BOOST_CHECK(composite_shape.getShapes() == shapes);
    BOOST_CHECK_THROW(composite_shape.removeShape(&removing_shape), invalid_argument);
    BOOST_CHECK_THROW(composite_shape.removeShape(nullptr), invalid_argument);
    BOOST_CHECK_THROW(composite_shape.addShape(nullptr), invalid_argument);
    BOOST_CHECK_THROW(composite_shape.addShape(&shape_1), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(shapesPartition)
  {
    CompositeShape composite_shape;
    Circle shape_1({0, 0}, 5);
    composite_shape.addShape(&shape_1);
    Rectangle shape_2({150, 320}, 10, 5);
    composite_shape.addShape(&shape_2);
    Rectangle shape_3({-1, 3}, 4, 6);
    composite_shape.addShape(&shape_3);
    Rectangle shape_4({-32, 44}, 700, 800);
    composite_shape.addShape(&shape_4);
    BOOST_CHECK(composite_shape.getLayers().getShape(0, 0) == &shape_1);
    BOOST_CHECK(composite_shape.getLayers().getShape(0, 1) == &shape_2);
    BOOST_CHECK(composite_shape.getLayers().getShape(1, 0) == &shape_3);
    BOOST_CHECK(composite_shape.getLayers().getShape(2, 0) == &shape_4);
    composite_shape.removeShape(&shape_3);
    BOOST_CHECK(composite_shape.getLayers().getShape(1, 0) == nullptr);
    BOOST_CHECK_THROW(composite_shape.getLayers().getShape(3, 0), invalid_argument);
    BOOST_CHECK_THROW(composite_shape.getLayers().getShape(0, 3), invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();
