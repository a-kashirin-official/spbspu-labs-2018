#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(CompositeShape_Tests)

  BOOST_AUTO_TEST_CASE(InvarienceOfAreaTest)
  {
    konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
    konkin::Circle circle ({2.0 , 2.0}, 1.0);
    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape::ptr_type circlePtr = std::make_shared<konkin::Circle>(circle);
    konkin::CompositeShape comp_shape;
    comp_shape.addShape(rectPtr);
    comp_shape.addShape(circlePtr);
    double area = comp_shape.getArea();
    comp_shape.move(3.0, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getArea(), area, EPS);
  }

  BOOST_AUTO_TEST_CASE(InvarienceOfCoordsTest)
  {
    konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
    konkin::Circle circle ({2.0 , 2.0}, 1.0);

    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape::ptr_type circlePtr = std::make_shared<konkin::Circle>(circle);
    konkin::CompositeShape comp_shape;
    comp_shape.addShape(rectPtr);
    comp_shape.addShape(circlePtr);
    double posX = comp_shape.getFrameRect().pos.x;
    double posY = comp_shape.getFrameRect().pos.y;
    comp_shape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().pos.x, posX, EPS);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().pos.y, posY, EPS);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    konkin::Circle circle ({2.0 , 2.0}, 1.0);
    konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape::ptr_type circlePtr = std::make_shared<konkin::Circle>(circle);
    konkin::CompositeShape comp_shape;
    comp_shape.addShape(rectPtr);
    comp_shape.addShape(circlePtr);

    double area = comp_shape.getArea();
    double coef = 2.0;
    comp_shape.scale(coef);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getArea(), area * pow(coef, 2.0), EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentAddShapeTest)
  {
    konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape comp_shape;
    comp_shape.addShape(rectPtr);

    BOOST_REQUIRE_THROW(comp_shape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScaleTest)
  {
    konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
    konkin::Circle circle ({2.0 , 2.0}, 1.0);
    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape::ptr_type circlePtr = std::make_shared<konkin::Circle>(circle);
    konkin::CompositeShape comp_shape;
    comp_shape.addShape(rectPtr);
    comp_shape.addShape(circlePtr);

    BOOST_REQUIRE_THROW(comp_shape.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(OutOfRangeRemoveShapeTest)
  {
      konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
      konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
      konkin::CompositeShape comp_shape;
      comp_shape.addShape(rectPtr);
      BOOST_REQUIRE_THROW(comp_shape.removeShape(1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeArrayOperatorTest)
  {
    konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape comp_shape;
    comp_shape.addShape(rectPtr);

    BOOST_CHECK_EQUAL(comp_shape[0], rectPtr);
    BOOST_REQUIRE_THROW(comp_shape[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(GeneralAccordance)
  {
    konkin::Rectangle rect ({1.0, 1.0, {4.0, 4.0}});
    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape comp_shape;
    comp_shape.addShape(rectPtr);

    konkin::rectangle_t shapeFrameRect = comp_shape.getFrameRect();
    konkin::rectangle_t rectFrameRect = rectPtr -> getFrameRect();

    BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.pos.x, rectFrameRect.pos.x, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.pos.y, rectFrameRect.pos.y, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.width, rectFrameRect.width, EPS);
    BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.height, rectFrameRect.height, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()
