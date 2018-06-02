#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include <circle.hpp>
#include <rectangle.hpp>

using namespace korovin;
const double epsilon = 0.0001;


BOOST_AUTO_TEST_SUITE(Rectangle_Test)

  BOOST_AUTO_TEST_CASE(Move_By_Incrementation)
  {
    Rectangle rectangle({8.9, 15.5}, 4, 3);
    rectangle.move(1.1, 4.5);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().width,4, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().height,3, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().x, 10, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().y, 20, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(),12,epsilon);
  }
  BOOST_AUTO_TEST_CASE(Move_To_Point)
  {
    Rectangle rectangle({100, 200}, 4, 3);
    rectangle.move({10,20});
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().width,4, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().height,3, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(),12,epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().x, 10, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().y, 20, epsilon);
  }
  BOOST_AUTO_TEST_CASE(Area_Scale_Test)
  {
    Rectangle rectangle({10,10}, 15,20);
    rectangle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(),1200,epsilon);
  }
  BOOST_AUTO_TEST_CASE(Invalid_Scale_Rect_Test)
  {
   BOOST_CHECK_THROW(Rectangle({100, 200}, 5, 4).scale(-1), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(Invalid_Args_Test)
  {
    BOOST_CHECK_THROW(Rectangle({1, 1}, -0.5, 5.5), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({1, 1}, 0.5, -5.5), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Move_By_Incrementation)
  {
    Circle circle({15.5, 25}, 4);
    circle.move(4.5, 25);
    BOOST_CHECK_CLOSE_FRACTION(circle.getRadius(),4, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * 4 * 4, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(circle.getPos().x, 20, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(circle.getPos().y, 50, epsilon);
  }
  BOOST_AUTO_TEST_CASE(move_To_Point)
  {
    Circle circle({20, 50}, 4);
    circle.move({10, 20});
    BOOST_CHECK_CLOSE_FRACTION(circle.getRadius(),4, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(),M_PI * 4 * 4, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(circle.getPos().x, 10, epsilon);
    BOOST_CHECK_CLOSE_FRACTION(circle.getPos().y, 20, epsilon);
  }
  BOOST_AUTO_TEST_CASE(Area_Scale_Test)
  {
    Circle circle({20, 50}, 4);
    circle.scale(3);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(),M_PI * 12 * 12, epsilon);
  }
  BOOST_AUTO_TEST_CASE(Invalid_Scale_CircleTest)
  {
    Circle circle({20, 50}, 4);
    BOOST_CHECK_THROW(circle.scale(-2),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(constructor_invalid_radius)
  {
    BOOST_CHECK_THROW(Circle({1, 1}, -0.5), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();


