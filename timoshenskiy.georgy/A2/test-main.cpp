//
//  test-main.cpp
//  A2
//
//  Created by Георгий Тимошенский on 17.04.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <math.h>
#include "rectangle.hpp"
#include "circle.hpp"

const double EPS_REL = 0.0001;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Rect_ParametersDuringMovingInTest)
  {
    timoshenskiy::Rectangle r({{2.0, 3.0}, 10.0, 14.0});
    double area = r.getArea();
    r.move({1.0, 2.0});
    BOOST_REQUIRE_EQUAL(r.getFrameRect().width, 10.0);
    BOOST_REQUIRE_EQUAL(r.getFrameRect().height, 14.0);
    BOOST_REQUIRE_EQUAL(r.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Rect_ParametersDuringMovingOnTest)
  {
    timoshenskiy::Rectangle r({{2.0, 3.0}, 10.0, 14.0});
    double area = r.getArea();
    r.move(1.0,2.0);
    BOOST_REQUIRE_EQUAL(r.getFrameRect().width, 10.0);
    BOOST_REQUIRE_EQUAL(r.getFrameRect().height, 14.0);
    BOOST_REQUIRE_EQUAL(r.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Rect_ScaleTest)
  {
    timoshenskiy::Rectangle r({{2.0, 3.0}, 10.0, 14.0});
    double area = r.getArea();
    double multiplierR = 2.0;
    r.scale(multiplierR);
    BOOST_REQUIRE_CLOSE_FRACTION(r.getArea(), area * std::pow(multiplierR, 2), EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Rect_InvalidArgumentsConstructorTest)
  {
    BOOST_CHECK_THROW(timoshenskiy::Rectangle r({{2.0, 3.0}, -10.0, 14.0}),std::invalid_argument);
 
    BOOST_CHECK_THROW(timoshenskiy::Rectangle r({{2.0, 3.0}, 10.0, -14.0}),std::invalid_argument);

    BOOST_CHECK_THROW(timoshenskiy::Rectangle r({{2.0, 3.0}, -10.0, -14.0}),std::invalid_argument);
 }

  BOOST_AUTO_TEST_CASE(Rect_InvalidArgumentScaleTest)
  {
    timoshenskiy::Rectangle r({{2.0, 3.0}, 10.0, 14.0});
    BOOST_CHECK_THROW(r.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Circle_Tests)

  BOOST_AUTO_TEST_CASE(Circle_ParametersDuringMovingInTest)
  {
    timoshenskiy::Circle c({{0.0, 0.0}, 10.0});
    double area = c.getArea();
    c.move({1.0, 2.0});
    BOOST_REQUIRE_EQUAL(c.getFrameRect().width, 20.0);
    BOOST_REQUIRE_EQUAL(c.getFrameRect().height, 20.0);
    BOOST_REQUIRE_EQUAL(c.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Circle_ParametersDuringMovingOnTest)
  {
    timoshenskiy::Circle c({{0.0, 0.0}, 10.0});
    double area = c.getArea();
    c.move(1.0,2.0);
    BOOST_REQUIRE_EQUAL(c.getFrameRect().width, 20.0);
    BOOST_REQUIRE_EQUAL(c.getFrameRect().height, 20.0);
    BOOST_REQUIRE_EQUAL(c.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Circle_ScaleTest)
  {
    timoshenskiy::Circle c({{0.0, 0.0}, 10.0});
    double area = c.getArea();
    double multiplierC = 2.0;
    c.scale(multiplierC);
    BOOST_REQUIRE_CLOSE_FRACTION(c.getArea(), area * std::pow(multiplierC, 2), EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Circle_InvalidArgumentsConstructorTest)
  {
    BOOST_CHECK_THROW(timoshenskiy::Circle c({{0.0, 0.0}, -10.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_InvalidArgumentScaleTest)
  {
    timoshenskiy::Circle c({{0.0, 0.0}, 10.0});
    BOOST_CHECK_THROW(c.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

