#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace aleksovski;

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(TestRectangle)
BOOST_AUTO_TEST_CASE(TestMoveAxisRectangle)
{
  Rectangle r(12, 21, { -7, 19 });
  const double width_old = r.getFrameRect().width;
  const double height_old = r.getFrameRect().height;
  const double area_old = r.getArea();
  r.move(7.53, 92.58);
  BOOST_CHECK_CLOSE(width_old, r.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(height_old, r.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(area_old, r.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(TestMoveToPointRectangle)
{
  Rectangle r(19.8, 3.29, { -83, 142.4 });
  const double width_old = r.getFrameRect().width;
  const double height_old = r.getFrameRect().height;
  const double area_old = r.getArea();
  r.move({ 1.63, -49.13 });
  BOOST_CHECK_CLOSE(width_old, r.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(height_old, r.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(area_old, r.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(TestScaleRectangle)
{
  Rectangle r(9, 6, { 17,23 });
  const double area_old = r.getArea();
  const double k = 2.5;
  r.scale(k);
  BOOST_CHECK_CLOSE(area_old * k * k, r.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(TestInvalidParametersRectangle)
{
  BOOST_CHECK_THROW(Rectangle(-3, -5, { 1, 1 }), std::invalid_argument);
BOOST_CHECK_THROW(Rectangle(3, -5, { 1, 1 }), std::invalid_argument);
BOOST_CHECK_THROW(Rectangle(-3, 5, { 1, 1 }), std::invalid_argument);
  Rectangle r(11, 15, { 2, 7 });
  BOOST_CHECK_THROW(r.scale(-3), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)
BOOST_AUTO_TEST_CASE(TestMoveAxisCircle)
{
  Circle c(20, { -6, 18 });
  const double width_old = c.getFrameRect().width;
  const double height_old = c.getFrameRect().height;
  const double area_old = c.getArea();
  c.move(3.36, 0);
  BOOST_CHECK_CLOSE(width_old, c.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(height_old, c.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(area_old, c.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(TestMoveToPointCircle)
{
  Circle c(2, { -77, 111.7 });
  const double width_old = c.getFrameRect().width;
  const double height_old = c.getFrameRect().height;
  const double area_old = c.getArea();
  c.move({ 3.46, -51.54 });
  BOOST_CHECK_CLOSE(width_old, c.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(height_old, c.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(area_old, c.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(TestScaleCircle)
{
  Circle c(5, { 11,16 });
  const double area_old = c.getArea();
  const double k = 1.2;
  c.scale(k);
  BOOST_CHECK_CLOSE(area_old * k * k, c.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(TestInvalidParametersCircle)
{
  BOOST_CHECK_THROW(Circle(-20, { 1, 1 }), std::invalid_argument);
  Circle c(8, { 2, 9 });
  BOOST_CHECK_THROW(c.scale(-3), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()
