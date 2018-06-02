#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Rect_Constructor_Invalid_Arguments)
  {
    BOOST_CHECK_THROW(sibikin::Rectangle({5.0, 5.0}, 0.0, -1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rect_Move_To_Test)
  {
    sibikin::Rectangle rect({5.0, 5.0}, 2.0, 3.0);
    double heightBeforeMove = rect.getFrameRect().height,
           areaBeforeMove = rect.getArea();
    rect.move({3.0, 3.0});
    sibikin::rectangle_t frame = rect.getFrameRect();
    BOOST_CHECK_EQUAL(frame.height, heightBeforeMove);
    BOOST_CHECK_EQUAL(rect.getArea(), areaBeforeMove);
    BOOST_CHECK_CLOSE(frame.pos.x, 3.0, EPS);
    BOOST_CHECK_CLOSE(frame.height, 3.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Rect_Move_By_Test)
  {
    sibikin::Rectangle rect({5.0, 5.0}, 2.0, 3.0);
    sibikin::rectangle_t frame = rect.getFrameRect();
    double heightBeforeMove = frame.height,
           areaBeforeMove = rect.getArea(),
           requiredX = frame.pos.x + 3.0,
           requiredY = frame.pos.y + 3.0;
    rect.move(3.0, 3.0);
    frame = rect.getFrameRect();
    BOOST_CHECK_EQUAL(frame.height, heightBeforeMove);
    BOOST_CHECK_CLOSE(rect.getArea(), areaBeforeMove, EPS);
    BOOST_CHECK_CLOSE(frame.pos.x, requiredX, EPS);
    BOOST_CHECK_CLOSE(frame.pos.y, requiredY, EPS);
  }

  BOOST_AUTO_TEST_CASE(Rect_Scale_Test_Initialization)
  {
    sibikin::Rectangle rect({5.0, 5.0}, 2.0, 3.0);
    BOOST_CHECK_THROW(rect.scale(-3.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rect_Scale_Test)
  {
    sibikin::Rectangle rect({5.0, 5.0}, 2.0, 3.0);
    sibikin::rectangle_t frame = rect.getFrameRect();
    double xBeforeScale = frame.pos.x,
           yBeforeScale = frame.pos.y,
           requiredArea = rect.getArea() * 9.0;
    rect.scale(3.0);
    frame = rect.getFrameRect();
    BOOST_CHECK_EQUAL(frame.pos.x, xBeforeScale);
    BOOST_CHECK_EQUAL(frame.pos.y, yBeforeScale);
    BOOST_CHECK_CLOSE(rect.getArea(), requiredArea, EPS);
  }

  BOOST_AUTO_TEST_CASE(Rect_Rotation_Test)
  {
    sibikin::Rectangle rect({5.0, 5.0}, 2.0, 4.0);
    rect.rotate(90.0);

    BOOST_CHECK_CLOSE(rect.getFrameRect().height, 2.0, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, 4.0, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, 5.0, EPS);

    rect.rotate(-90.0);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, 5.0, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, 5.0, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, 2.0, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, 4.0, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()
