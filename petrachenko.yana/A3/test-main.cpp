#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

const double ACCURACY = 0.0001;
const double RADIUS = 21.0;
const double AREA = M_PI * RADIUS * RADIUS;
const double COEFFICIENT = 1.1;

BOOST_AUTO_TEST_SUITE(CompositeShape_test)

  BOOST_AUTO_TEST_CASE(Constructor_test_for_compositeShape)
  {
    BOOST_CHECK_THROW(petrachenko::CompositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Adding_rectangle)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::CompositeShape compositeShape(rectangle);
    double area = rectangle->getArea();
    BOOST_CHECK_CLOSE(compositeShape.getArea(), area, ACCURACY);
    compositeShape.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), pow(COEFFICIENT, 2) * area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Adding_circle)
  {
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::CompositeShape compositeShape(circle);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), AREA, ACCURACY);
    compositeShape.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), AREA*pow(COEFFICIENT, 2), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(AddShape_test_for_compositeShape)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::CompositeShape compositeShape(rectangle);
    BOOST_CHECK_THROW(compositeShape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Both_addShape_for_compositeShape)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::CompositeShape compositeShape(rectangle);
    compositeShape.addShape(circle);
    double rectangleArea = rectangle->getArea();
    double circleArea = circle->getArea();
    BOOST_CHECK_EQUAL(compositeShape.getCount(), 2);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), rectangleArea+circleArea, ACCURACY);
    compositeShape.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), pow(COEFFICIENT, 2)*(rectangleArea+circleArea), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Moving_test_for_compositeShape)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::CompositeShape compositeShape(rectangle);
    compositeShape.addShape(circle);
    BOOST_CHECK_EQUAL(compositeShape.getCount(),2);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), rectangle->getArea()+circle->getArea(), ACCURACY);
    petrachenko::point_t posx = {14.8, 88.0};
    compositeShape.move(posx);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), rectangle->getArea()+circle->getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, posx.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, posx.y, ACCURACY);
    compositeShape.move(posx.x,posx.y);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), rectangle->getArea()+circle->getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, posx.x+posx.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, posx.y+posx.y, ACCURACY);
  }
BOOST_AUTO_TEST_SUITE_END()

