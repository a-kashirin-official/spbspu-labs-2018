#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace xiezhuang;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

BOOST_AUTO_TEST_CASE(Move_Test_Absolute_Rect)
{
  Rectangle rect({10, 0}, 10, 10);
  rect.move({15, 20});
  BOOST_CHECK(rect.getPosition().x == 15 && rect.getPosition().y == 20);
}

BOOST_AUTO_TEST_CASE(MOVE_Test_Relative_Rect)
{
  Rectangle rect({10, 0}, 15, 10);
  rect.move(-5, 8);
  BOOST_CHECK(rect.getPosition().x == 5 && rect.getPosition().y == 8);
}

BOOST_AUTO_TEST_CASE(Area_Test_Rect)
{
  Rectangle rect({0, 0}, 15, 10);
  BOOST_REQUIRE_EQUAL(rect.getArea(), 150);
}

BOOST_AUTO_TEST_CASE(Area_Test_move_x_Rect)
{
  Rectangle rect({0, 0}, 15, 10);
  rect.move(10, 0);
  BOOST_REQUIRE_EQUAL(rect.getArea(), 150);
}

BOOST_AUTO_TEST_CASE(Area_Test_move_y_Rect)
{
  Rectangle rect({0, 0}, 15, 10);
  rect.move(0, 10);
  BOOST_REQUIRE_EQUAL(rect.getArea(), 150);
}

BOOST_AUTO_TEST_CASE(Height_Test_Rect)
{
  Rectangle rect({0, 0}, 15, 10);
  rect.move(10, 0);
  BOOST_REQUIRE_EQUAL(rect.getHeight(), 10);
}

BOOST_AUTO_TEST_CASE(Widht_Test_Rect)
{
  Rectangle rect({0, 0}, 15, 10);
  rect.move(10, 0);
  BOOST_REQUIRE_EQUAL(rect.getWidth(), 15);
}

BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Rect)
{
  Rectangle rect({3, 0}, 15, 10);
  BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().width, 15, 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().height, 10, 0.00001);
  BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.x, 3);
  BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.y, 0);
}

BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
{
  Rectangle rect({0, 0}, 15, 10);
  rect.scale(10);
  BOOST_REQUIRE_EQUAL(rect.getArea(), 150 * 100);
}

BOOST_AUTO_TEST_CASE(Inavalid_argumend_constructor_Test_Rect)
{
  BOOST_CHECK_THROW(Rectangle({0, 0}, -10, -10), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Invalid_argument_scale_Test_Rect)
{
  Rectangle rect({0, 0}, 10, 10);
  BOOST_CHECK_THROW(rect.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Test)

BOOST_AUTO_TEST_CASE(Move_Test_Absolute_Circle)
{
  Circle circle({10, 0}, 10);
  circle.move({15, 20});
  BOOST_CHECK(circle.getPosition().x == 15 && circle.getPosition().y == 20);
}

BOOST_AUTO_TEST_CASE(MOVE_Test_Relative_Circle)
{
  Circle circle({10, 0}, 10);
  circle.move(-5, 8);
  BOOST_CHECK(circle.getPosition().x == 5 && circle.getPosition().y == 8);
}

BOOST_AUTO_TEST_CASE(Area_Test_Circle)
{
  Circle circle({10, 0}, 10);
  BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 100 * M_PI, 0.01);
}

BOOST_AUTO_TEST_CASE(Area_Test_move_x_Circle)
{
  Circle circle({10, 0}, 10);
  circle.move(10, 0);
  BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 100 * M_PI, 0.01);
}

BOOST_AUTO_TEST_CASE(Area_Test_move_y_Circle)
{
  Circle circle({10, 0}, 10);
  circle.move(0, 10);
  BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 100 * M_PI, 0.01);
}

BOOST_AUTO_TEST_CASE(Radius_Test_Circle)
{
  Circle circle({10, 0}, 10);
  circle.move(0, 10);
  BOOST_REQUIRE_EQUAL(circle.getRadius(), 10);
}


BOOST_AUTO_TEST_CASE(Scale_Test_Circle)
{
  Circle circle({10, 0}, 10);
  circle.scale(2);
  BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 100 * M_PI * 4, 0.01);
}

BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Circle)
{
  Circle circle({3, 0}, 15);
  BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 30);
  BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 30);
  BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 3);
  BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 0);
}

BOOST_AUTO_TEST_CASE(Inavalid_argumend_constructor_Test_Circle)
{
  BOOST_CHECK_THROW(Circle({0, 0}, -10), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Invalid_argument_scale_Test_Circle)
{
  Circle circle({0, 0}, 10);
  BOOST_CHECK_THROW(circle.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
