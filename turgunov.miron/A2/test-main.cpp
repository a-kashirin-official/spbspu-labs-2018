#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

using namespace turgunov;
const double TOLERANCE = 0.0001;

BOOST_AUTO_TEST_SUITE(testRectangle)

BOOST_AUTO_TEST_CASE(move_width)
{
  Rectangle shape({0, 0}, 4, 8);
  Shape *rectangle = &shape;
  rectangle->move({10, 20});
  BOOST_CHECK_CLOSE(shape.getWidth(), 4, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_height)
{
  Rectangle shape({0, 0}, 10, 2);
  Shape *rectangle = &shape;
  rectangle->move({0, 0});
  BOOST_CHECK_CLOSE(shape.getHeight(), 2, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_area)
{
  Rectangle shape({10, 10}, 5, 3);
  Shape *rectangle = &shape;
  rectangle->move({0, 0});
  BOOST_CHECK_CLOSE(rectangle->getArea(), 15, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_area)
{
  Rectangle shape({0, 0}, 2, 3);
  Shape *rectangle = &shape;
  rectangle->scale(2);
  BOOST_CHECK_CLOSE(rectangle->getArea(), 24, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(invalid_width)
{
  BOOST_CHECK_THROW(Rectangle shape({0, 0}, -10, 3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_height)
{
  BOOST_CHECK_THROW(Rectangle shape({0, 0}, 5, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_scale)
{
  Rectangle shape({0, 0}, 10, 10);
  Shape *rectangle = &shape;
  BOOST_CHECK_THROW(rectangle->scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testCircle)

BOOST_AUTO_TEST_CASE(move_radius)
{
  Circle shape({0, 0}, 3);
  Shape *circle = &shape;
  circle->move({30, 10});
  BOOST_CHECK_CLOSE(shape.getRadius(), 3, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_area)
{
  Circle shape({0, 0}, 5);
  Shape *circle = &shape;
  circle->move({5, 20});
  BOOST_CHECK_CLOSE(circle->getArea(), M_PI * 25, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_area)
{
  Circle shape({0, 0}, 5);
  Shape *circle = &shape;
  circle->scale(2);
  BOOST_CHECK_CLOSE(circle->getArea(), M_PI * 100, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(invalid_radius)
{
  BOOST_CHECK_THROW(Circle shape({0, 0}, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_scale)
{
  Circle shape({0, 0}, 1);
  Shape *circle = &shape;
  BOOST_CHECK_THROW(circle->scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testTriangle)

BOOST_AUTO_TEST_CASE(move_center)
{
  Triangle triangle({-3, 0}, {0, 9}, {3, 0});
  triangle.move(5, 6);
  
  BOOST_CHECK_CLOSE(triangle.getCenter().x, 5, TOLERANCE);
  BOOST_CHECK_CLOSE(triangle.getCenter().y, 9, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(move_area)
{
  Triangle triangle({0, 0}, {0, 2}, {3, 0});
  triangle.move({7, 3});
  
  BOOST_CHECK_CLOSE(triangle.getArea(), 3, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_center)
{
  Triangle triangle({1, 0}, {2, 3}, {3, 0});
  triangle.scale(3);
  
  BOOST_CHECK_CLOSE(triangle.getCenter().x, 2, TOLERANCE);
  BOOST_CHECK_CLOSE(triangle.getCenter().y, 1, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(scale_area)
{
  Triangle triangle({1, -1}, {3, -1}, {1, -3});
  triangle.scale(2);
  
  BOOST_CHECK_CLOSE(triangle.getArea(), 8, TOLERANCE);
}

BOOST_AUTO_TEST_CASE(invalid_scale)
{
  Triangle triangle({6, 2}, {0, 3}, {5, 2});

  BOOST_CHECK_THROW(triangle.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
