#define BOOST_TEST_MODULE main_test

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double DELTA = 0.00001;
const double KSCALE = 2.0;

BOOST_AUTO_TEST_SUITE(TestCompositeShp)
  BOOST_AUTO_TEST_CASE(TestMoveToPoint)
  {
    revtova::Rectangle rect ({5.5, 5.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({6.5, 6.5}, 1.0, 1.0);
    revtova::CompositeShape CompShp(&rect);
    CompShp.addShape(&rect1);
    CompShp.move({2.1, 5.6});
    BOOST_CHECK_CLOSE(CompShp.getFrameRect().pos.x, 2.1, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getFrameRect().pos.y, 5.6, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getArea(), 2, DELTA);
    CompShp.clear();
  }
  BOOST_AUTO_TEST_CASE(TestMoveToXY)
  {
    revtova::Rectangle rect ({5.5, 5.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({6.5, 6.5}, 1.0, 1.0);
    revtova::CompositeShape CompShp(&rect);
    CompShp.addShape(&rect1);
    CompShp.move(4.1, 6.3);
    BOOST_CHECK_CLOSE(CompShp.getFrameRect().pos.x, 10.1, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getFrameRect().pos.y, 12.3, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getArea(), 2, DELTA);
    CompShp.clear();
  }
  BOOST_AUTO_TEST_CASE(TestScaleArea)
  {
    revtova::Rectangle rect ({5.5, 5.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({6.5, 6.5}, 1.0, 1.0);
    revtova::CompositeShape CompShp(&rect);
    CompShp.addShape(&rect1);
    CompShp.scale(KSCALE);
    BOOST_CHECK_CLOSE(CompShp.getArea(), 8, DELTA);
    CompShp.clear();
  }
  BOOST_AUTO_TEST_CASE(TestScaleFrameRect)
  {
    revtova::Rectangle rect ({1.5, 1.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({2.5, 2.5}, 1.0, 1.0);
    revtova::Rectangle rect2 ({3.5, 3.5}, 1.0, 1.0);
    revtova::CompositeShape CompShp(&rect);
    CompShp.addShape(&rect1);
    CompShp.addShape(&rect2);
    CompShp.scale(KSCALE);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().pos.x, 2.5, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().pos.y, 2.5, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().width, 6, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().height, 6, DELTA);
    CompShp.clear();
  }
  BOOST_AUTO_TEST_CASE(TestFrameRect)
  {
    revtova::Rectangle rect ({1.0, 2.0}, 3.0, 4.0);
    revtova::Circle circ ({1.0, 2.0}, 10.0);
    revtova::CompositeShape CompShp (&rect);
    CompShp.addShape(&circ);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().pos.x, 1.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().pos.y, 2.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().width, 20, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().height, 20, DELTA);
    CompShp.clear();
  }
  BOOST_AUTO_TEST_CASE(TestCount)
  {
    revtova::Rectangle rect1({2.5, 5.3}, 5.0, 4.1);
    revtova::Rectangle rect2({2.6, 1.4}, 9.2, 3.3);
    revtova::Circle circ1({3.2, 4.1}, 10.2);
    revtova::Circle circ2({3.3, 4.8}, 4.2);
    revtova::CompositeShape CompShp (&rect1);
    CompShp.addShape(&rect2);
    CompShp.addShape(&circ1);
    CompShp.addShape(&circ2);
    BOOST_REQUIRE_EQUAL(CompShp.getCount(), 4);
    CompShp.remove(2);
    BOOST_REQUIRE_EQUAL(CompShp.getCount(), 3);
    CompShp.clear();
  }
  BOOST_AUTO_TEST_CASE(IncorValueScale)
  {
    revtova::Rectangle rect({0.0, 0.0}, 10.0, 15.0);
    revtova::CompositeShape CompShp(&rect);
    BOOST_CHECK_THROW(CompShp.scale(-1), std::invalid_argument);
    CompShp.clear();
  }
BOOST_AUTO_TEST_SUITE_END()
