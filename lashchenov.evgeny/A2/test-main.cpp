#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include <boost/test/included/unit_test.hpp>

//Testing class Circle
BOOST_AUTO_TEST_SUITE(CircleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(lashchenov::Circle circle(-3.3, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Circle circle(-3.3, 1, 2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    lashchenov::Circle circle{3.3, {1, 2}};
    circle.move({4, 5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    lashchenov::Circle circle1{3.3, {1, 2}};
    circle1.move(4, 5);
    BOOST_CHECK_CLOSE(circle1.getFrameRect().height / 2, 3.3, Accuracy);
    BOOST_CHECK_CLOSE(circle1.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(circle1.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    lashchenov::Circle circle{3.3, {1, 2}};
    BOOST_CHECK_CLOSE(circle.getArea(), 34.21194399, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    lashchenov::Circle circle{3.3, {1, 2}};
    circle.scale(1.5);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 4.95, Accuracy);
    BOOST_CHECK_CLOSE(circle.getArea(), 76.97687399, Accuracy);
    BOOST_CHECK_THROW(circle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


//Testing class Rectangle
BOOST_AUTO_TEST_SUITE(RectangleTests)
  const double Accuracy = 0.00001;

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(-5, 7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(-5, 7.5, 1, 2), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(5, -7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(lashchenov::Rectangle rectangle(5, -7.5, 1, 2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    lashchenov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move({4, 5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    lashchenov::Rectangle rectangle1(5, 7.5, {1, 2});
    rectangle1.move(4, 5);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().width, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().height, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().pos.x, 5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle1.getFrameRect().pos.y, 7, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    lashchenov::Rectangle rectangle(5, 7.5, {1, 2});
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    lashchenov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.scale(1.5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.5, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 11.25, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 84.375, Accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
