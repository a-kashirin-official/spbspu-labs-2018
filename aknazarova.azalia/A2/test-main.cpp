#define BOOST_TEST_MODULE MAIN

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <stdexcept>
#include <cmath>

#include "circle.hpp"
#include "rectangle.hpp"

using namespace aknazarova;

const double EPSI = 0.0001;

BOOST_AUTO_TEST_SUITE (rectangle_suite)
  BOOST_AUTO_TEST_CASE (move)
  {
    point_t cent {19.1, 6.17};
    
    Rectangle rect (cent, 3.6, 12.2);

    rect.move ({11.9, 4.4});

    BOOST_CHECK_EQUAL (rect.getFrameRect ().height, 12.2);
    BOOST_CHECK_EQUAL (rect.getFrameRect ().width, 3.6);
    BOOST_CHECK_CLOSE_FRACTION (rect.getFrameRect ().pos.x, 11.9, EPSI);
    BOOST_CHECK_CLOSE_FRACTION (rect.getFrameRect ().pos.y, 4.4, EPSI);
    BOOST_CHECK_CLOSE_FRACTION (rect.getArea (), 3.6 * 12.2, EPSI);
  }
  
  BOOST_AUTO_TEST_CASE (move_on)
  {
    Rectangle rect ({12.5, 10.1}, 2.15, 14.1);

    rect.move (11.9, 4.4);

    BOOST_CHECK_EQUAL (rect.getFrameRect ().height, 14.1);
    BOOST_CHECK_EQUAL (rect.getFrameRect ().width, 2.15);
    BOOST_CHECK_CLOSE_FRACTION (rect.getFrameRect ().pos.x, 24.4, EPSI);
    BOOST_CHECK_CLOSE_FRACTION (rect.getFrameRect ().pos.y, 14.5, EPSI);
    BOOST_CHECK_CLOSE_FRACTION (rect.getArea (), 2.15 * 14.1, EPSI);
  }

  BOOST_AUTO_TEST_CASE (Scale)
  {
    Rectangle rect ({3, 3.11}, 2.2, 10.5);

    rect.scale (4);

    BOOST_CHECK_CLOSE_FRACTION (rect.getArea (), 10.5 * 2.2 * 4 * 4, EPSI);
    BOOST_CHECK_EQUAL (rect.getFrameRect ().pos.x, 3);
    BOOST_CHECK_EQUAL (rect.getFrameRect ().pos.y, 3.11);
  }

  BOOST_AUTO_TEST_CASE (invalid_constructor_parameters) 
  {
    BOOST_CHECK_THROW (Rectangle ({1, 2}, -10.2, -15.1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (invalid_scale_parameter)
  {
    Rectangle rect ({5.2, 16}, 32, 13.2);
  
    BOOST_CHECK_THROW (rect.scale (-15), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END ()

BOOST_AUTO_TEST_SUITE (circle_suite)
  BOOST_AUTO_TEST_CASE (move)
  {
    point_t point {19.1, 6.17};
    
    Circle circ (point, 3.6);

    circ.move ({11.9, 4.4});

    BOOST_CHECK_EQUAL (circ.getFrameRect ().height, 3.6*2);
    BOOST_CHECK_EQUAL (circ.getFrameRect ().width, 3.6*2);
    BOOST_CHECK_CLOSE_FRACTION (circ.getFrameRect ().pos.x, 11.9, EPSI);
    BOOST_CHECK_CLOSE_FRACTION (circ.getFrameRect ().pos.y, 4.4, EPSI);
    BOOST_CHECK_CLOSE_FRACTION (circ.getArea (), 3.6 * 3.6*M_PI, EPSI);
  }
  
  BOOST_AUTO_TEST_CASE (move_on)
  {
    Circle circ ({12.5,11.2},8.15);

    circ.move (11.9, 4.4);
    
    BOOST_CHECK_CLOSE_FRACTION (circ.getFrameRect ().pos.x, 24.4, EPSI);
    BOOST_CHECK_CLOSE_FRACTION (circ.getFrameRect ().pos.y, 15.6, EPSI);
    BOOST_CHECK_EQUAL (circ.getFrameRect ().height, 8.15*2);
    BOOST_CHECK_EQUAL (circ.getFrameRect ().width, 8.15*2);
    BOOST_CHECK_CLOSE_FRACTION (circ.getArea (), 8.15 * 8.15 * M_PI, EPSI);
  }

  BOOST_AUTO_TEST_CASE (Scale)
  {
    Circle circ ({2, 13.2}, 10.5);

    circ.scale (3);
    
    BOOST_CHECK_EQUAL (circ.getFrameRect ().pos.x, 2);
    BOOST_CHECK_EQUAL (circ.getFrameRect ().pos.y, 13.2);
    BOOST_CHECK_CLOSE_FRACTION (circ.getArea (), 10.5 * 10.5 * 3 * 3 * M_PI,EPSI);
  }

  BOOST_AUTO_TEST_CASE (invalid_constructor_parameters)
  {
    BOOST_CHECK_THROW (Circle ({1, 2}, -10.2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END ()
