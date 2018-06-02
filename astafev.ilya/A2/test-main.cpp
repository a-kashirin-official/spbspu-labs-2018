#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"

const double EPS=0.00001;

using namespace astafev;

BOOST_AUTO_TEST_SUITE(Circle_Tests)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_Circle)
  {
    Circle Circle1({ 7.0, 3.0 }, 10.0);
    Circle1.move({ 10.0, 10.0 });
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.x, 10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.y, 10.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_Circle)
  {
    Circle Circle1({ 5.0, 0.0 }, 7.0);
    Circle1.move(-4.0, 9.4);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.x, 1.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.y, 9.4, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Circle)
  {
    Circle Circle1({ 6.5, 7.0}, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getArea(), 25.0 * M_PI, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_With_Move_Circle)
  {
    Circle Circle1({ 6.5, 7.0 }, 5.0);
    Circle1.move(10.0, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getArea(), 25.0 * M_PI, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Circle)
  {
    Circle Circle1({ 10.0, 10.0 }, 5.0);
    Circle1.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getArea(), 25.0 * M_PI * 4.0, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Scale_Test_With_Move_Circle)
  {
    Circle Circle1({ 10.0, 10.0 }, 5.0);
    Circle1.scale(2.0);
    Circle1.move({10.0, 5.0});
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getArea(), 25.0 * M_PI * 4.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Circle)
  {
    Circle Circle1({ 10.0, 10.0 }, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.x, 10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.y, 10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().width, 10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().height, 10.0, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Wiht_Move_Circle)
  {
    Circle Circle1({ 10.0, 10.0 }, 5.0);
    Circle1.move({10.0, 5.0});
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.x, 10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().pos.y, 5.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().width, 10.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Circle1.getFrameRect().height, 10.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Circle)
  {
    BOOST_CHECK_THROW(Circle({ 0.0, 0.0 }, -1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Circle)
  {
    Circle Circle1({ 0.0, 0.0 }, 10.0);
    BOOST_CHECK_THROW(Circle1.scale(-1.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_Rect)
  {
    Rectangle Rectangle1({ 11.1, 15.6 }, 5.0, 5.0);
    Rectangle1.move({ 29.3, 15.7 });
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.x, 29.3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.y, 15.7, EPS);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_Rect)
  {
    Rectangle Rectangle1({ 11.1, 15.6 }, 5.0, 5.0);
    Rectangle1.move(-10.1, 0.4);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.x, 1.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.y, 16.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Rect)
  {
    Rectangle Rectangle1({ 11.1, 15.6 }, 5.0, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getArea(), 25.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_With_Move_Rect)
  {
    Rectangle Rectangle1({ 11.1, 15.6 }, 5.0, 5.0);
    Rectangle1.move(7.0, 10.0);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getArea(), 25.0, EPS);
  }


  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Rect)
  {
    Rectangle Rectangle1({ 11.1, 15.6 }, 5.0, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.x, 11.1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.y, 15.6, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().width, 5.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().height, 5.0, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_With_Move_Rect)
  {
    Rectangle Rectangle1({ 11.1, 15.6 }, 5.0, 5.0);
    Rectangle1.move({ 29.3, 15.7 });
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.x, 29.3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().pos.y, 15.7, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().width, 5.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getFrameRect().height, 5.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
  {
    Rectangle Rectangle1({ 10.5, 10.5 }, 7.0, 5.0);
    Rectangle1.scale(5.0);
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getArea(), 35.0 * 25.0, EPS);
  }
  
  BOOST_AUTO_TEST_CASE(Scale_Test_With_Move_Rect)
  {
    Rectangle Rectangle1({ 10.5, 10.5 }, 7.0, 5.0);
    Rectangle1.scale(5.0);
    Rectangle1.move({ 29.3, 15.7 });
    BOOST_CHECK_CLOSE_FRACTION(Rectangle1.getArea(), 35.0 * 25.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Rect)
  {
    BOOST_CHECK_THROW(Rectangle({ 0.0, 0.0 }, -5.0, 1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Rect)
  {
    Rectangle Rectangle1({ 0.0, 0.0 }, 10.0, 10.0);
    BOOST_CHECK_THROW(Rectangle1.scale(-10.0), std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()

