#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <memory>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace stashevskii;

const double EPSILON_TEST = 0.00001;

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYRadiusTest)
  {
    Circle new_circle(10, {0,0});
    new_circle.move(10, 20);
    BOOST_REQUIRE_EQUAL(new_circle.getFrameRect().height / 2 , 10);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_EQUAL(new_circle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(new_circle.getPosition().y, 20);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointRadiusTest)
  {
    Circle new_circle(10, {0,0});
    new_circle.move({20, 10});
    BOOST_REQUIRE_EQUAL(new_circle.getFrameRect().height / 2 , 10);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_EQUAL(new_circle.getPosition().x, 20);
    BOOST_CHECK_EQUAL(new_circle.getPosition().y, 10);
  }

  BOOST_AUTO_TEST_CASE(MoveToXYAreaTest)
  {
    Circle new_circle(10, {0,0});
    new_circle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_EQUAL(new_circle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(new_circle.getPosition().y, 20);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointAreaTest)
  {
    Circle new_circle(10, {0,0});
    new_circle.move({20,10});
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_EQUAL(new_circle.getPosition().x, 20);
    BOOST_CHECK_EQUAL(new_circle.getPosition().y, 10);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    Circle new_circle(10, {0,0});
    new_circle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI * 5 * 5, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleTest)
  {
    BOOST_CHECK_THROW(Circle(-5.5, {0,0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleScaleTest)
  {
    Circle new_circle (10, {0,0});
    BOOST_CHECK_THROW(new_circle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYHeightTest)
  {
    Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move(10, 20);
    BOOST_REQUIRE_EQUAL(new_rectangle.getFrameRect().height , 20);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().y, 20);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointHeightTest)
  {
    Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move({20, 10});
    BOOST_REQUIRE_EQUAL(new_rectangle.getFrameRect().height , 20);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().x, 20);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().y, 10);
  }

  BOOST_AUTO_TEST_CASE(MoveToXYWidthTest)
  {
    Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move(10, 20);
    BOOST_REQUIRE_EQUAL(new_rectangle.getFrameRect().width , 10);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().y, 20);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointWidthTest)
  {
    Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move({20, 10});
    BOOST_REQUIRE_EQUAL(new_rectangle.getFrameRect().width , 10);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().x, 20);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().y, 10);
  }

  BOOST_AUTO_TEST_CASE(MoveToXYAreaTest)
  {
    Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 10 * 20 , EPSILON_TEST);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().y, 20);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointAreaTest)
  {
    Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move({10,20});
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 10 * 20 , EPSILON_TEST);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().x, 10);
    BOOST_CHECK_EQUAL(new_rectangle.getPosition().y, 20);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 10 * 5 * 20 * 5 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleHeightTest)
  {
    BOOST_CHECK_THROW(Rectangle(10, -5.5, {0,0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleWigthTest)
  {
    BOOST_CHECK_THROW(Rectangle(-5.5, 10, {0,0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleScaleTest)
  {
    Rectangle new_rectangle (10, 20, {0,0});
    BOOST_CHECK_THROW(new_rectangle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    CompositeShape objShape;
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(8, 8, { 8, 8 })));
    objShape.addShape(std::shared_ptr< Shape >(new Circle(5, { 5, 5 })));
    CompositeShape objShape2(objShape);
    BOOST_CHECK_EQUAL(objShape.getArea(), objShape2.getArea());
  }

  BOOST_AUTO_TEST_CASE(CopyOperatorTest)
  {    
    CompositeShape Comp1;
    Comp1.addShape(std::shared_ptr< Shape >(new Rectangle(8, 8, { 8, 8 })));
    Comp1.addShape(std::shared_ptr< Shape >(new Rectangle(5, 5, { 0, 0 })));
    Comp1.addShape(std::shared_ptr<Shape>(new Circle(5, { 5, 5 })));
    CompositeShape Comp2;
    Comp2.addShape(std::shared_ptr< Shape >(new Rectangle(1, 6, { 5, 5 })));
    Comp2 = Comp1;
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getArea(), Comp1.getArea(),EPSILON_TEST);
  }
  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    CompositeShape objShape,objShape3;
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(5, 5, { 5, 5 })));
    objShape3.addShape(std::shared_ptr< Shape >(new Rectangle(5, 5, { 5, 5 })));
    CompositeShape objShape2 (std::move(objShape));
    BOOST_CHECK_EQUAL(objShape3.getArea(), objShape2.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    CompositeShape objShape, objShape2,objShape3;
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(5, 5, { 5, 5 })));
    objShape3.addShape(std::shared_ptr< Shape >(new Rectangle(5, 5, { 5, 5 })));
    objShape2 = std::move(objShape);
    BOOST_CHECK_EQUAL(objShape3.getArea(), objShape2.getArea());
  }

  BOOST_AUTO_TEST_CASE(OperatorIndexTest)
  {
    CompositeShape objShape;
    std::shared_ptr< Shape > shape(new Rectangle(5, 5, { 5, 5 }));
    objShape.addShape(shape);
    BOOST_REQUIRE_EQUAL(objShape[0], shape);
  }
  BOOST_AUTO_TEST_CASE(ThrowIndexTest)
  {
    CompositeShape objShape;
    std::shared_ptr< Shape > shape(new Rectangle(5, 5, { 5, 5 }));
    objShape.addShape(shape);
    BOOST_CHECK_THROW(objShape[7], std::out_of_range);
    BOOST_CHECK_THROW(objShape[-10], std::out_of_range);
  }
  
   BOOST_AUTO_TEST_CASE(AreaTest)
  {
    CompositeShape objShape;
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(5, 5, { 5, 5 })));
    objShape.addShape(std::shared_ptr< Shape >(new Circle(2, { 2, 2 })));
    BOOST_CHECK_CLOSE(objShape.getArea(), M_PI * 2 * 2 + 25, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ScaleAreaTest)
  {
    CompositeShape objShape;
    objShape.addShape(std::shared_ptr< Shape >(new Circle(40, { 5, 5 })));
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(40, 40, { 5, 5 })));
    objShape.scale(10);
    BOOST_CHECK_CLOSE(objShape[0]->getArea(), M_PI * 40 * 40 * 10 * 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE(objShape[1]->getArea(), 40 * 40 * 10 * 10, EPSILON_TEST);
    BOOST_REQUIRE_EQUAL(objShape.getArraySize(), 2);
    BOOST_CHECK_CLOSE(objShape[0]->getFrameRect().pos.x, 5, EPSILON_TEST);
    BOOST_CHECK_CLOSE(objShape[0]->getFrameRect().pos.y, 5, EPSILON_TEST);
    BOOST_CHECK_CLOSE(objShape[1]->getFrameRect().pos.x, 5, EPSILON_TEST);
    BOOST_CHECK_CLOSE(objShape[1]->getFrameRect().pos.y, 5, EPSILON_TEST);
  }
    
  BOOST_AUTO_TEST_CASE(InvalidArgumentScale)
  {
    CompositeShape objShape;
    std::shared_ptr< Shape > shape(new Rectangle(5, 5, { 5, 5 }));
    objShape.addShape(shape);
    BOOST_CHECK_THROW(objShape.scale(-10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTest)
  {
    CompositeShape objShape;
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { -20, 15 })));
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { -20, -15 })));
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { 10, 15 })));
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { 10, -15 })));
    objShape.move({ 10, 10 });
    BOOST_CHECK_CLOSE(objShape.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE(objShape.getFrameRect().pos.y, 10, EPSILON_TEST);
  }

