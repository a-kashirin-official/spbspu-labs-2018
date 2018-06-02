#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"

const double dx = 0.0001;

BOOST_AUTO_TEST_SUITE(testCircle)

  BOOST_AUTO_TEST_CASE(test_Circle_moving_width)
  {
    kostylev::Circle circle({24.73, 19.81}, 5.2);
    circle.move(5.87, 10.39);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width/2, 5.2);
  }

  BOOST_AUTO_TEST_CASE(test_Circle_moving_to_point)
  {
    kostylev::Circle circle({24.73, 19.81}, 5.2);
    circle.move({7.41, 12.38});
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width/2, 5.2);
  }

  BOOST_AUTO_TEST_CASE(test_Circle_scale_area)
  {
    kostylev::Circle circle({24.73, 19.81}, 5.2);
    circle.scale(3.1);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 3.14 * 5.2 * 5.2 * 3.1 * 3.1, dx);
  }

  BOOST_AUTO_TEST_CASE(test_Circle_invalid_parameters)
  {
    BOOST_CHECK_THROW(kostylev::Circle({24.73, 19.81}, -5.2), std::invalid_argument);
    kostylev::Circle circle{{24.73, 19.81}, 5.2};
    BOOST_CHECK_THROW(circle.scale(-1.3), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testRectangle)

  BOOST_AUTO_TEST_CASE(test_Rectangle_moving_width_height)
  {
    kostylev::Rectangle rectangle({15.97, 26.17}, 12.4, 16.5);
    rectangle.move(5.69, 9.46);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 12.4);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 16.5);
    rectangle.move({8.25, 17.31});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 12.4);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 16.5);
  }

  BOOST_AUTO_TEST_CASE(test_Rectangle_moving_area)
  {
    kostylev::Rectangle rectangle({15.97, 26.17}, 12.4, 16.5);
    rectangle.move(5.69, 9.46);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 12.4 * 16.5, dx);
  }

  BOOST_AUTO_TEST_CASE(test_Rectangle_moving_to_point_area)
  {
    kostylev::Rectangle rectangle({15.97, 26.17}, 12.4, 16.5);
    rectangle.move({5.69, 9.46});
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 12.4 * 16.5, dx);
  }

  BOOST_AUTO_TEST_CASE(test_Rectangle_scale_area)
  {
    kostylev::Rectangle rectangle({15.97, 26.17}, 12.4, 16.5);
    rectangle.scale(5.5);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 12.4 * 16.5 * 5.5 * 5.5, dx);
  }

  BOOST_AUTO_TEST_CASE(test_Rectangle_invalid_parameters)
  {
    BOOST_CHECK_THROW(kostylev::Rectangle({15.97, 26.17}, -12.4, 16.5), std::invalid_argument);
    BOOST_CHECK_THROW(kostylev::Rectangle({15.97, 26.17}, 12.4, -16.5), std::invalid_argument);
    BOOST_CHECK_THROW(kostylev::Rectangle({15.97, 26.17}, -12.4, -16.5), std::invalid_argument);
    kostylev::Rectangle rectangle{{15.97, 26.17}, 12.4, 16.5};
    BOOST_CHECK_THROW(rectangle.scale(-1.5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
