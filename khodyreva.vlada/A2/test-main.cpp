#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace khodyreva;

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_SUITE(Rectangle_Test)

  BOOST_AUTO_TEST_CASE(Moving_To_Point)
  {
    Rectangle rectangle ({19.0, 17.0}, 7.0, 9.0);
    rectangle_t rectangleBeforeMoving = rectangle.getFrameRect();
    double areaBeforeMoving = rectangle.getArea();
    rectangle.move({7.0, 5.0});
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, rectangle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, rectangle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Relative_Moving)
  {
    Rectangle rectangle({19.0, 17.0}, 7.0, 9.0);
    rectangle_t rectangleBeforeMoving = rectangle.getFrameRect();
    double areaBeforeMoving = rectangle.getArea();
    rectangle.move(19.0, -17.0);
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, rectangle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, rectangle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rectangle({19.0, 17.0}, 7.0, 9.0);
    double areaBeforeScaling = rectangle.getArea();
    rectangle.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(areaBeforeScaling * 4.0, rectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Constructor)
  {
    BOOST_CHECK_THROW(Rectangle rectangle({19.0, 17.0}, -7.0, 9.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rectangle({19.0, 17.0}, 7.0, -9.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Rectangle rectangle({19.0, 17.0}, 7.0, 9.0);
    BOOST_CHECK_THROW(rectangle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Moving_To_Point)
  {
    Circle circle ({9.0, 7.0}, 5.0);
    rectangle_t rectangleBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    circle.move({1.0, 3.0});
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Relative_Moving)
  {
    Circle circle({9.0, 7.0}, 5.0);
    rectangle_t rectangleBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();
    circle.move(9.0, -7.0);
    BOOST_REQUIRE_EQUAL(areaBeforeMoving, circle.getArea());
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectangleBeforeMoving.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Circle circle({9.0, 7.0}, 5.0);
    double areaBeforeScaling = circle.getArea();
    circle.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(areaBeforeScaling * 4.0, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Constructor)
  {
    BOOST_CHECK_THROW(Circle circle({9.0, 7.0}, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Circle circle({9.0, 7.0}, 5.0);
    BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