BOOST_AUTO_TEST_CASE(MoveTest)
  {
    CompositeShape objShape;
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { -20, 15 })));
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { -20, -15 })));
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { 10, 15 })));
    objShape.addShape(std::shared_ptr< Shape >(new Rectangle(4, 4, { 10, -15 })));
    objShape.move( 10, 0 );
    BOOST_CHECK_CLOSE(objShape.getPosition().x, 5, EPSILON_TEST);
    BOOST_CHECK_CLOSE(objShape.getPosition().y, 0, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapeThrowTest)
  {
    CompositeShape objShape;
    std::shared_ptr< Shape > shape(new Circle(6, { 6, 6 }));
    std::shared_ptr< Shape > shape1(new Circle(3, { 2, 2 }));
    objShape.addShape(shape);
    objShape.addShape(shape1);
    BOOST_CHECK_THROW(objShape.deleteShape(100), std::out_of_range);
    BOOST_CHECK_THROW(objShape.deleteShape(-100), std::out_of_range);    
  }
  

  BOOST_AUTO_TEST_CASE(DeleteShapeTest)
  {
    CompositeShape objShape;
    std::shared_ptr< Shape > shape(new Circle(4, { 7, 4 }));
    std::shared_ptr< Shape > shape1(new Circle(8, { 8, 9 }));
    objShape.addShape(shape);
    objShape.addShape(shape1);
    objShape.deleteShape(1);
    BOOST_REQUIRE_EQUAL(objShape.getArraySize(), 1);
    BOOST_CHECK_CLOSE(objShape[0]->getFrameRect().height, 16, EPSILON_TEST);
    BOOST_CHECK_CLOSE(objShape[0]->getFrameRect().width, 16, EPSILON_TEST);
  }
  
BOOST_AUTO_TEST_SUITE_END()

