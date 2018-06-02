#include <boost/test/unit_test.hpp>
#include "circle.hpp"

const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(Circle_Tests)

  BOOST_AUTO_TEST_CASE(Circle_Constructor_Invalid_Arguments)
  {
    BOOST_CHECK_THROW(sibikin::Circle({5.0, 5.0}, -1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_Move_To_Test)
  {
    sibikin::Circle circle({5.0, 5.0}, 2.0);
    double heightBeforeMove = circle.getFrameRect().height,
           areaBeforeMove = circle.getArea();
    circle.move({3.0, 3.0});
    sibikin::rectangle_t frame = circle.getFrameRect();
    BOOST_CHECK_CLOSE(frame.height, heightBeforeMove, EPS);
    BOOST_CHECK_EQUAL(circle.getArea(), areaBeforeMove);
    BOOST_CHECK_CLOSE(frame.pos.x, 3.0, EPS);
    BOOST_CHECK_CLOSE(frame.pos.y, 3.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Circle_Move_By_Test)
  {
    sibikin::Circle circle({5.0, 5.0}, 2.0);
    sibikin::rectangle_t frame = circle.getFrameRect();
    double heightBeforeMove = frame.height,
           areaBeforeMove = circle.getArea(),
           requiredX = frame.pos.x + 3.0,
           requiredY = frame.pos.y + 3.0;
    circle.move(3.0, 3.0);
    frame = circle.getFrameRect();
    BOOST_CHECK_CLOSE(frame.height, heightBeforeMove, EPS);
    BOOST_CHECK_EQUAL(circle.getArea(), areaBeforeMove);
    BOOST_CHECK_CLOSE(frame.pos.x, requiredX, EPS);
    BOOST_CHECK_CLOSE(frame.pos.y, requiredY, EPS);
  }

  BOOST_AUTO_TEST_CASE(Circle_Scale_Test_Initialization)
  {
    sibikin::Circle circle({5.0, 5.0}, 2.0);
    BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_Scale_Test)
  {
    sibikin::Circle circle({5.0, 5.0}, 2.0);
    sibikin::rectangle_t frame = circle.getFrameRect();
    double xBeforeScale = frame.pos.x,
           yBeforeScale = frame.pos.y,
           requiredArea = circle.getArea() * 9.0;
    circle.scale(3.0);
    frame = circle.getFrameRect();
    BOOST_CHECK_CLOSE(circle.getArea(), requiredArea, EPS);
    BOOST_CHECK_EQUAL(frame.pos.x, xBeforeScale);
    BOOST_CHECK_EQUAL(frame.pos.y, yBeforeScale);
  }
BOOST_AUTO_TEST_SUITE_END()
