#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double EPS = 0.00001;

using namespace konkin;

BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    konkin::Rectangle rect({20.0, 30.0, {100.0, 50.0}});
    rectangle_t startRect = rect.getFrameRect();
    double startArea = rect.getArea();

    rect.move({10.0, 20.0});
    BOOST_CHECK_EQUAL(startArea, rect.getArea());
    BOOST_CHECK_EQUAL(startRect.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(startRect.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MovingFor)
  {
    konkin::Rectangle rect({20.0, 30.0, {100.0, 50.0}});
    rectangle_t startRect = rect.getFrameRect();
    double startArea = rect.getArea();

    rect.move(-10.0, 50.0);
    BOOST_CHECK_EQUAL(startArea, rect.getArea());
    BOOST_CHECK_EQUAL(startRect.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(startRect.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    konkin::Rectangle rect({20.0, 30.0, {100.0, 50.0}});
    double startArea = rect.getArea();
    const double coef = 10.0;

    rect.scale(coef);
    BOOST_CHECK_CLOSE(coef * coef * startArea, rect.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(WrongParameters)
  {
    BOOST_REQUIRE_THROW( konkin::Rectangle({20.0, -30.0, {100.0, 50.0}}), std::invalid_argument );
    BOOST_REQUIRE_THROW( konkin::Rectangle({-20.0, 30.0, {100.0, 50.0}}), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(WrongScaleParameter)
  {
    konkin::Rectangle rect({20.0, 30.0, {100.0, 50.0}});
    BOOST_CHECK_THROW( rect.scale(-10.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    konkin::Circle circle({50.0, 50.0}, 10.0);
    rectangle_t startRect = circle.getFrameRect();
    double startArea = circle.getArea();

    circle.move({0.0, 0.0});
    BOOST_CHECK_EQUAL(startArea, circle.getArea());
    BOOST_CHECK_EQUAL(startRect.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(startRect.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(MovingFor)
  {
    konkin::Circle circle({50.0, 50.0}, 10.0);
    rectangle_t startRect = circle.getFrameRect();
    double startArea = circle.getArea();

    circle.move(-10.0, 50.0);
    BOOST_CHECK_EQUAL(startArea, circle.getArea());
    BOOST_CHECK_EQUAL(startRect.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(startRect.height, circle.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    konkin::Circle circle({50.0, 50.0}, 10.0);
    double startArea = circle.getArea();
    const double coef = 10;

    circle.scale(coef);
    BOOST_CHECK_CLOSE(coef * coef * startArea, circle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(WrongParameters)
  {
    BOOST_CHECK_THROW( Circle({50.0, 50.0}, -10.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(WrongScaleParameter)
  {
    konkin::Circle circle({50.0, 50.0}, 10.0);
    BOOST_CHECK_THROW( circle.scale(-10.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()
