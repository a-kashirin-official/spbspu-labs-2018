#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"

const double TOLERANCE = 0.0001;

BOOST_AUTO_TEST_SUITE(testRectangle)

BOOST_AUTO_TEST_CASE(move_size)
{
  stankeviciute::Rectangle rectangle({0, 0}, 4, 8);
  rectangle.move(10, 20);
  
  BOOST_CHECK_CLOSE(rectangle.getWidth(), 4, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), 8, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_area)
{
  stankeviciute::Rectangle rectangle({10, 10}, 5, 3);
  rectangle.move({0, 0});
  
  BOOST_CHECK_CLOSE(rectangle.getArea(), 15, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_size)
{
  stankeviciute::Rectangle rectangle({5, 2}, 7, 1);
  rectangle.scale(0.5);
  
  BOOST_CHECK_CLOSE(rectangle.getWidth(), 3.5, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), 0.5, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_area)
{
  stankeviciute::Rectangle rectangle({0, 0}, 2, 3);;
  rectangle.scale(2);
  
  BOOST_CHECK_CLOSE(rectangle.getArea(), 24, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(rotate_size)
{
  stankeviciute::Rectangle rectangle({0, 10}, 5, 8);
  rectangle.rotate(90);
  
  BOOST_CHECK_CLOSE(rectangle.getWidth(), 5, TOLERANCE);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), 8, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(rotate_area)
{
  stankeviciute::Rectangle rectangle({0, 0}, 2, 3);
  rectangle.rotate(120);
  
  BOOST_CHECK_CLOSE(rectangle.getArea(), 6, TOLERANCE);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testTriangle)

BOOST_AUTO_TEST_CASE(move_center)
{
  stankeviciute::Triangle triangle({-3, 0}, {0, 9}, {3, 0});
  triangle.move(5, 6);
  
  BOOST_CHECK_CLOSE(triangle.getCenter().x, 5, TOLERANCE);
  BOOST_CHECK_CLOSE(triangle.getCenter().y, 9, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_area)
{
  stankeviciute::Triangle triangle({0, 0}, {0, 2}, {3, 0});
  triangle.move({7, 3});
  
  BOOST_CHECK_CLOSE(triangle.getArea(), 3, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_center)
{
  stankeviciute::Triangle triangle({1, 0}, {2, 3}, {3, 0});
  triangle.scale(3);
  
  BOOST_CHECK_CLOSE(triangle.getCenter().x, 2, TOLERANCE);
  BOOST_CHECK_CLOSE(triangle.getCenter().y, 1, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_area)
{
  stankeviciute::Triangle triangle({1, -1}, {3, -1}, {1, -3});
  triangle.scale(2);
  
  BOOST_CHECK_CLOSE(triangle.getArea(), 8, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(rotate_center)
{
  stankeviciute::Triangle triangle({-2, 0}, {0, 3}, {2, 0});
  triangle.rotate(0);
  
  BOOST_CHECK_CLOSE(triangle.getCenter().x, 0, TOLERANCE);
  BOOST_CHECK_CLOSE(triangle.getCenter().y, 1, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(rotate_area)
{
  stankeviciute::Triangle triangle({0, 0}, {0, 5}, {2, 0});
  triangle.rotate(270);
  
  BOOST_CHECK_CLOSE(triangle.getArea(), 5, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(invalid_constructor)
{ 
  BOOST_CHECK_THROW(stankeviciute::Triangle triangle({1, 0}, {2, 0}, {3, 0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_scale)
{
  stankeviciute::Triangle triangle({6, 2}, {0, 3}, {5, 2});

  BOOST_CHECK_THROW(triangle.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testRotation)

BOOST_AUTO_TEST_CASE(rectangle)
{
  stankeviciute::Rectangle rectangle({10, 0}, 3, 3);
  rectangle.rotate(-45);

  stankeviciute::rectangle_t frame_rect = rectangle.getFrameRect();
  
  BOOST_CHECK_CLOSE(frame_rect.pos.x, 10, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.pos.y, 0, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.width, 3 * sqrt(2), TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.height, 3 * sqrt(2), TOLERANCE);
}

BOOST_AUTO_TEST_CASE(triangle)
{
  stankeviciute::Triangle triangle({0, 0}, {0, 2}, {2, 0});
  triangle.rotate(360);

  stankeviciute::rectangle_t frame_rect = triangle.getFrameRect();
  
  BOOST_CHECK_CLOSE(frame_rect.pos.x, 1, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.pos.y, 1, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.width, 2, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.height, 2, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(composite_shape)
{
  auto rectangle_1 = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{-3, -5}, 4, 4);
  auto rectangle_2 = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{4, 2}, 4, 4);

  stankeviciute::CompositeShape composite_shape(rectangle_1);
  composite_shape.addShape(rectangle_2);
  composite_shape.rotate(90);

  stankeviciute::rectangle_t frame_rect = composite_shape.getFrameRect();
  
  BOOST_CHECK_CLOSE(frame_rect.pos.x, 0.5, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.pos.y, -1.5, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.width, 11, TOLERANCE);
  BOOST_CHECK_CLOSE(frame_rect.height, 11, TOLERANCE);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testMatrixShape)

BOOST_AUTO_TEST_CASE(new_rows)
{
  auto rectangle = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{-3, -1}, 4, 4);
  auto circle = std::make_shared<stankeviciute::Circle>(stankeviciute::point_t{-1, 0}, 2);
  auto triangle = std::make_shared<stankeviciute::Triangle>(stankeviciute::point_t{4, 2}, stankeviciute::point_t{6, -2}, stankeviciute::point_t{2, -1});
  
  stankeviciute::MatrixShape matrix_shape(rectangle);
  matrix_shape.addShape(circle);
  matrix_shape.addShape(triangle);
  
  BOOST_CHECK(matrix_shape[1][0] == circle);
}

BOOST_AUTO_TEST_CASE(new_columns)
{
  auto rectangle_1 = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{-2, 2}, 2, 2);
  auto rectangle_2 = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{0, 0}, 2, 2);
  auto rectangle_3 = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{2, -2}, 2, 2);
  
  stankeviciute::MatrixShape matrix_shape(rectangle_1);
  matrix_shape.addShape(rectangle_2);
  matrix_shape.addShape(rectangle_3);
  
  BOOST_CHECK(matrix_shape[0][2] == rectangle_3);
}

BOOST_AUTO_TEST_CASE(add_one_shape)
{
  auto triangle = std::make_shared<stankeviciute::Triangle>(stankeviciute::point_t{0, 0}, stankeviciute::point_t{0, 5}, stankeviciute::point_t{8, 0});
  stankeviciute::MatrixShape matrix_shape(triangle);
  
  BOOST_CHECK(matrix_shape[0][0] == triangle);
}

BOOST_AUTO_TEST_CASE(add_composite_shape)
{
  auto rectangle_1 = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{0, 3}, 4, 2);
  auto rectangle_2 = std::make_shared<stankeviciute::Rectangle>(stankeviciute::point_t{-1, -1}, 2, 2);
  auto circle = std::make_shared<stankeviciute::Circle>(stankeviciute::point_t{0, 2}, 2);

  auto composite_shape_1 = std::make_shared<stankeviciute::CompositeShape>(rectangle_1);
  composite_shape_1->addShape(circle);

  auto composite_shape_2 = std::make_shared<stankeviciute::CompositeShape>(composite_shape_1);

  stankeviciute::MatrixShape matrix_shape(composite_shape_1);
  matrix_shape.addShape(composite_shape_2);

  BOOST_CHECK(matrix_shape[0][0] == composite_shape_1 && matrix_shape[1][0] == composite_shape_2);
}

BOOST_AUTO_TEST_CASE(invalid_constructor)
{ 
  BOOST_CHECK_THROW(stankeviciute::MatrixShape matrix_shape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_add_shape)
{
  auto triangle = std::make_shared<stankeviciute::Triangle>(stankeviciute::point_t{-2, 3}, stankeviciute::point_t{0, 5}, stankeviciute::point_t{5, -2});
  stankeviciute::MatrixShape matrix_shape(triangle);
  
  BOOST_CHECK_THROW(matrix_shape.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
