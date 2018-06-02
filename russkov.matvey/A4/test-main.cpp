//
// Created by matvey on 28.05.18.
//
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

BOOST_AUTO_TEST_SUITE(Rotate_Tests)

  const double EPS = 0.0001;

  BOOST_AUTO_TEST_CASE(CircleTest)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Circle circle(point, 14.0);
    russkov::rectangle_t rectBefore = circle.getFrameRect();
    circle.rotate(50.0);
    russkov::rectangle_t rectAfter = circle.getFrameRect();
    BOOST_CHECK_CLOSE(rectBefore.height, rectAfter.height, EPS);
    BOOST_CHECK_CLOSE(rectBefore.width, rectAfter.width, EPS);
    BOOST_CHECK_CLOSE(rectBefore.pos.x, rectAfter.pos.x, EPS);
    BOOST_CHECK_CLOSE(rectBefore.pos.y, rectAfter.pos.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(RectangleTest)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Rectangle rect(point, 10.0, 20.0);
    russkov::rectangle_t rectBefore = rect.getFrameRect();
    rect.rotate(50.0);
    russkov::rectangle_t rectAfter = rect.getFrameRect();
    BOOST_CHECK_CLOSE(rectBefore.height, rectAfter.height, EPS);
    BOOST_CHECK_CLOSE(rectBefore.width, rectAfter.width, EPS);
    BOOST_CHECK_CLOSE(rectBefore.pos.x, rectAfter.pos.x, EPS);
    BOOST_CHECK_CLOSE(rectBefore.pos.y, rectAfter.pos.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeTest)
  {
    russkov::point_t point = {4.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 50.0, 40.0));
    std::shared_ptr<russkov::Shape> circlePtr (new russkov::Circle(point, 56.0));
    russkov::CompositeShape comp_shape(rectPtr);
    comp_shape.addShape(circlePtr);
    russkov::rectangle_t comp_shapeBefore = comp_shape.getFrameRect();
    comp_shape.rotate(50.0);
    russkov::rectangle_t comp_shapeAfter = comp_shape.getFrameRect();
    BOOST_CHECK_CLOSE(comp_shapeBefore.height, comp_shapeAfter.height, EPS);
    BOOST_CHECK_CLOSE(comp_shapeBefore.width, comp_shapeAfter.width, EPS);
    BOOST_CHECK_CLOSE(comp_shapeBefore.pos.x, comp_shapeAfter.pos.x, EPS);
    BOOST_CHECK_CLOSE(comp_shapeBefore.pos.y, comp_shapeAfter.pos.y, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_Tests)

  const double EPS = 0.0001;

  BOOST_AUTO_TEST_CASE(AddShapeTest)
  {
    russkov::point_t point = {4.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 50.0, 40.0));
    std::shared_ptr<russkov::Shape> circlePtr (new russkov::Circle(point, 56.0));
    russkov::Matrix matrix(rectPtr);
    matrix.addShape(circlePtr);


    BOOST_CHECK_CLOSE_FRACTION(matrix[0][0] -> getFrameRect().width, rectPtr -> getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE_FRACTION(matrix[0][0] -> getFrameRect().height, rectPtr -> getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE_FRACTION(matrix[1][0] -> getFrameRect().width, circlePtr -> getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE_FRACTION(matrix[1][0] -> getFrameRect().height, circlePtr -> getFrameRect().height, EPS);
  }

  BOOST_AUTO_TEST_CASE(AddCompositeShapeTest)
  {
    russkov::point_t point = {4.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr1 (new russkov::Rectangle(point, 50.0, 40.0));
    std::shared_ptr<russkov::Shape> circlePtr (new russkov::Circle(point, 56.0));
    point = {6.0, 7.0};
    std::shared_ptr<russkov::Shape> rectPtr2 (new russkov::Rectangle(point, 23.0, 50.0));
    russkov::CompositeShape comp_shape(rectPtr1);
    russkov::Matrix matrix(rectPtr1);
    comp_shape.addShape(rectPtr2);
    matrix.addShape(rectPtr2);

    std::shared_ptr<russkov::Shape> compPtr (new russkov::CompositeShape(comp_shape));
    matrix.addShape(compPtr);

    BOOST_CHECK_CLOSE_FRACTION(matrix[0][0] -> getFrameRect().width, rectPtr1 -> getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE_FRACTION(matrix[0][0] -> getFrameRect().height, rectPtr1 -> getFrameRect().height, EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentConstructorTest)
  {
    BOOST_REQUIRE_THROW(russkov::Matrix matrix_shape(nullptr), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
