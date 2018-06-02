#define BOOST_TEST_MODULE MyTest
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double tolerance = 1e-4;

BOOST_AUTO_TEST_SUITE(RectangleTest)
double widthRect = 1, heightRect = 4;
ryabov::rectangle_t frame;
double areaPrev, areaCur;
ryabov::Rectangle rect(widthRect, heightRect);

BOOST_AUTO_TEST_CASE(MovingToPoint)
{
  areaPrev = rect.getArea();
  rect.move({ 10, 20 });
  areaCur = rect.getArea();
  frame = rect.getFrameRect();
  BOOST_CHECK_CLOSE(widthRect, frame.width, tolerance);
  BOOST_CHECK_CLOSE(heightRect, frame.height, tolerance);
  BOOST_CHECK_CLOSE(areaPrev, areaCur, tolerance);
}

BOOST_AUTO_TEST_CASE(MovingAxes)
{
  areaPrev = rect.getArea();
  rect.move(2, 4);
  areaCur = rect.getArea();
  frame = rect.getFrameRect();
  BOOST_CHECK_CLOSE(widthRect, frame.width, tolerance);
  BOOST_CHECK_CLOSE(heightRect, frame.height, tolerance);
  BOOST_CHECK_CLOSE(areaPrev, areaCur, tolerance);
}

BOOST_AUTO_TEST_CASE(Scaling)
{
  double factor = 3.0;
  areaPrev = rect.getArea();
  rect.scale(factor);
  areaCur = rect.getArea();
  BOOST_CHECK_CLOSE(areaPrev * factor * factor, areaCur, tolerance);
}

BOOST_AUTO_TEST_CASE(InvalidArguments)
{
  frame = { -10.0, -20.0, {0.0, 0.0} };
  BOOST_CHECK_THROW(ryabov::Rectangle(-10, -14), std::invalid_argument);
  BOOST_CHECK_THROW(ryabov::Rectangle(-10, 4), std::invalid_argument);
  BOOST_CHECK_THROW(ryabov::Rectangle(4, -10), std::invalid_argument);
  BOOST_CHECK_THROW(ryabov::Rectangle{frame}, std::invalid_argument);
  BOOST_CHECK_THROW(rect.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)
double radius = 4.0;
ryabov::rectangle_t frame;
double areaPrev, areaCur;
ryabov::Circle circ(radius);

BOOST_AUTO_TEST_CASE(MovingToPoint)
{
  areaPrev = circ.getArea();
  circ.move({ 4, 7 });
  areaCur = circ.getArea();
  frame = circ.getFrameRect();
  BOOST_CHECK_CLOSE(radius * 2, frame.width, tolerance);
  BOOST_CHECK_CLOSE(radius * 2, frame.height, tolerance);
  BOOST_CHECK_CLOSE(areaPrev, areaCur, tolerance);
}

BOOST_AUTO_TEST_CASE(MovingAxes)
{
  areaPrev = circ.getArea();
  circ.move(5, 2);
  areaCur = circ.getArea();
  frame = circ.getFrameRect();
  BOOST_CHECK_CLOSE(radius * 2, frame.width, tolerance);
  BOOST_CHECK_CLOSE(radius * 2, frame.height, tolerance);
  BOOST_CHECK_CLOSE(areaPrev, areaCur, tolerance);
}

BOOST_AUTO_TEST_CASE(Scaling)
{
  double factor = 2.0;
  areaPrev = circ.getArea();
  circ.scale(factor);
  areaCur = circ.getArea();
  BOOST_CHECK_CLOSE(areaPrev * factor * factor, areaCur, tolerance);
}

BOOST_AUTO_TEST_CASE(InvalidArguments)
{
  BOOST_CHECK_THROW(ryabov::Circle(-4), std::invalid_argument);
  BOOST_CHECK_THROW(circ.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
