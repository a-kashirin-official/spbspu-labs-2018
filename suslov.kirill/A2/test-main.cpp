#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"

#define FRACTION_EPS (0.000001)

BOOST_AUTO_TEST_SUITE(Rectangle_tests)
  
  BOOST_AUTO_TEST_CASE(Move_to_point_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move({60,80});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.x, 60);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.y, 80);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move(15, -20);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.x, 35);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.y, 20);
  }
  
  BOOST_AUTO_TEST_CASE(GetArea_test)
    {
      suslov::Rectangle rectangle({20, 40}, 100, 50);
      BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100*50, FRACTION_EPS);
    }

  BOOST_AUTO_TEST_CASE(Frame_rect_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 100);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 50);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.x, 20);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.y, 40);
  }

  BOOST_AUTO_TEST_CASE(Scale_area_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100*50*pow(5, 2), FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_area_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move({60, 80});
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100*50, FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_area_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move(15, -20);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100*50, FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_width_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move({60, 80});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 100);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_width_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move(15, -20);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 100);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_height_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move({60, 80});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 50);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_height_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    rectangle.move(15, -20);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 50);
  }

  BOOST_AUTO_TEST_CASE(Invalid_scale_coefficient_test)
  {
    suslov::Rectangle rectangle({20, 40}, 100, 50);
    BOOST_CHECK_THROW(rectangle.scale(-10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_width_or_height_test)
  {
    BOOST_CHECK_THROW(suslov::Rectangle({20, 40}, -100, 50), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_tests)
  
  BOOST_AUTO_TEST_CASE(Move_to_point_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    circle.move({290,110});
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 290);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 110);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    circle.move(-10, 140);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 40);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 210);
  }
  
  BOOST_AUTO_TEST_CASE(GetArea_test)
    {
      suslov::Circle circle ({50, 70}, 80);
      BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80, 2), FRACTION_EPS);
    }

  BOOST_AUTO_TEST_CASE(Frame_rect_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 80 * 2);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 80 * 2);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 50);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 70);
  }

  BOOST_AUTO_TEST_CASE(Scale_area_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    circle.scale(10);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80, 2) * pow(10, 2), FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_area_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    circle.move({290,110});
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80, 2), FRACTION_EPS);
  }

    BOOST_AUTO_TEST_CASE(Move_dx_dy_area_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    circle.move(-10, 140);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80, 2), FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_radius_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    circle.move({290,110});
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width / 2, 80);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_radius_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    circle.move(-10, 140);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width / 2, 80);
  }

  BOOST_AUTO_TEST_CASE(Invalid_scale_coefficient_test)
  {
    suslov::Circle circle ({50, 70}, 80);
    BOOST_CHECK_THROW(circle.scale(-10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_radius_test)
  {
    BOOST_CHECK_THROW(suslov::Circle({50, 70}, -80), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
