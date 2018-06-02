#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"

const double ACCURACY = 0.0001;
const double RADIUS = 21.0;
const double AREA = M_PI * RADIUS * RADIUS;
const double COEFFICIENT = 1.1;

BOOST_AUTO_TEST_SUITE(Rectangle_test)
  BOOST_AUTO_TEST_CASE(Constructor_test_for_rectangle)
  {
    BOOST_CHECK_THROW(petrachenko::Rectangle rectangle(-21.0, 48.4, {87.6, 101.01}), std::invalid_argument);
    BOOST_CHECK_THROW(petrachenko::Rectangle rectangle(21.0, -48.4, {87.6, 101.01}), std::invalid_argument);
    BOOST_CHECK_THROW(petrachenko::Rectangle rectangle(-21.0, -48.4, {87.6, 101.01}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_to_delta_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    rectangle.move(14.8, 88.0);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 21.0, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 48.4, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 21.0*48.4, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    rectangle.move({13.0, 13.5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 21.0, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 48.4, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 21.0*48.4, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    rectangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 21.0*48.4*pow(COEFFICIENT, 2), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_coefficient_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    BOOST_CHECK_THROW(rectangle.scale(-2.3), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rotate_test_for_rectangle)
  {
    petrachenko::Rectangle rectangle(21.0, 48.4, {87.6, 101.01});
    rectangle.rotate(90);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 48.4, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 21.0, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 21.0*48.4, ACCURACY);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_test)
  BOOST_AUTO_TEST_CASE(Constructor_test_for_circle)
  {
    BOOST_CHECK_THROW(petrachenko::Circle circle(-21.0, {87.6, 101.01}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_to_delta_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    circle.move(14.8, 88.0);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    circle.move({13.0, 13.5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().width / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, RADIUS, ACCURACY);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    circle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA*pow(COEFFICIENT, 2), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Scale_coefficient_test_for_circle)
  {
    petrachenko::Circle circle(RADIUS, {87.6, 101.01});
    BOOST_CHECK_THROW(circle.scale(-2.3), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_test)

  BOOST_AUTO_TEST_CASE(Constructor_test_for_compositeShape)
  {
    BOOST_CHECK_THROW(petrachenko::CompositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Adding_rectangle)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::CompositeShape CompositeShape(rectangle);
    double area = rectangle->getArea();
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), area, ACCURACY);
    CompositeShape.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), pow(COEFFICIENT, 2) * area, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Adding_circle)
  {
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::CompositeShape CompositeShape(circle);
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), circle->getArea(), ACCURACY);
    CompositeShape.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), AREA*pow(COEFFICIENT, 2), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(AddShape_test_for_compositeShape)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::CompositeShape CompositeShape(rectangle);
    BOOST_CHECK_THROW(CompositeShape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Both_addShape_for_compositeShape)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::CompositeShape CompositeShape(rectangle);
    CompositeShape.addShape(circle);
    double rectangleArea = rectangle->getArea();
    double circleArea = circle->getArea();
    BOOST_CHECK_EQUAL(CompositeShape.getCount(), 2);
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), rectangleArea+circleArea, ACCURACY);
    CompositeShape.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), pow(COEFFICIENT, 2)*(rectangleArea+circleArea), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Moving_test_for_compositeShape)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::CompositeShape CompositeShape(rectangle);
    CompositeShape.addShape(circle);
    BOOST_CHECK_EQUAL(CompositeShape.getCount(),2);
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), rectangle->getArea()+circle->getArea(), ACCURACY);
    petrachenko::point_t posx = {13.8, 82.0};
    CompositeShape.move(posx); //move to point
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), rectangle->getArea()+circle->getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(CompositeShape.getFrameRect().pos.x, posx.x, ACCURACY);
    BOOST_CHECK_CLOSE(CompositeShape.getFrameRect().pos.y, posx.y, ACCURACY);
    CompositeShape.move(posx.x,posx.y); //move to delta
    BOOST_CHECK_CLOSE(CompositeShape.getArea(), rectangle->getArea()+circle->getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(CompositeShape.getFrameRect().pos.x, posx.x+posx.x, ACCURACY);
    BOOST_CHECK_CLOSE(CompositeShape.getFrameRect().pos.y, posx.y+posx.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Rotate_test_for_compositeShape)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::CompositeShape compositeShape(rectangle);
    compositeShape.addShape(circle);
    compositeShape.rotate(90);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), rectangle->getArea()+circle->getArea(), ACCURACY);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_test)

  BOOST_AUTO_TEST_CASE(AddShape_test_for_matrix)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::Circle *circle = new petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::Matrix mtrx(rectangle);
    mtrx.addShape(circle);
    BOOST_CHECK_EQUAL(mtrx[0], rectangle);
    BOOST_CHECK_EQUAL(mtrx[1], circle);
  }

  BOOST_AUTO_TEST_CASE(Test_move)
  {
    petrachenko::Rectangle *rectangle = new petrachenko::Rectangle(21.0, 48.4, {87.6, 101.01});
    petrachenko::Circle *circle = new  petrachenko::Circle(RADIUS, {87.6, 101.01});
    petrachenko::Matrix mtrx(rectangle);
    mtrx.addShape(circle);
    petrachenko::Matrix mtrx2(std::move(mtrx));
    BOOST_CHECK_EQUAL(mtrx2[0], rectangle);
    BOOST_CHECK_EQUAL(mtrx2[1], circle);
  }
BOOST_AUTO_TEST_SUITE_END()

