#define BOOST_TEST_MODULE MAIN

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <stdexcept>
#include <cmath>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace aknazarova;

const double EPSI = 0.0001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)
  BOOST_AUTO_TEST_CASE(Move)
  {
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle ({{20.0, 20.0}, 60.0, 40.0}));
    CompositeShape shape(rectPtr);
    
    std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(Circle ({0.0,-10.0},10.0));
    shape.addShape(circPtr);
    
    double area = shape.getArea();
    
    shape.move(15.0, 5.0);
    
    BOOST_CHECK_CLOSE_FRACTION(area, shape.getArea(), EPSI);
    BOOST_CHECK_CLOSE_FRACTION(60, shape.getFrameRect().width, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(60, shape.getFrameRect().height, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(35.0, shape.getFrameRect().pos.x, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(15.0, shape.getFrameRect().pos.y, EPSI);
  }
  
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle ({{20.0, 20.0}, 60.0, 40.0}));
    CompositeShape shape(rectPtr);
    
    std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(Circle ({0.0, -10.0}, 10.0));
    shape.addShape(circPtr);
    
    double area = shape.getArea();
    
    shape.move({15.0, 5.0});
    
    BOOST_CHECK_CLOSE_FRACTION(area, shape.getArea(), EPSI);
    BOOST_CHECK_CLOSE_FRACTION(60, shape.getFrameRect().width, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(60, shape.getFrameRect().height, EPSI);
    BOOST_CHECK_EQUAL(15.0,shape.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(5.0,shape.getFrameRect().pos.y);
  }
  
  BOOST_AUTO_TEST_CASE(CopyInfTest)
  {
    Circle circ({0, 0}, 20);
    Rectangle rect({20, 60},80,40);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    CompositeShape shape(circPtr);
    shape.addShape(rectPtr);
    CompositeShape shape1 = shape;
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().height, 100, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().width, 80, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().pos.x, 20, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().pos.y, 30, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, shape1.getFrameRect().height, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, shape1.getFrameRect().width, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, shape1.getFrameRect().pos.x, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, shape1.getFrameRect().pos.y, EPSI);
  }

  BOOST_AUTO_TEST_CASE(CopyInfOperatorTest)
  {
    Circle circ({0, 0}, 20);
    Rectangle rect({20, 60}, 60, 40);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    CompositeShape shape(circPtr);
    shape.addShape(rectPtr);
    CompositeShape shape1(rectPtr);
    shape = shape1;
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 40, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 60, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, 20, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, 60, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, shape1.getFrameRect().height, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, shape1.getFrameRect().width, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, shape1.getFrameRect().pos.x, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, shape1.getFrameRect().pos.y, EPSI);
  }
 
 BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(Circle({ 0,0 },20));
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle({ 40,0 },40,40));
    CompositeShape shape(circPtr);
    shape.addShape(rectPtr);
    CompositeShape shape1(rectPtr);
    shape1 = std::move(shape);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().width, 80 , EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().height, 40, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().pos.x, 20 , EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().pos.y, 0, EPSI);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(Circle({ 0,0 },20));
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle({ 40,0 },40,40));
    CompositeShape shape(circPtr);
    shape.addShape(rectPtr);
    CompositeShape shape1(std::move(shape));
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().width, 80 , EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().height, 40 , EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().pos.x, 20, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape1.getFrameRect().pos.y, 0, EPSI);
  }

  BOOST_AUTO_TEST_CASE(AreaScaling)
  {
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle ({{20.0, 20.0}, 60.0, 40.0}));
    CompositeShape shape(rectPtr);
    
    std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(Circle ({0.0, -10.0}, 10.0));
    shape.addShape(circPtr);
    
    double area = shape.getArea();
   
    shape.scale(0.5);
    
    BOOST_CHECK_CLOSE_FRACTION(shape.getArea(), area * 0.5 * 0.5, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().height, 30.0, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().width, 30.0, EPSI);
  }
  
  BOOST_AUTO_TEST_CASE(DeleteShapes)
  {
    Circle circ({0, 0}, 10);
    Rectangle rect({10, 20}, 40, 20);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    CompositeShape shape(circPtr);
    shape.addShape(rectPtr);
    shape.deleteShapes();
    BOOST_REQUIRE_EQUAL(shape.getSize(), 0);
    BOOST_CHECK_CLOSE_FRACTION(shape.getArea(), 0, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.x, 0, EPSI);
    BOOST_CHECK_CLOSE_FRACTION(shape.getFrameRect().pos.y, 0, EPSI);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentOfConstructor)
  {
    std::shared_ptr<Shape> circPtr = nullptr;
    BOOST_CHECK_THROW(CompositeShape shape(circPtr), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidArgumentOfAddedElement)
  {
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    CompositeShape shape(rectPtr);
    
    std::shared_ptr<Shape> circPtr = nullptr;
    BOOST_CHECK_THROW(shape.addShape(circPtr), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidArgumentOfScaling)
  {
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    CompositeShape shape(rectPtr);
    
    std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(Circle ({40.0, 80.0}, 10.0));
    shape.addShape(circPtr);
    BOOST_CHECK_THROW(shape.scale(-2.0), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(GeneralParameters)
  {
    std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    CompositeShape shape(rectPtr);
    BOOST_REQUIRE_EQUAL(rectPtr -> getFrameRect().width, shape.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectPtr -> getFrameRect().height, shape.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(rectPtr -> getFrameRect().pos.x, shape.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(rectPtr -> getFrameRect().pos.y, shape.getFrameRect().pos.y);
  }
  
  BOOST_AUTO_TEST_CASE(EmptyCompositeShapeWhenRemovingTest)
  {
    Circle circ({0, 0}, 10);
    Rectangle rect({10, 20}, 40, 20);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    CompositeShape shape(circPtr);
    shape.addShape(rectPtr);
    shape.deleteShapes();
    BOOST_CHECK_THROW(shape.removeShape(1), std::out_of_range);
  }
  
BOOST_AUTO_TEST_SUITE_END()
