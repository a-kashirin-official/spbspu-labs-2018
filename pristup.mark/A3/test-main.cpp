#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(InvarienceOfArea)
  {
    double EPSILON = 0.0001;
    
    pristup::Rectangle rectangle({24.0, 48.0, {128.0, 256.0}});
    pristup::Shape * r = &rectangle;
    pristup::CompositeShape comp_shape(r);
    
    pristup::Circle circle(5.0, {10.0, 10.0});
    pristup::Shape * c = &circle;
    comp_shape.addShape(c);
    
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    pristup::Shape * t = &triangle;
    comp_shape.addShape(t);
    
    double area = comp_shape.getArea();
    comp_shape.move(16.0, 32.0);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getArea(), area, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvarienceOfCoords)
  {
    double EPSILON = 0.0001;
    
    pristup::Rectangle rectangle({24.0, 48.0, {128.0, 256.0}});
    pristup::Shape * r = &rectangle;
    pristup::CompositeShape comp_shape(r);
    
    pristup::Circle circle(5.0, {10.0, 10.0});
    pristup::Shape * c = &circle;
    comp_shape.addShape(c);
    
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    pristup::Shape * t = &triangle;
    comp_shape.addShape(t);
    
    double posX = comp_shape.getFrameRect().pos.x;
    double posY = comp_shape.getFrameRect().pos.y;
    comp_shape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().pos.x, posX, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().pos.y, posY, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    double EPSILON = 0.0001;
    
    pristup::Circle circle(5.0, {10.0, 10.0});
    pristup::Shape * c = &circle;
    pristup::CompositeShape comp_shape(c);
    
    pristup::Rectangle rectangle({24.0, 48.0, {128.0, 256.0}});
    pristup::Shape * r = &rectangle;
    comp_shape.addShape(r);
    
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    pristup::Shape * t = &triangle;
    comp_shape.addShape(t);
    
    double area = comp_shape.getArea();
    comp_shape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getArea(), area * pow(2.0, 2.0), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentConstructor)
  {
    
    pristup::Shape * r = nullptr;
    BOOST_CHECK_THROW(pristup::CompositeShape comp_shape(r), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentAddShape)
  {
    pristup::Rectangle rectangle({24.0, 48.0, {128.0, 256.0}});
    pristup::Shape * r = &rectangle;
    pristup::CompositeShape comp_shape(r);
    
    pristup::Circle circle(5.0, {10.0, 10.0});
    pristup::Shape * c = nullptr;
    
    BOOST_CHECK_THROW(comp_shape.addShape(c), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScale)
  {
    pristup::Rectangle rectangle({24.0, 48.0, {128.0, 256.0}});
    pristup::Shape * r = &rectangle;
    pristup::CompositeShape comp_shape(r);
    
    pristup::Circle circle(5.0, {10.0, 10.0});
    pristup::Shape * c = &circle;
    comp_shape.addShape(c);
    
    pristup::Triangle triangle({3.0, 6.0}, {4.0, 4.0}, {7.0, 5.0});
    pristup::Shape * t = &triangle;
    comp_shape.addShape(t);
    
    BOOST_CHECK_THROW(comp_shape.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(GeneralAccordance)
  {
    double EPSILON = 0.0001;
    
    pristup::Rectangle rectangle({24.0, 48.0, {128.0, 256.0}});
    pristup::Shape * r = &rectangle;
    pristup::CompositeShape comp_shape(r);
    
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().pos.x, rectangle.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().pos.y, rectangle.getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().width, rectangle.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(comp_shape.getFrameRect().height, rectangle.getFrameRect().height, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()


