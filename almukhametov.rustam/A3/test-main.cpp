#define BOOST_TEST_MODULE

#include <cmath>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(CompositeShape_Tests)

  BOOST_AUTO_TEST_CASE(Constructor_Test)
  {
    BOOST_CHECK_THROW(almukhametov::CompositeShape comp(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingToPos)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {0.0, 1.0});
    almukhametov::CompositeShape comp(&rectangle);
    comp.move({4.0, 0.0});
    BOOST_CHECK_CLOSE(7.0, comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(6.0, comp.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, 4.0, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(7.0*6.0, comp.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Moving)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {3.0, 1.0});
    almukhametov::CompositeShape comp(&rectangle);
    comp.move(4.0, 0.0);
    BOOST_CHECK_CLOSE(7.0, comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(6.0, comp.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, 7.0, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, 1.0, EPSILON);
    BOOST_CHECK_CLOSE(7.0*6.0, comp.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {0.0, 1.0});
    almukhametov::CompositeShape comp(&rectangle);
    comp.scale(4.0);
    BOOST_CHECK_CLOSE(7.0*6.0*4.0*4.0, comp.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scaling_InvalidParameters)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {0.0, 1.0});
    almukhametov::CompositeShape comp(&rectangle);
    BOOST_CHECK_THROW(comp.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AddingShapes)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {0.0, 1.0});
    almukhametov::CompositeShape comp(&rectangle);
    BOOST_CHECK_THROW(comp.newShape(nullptr),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

