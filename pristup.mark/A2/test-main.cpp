#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

// Rectangle Tests

BOOST_AUTO_TEST_SUITE(RectangleTests)

  double EPSILON = 0.001;

  BOOST_AUTO_TEST_CASE(InvarienceOfParameters)
  {
    pristup::Rectangle rectangle({5.0, 4.0, {3.0, 7.0}});
    double area = rectangle.getArea();
      
    rectangle.move(24.0, 40.0);
      
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 5.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 4.0);
    BOOST_REQUIRE_EQUAL(rectangle.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    pristup::Rectangle rectangle({5.0, 4.0, {3.0, 7.0}});
    double area = rectangle.getArea();
      
    rectangle.scale(2.0);
      
    BOOST_REQUIRE_CLOSE_FRACTION(rectangle.getArea(), area * pow(2.0, 2.0), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ArgumentsConstructor)
  {
    BOOST_CHECK_THROW(pristup::Rectangle rectangle({-2.0, -2.0, {5.0, 4.0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ArgumentScale)
  {
    pristup::Rectangle rectangle({5.0, 4.0, {3.0, 7.0}});
    BOOST_CHECK_THROW(rectangle.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

// Circle Tests

BOOST_AUTO_TEST_SUITE(CircleTests)

  double EPSILON = 0.001;

  BOOST_AUTO_TEST_CASE(InvarienceOfParameters)
  {
    pristup::Circle circle(6.0, {12.0,12.0});
    double area = circle.getArea();
      
    circle.move(24.0, 40.0);
      
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 12.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 12.0);
    BOOST_REQUIRE_EQUAL(circle.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    pristup::Circle circle(6.0, {12.0, 12.0});
    double area = circle.getArea();
      
    circle.scale(3.0);
      
    BOOST_REQUIRE_CLOSE_FRACTION(circle.getArea(), (area * pow(3.0, 2.0)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ArgumentsConstructor)
  {
    BOOST_CHECK_THROW(pristup::Circle circle(-2.0, {12.0, 12.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ArgumentScale)
  {
    pristup::Circle circle(6.0, {12.0, 12.0});
    BOOST_CHECK_THROW(circle.scale(-1.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

// Triangle Tests

BOOST_AUTO_TEST_SUITE(TriangleTests)

  double EPSILON = 0.001;

  BOOST_AUTO_TEST_CASE(InvarienceOfParameters)
  {
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    double area = triangle.getArea();
    double widthBefore = triangle.getFrameRect().width;
    double heightBefore = triangle.getFrameRect().height;
    
    triangle.move(24.0, 40.0);
    
    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().width, widthBefore);
    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().height, heightBefore);
    BOOST_REQUIRE_EQUAL(triangle.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    double area = triangle.getArea();
      
    triangle.scale(4.0);
    
    BOOST_REQUIRE_CLOSE_FRACTION(triangle.getArea(), (area * pow(4.0, 2.0)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ArgumentsConstructor)
  {
    BOOST_CHECK_THROW(pristup::Triangle triangle({1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}), std::invalid_argument);
  }


  BOOST_AUTO_TEST_CASE(ArgumentScale)
  {
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    BOOST_CHECK_THROW(triangle.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

