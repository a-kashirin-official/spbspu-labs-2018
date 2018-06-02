//
// Created by 811432 on 15.04.2018.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(CircleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(turkin::Circle circle(-3.3, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    turkin::Circle circle{3.3, {1, 2}};
    circle.move({4, 5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    turkin::Circle circle{3.3, {1, 2}};
    circle.move(4, 5);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    turkin::Circle circle{3, {1, 2}};
    BOOST_CHECK_CLOSE(circle.getArea(), 28.274333882308138, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    turkin::Circle circle{3, {1, 2}};
    circle.scale(2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 6, Accuracy);
    BOOST_CHECK_CLOSE(circle.getArea(), 113.09733552923255, Accuracy);
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


//Testing class Rectangle
BOOST_AUTO_TEST_SUITE(RectangleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(turkin::Rectangle rectangle(-5, 7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(turkin::Rectangle rectangle(5, -7.5, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move({4, 5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move(4, 5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    turkin::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.scale(1.5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 11.25, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 84.375, Accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TriangleTests)
  const double fault = 0.00001;

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    turkin::Triangle triangle({3.0,10.0}, {4.0,5.0}, {2.0,3.0});
    triangle.move({4.0, 5.0});
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 4, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 5.5, fault);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    turkin::Triangle triangle({3.0,10.0}, {4.0,5.0}, {2.0,3.0});
    triangle.move(4.0, 5.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 7, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 11.5, fault);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    turkin::Triangle triangle({3.0,10.0}, {4.0,5.0}, {2.0,3.0});
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, fault);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    turkin::Triangle triangle({3.0,10.0}, {4.0,5.0}, {2.0,3.0});
    triangle.scale(2.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 4, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 14, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 3, fault);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 7, fault);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
