#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

using namespace ponomarev;

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rect({5.0, 5.0}, 5.0, 5.0);
    double heightBeforeChange = rect.getFrameRect().height;
    double widthBeforeChange = rect.getFrameRect().width;
    double areaBeforeChange = rect.getArea();
    rect.move({-3.0, 4.0});
    BOOST_CHECK(rect.getFrameRect().pos.x == -3.0 && rect.getFrameRect().pos.y == 4.0);
    BOOST_CHECK_CLOSE(areaBeforeChange, rect.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, rect.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, rect.getFrameRect().width, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(MoveAxis)
  {
    Rectangle rect({0.0, 0.0}, 4.0, 3.0);
    double heightBeforeChange = rect.getFrameRect().height;
    double widthBeforeChange = rect.getFrameRect().width;
    double areaBeforeChange = rect.getArea();
    rect.move(5.0, 6.0);
    BOOST_CHECK(rect.getFrameRect().pos.x == 5.0 && rect.getFrameRect().pos.y == 6.0);
    BOOST_CHECK_CLOSE(areaBeforeChange, rect.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, rect.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, rect.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Rectangle rect({0.0, 0.0}, 4.0, 2.0);
    BOOST_CHECK_THROW(rect.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
  {
    Rectangle rect({0.0, 0.0}, 4.0, 4.0);
    double areaBeforeChange = rect.getArea();
    rect.scale(4.0);
    BOOST_CHECK_CLOSE(4.0 * 4.0 * areaBeforeChange, rect.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Initialization)
  {
    BOOST_CHECK_THROW(Rectangle({0.0, 0.0}, 10.0, -10.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({0.0, 0.0}, -10.0, 10.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({0.0, 0.0}, -10.0, -10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
 
BOOST_AUTO_TEST_SUITE(Circle_Tests)
  
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle circle({1.0, 4.0}, 5.0);
    double heightBeforeChange = circle.getFrameRect().height;
    double widthBeforeChange = circle.getFrameRect().width;
    double areaBeforeChange = circle.getArea();
    circle.move({22.0, 12.2});
    BOOST_CHECK(circle.getFrameRect().pos.x == 22.0 && circle.getFrameRect().pos.y == 12.2);
    BOOST_CHECK_CLOSE(areaBeforeChange, circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, circle.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, circle.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(MoveAxis)
  {
    Circle circle({0.0, 0.0}, 4.0);
    double heightBeforeChange = circle.getFrameRect().height;
    double widthBeforeChange = circle.getFrameRect().width;
    double areaBeforeChange = circle.getArea();
    circle.move(5.0, 6.0);
    BOOST_CHECK(circle.getFrameRect().pos.x == 5.0 && circle.getFrameRect().pos.y == 6.0);
    BOOST_CHECK_CLOSE(areaBeforeChange, circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(heightBeforeChange, circle.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(widthBeforeChange, circle.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    Circle circle({0.0, 0.0}, 4.0);
    BOOST_CHECK_THROW(circle.scale(-13.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
  {
    Circle circle({0.0, 0.0}, 4.0);
    double areaBeforeChange = circle.getArea();
    circle.scale(4.0);
    BOOST_CHECK_CLOSE(4.0 * 4.0 * areaBeforeChange, circle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Initialization)
  {
    BOOST_CHECK_THROW(Circle({0.0, 0.0}, -10.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

