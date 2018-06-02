//
// Created by russk on 13.04.2018.
//
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(RectangleTest)

  const double EPSILON = 0.001;

  BOOST_AUTO_TEST_CASE(ConstWidthHeightMoveTo)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Rectangle rec (point, 10.0, 20.0);
    double widthBefore = rec.getFrameRect().width;
    double heightBefore = rec.getFrameRect().height;

    rec.move({9.0, 20.0});

    BOOST_CHECK_CLOSE(heightBefore, rec.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(widthBefore, rec.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstWidthHeightMoveOn)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Rectangle rec (point, 10.0, 20.0);
    double widthBefore = rec.getFrameRect().width;
    double heightBefore = rec.getFrameRect().height;

    rec.move(9.0, 10.0);

    BOOST_CHECK_CLOSE(heightBefore, rec.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(widthBefore, rec.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstAreaMoveTo)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Rectangle rec (point, 10.0, 20.0);
    double areaBefore = rec.getArea();

    rec.move({9.0, 20.0});

    BOOST_CHECK_CLOSE(areaBefore, rec.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstAreaMoveOn)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Rectangle rec (point, 10.0, 20.0);
    double areaBefore = rec.getArea();

    rec.move(9.0, 10.0);

    BOOST_CHECK_CLOSE(areaBefore, rec.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterScaling)
  {
    const double FACTOR = 2.0;

    russkov::point_t point = {6.0, 8.0};
    russkov::Rectangle rec (point, 10.0, 20.0);
    double areaBefore = rec.getArea();

    rec.scale(FACTOR);

    BOOST_CHECK_CLOSE(areaBefore*FACTOR*FACTOR, rec.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstructorArgument)
  {
    russkov::point_t point = {6.0, 7.0};

    BOOST_CHECK_THROW(russkov::Rectangle(point, -4.0, 5.0), std::invalid_argument);
    BOOST_CHECK_THROW(russkov::Rectangle(point, 4.0, -5.0), std::invalid_argument);
    BOOST_CHECK_THROW(russkov::Rectangle(point, -4.0, -5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScalingArgument)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Rectangle rec (point, 10.0, 20.0);

    BOOST_CHECK_THROW(rec.scale(-5.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  const double RADIUS = 3.33;
  const double AREA = M_PI*RADIUS*RADIUS;
  const double EPSILON = 0.001;

  BOOST_AUTO_TEST_CASE(ConstRadiusMoveTo)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Circle cir (point, RADIUS);
    double widthBefore = cir.getFrameRect().width;
    double heightBefore = cir.getFrameRect().height;

    cir.move({9.0, 20.0});

    BOOST_CHECK_CLOSE(heightBefore, cir.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(widthBefore, cir.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstRadiusMoveOn)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Circle cir (point, RADIUS);
    double widthBefore = cir.getFrameRect().width;
    double heightBefore = cir.getFrameRect().height;

    cir.move(9.0, 10.0);

    BOOST_CHECK_CLOSE(heightBefore, cir.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(widthBefore, cir.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstAreaMoveTo)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Circle cir (point, RADIUS);

    cir.move({9.0, 20.0});

    BOOST_CHECK_CLOSE(AREA, cir.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstAreaMoveOn)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Circle cir (point, RADIUS);

    cir.move(9.0, 10.0);

    BOOST_CHECK_CLOSE(AREA, cir.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterScaling)
  {
    const double FACTOR = 2.0;

    russkov::point_t point = {6.0, 8.0};
    russkov::Circle cir (point, RADIUS);

    cir.scale(FACTOR);

    BOOST_CHECK_CLOSE(AREA*FACTOR*FACTOR, cir.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstructorArgument)
  {
    russkov::point_t point = {6.0, 7.0};

    BOOST_CHECK_THROW(russkov::Circle(point, -15.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScalingArgument)
  {
    russkov::point_t point = {6.0, 8.0};
    russkov::Circle cir (point, RADIUS);

    BOOST_CHECK_THROW(cir.scale(-5.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

