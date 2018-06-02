#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

#define BOOST_TEST_MODULE testMain
#include <boost/test/included/unit_test.hpp>

// Delta epsilon
const double Epsilon = 0.0000001;

// Testing Rectangle class
BOOST_AUTO_TEST_SUITE(testSuiteCircle)

// Cover for the test rect object
struct CircleFixture
{
  // Test rect object
  hvatov::Circle circle;

  // Test rect init
  CircleFixture() :
    circle({ 30, 30 }, 10)
  {

  }

  // Test rect destructor
  ~CircleFixture() = default;
};

BOOST_FIXTURE_TEST_CASE(testCircleMove1, CircleFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(circle.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);

  // Move and check again
  circle.move({ 300, 300 });
  BOOST_CHECK_CLOSE(circle.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testCircleMove2, CircleFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(circle.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);

  // Move and check again
  circle.move(270, 270);
  BOOST_CHECK_CLOSE(circle.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), 10, Epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testCircleArea, CircleFixture)
{
  // Scale object 10 times and check its area
  circle.scale(10);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10 * 10 * 10 * 10, Epsilon);
  // Scale object 5 times and check its area
  circle.scale(5);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 5 * 5 * 10 * 10 * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testCircleThrowScale, CircleFixture)
{
  // Check if throws exceptions in scale method
  BOOST_CHECK_THROW(circle.scale(-5), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testCircleThrowConstructor, CircleFixture)
{
  // Check if throws exceptions in constructor
  BOOST_CHECK_THROW(hvatov::Circle(10, 10, -10), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

// Testing Rect class
BOOST_AUTO_TEST_SUITE(testSuiteRectangle)

// Cover for the test rect object
struct RectFixture
{
  // Test rect object
  hvatov::Rectangle rect;

  // Test rect init
  RectFixture() :
    rect({ 30, 30 }, 10, 10)
  {

  }

  // Test rect destructor
  ~RectFixture() = default;
};

BOOST_FIXTURE_TEST_CASE(testRectangleMove1, RectFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(rect.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);

  // Move and check again
  rect.move({ 300, 300 });
  BOOST_CHECK_CLOSE(rect.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testRectangleMove2, RectFixture)
{
  // Check at the beginning
  BOOST_CHECK_CLOSE(rect.getPosition().x, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 30, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);

  // Move and check again
  rect.move(270, 270);
  BOOST_CHECK_CLOSE(rect.getPosition().x, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getPosition().y, 300, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testRectangleArea, RectFixture)
{
  // Scale object 10 times and check its area
  rect.scale(10);
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10 * 10 * 10, Epsilon);
  // Scale object 5 times and check its area
  rect.scale(5);
  BOOST_CHECK_CLOSE(rect.getArea(), 5 * 5 * 10 * 10 * 10 * 10, Epsilon);
}

BOOST_FIXTURE_TEST_CASE(testRectangleThrowScale, RectFixture)
{
  // Check if throws exceptions in scale method
  BOOST_CHECK_THROW(rect.scale(-5), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testRectangleThrowConstructor, RectFixture)
{
  // Check if throws exceptions in constructor
  BOOST_CHECK_THROW(hvatov::Rectangle(10, 10, -10, -10), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(testRectangleRotate, RectFixture)
{
  // rotate object 90 degress
  rect.rotate(90);
  // Check area
  BOOST_CHECK_CLOSE(rect.getArea(), 10 * 10, Epsilon);
  // Check other params
  BOOST_CHECK_CLOSE(rect.getHeight(), 10, Epsilon);
  BOOST_CHECK_CLOSE(rect.getWidth(), 10, Epsilon);
  // Check frame rectangle
  hvatov::rectangle_t r = rect.getFrameRect();
  BOOST_CHECK_CLOSE(r.width, 10, Epsilon);
  BOOST_CHECK_CLOSE(r.height, 10, Epsilon);
  BOOST_CHECK_CLOSE(r.pos.x, 30, Epsilon);
  BOOST_CHECK_CLOSE(r.pos.y, 30, Epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

