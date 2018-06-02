#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double precision = 1e-3;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructorParams)
  {
    BOOST_CHECK_THROW(mihajlov::Rectangle({10.0, 10.0}, -2.2, 5.0), std::invalid_argument);
    BOOST_CHECK_THROW(mihajlov::Rectangle({10.0, 10.0}, 0.0, -7.46), std::invalid_argument);
    BOOST_CHECK_THROW(mihajlov::Rectangle({10.0, 10.0}, -32.12, -3.4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    mihajlov::Rectangle rectangle({0.0, 0.0}, 10.3, 5.9);
    const double areaBeforeMoving = rectangle.getArea();
    const mihajlov::rectangle_t rectBeforeMoving  = rectangle.getFrameRect();

    rectangle.move({100.0, 100.0});

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, rectangle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.height, rectangle.getFrameRect().height, precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.width, rectangle.getFrameRect().width, precision);

  }

  BOOST_AUTO_TEST_CASE(MoveByShifting)
  {
    mihajlov::Rectangle rectangle({0.0, 0.0}, 3.0, 14.53);
    const double areaBeforeMoving = rectangle.getArea();
    const mihajlov::rectangle_t rectBerofeMoving = rectangle.getFrameRect();

    rectangle.move(10.42, 4.66);

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, rectangle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBerofeMoving.height, rectangle.getFrameRect().height, precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBerofeMoving.width, rectangle.getFrameRect().width, precision);

  }

  BOOST_AUTO_TEST_CASE(ScallingObject)
  {
    mihajlov::Rectangle rectangle({10.0, 10.0}, 20.0, 30.0);
    const double areaBeforeScalling = rectangle.getArea();
    const double multiplier = 2.5;

    rectangle.scale(multiplier);

    BOOST_CHECK_CLOSE(multiplier*multiplier*areaBeforeScalling, rectangle.getArea(), precision);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructorParams)
  {
    BOOST_CHECK_NO_THROW(mihajlov::Circle({10.0, 10.0}, 0.0));
    BOOST_CHECK_THROW(mihajlov::Circle({10.0, 10.0}, -3.53), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    mihajlov::Circle circle({0.0, 0.0}, 20.0);

    const double areaBeforeMoving = circle.getArea();
    const mihajlov::rectangle_t frameBeforeMoving = circle.getFrameRect();

    circle.move({30.0, 30.0});

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, circle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(frameBeforeMoving.width, circle.getFrameRect().width, precision);
    BOOST_CHECK_CLOSE_FRACTION(frameBeforeMoving.height, circle.getFrameRect().height, precision);
  }

  BOOST_AUTO_TEST_CASE(MoveByShifting)
  {
    mihajlov::Circle circle({10.0, 10.0}, 50.0);

    const double areaBeforeMoving = circle.getArea();
    const mihajlov::rectangle_t rectBeforeMoving = circle.getFrameRect();

    circle.move(32.54, -3.43);

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, circle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.height, circle.getFrameRect().height, precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.width, circle.getFrameRect().width, precision);
  }

  BOOST_AUTO_TEST_CASE(ScallingObject)
  {
    mihajlov::Circle circle({0.0, 0.0}, 10.0);
    const double areaBeforeScalling = circle.getArea();
    const double multiplier = 2.5;

    circle.scale(multiplier);

    BOOST_CHECK_CLOSE(multiplier*multiplier*areaBeforeScalling, circle.getArea(), precision);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape)

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    mihajlov::CompositeShape shape;
    mihajlov::CompositeShape fshape;
    std::shared_ptr<mihajlov::Shape> rectangle(new mihajlov::Rectangle({10.0, 21.3}, 5.0, 10.0));
    std::shared_ptr<mihajlov::Shape> circle(new mihajlov::Circle({10.0, 20.0}, 20.0));
    fshape.addShape(rectangle);
    fshape.addShape(circle);

    BOOST_CHECK_THROW(shape.addShape(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(mihajlov::CompositeShape(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(fshape[2], std::out_of_range);
    BOOST_CHECK_THROW(fshape[-13], std::out_of_range);
    BOOST_CHECK_THROW(fshape.remove(2), std::out_of_range);
    BOOST_CHECK_THROW(fshape.remove(-21), std::out_of_range);
    BOOST_CHECK_THROW(fshape.scale(-2.43), std::invalid_argument);
    BOOST_CHECK_THROW(shape.scale(43.0), std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(CompositeArea)
  {
    mihajlov::CompositeShape shape;
    std::shared_ptr<mihajlov::Shape> circle(new mihajlov::Circle({10.0, 10.0}, 5));
    std::shared_ptr<mihajlov::Shape> rectangle(new mihajlov::Rectangle({2.0, 18.0}, 10.0, 2.0));
    std::shared_ptr<mihajlov::Shape> rectangle1(new mihajlov::Rectangle({32.0, 42.0}, 20.25, 18.5));
    shape.addShape(circle);
    shape.addShape(rectangle);
    shape.addShape(rectangle1);
    const double area = circle->getArea() + rectangle->getArea() + rectangle1->getArea();

    BOOST_CHECK_CLOSE_FRACTION(area, shape.getArea(), precision);

  }

  BOOST_AUTO_TEST_CASE(CompositeMoving)
  {
    mihajlov::CompositeShape shape;
    std::shared_ptr<mihajlov::Shape> circle(new mihajlov::Circle({0.0, 0.0}, 2.5));
    std::shared_ptr<mihajlov::Shape> rectangle(new mihajlov::Rectangle({-12.5, 0.0}, 10.0, 20.0));
    shape.addShape(circle);
    shape.addShape(rectangle);

    const double areaBefore = shape.getArea();
    const mihajlov::rectangle_t previousFrame = shape.getFrameRect();

    shape.move(20.0, -24.536);

    BOOST_CHECK_CLOSE_FRACTION(shape.getArea(), areaBefore, precision);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, previousFrame.width, precision);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, previousFrame.height, precision);

    shape.move(previousFrame.pos);

    BOOST_CHECK_CLOSE_FRACTION(shape.getArea(), areaBefore, precision);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, previousFrame.width, precision);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, previousFrame.height, precision);

  }

  BOOST_AUTO_TEST_CASE(CompositeScalling)
  {
    mihajlov::CompositeShape shape;
    std::shared_ptr<mihajlov::Shape> rectangle(new mihajlov::Rectangle({10.0, 0.0}, 25.0, 12.35));
    std::shared_ptr<mihajlov::Shape> circle(new mihajlov::Circle({32.12, 26.7}, 12.2));
    shape.addShape(rectangle);
    shape.addShape(circle);
    const double areaBefore = shape.getArea();
    shape.scale(3.0);

    BOOST_CHECK_CLOSE(shape.getArea(), 3.0*3.0*areaBefore, precision);
    BOOST_CHECK_CLOSE_FRACTION(shape.getArea(), 3.0*3.0*areaBefore, precision);
  }

BOOST_AUTO_TEST_SUITE_END()
