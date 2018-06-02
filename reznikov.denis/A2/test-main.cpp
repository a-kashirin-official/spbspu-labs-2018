#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include <circle.hpp>
#include <rectangle.hpp>

using namespace reznikov;
const double epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(MoveByIncrementation)
  {
    Circle circle(4, {15.5, 25});
    circle.move(4.5, 25);
    BOOST_REQUIRE_EQUAL(circle.getRadius(),4);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * 4 * 4, epsilon);
    BOOST_CHECK_EQUAL(circle.getPosition().x, 20);
    BOOST_CHECK_EQUAL(circle.getPosition().y, 50);
  }
  BOOST_AUTO_TEST_CASE(moveToPoint)
  {
    Circle circle(4, {20, 50});
    circle.move({10, 20});
    BOOST_REQUIRE_EQUAL(circle.getRadius(),4);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(),M_PI * 4 * 4, epsilon);
    BOOST_CHECK_EQUAL(circle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(circle.getPosition().y, 20);
  }
  BOOST_AUTO_TEST_CASE(AreaScaleTest)
  {
    Circle circle(4, {20, 50});
    circle.scale(3);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(),M_PI * 12 * 12, epsilon);
  }
  BOOST_AUTO_TEST_CASE(InvalidScaleCircleTest)
  {
    Circle circle(4, {20, 50});
    BOOST_CHECK_THROW(circle.scale(-2),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(constructor_invalid_radius)
  {
    BOOST_CHECK_THROW(Circle(-0.5, {1, 1}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(MoveByIncrementation)
  {
    Rectangle rectangle(4, 3, {8.9, 15.5});
    rectangle.move(1.1, 4.5);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width,4);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height,3);
    BOOST_CHECK_EQUAL(rectangle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(rectangle.getPosition().y, 20);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(),12,epsilon);
  }
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rectangle(4, 3, {100, 200});
    rectangle.move({10,20});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width,4);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height,3);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(),12,epsilon);
    BOOST_CHECK_EQUAL(rectangle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(rectangle.getPosition().y, 20);
  }
  BOOST_AUTO_TEST_CASE(AreaScaleTest)
  {
    Rectangle rectangle(15,20,{10,10});
    rectangle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(),1200,epsilon);
  }
  BOOST_AUTO_TEST_CASE(InvalidScaleRectTest)
  {
   BOOST_CHECK_THROW(Rectangle(5, 4, {100, 200}).scale(-1), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InvalidArgsTest)
  {
    BOOST_CHECK_THROW(Rectangle(-0.5, 5.5, {1, 1}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle(0.5, -5.5, {1, 1}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();
