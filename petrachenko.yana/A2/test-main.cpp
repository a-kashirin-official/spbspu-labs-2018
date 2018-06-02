#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

const double ACCURACY = 0.0001;
const double RADIUS = 21.0;
const double AREA = M_PI * RADIUS * RADIUS;
const double COEFFICIENT = 1.1;

BOOST_AUTO_TEST_SUITE(Rectangle_test)
  BOOST_AUTO_TEST_CASE(Constructor_test_for_rectangle)
  {
    BOOST_CHECK_THROW(petrachenko::Rectangle rectangle(-21.0, 48.4, {87.6, 101.01}), std::invalid_argument);
    BOOST_CHECK_THROW(petrachenko::Rectangle rectangle(21.0, -48.4, {87.6, 101.01}), std::invalid_argument);
    BOOST_CHECK_THROW(petrachenko::Rectangle rectangle(-21.0, -48.4, {87.6, 101.01}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_to_delta_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    rectangle.move(14.8, 88.0);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 21.0, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 48.4, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 21.0*48.4, ACCURACY);
  }

   BOOST_AUTO_TEST_CASE(Move_to_point_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    rectangle.move({13.0, 13.5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 21.0, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 48.4, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 21.0*48.4, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    rectangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 21.0*48.4*pow(COEFFICIENT, 2), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_coefficient_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    BOOST_CHECK_THROW(rectangle.scale(-2.3), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_test)
  BOOST_AUTO_TEST_CASE(Constructor_test_for_circle)
  {
    BOOST_CHECK_THROW(petrachenko::Circle circle(-21.0, {87.6, 101.01}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_to_delta_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    circle.move(14.8, 88.0);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    circle.move({13.0, 13.5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().width / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    circle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA*pow(COEFFICIENT, 2), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_coefficient_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    BOOST_CHECK_THROW(circle.scale(-2.3), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

