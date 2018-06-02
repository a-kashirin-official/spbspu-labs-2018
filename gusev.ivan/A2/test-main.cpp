#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

using namespace gusev;

const double dx = 0.000001;

BOOST_AUTO_TEST_SUITE(testRect)

  BOOST_AUTO_TEST_CASE(testRectMove1)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move({ 11.3, 0.7 });
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, 11.3);
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, 0.7);
  }

  BOOST_AUTO_TEST_CASE(testRectMove2)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.x, 18.5, dx);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.y, 8.5, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectMoveWidth)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().width, 5.3, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectMoveHeight)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().height, 6.9, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectMoveArea)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    double area = rect.getArea();
    rect.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(area, rect.getArea(), dx);
  }

 BOOST_AUTO_TEST_CASE(testRectScale)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    double area = rect.getArea();
    rect.scale(2.5);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), area * 2.5 * 2.5, dx);
  }

  BOOST_AUTO_TEST_CASE(testRectInit)
  {
    BOOST_CHECK_THROW(Rectangle rect1(-1, 3, { 3, 3 }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rect2(1, -3, { 3, 3 }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rect3(-1, -3, { 3, 3 }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rect4(0, 3, { 3, 3 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testInitScale)
  {
    Rectangle rect(5.3, 6.9, { 0.4, 3.5 });
    BOOST_CHECK_THROW(rect.scale(-5), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(testCirc)

  BOOST_AUTO_TEST_CASE(testCircMove1)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    circ.move({ 11.3, 0.7 });
    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.x, 11.3);
    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.y, 0.7);
  }

  BOOST_AUTO_TEST_CASE(testCircMove2)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    circ.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.x, 19.1, dx);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.y, 7.0, dx);
  }

  BOOST_AUTO_TEST_CASE(testCircMoveRadius)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    circ.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().width/2, 5.0, dx);
  }

  BOOST_AUTO_TEST_CASE(testCircMoveArea)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    double area = circ.getArea();
    circ.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(area, circ.getArea(), dx);
  }

 BOOST_AUTO_TEST_CASE(testCircScaleArea)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    double area = circ.getArea();
    circ.scale(2.5);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), area * 2.5 * 2.5, dx);
  }

  BOOST_AUTO_TEST_CASE(testCircInit)
  {
    BOOST_CHECK_THROW(Circle circ1(-1, { 3, 3 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testCircInitScale)
  {
    Circle circ(5.0 , { 1.0, 2.0 });
    BOOST_CHECK_THROW(circ.scale(-5), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(testTrian)

  BOOST_AUTO_TEST_CASE(testTrianMove1)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    trian.move({ 11.3, 0.7 });
    BOOST_CHECK_EQUAL(trian.getCenter().x, 11.3);
    BOOST_CHECK_EQUAL(trian.getCenter().y, 0.7);
  }

  BOOST_AUTO_TEST_CASE(testTrianMove2)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 3.0, 6.0 });
    rectangle_t frame = trian.getFrameRect();
    trian.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(trian.getCenter().x, 21.1, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getCenter().y, 9.0, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getFrameRect().width, frame.width, dx);
    BOOST_CHECK_CLOSE_FRACTION(trian.getFrameRect().height, frame.height, dx);
  }

  BOOST_AUTO_TEST_CASE(testTrianMoveArea)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    double area = trian.getArea();
    trian.move(18.1, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(area, trian.getArea(), dx);
  }

 BOOST_AUTO_TEST_CASE(testTrianScaleArea)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    double area = trian.getArea();
    trian.scale(2.5);
    BOOST_CHECK_CLOSE_FRACTION(trian.getArea(), area * 2.5 * 2.5, dx);
  }

  BOOST_AUTO_TEST_CASE(testTrianInitScale)
  {
    Triangle trian({ 1.0, 3.0 }, { 5.0, 3.0 }, { 2.0, 4.0 });
    BOOST_CHECK_THROW(trian.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(testCircInit)
  {
    BOOST_CHECK_THROW(Triangle trian({ 1.0, 3.0 }, { 1.0, 3.0 }, { 1.0, 4.0 }), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();
