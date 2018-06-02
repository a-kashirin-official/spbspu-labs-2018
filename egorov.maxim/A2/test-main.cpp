#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "rectangle.hpp"
#include "circle.hpp"
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

using namespace egorov;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Invalid_Initialization)
  {
    BOOST_CHECK_THROW(Circle(-5, {0, 0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle circle(5, {5, 3});
    double tmpHeight = circle.getFrameRect().height;
    double tmpWidth = circle.getFrameRect().width;
    double tmpArea = circle.getArea();
    circle.move({10, 12});
    BOOST_CHECK(circle.getFrameRect().pos.x == 10 && circle.getFrameRect().pos.y == 12);
    BOOST_CHECK_CLOSE(tmpArea, circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, circle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, circle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(DeltaMove)
  {
    Circle circle(5, {0, 0});
    double tmpHeight = circle.getFrameRect().height;
    double tmpWidth = circle.getFrameRect().width;
    double tmpArea = circle.getArea();
    circle.move(1, 2);
    BOOST_CHECK(circle.getFrameRect().pos.x == 1 && circle.getFrameRect().pos.y == 2);
    BOOST_CHECK_CLOSE(tmpArea, circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, circle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, circle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Circle circle(5, {0, 0});
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_Scale)
  {
    Circle circle(5, {0, 0});
    double tmpArea = circle.getArea();
    circle.scale(2);
    BOOST_CHECK_CLOSE(2 * 2 * tmpArea, circle.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle_Test)

  BOOST_AUTO_TEST_CASE(Invalid_Initialization)
  {
    BOOST_CHECK_THROW(Rectangle({-5, -5, {0, 0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rectangle({2, 4, {1, 1}});
    double tmpHeight = rectangle.getFrameRect().height;
    double tmpWidth = rectangle.getFrameRect().width;
    double tmpArea = rectangle.getArea();
    rectangle.move({5, 5});
    BOOST_CHECK(rectangle.getFrameRect().pos.x == 5 && rectangle.getFrameRect().pos.y);
    BOOST_CHECK_CLOSE(tmpArea, rectangle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, rectangle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, rectangle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(DeltaMove)
  {
    Rectangle rectangle({2, 4, {1, 1}});
    double tmpHeight = rectangle.getFrameRect().height;
    double tmpWidth = rectangle.getFrameRect().width;
    double tmpArea = rectangle.getArea();
    rectangle.move(1, 2);
    BOOST_CHECK(rectangle.getFrameRect().pos.x == 2 && rectangle.getFrameRect().pos.y == 3);
    BOOST_CHECK_CLOSE(tmpArea, rectangle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, rectangle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, rectangle.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Rectangle rectangle({5, 5, {1, 1}});
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_Scale)
  {
    Rectangle rectangle({5, 5, {1, 1}});
    double tmpArea = rectangle.getArea();
    rectangle.scale(2);
    BOOST_CHECK_CLOSE(2 * 2 * tmpArea, rectangle.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
