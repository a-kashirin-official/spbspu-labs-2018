#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define USE_DEFINE_MATH

#include <cmath>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(TestCircle)

  BOOST_AUTO_TEST_CASE(ConstructorInvalidValue)
  {
    BOOST_CHECK_THROW(kudryavtseva::Circle cir({9,5}, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RadiusConstAfterMovingToPoint)
  {
    kudryavtseva::point_t p={0.0, 0.0};
    kudryavtseva::Circle cir({1.0, 1.0}, 1.0);
    cir.move(p);
    BOOST_CHECK_CLOSE(cir.getRadius(), 1.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaConstAfterMovingToPoint)
  {
    kudryavtseva::point_t p={0.0, 0.0};
    kudryavtseva::Circle cir({1.0, 1.0}, 2.0);
    cir.move(p);
    BOOST_CHECK_CLOSE(cir.getArea(), 2.0*2.0*M_PI, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RadiusConstAfterMovingByXY)
  {
    kudryavtseva::Circle cir({4.0, 5.0}, 24.0);
    cir.move(0.0, 0.0);
    BOOST_CHECK_CLOSE(cir.getRadius(), 24.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaConstAfterMovinByXY)
  {
    kudryavtseva::Circle cir({4.0, 5.0}, 3.0);
    cir.move(0.0, 0.0);
    BOOST_CHECK_CLOSE(cir.getArea(), 9.0*M_PI, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaChangeAfterScaling)
  {
    kudryavtseva::Circle cir({4.0, 5.0}, 7.0);
    cir.scale(7.0);
    BOOST_CHECK_CLOSE(cir.getArea(), 2401.0*M_PI, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ScaleInvalidValues)
  {
    kudryavtseva::Circle cir({4.0, 5.0}, 8.0);
    BOOST_CHECK_THROW(cir.scale(-78.9), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(ConstructorInvalidValues1)
  {
    BOOST_CHECK_THROW(kudryavtseva::Rectangle rect({1.0, 1.0}, -1.0, 1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstructorInvalidValues2)
  {
    BOOST_CHECK_THROW(kudryavtseva::Rectangle rect({1.8,1.8}, 1.0, -1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ConstructorInvalidValues3)
  {
    BOOST_CHECK_THROW(kudryavtseva::Rectangle rect({1.0, 1.0}, -1.0, -1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(WidthConstAfterMovingToPoint)
  {
    kudryavtseva::point_t p={0.0, 0.0};
    kudryavtseva::Rectangle rect({1.0, 1.0}, 4.82, 1.0);
    rect.move(p);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, 4.82, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(HeightConstAfterMovingToPoint)
  {
    kudryavtseva::point_t p={0.0, 0.0};
    kudryavtseva::Rectangle rect({1.0, 1.0}, 4.82, 131.22);
    rect.move(p);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, 131.22, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaConstAfterMovingToPoint)
  {
    kudryavtseva::point_t p={0.0, 0.0};
    kudryavtseva::Rectangle rect({1.0, 1.0}, 4.0, 9.0);
    rect.move(p);
    BOOST_CHECK_CLOSE(rect.getArea(), 36.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(WidthConstAfterMovingByXY)
  {
    kudryavtseva::Rectangle rect({1.0, 1.0}, 24.82, 1.0);
    rect.move(-1.1, 0.9);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, 24.82, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(HeightConstAfterMovingByXY)
  {
    kudryavtseva::Rectangle rect({1.0, 1.0}, 82.0, 12.31);
    rect.move(-1.98, 12.0);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, 12.31, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaConstAfterMovingByXY)
  {
    kudryavtseva::Rectangle rect({1.0, 1.0}, 2.0, 9.1);
    rect.move(21.0, -32.0);
    BOOST_CHECK_CLOSE(rect.getArea(), 18.2, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaChangeAfterScaling)
  {
    kudryavtseva::Rectangle rect({1.0, 1.0}, 2.0, 2.0);
    rect.scale(2.0);
    BOOST_CHECK_CLOSE(rect.getArea(), 16.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ScaleInvalidValues)
  {
    kudryavtseva::Rectangle rect({1.0, 1.0}, 2.0, 2.0);
    BOOST_CHECK_THROW(rect.scale(-322.0),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
