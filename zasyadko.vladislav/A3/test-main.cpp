#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <memory>
#include <cmath>
#include <stdexcept>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace zasyadko;
const double EPSILON = 0.0001;
BOOST_AUTO_TEST_SUITE(CircleTesting)

  BOOST_AUTO_TEST_CASE(MoveByXYTest)
  {
    Circle testCircle({10,10},20);
    testCircle.move(15,15);
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(),20);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(),400*M_PI,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MoveToXYPointTest)
  {
    Circle testCircle({10,10},20);
    testCircle.move({20,20});
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(),20);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(),400*M_PI,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(AreaScaleTest)
  {
    Circle testCircle({10,10},20);
    testCircle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(),400*4*M_PI,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(InvalidScaleCircleTest)
  {
    Circle testCircle({10,10},20);
    BOOST_CHECK_THROW(testCircle.scale(-2),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InvalidInitCircleTest)
  {
    BOOST_CHECK_THROW(Circle({10,10},-20),std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(MoveByXYTest)
  {
    Rectangle testRect({10,10},15,20);
    testRect.move(10,10);
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().width,20);
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().height,15);
    BOOST_CHECK_CLOSE_FRACTION(testRect.getArea(),300,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MoveToXYPointTest)
  {
    Rectangle testRect({10,10},15,20);
    testRect.move({10,10});
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().width,20);
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().height,15);
    BOOST_CHECK_CLOSE_FRACTION(testRect.getArea(),300,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(AreaScaleTest)
  {
    Rectangle testRect({10,10},15,20);
    testRect.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testRect.getArea(),300*4,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(InvalidScaleRectTest)
  {
    Rectangle testRect({10,10},15,20);
    BOOST_CHECK_THROW(testRect.scale(-2),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InvalidArgsTest)
  {
    BOOST_CHECK_THROW(Rectangle({10,10},-15,20),std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({10,10},15,-20),std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(MoveByXYTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    testCompShape.move(10.0,10.0);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().height,30,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().width,30,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getArea(),testCircle.getArea()+testRect.getArea(),EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(MoveToXYPointTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    testCompShape.move({10.0,10.0});
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().height,30,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().width,30,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getArea(),testCircle.getArea()+testRect.getArea(),EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(AreaScaleTest)
  {
    Rectangle testRect({10.0,30.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({30.0,10.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    rectangle_t frame = testCompShape.getFrameRect();
    testCompShape.scale(2.0);
    BOOST_CHECK_CLOSE(testCompShape.getShapeInfo(0)->getFrameRect().height, 40.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getShapeInfo(0)->getFrameRect().width, 40.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getShapeInfo(0)->getFrameRect().pos.x, 0.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getShapeInfo(0)->getFrameRect().pos.y, 40.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getShapeInfo(1)->getFrameRect().width, 40.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getShapeInfo(1)->getFrameRect().pos.x, 40.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getShapeInfo(1)->getFrameRect().pos.y, 0.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().height, frame.height*2,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().width, frame.width*2,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getArea(),(testCircle.getArea()+testRect.getArea())*4.0,EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(ShapeDeleteTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    testCompShape.deleteShape(1);
    BOOST_REQUIRE_EQUAL(testCompShape.getAmount(), 1);
  }
  
  BOOST_AUTO_TEST_CASE(CenterTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    rectangle_t frame = testCompShape.getFrameRect();
    testCompShape.scale(2.0);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().pos.x,frame.pos.x,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().pos.y,frame.pos.y,EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidScaleTest)
  {
    Rectangle testRect({10,10},20,20);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    CompositeShape testCompShape(rectptr);
    BOOST_CHECK_THROW(testCompShape.scale(-2), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(SameShapeTest)
  {
    Rectangle testRect({10,10},20,20);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    CompositeShape testCompShape(rectptr);
    BOOST_CHECK_THROW(testCompShape.addShape(rectptr),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(InvalidDeleteTest)
  {
    Rectangle testRect({10,10},20,20);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    CompositeShape testCompShape(rectptr);
    BOOST_CHECK_THROW(testCompShape.deleteShape(2),std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(CopyTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    rectangle_t frame = testCompShape.getFrameRect();
    CompositeShape testCopy(testCompShape);
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().height,frame.height,EPSILON);
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().width,frame.width,EPSILON);
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().pos.x,frame.pos.x,EPSILON);
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().pos.y,frame.pos.y,EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    rectangle_t frame = testCompShape.getFrameRect();
    CompositeShape testCopy(circptr);
    testCopy = testCompShape;
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().height,frame.height,EPSILON);
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().width,frame.width,EPSILON);
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().pos.x,frame.pos.x,EPSILON);
    BOOST_CHECK_CLOSE(testCopy.getFrameRect().pos.y,frame.pos.y,EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(DeleteAllTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    testCompShape.deleteAll();
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().width,0.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().height,0.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().pos.x,0.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getFrameRect().pos.y,0.0,EPSILON);
    BOOST_CHECK_CLOSE(testCompShape.getArea(),0.0,EPSILON);
    BOOST_REQUIRE_EQUAL(testCompShape.getAmount(),0);
  }
  
  BOOST_AUTO_TEST_CASE(MovingCompositeShapeTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    rectangle_t frame = testCompShape.getFrameRect();
    CompositeShape testMove(std::move(testCompShape));
    BOOST_CHECK_CLOSE(testMove.getFrameRect().height,frame.height,EPSILON);
    BOOST_CHECK_CLOSE(testMove.getFrameRect().width,frame.width,EPSILON);
    BOOST_CHECK_CLOSE(testMove.getFrameRect().pos.x,frame.pos.x,EPSILON);
    BOOST_CHECK_CLOSE(testMove.getFrameRect().pos.y,frame.pos.y,EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(MovingOperatorTest)
  {
    Rectangle testRect({10.0,10.0},20.0,20.0);
    std::shared_ptr< Shape > rectptr = std::make_shared< Rectangle >(testRect);
    Circle testCircle({20.0,20.0},10.0);
    std::shared_ptr< Shape > circptr = std::make_shared< Circle >(testCircle);
    CompositeShape testCompShape(rectptr);
    testCompShape.addShape(circptr);
    rectangle_t frame = testCompShape.getFrameRect();
    CompositeShape testMove(circptr);
    testMove = std::move(testCompShape);
    BOOST_CHECK_CLOSE(testMove.getFrameRect().height,frame.height,EPSILON);
    BOOST_CHECK_CLOSE(testMove.getFrameRect().width,frame.width,EPSILON);
    BOOST_CHECK_CLOSE(testMove.getFrameRect().pos.x,frame.pos.x,EPSILON);
    BOOST_CHECK_CLOSE(testMove.getFrameRect().pos.y,frame.pos.y,EPSILON);
  }
  BOOST_AUTO_TEST_SUITE_END()
