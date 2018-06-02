//
// Created by matvey on 09.05.18.
//
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  const double EPSILON = 0.001;

  BOOST_AUTO_TEST_CASE(InvalidPointer)
  {
    BOOST_CHECK_THROW(russkov::CompositeShape comp_shape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidAddShape)
  {
    russkov::point_t point = {4.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 6.0, 8.0));
    russkov::CompositeShape comp_shape(rectPtr);
    BOOST_CHECK_THROW(comp_shape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidIndexDeleteShape)
  {
    russkov::point_t point = {4.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 50.0, 40.0));
    std::shared_ptr<russkov::Shape> circlePtr (new russkov::Circle(point, 56.0));
    russkov::CompositeShape comp_shape(rectPtr);
    comp_shape.addShape(circlePtr);
    BOOST_CHECK_THROW(comp_shape.deleteShape(2), std::invalid_argument);
    BOOST_CHECK_THROW(comp_shape.deleteShape(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingArgument)
  {
    russkov::point_t point = {6.0, 8.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 40.0, 50.0));
    russkov::CompositeShape comp_shape(rectPtr);
    BOOST_CHECK_THROW(comp_shape.scale(-5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstArgumentsMoveTo)
  {
    russkov::point_t point = {6.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 6.0, 4.0));
    std::shared_ptr<russkov::Shape> circlePtr (new russkov::Circle(point, 40.0));
    russkov::CompositeShape comp_shape(rectPtr);
    comp_shape.addShape(circlePtr);
    double area = comp_shape.getArea();
    double width = comp_shape.getFrameRect().width;
    double height = comp_shape.getFrameRect().height;
    russkov::point_t new_pos = {10.0, 5.0};
    comp_shape.move(new_pos);
    BOOST_CHECK_CLOSE(comp_shape.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(comp_shape.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE(comp_shape.getFrameRect().height, height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstArgumentsMoveOn)
  {
    russkov::point_t point = {6.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 6.0, 4.0));
    std::shared_ptr<russkov::Shape> circlePtr (new russkov::Circle(point, 40.0));
    russkov::CompositeShape comp_shape(rectPtr);
    comp_shape.addShape(circlePtr);
    double area = comp_shape.getArea();
    double width = comp_shape.getFrameRect().width;
    double height = comp_shape.getFrameRect().height;
    comp_shape.move(20.0, 30.0);
    BOOST_CHECK_CLOSE(comp_shape.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(comp_shape.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE(comp_shape.getFrameRect().height, height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstArgumentsScaling)
  {
    const double RATIO = 2.0;
    russkov::point_t point = {6.0, 4.0};
    std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(point, 6.0, 4.0));
    std::shared_ptr<russkov::Shape> circlePtr (new russkov::Circle(point, 40.0));
    russkov::CompositeShape comp_shape(rectPtr);
    comp_shape.addShape(circlePtr);
    double area = comp_shape.getArea();
    double posX = comp_shape.getFrameRect().pos.x;
    double posY = comp_shape.getFrameRect().pos.y;
    comp_shape.scale(RATIO);
    BOOST_CHECK_CLOSE(comp_shape.getArea(), area*RATIO*RATIO, EPSILON);
    BOOST_CHECK_CLOSE(comp_shape.getFrameRect().pos.x, posX, EPSILON);
    BOOST_CHECK_CLOSE(comp_shape.getFrameRect().pos.y, posY, EPSILON);
  }
BOOST_AUTO_TEST_SUITE_END()
