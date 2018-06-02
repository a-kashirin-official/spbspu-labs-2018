#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <math.h>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace std;
using namespace pashin;

const double kTolerance = 1E-10;


BOOST_AUTO_TEST_SUITE(circle)

  BOOST_AUTO_TEST_CASE(constructor)
  {
    BOOST_CHECK_THROW(Circle circle({8, 5}, -23), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(move)
  {
    double radius = 10;
    Circle circle({1, 2}, radius);
    double area = circle.getArea();
    circle.move({7, 4});
    BOOST_CHECK_CLOSE(circle.getArea(), area, kTolerance);
    BOOST_CHECK_CLOSE(circle.getRadius(), radius, kTolerance);
    circle.move(5, 9);
    BOOST_CHECK_CLOSE(circle.getArea(), area, kTolerance);
    BOOST_CHECK_CLOSE(circle.getRadius(), radius, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Circle circle({4, 10}, 15);
    double area = circle.getArea();
    double k = 1.5;
    circle.scale(k);
    BOOST_CHECK_CLOSE(circle.getArea(), area * pow(k, 2), kTolerance);
    BOOST_CHECK_THROW(circle.scale(-1), invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle)

  BOOST_AUTO_TEST_CASE(constructor)
  {
    BOOST_CHECK_THROW(Rectangle rectangle({5, 5}, -3, 7), invalid_argument);
    BOOST_CHECK_THROW(Rectangle rectangle({5, 5}, 7, -3), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(move)
  {
    double width = 4;
    double height = 5;
    Rectangle rectangle({6, 1}, width, height);
    double area = rectangle.getArea();
    rectangle.move({3, 8});
    BOOST_CHECK_CLOSE(rectangle.getWidth(), width, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getHeight(),height, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area, kTolerance);
    rectangle.move(6, 5);
    BOOST_CHECK_CLOSE(rectangle.getWidth(), width, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getHeight(), height, kTolerance);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rectangle({4, -7}, 15, 20);
    double area = rectangle.getArea();
    double k = 1.5;
    rectangle.scale(k);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area * pow(k, 2), kTolerance);
    BOOST_CHECK_THROW(rectangle.scale(-2), invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(triangle)

  BOOST_AUTO_TEST_CASE(move)
  {
    point_t vertices[3] {{15, 21}, {32, 7}, {3, 80}};
    Triangle triangle(vertices);
    double area = triangle.getArea();
    triangle.move({2, 5});
    BOOST_CHECK_CLOSE(triangle.getArea(), area, kTolerance);
    triangle.move(43, 50);
    BOOST_CHECK_CLOSE(triangle.getArea(), area, kTolerance);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    point_t vertices[3] {{39, 1}, {17, 5}, {53, 9}};
    Triangle triangle(vertices);
    double area = triangle.getArea();
    double k = 1.5;
    triangle.scale(k);
    BOOST_CHECK_CLOSE(triangle.getArea(), area * pow(k, 2), kTolerance);
    BOOST_CHECK_THROW(triangle.scale(-3), invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
