#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"

//неизменность ширины и высоты, а также площади фигуры при перемещениях;
//квадратичное изменение площади фигуры при масштабировании;
//наличие и обработку некорректных параметров в функциях
using namespace lobanova;

const double EPS = 0.0001;
BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Moving_to_point_test)
  {
    lobanova::Rectangle rect({11.1, 15.6}, 5.4, 9);
    double area = rect.getArea();
    rect.move({4.3, -4.7});
    BOOST_REQUIRE_EQUAL(rect.getWidth(), 5.4);
    BOOST_REQUIRE_EQUAL(rect.getHeight(), 9);
    BOOST_REQUIRE_EQUAL(rect.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Moving_to_vector_test)
  {
    lobanova::Rectangle rect({11.1, 15.6}, 5.4, 9);
    double area = rect.getArea();
    rect.move(7.3, -4.7);
    BOOST_REQUIRE_EQUAL(rect.getWidth(), 5.4);
    BOOST_REQUIRE_EQUAL(rect.getHeight(), 9);
    BOOST_REQUIRE_EQUAL(rect.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Scale_test)
  {
    lobanova::Rectangle rect({11.1, 15.6}, 5.4, 9);
    double area = rect.getArea();
    rect.scale(7);
    BOOST_REQUIRE_CLOSE(rect.getArea(), area * 7 * 7, EPS);
    area = rect.getArea();
    rect.scale(0.3);
    BOOST_REQUIRE_CLOSE(rect.getArea(), area * 0.3 * 0.3, EPS);
  }


  BOOST_AUTO_TEST_CASE(Constructor_error_test)
  {
    BOOST_CHECK_THROW(Rectangle({8, 0}, -4, 10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_error_test)
  {
    lobanova::Rectangle rect({7, 0}, 9, 3);
    BOOST_CHECK_THROW(rect.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Moving_to_point_test)
  {
    lobanova::Circle c({11.1, 15.6}, 5.4);
    double area = c.getArea();
    c.move({4.3, -4.7});
    BOOST_REQUIRE_CLOSE(c.getRadius(), 5.4, EPS);
    BOOST_REQUIRE_CLOSE(c.getArea(), area, EPS);
  }

  BOOST_AUTO_TEST_CASE(Moving_to_vector_test)
  {
    lobanova::Circle c({11.1, 15.6}, 5.4);
    double area = c.getArea();
    c.move(7.3, -4.7);
    BOOST_REQUIRE_CLOSE(c.getRadius(), 5.4, EPS);
    BOOST_REQUIRE_CLOSE(c.getArea(), area, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scale_test)
  {
    lobanova::Circle c({11.1, 15.6}, 5.4);
    double area = c.getArea();
    c.scale(7);
    BOOST_REQUIRE_CLOSE(c.getArea(), area * 7 * 7, EPS);
    area = c.getArea();
    c.scale(0.3);
    BOOST_REQUIRE_CLOSE(c.getArea(), area * 0.3 * 0.3, EPS);
  }


  BOOST_AUTO_TEST_CASE(Constructor_error_test)
  {
    BOOST_CHECK_THROW(Circle({8, 0}, -4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_error_test)
  {
    lobanova::Circle c({7, 0}, 9);
    BOOST_CHECK_THROW(c.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
