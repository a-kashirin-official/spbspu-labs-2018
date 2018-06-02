#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

#include <boost/test/included/unit_test.hpp>

const double EPS = 0.000001;

BOOST_AUTO_TEST_SUITE(RectangleTest)
  BOOST_AUTO_TEST_CASE (MoveToTest)
  {
    belonogova::Rectangle rect ({1.0, 2.0, {3.0, 4.0}});
    belonogova::Rectangle originalRect = rect;
    rect.move({1, 1});

    BOOST_CHECK_EQUAL(rect.getFrameRect().height, originalRect.getFrameRect().height);
    BOOST_CHECK_EQUAL(rect.getFrameRect().width, originalRect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect.getArea(), originalRect.getArea());
  }

  BOOST_AUTO_TEST_CASE (MoveOnTest)
  {
    belonogova::Rectangle rect ({1.0, 2.0, {3.0, 4.0}});
    belonogova::Rectangle originalRect = rect;
    rect.move(2.0, 5.0);

    BOOST_CHECK_EQUAL(rect.getFrameRect().height, originalRect.getFrameRect().height);
    BOOST_CHECK_EQUAL(rect.getFrameRect().width, originalRect.getFrameRect().width);
    BOOST_CHECK_EQUAL(rect.getArea(), originalRect.getArea());
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    belonogova::Rectangle rect ({1.0, 2.0, {3.0, 4.0}});
    double areaBeforeScale = rect.getArea();
    double coef = 3.0;
    rect.scale(coef);

    BOOST_CHECK_CLOSE(rect.getArea(), areaBeforeScale*coef*coef, EPS);
  }

  BOOST_AUTO_TEST_CASE(RectangleParametersTest)
  {
    BOOST_CHECK_THROW(belonogova::Rectangle rect ({-1.0, 2.0, {3.0, 4.0}}), std::invalid_argument);
    BOOST_CHECK_THROW(belonogova::Rectangle rect ({1.0, -2.0, {3.0, 4.0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScalingCoefTest)
  {
    belonogova::Rectangle rect ({1.0, 2.0, {3.0, 4.0}});
    BOOST_CHECK_THROW(rect.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)
  BOOST_AUTO_TEST_CASE (MoveToTest)
  {
    belonogova::Circle circ ({1.0, {2.0, 3.0}});
    belonogova::Circle originalCirc = circ;
    circ.move({1,1});

    BOOST_CHECK_EQUAL(circ.getFrameRect().height, originalCirc.getFrameRect().height);
    BOOST_CHECK_EQUAL(circ.getFrameRect().width, originalCirc.getFrameRect().width);
    BOOST_CHECK_EQUAL(circ.getArea(), originalCirc.getArea());
  }

  BOOST_AUTO_TEST_CASE (MoveOnTest)
  {
    belonogova::Circle circ ({1.0, {2.0, 3.0}});
    belonogova::Circle originalCirc = circ;
    circ.move(3, 6);

    BOOST_CHECK_EQUAL(circ.getFrameRect().height, originalCirc.getFrameRect().height);
    BOOST_CHECK_EQUAL(circ.getFrameRect().width, originalCirc.getFrameRect().width);
    BOOST_CHECK_EQUAL(circ.getArea(), originalCirc.getArea());
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    belonogova::Circle circ ({1.0, {2.0, 3.0}});
    double areaBeforeScale = circ.getArea();
    double coef = 5.0;
    circ.scale(coef);

    BOOST_CHECK_CLOSE(circ.getArea(), areaBeforeScale*coef*coef, EPS);
  }

  BOOST_AUTO_TEST_CASE(CircleParametersTest)
  {
    BOOST_CHECK_THROW(belonogova::Circle circ({-1.0, {2.0, 3.0}}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScalingCoefTest)
  {
    belonogova::Circle circ({1.0, {2.0, 3.0}});
    BOOST_CHECK_THROW(circ.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
