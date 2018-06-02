#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double EPS = 0.0001;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Rect_InvarienceOfParametersTest)
  {
    spodeneyko::Rectangle rect({24.0, 48.0, {128.0, 256.0}});
    double area = rect.getArea();
    rect.move(16.0, 32.0);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().width, 24.0);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().height, 48.0);
    BOOST_REQUIRE_CLOSE_FRACTION(rect.getArea(), area, EPS);
  }

  BOOST_AUTO_TEST_CASE(Rect_ScaleTest)
  {
    spodeneyko::Rectangle rect({24.0, 48.0, {128.0, 256.0}});
    double area = rect.getArea();
    rect.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(rect.getArea(), area * pow(2.0, 2.0), EPS);
  }

  BOOST_AUTO_TEST_CASE(Rect_InvalidArgumentConstructorTest)
  {
    BOOST_REQUIRE_THROW(spodeneyko::Rectangle rect({-2.0, -2.0, {24.0, 48.0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rect_InvalidArgumentScaleTest)
  {
    spodeneyko::Rectangle rect({24.0, 48.0, {128.0, 256.0}});
    BOOST_REQUIRE_THROW(rect.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Tests)

  BOOST_AUTO_TEST_CASE(Circle_InvarienceOfParametersTest)
  {
    spodeneyko::Circle circle(5.0, {10.0, 10.0});
    double area = circle.getArea();
    circle.move(16.0, 32.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 10.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 10.0);
    BOOST_REQUIRE_CLOSE_FRACTION(circle.getArea(), area, EPS);
  }

  BOOST_AUTO_TEST_CASE(Circle_ScaleTest)
  {
    spodeneyko::Circle circle(5.0, {10.0, 10.0});
    double area = circle.getArea();
    circle.scale(3.0);
    BOOST_REQUIRE_CLOSE_FRACTION(circle.getArea(), area * pow(3.0, 2.0), EPS);
  }

  BOOST_AUTO_TEST_CASE(Cirlce_InvalidArgumentConstructorTest)
  {
    BOOST_REQUIRE_THROW(spodeneyko::Circle circle(-2.0, {10.0, 10.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_InvalidArgumentScaleTest)
  {
    spodeneyko::Circle circle(5.0, {10.0, 10.0});
    BOOST_REQUIRE_THROW(circle.scale(-1.0), std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()
