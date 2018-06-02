#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include <stdexcept>

using namespace usov;
const double epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(Rectangle_tests)

BOOST_AUTO_TEST_CASE(get_height)
{
  BOOST_CHECK_CLOSE(Rectangle(20, 15, { 30,30 }).getHeight(),15,epsilon);
}

BOOST_AUTO_TEST_CASE(get_width)
{
  BOOST_CHECK_CLOSE(Rectangle(20, 15, { 30,30 }).getWidth(),20, epsilon);
}

BOOST_AUTO_TEST_CASE(test_area_coordinates)
{
  Rectangle rect(15, 15, { 10,10 });
  const double area = rect.getArea();
  rect.move(5, 5);
  BOOST_CHECK_CLOSE(rect.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, 15.0, epsilon);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, 15.0, epsilon);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, 15.0, epsilon);
  BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, 15.0, epsilon);
}

BOOST_AUTO_TEST_CASE(test_area_point)
{
  Rectangle rect(15, 15, { 10,10 });
  const double area = rect.getArea();
  rect.move({ 10,10 });
  BOOST_CHECK_CLOSE(rect.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(rect.getFrameRect().width, 15.0, epsilon);
  BOOST_CHECK_CLOSE(rect.getFrameRect().height, 15.0, epsilon);
}

BOOST_AUTO_TEST_CASE(test_scale_bigger)
{
  Rectangle rect(2, 2, { 10,10 });
  rect.scale(5);
  BOOST_CHECK_CLOSE(rect.getArea(),100, epsilon);
}

BOOST_AUTO_TEST_CASE(test_scale_smaller)
{
  Rectangle rect(10, 10, { 10,10 });
  rect.scale(0.5);
  BOOST_CHECK_CLOSE(rect.getArea(),25, epsilon);
}

BOOST_AUTO_TEST_CASE(incorrect_test_rectangle)
{
  BOOST_CHECK_THROW(Rectangle(-1, 15, { 10,10 }).getWidth(), std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle(15, -1, { 10,10 }).getHeight(), std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle(15, 15, { 10,10 }).scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_tests)

  BOOST_AUTO_TEST_CASE(get_raduis)
  {
    BOOST_CHECK_EQUAL(Circle(10, { 15,15 }).getRadius(), 10);
  }

  BOOST_AUTO_TEST_CASE(test_area_coordinates)
  {
    Circle circ(15,{ 10,10 });
    const double area = circ.getArea();
    circ.move(5, 5);
    BOOST_CHECK_CLOSE(circ.getArea(), area, epsilon);
  }

  BOOST_AUTO_TEST_CASE(test_area_point)
  {
    Circle circ(15,{ 10,10 });
    const double area = circ.getArea();
    circ.move({5, 5});
    BOOST_CHECK_CLOSE(circ.getArea(), area, epsilon);
    BOOST_CHECK_CLOSE(circ.getRadius(),15, epsilon);
  }

  BOOST_AUTO_TEST_CASE(test_scale_bigger)
  {
    Circle circ(15,{ 10,10 });
    const double area = circ.getArea();
    circ.scale(5);
    BOOST_CHECK_CLOSE(circ.getArea(), area * 25, epsilon);
  }

  BOOST_AUTO_TEST_CASE(test_scale_smaller)
  {
    Circle circ(10,{ 10,10 });
    const double area = circ.getArea();
    circ.scale(0.5);
    BOOST_CHECK_CLOSE(circ.getArea(), area / 4, epsilon);
  }

  BOOST_AUTO_TEST_CASE(incorrect_test_scale_circle)
  {
    BOOST_CHECK_THROW(Circle(-1, { 15,5 }).getRadius(), std::invalid_argument);
    BOOST_CHECK_THROW(Circle(-1, { 15,5 }).scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
