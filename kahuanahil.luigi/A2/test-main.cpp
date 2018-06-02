#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "rectangle.hpp"
#include "circle.hpp"
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

using namespace kahuanahil;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(TestFrameRectValues_Rectangle)
  {
    Rectangle rect(10.5, 12.3, {2.0, 3.0});
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().width, 10.5);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().height, 12.3);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.x, 2.0);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.y, 3.0);
  }

  BOOST_AUTO_TEST_CASE(MovetoPoint_Rectangle)
  {
    Rectangle rect(10.5, 12.3 , {5.0, 6.0});
    double HeightBefore = rect.getFrameRect().height;
    double WidhtBefore = rect.getFrameRect().width;
    double AreaBefore = rect.getArea();
    rect.move({3.0, 4.2});
    BOOST_CHECK_CLOSE(rect.getCenter().x, 3.0, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCenter().y, 4.2, EPSILON);
    BOOST_CHECK_CLOSE(HeightBefore, rect.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(WidhtBefore, rect.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(AreaBefore, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveCoordinates_Rectangle)
  {
    Rectangle rect(10.5, 12.3, {5.0, 6.0});
    double HeightBefore = rect.getFrameRect().height;
    double WidhtBefore = rect.getFrameRect().width;
    double AreaBefore = rect.getArea();
    rect.move(3.0, 4.2);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, 8.0, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, 10.2, EPSILON);
    BOOST_CHECK_CLOSE(HeightBefore, rect.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(WidhtBefore, rect.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(AreaBefore, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(TestScale_Rectangle)
  {
    Rectangle rect(10.5, 12.3, {5.0, 6.0});
    double AreaBefore = rect.getArea();
    rect.scale(3.0);
    BOOST_CHECK_CLOSE(3.0 * 3.0 * AreaBefore, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidValueScale_Rectangle)
  {
    Rectangle rect(10.5, 12.3, {5.0, 6.0});
    BOOST_CHECK_THROW(rect.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidValueRectangle)
  {
    BOOST_CHECK_THROW(Rectangle(-1.0, 0.0, { 5.0, 6.0}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle(0.0, -1.0, {5.0, 6.0}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)
 
  BOOST_AUTO_TEST_CASE(TestFrameRectValues_Circle)
  {
    Circle cir(2.3, {5.0, 6.0});
    BOOST_CHECK_CLOSE(cir.getFrameRect().width, 2.3 * 2, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().height, 2.3 * 2, EPSILON);
    BOOST_REQUIRE_EQUAL(cir.getFrameRect().pos.x, 5.0);
    BOOST_REQUIRE_EQUAL(cir.getFrameRect().pos.y, 6.0);
  }

  BOOST_AUTO_TEST_CASE(MovetoPoint_Circle)
  {
    Circle cir(2.3, {7.0, 7.0});
    double WidhtBefore = cir.getFrameRect().width;
    double HeightBefore = cir.getFrameRect().height;
    double AreaBefore = cir.getArea();
    cir.move({3.0, 4.2});
    BOOST_CHECK_CLOSE(cir.getCenter().x, 3.0, EPSILON );
    BOOST_CHECK_CLOSE(cir.getCenter().y, 4.2, EPSILON);
    BOOST_CHECK_CLOSE(WidhtBefore, cir.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(HeightBefore, cir.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(AreaBefore, cir.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveCoordinate_Circle)
  {
    Circle cir(2.3, {1.0, 1.0});
    double WidhtBefore = cir.getFrameRect().width;
    double HeightBefore = cir.getFrameRect().height;
    double AreaBefore = cir.getArea();
    cir.move(3.0, 4.2);
    BOOST_CHECK(cir.getCenter().x == 4.0 && cir.getCenter().y == 5.2);
    BOOST_CHECK_CLOSE(WidhtBefore, cir.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(HeightBefore, cir.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(AreaBefore, cir.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(TestScale_Circle)
  {
    Circle cir(2.3, {6.0, 4.0});
    double AreaBefore = cir.getArea();
    cir.scale(3.0);
    BOOST_CHECK_CLOSE(3.0 * 3.0 * AreaBefore, cir.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidValueScale_Circle)
  {
    Circle cir(2.3, {5.0, 6.0});
    BOOST_CHECK_THROW(cir.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidValueCircle)
  {
    BOOST_CHECK_THROW(Circle(-1.0, {5.0, 6.0}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
