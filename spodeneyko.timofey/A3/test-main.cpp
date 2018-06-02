#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPS = 0.0001;

BOOST_AUTO_TEST_SUITE(CompositeShape_Tests)

  BOOST_AUTO_TEST_CASE(InvarienceOfAreaTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    std::shared_ptr<spodeneyko::Shape> circlePtr
        = std::make_shared<spodeneyko::Circle>(spodeneyko::Circle(5.0, {10.0, 10.0}));
    comp_shape.addShape(circlePtr);
    double area = comp_shape.getArea();
    comp_shape.move(16.0, 32.0);
    BOOST_REQUIRE_CLOSE_FRACTION(comp_shape.getArea(), area, EPS);
  }

  BOOST_AUTO_TEST_CASE(InvarienceOfCoordsTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    std::shared_ptr<spodeneyko::Shape> circlePtr
        = std::make_shared<spodeneyko::Circle>(spodeneyko::Circle(5.0, {10.0, 10.0}));
    comp_shape.addShape(circlePtr);
    double posX = comp_shape.getFrameRect().pos.x;
    double posY = comp_shape.getFrameRect().pos.y;
    comp_shape.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(comp_shape.getFrameRect().pos.x, posX, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(comp_shape.getFrameRect().pos.y, posY, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    std::shared_ptr<spodeneyko::Shape> circlePtr
        = std::make_shared<spodeneyko::Circle>(spodeneyko::Circle(5.0, {10.0, 10.0}));
    spodeneyko::CompositeShape comp_shape(circlePtr);
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    comp_shape.addShape(rectPtr);
    double area = comp_shape.getArea();
    comp_shape.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(comp_shape.getArea(), area * pow(2.0, 2.0), EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentConstructorTest)
  {
    BOOST_REQUIRE_THROW(spodeneyko::CompositeShape comp_shape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentAddShapeTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    BOOST_REQUIRE_THROW(comp_shape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScaleTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    std::shared_ptr<spodeneyko::Shape> circlePtr
        = std::make_shared<spodeneyko::Circle>(spodeneyko::Circle(5.0, {10.0, 10.0}));
    comp_shape.addShape(circlePtr);
    BOOST_REQUIRE_THROW(comp_shape.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(OutOfRangeRemoveShapeTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    BOOST_REQUIRE_THROW(comp_shape.removeShape(1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeArrayOperatorTest)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    BOOST_REQUIRE_EQUAL(comp_shape[0], rectPtr);
    BOOST_REQUIRE_THROW(comp_shape[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(GeneralAccordance)
  {
    std::shared_ptr<spodeneyko::Shape> rectPtr
        = std::make_shared<spodeneyko::Rectangle>(spodeneyko::Rectangle({24.0, 48.0, {128.0, 256.0}}));
    spodeneyko::CompositeShape comp_shape(rectPtr);
    spodeneyko::rectangle_t shapeFrameRect = comp_shape.getFrameRect();
    spodeneyko::rectangle_t rectFrameRect = rectPtr -> getFrameRect();
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.pos.x, rectFrameRect.pos.x, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.pos.y, rectFrameRect.pos.y, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.width, rectFrameRect.width, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(shapeFrameRect.height, rectFrameRect.height, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()
