#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_SUITE (CompositeShape_test)

  BOOST_AUTO_TEST_CASE (Wrong_composite_shape_creating_test)
  {
    BOOST_CHECK_THROW (gessen::CompositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (Invarience_of_area_after_moving_test)
  {
    gessen::Rectangle *rect = new gessen::Rectangle({128.0, 256.0}, 14.0, 57.0);
    gessen::CompositeShape compShape(rect);
    gessen::Circle *circ = new gessen::Circle ({59.0, 61.0}, 10.0);
    compShape.addShape(circ);
    double area = compShape.getArea();
    compShape.move ({55.0, 39.0});
    BOOST_REQUIRE_EQUAL (compShape.getArea(), area);
    compShape.move (11.0, 22.0);
    BOOST_REQUIRE_EQUAL (compShape.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE (Invarience_of_parametrs_ater_moving_test)
  {
    gessen::Rectangle *rect = new gessen::Rectangle({128.0, 256.0}, 14.0, 57.0);
    gessen::CompositeShape compShape(rect);
    gessen::Circle *circ = new gessen::Circle ({59.0, 61.0}, 10.0);
    compShape.addShape(circ);
    double width = compShape.getFrameRect().width;
    double height = compShape.getFrameRect().height;
    compShape.move ({55.0, 39.0});
    BOOST_REQUIRE_EQUAL(width, compShape.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(height, compShape.getFrameRect().height);
    compShape.move (55.0, 39.0);
    BOOST_REQUIRE_EQUAL(width, compShape.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(height, compShape.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE (Wrong_adding_test)
  {
    gessen::Rectangle *rect = new gessen::Rectangle({128.0, 256.0}, 14.0, 57.0);
    gessen::CompositeShape compShape(rect);
    BOOST_CHECK_THROW(compShape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (Invarience_of_area_after_scaling_test)
  {
    gessen::Rectangle *rect = new gessen::Rectangle({128.0, 256.0}, 14.0, 57.0);
    gessen::CompositeShape compShape(rect);
    gessen::Circle *circ = new gessen::Circle ({59.0, 61.0}, 10.0);
    compShape.addShape(circ);
    compShape.scale(2.0);
    BOOST_CHECK_CLOSE(compShape.getArea(), 4448.637061, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()
