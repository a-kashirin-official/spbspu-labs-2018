#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace shumkovskaya;

const double DELTA = 1e-6;

BOOST_AUTO_TEST_SUITE(TestCircle)

BOOST_AUTO_TEST_CASE(MoveByDelta)
{
  shumkovskaya::Circle circle( 1.0, {3.0, 4.0 });
  circle.move(1.0, 18.0);
  BOOST_CHECK_EQUAL(circle.getFrameRect().height / 2, 1.0);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 4.0, DELTA);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 22.0, DELTA);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI, DELTA);
}

BOOST_AUTO_TEST_CASE(TestMoveToPoint)
{
  shumkovskaya::Circle circle( 1.0, { 3.0, 4.0 });
  circle.move( {1.0, 18.0} );
  BOOST_CHECK_EQUAL(circle.getFrameRect().height / 2, 1.0);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, 1.0);
  BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, 18.0);
  BOOST_CHECK_CLOSE(circle.getArea(), M_PI, DELTA);
}

BOOST_AUTO_TEST_CASE(ScaleTest)
{
  shumkovskaya::Circle circle( 4.3, { 15.32, 1.23 } );
  circle.scale(7.0);
  BOOST_CHECK_CLOSE(circle.getArea(), 4.3 * 4.3 * M_PI * 49.0, DELTA);
  BOOST_CHECK_THROW(circle.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestConstructor)
{
  BOOST_CHECK_THROW(shumkovskaya::Circle(-1.0, { 1.32, 1.23 }), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

BOOST_AUTO_TEST_CASE(MoveByDeltaTest)
{
  shumkovskaya::Rectangle rectangle( 7.4, 10.1, { 19.0, 8.0 } );
  rectangle.move(1.0, 12.0);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, 10.1);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, 7.4);
  BOOST_CHECK_CLOSE(rectangle.getArea(), 7.4 * 10.1, DELTA);
}

BOOST_AUTO_TEST_CASE(MoveToPosTest)
{
  shumkovskaya::Rectangle rectangle( 7.0, 10.79,{ 19.64, 8.35 } );
  rectangle.move({ 5.27, 18.9 });
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, 10.79);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, 7.0);
  BOOST_CHECK_CLOSE(rectangle.getArea(), 7.0 * 10.79, DELTA);
}

BOOST_AUTO_TEST_CASE(ScaleTest)
{
  shumkovskaya::Rectangle rectangle( 7.0, 10.7, { 19.64, 8.35 } );
  rectangle.scale(2.0);
  BOOST_CHECK_CLOSE(rectangle.getArea(), 7.0 * 10.7 * 2.0 * 2.0, DELTA);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, 19.64);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, 8.35);
  BOOST_CHECK_THROW(rectangle.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(ConstructorTest)
{
  BOOST_CHECK_THROW(shumkovskaya::Rectangle( -3.26, 7.15, { 15.32, 16.23 }), std::invalid_argument);
  BOOST_CHECK_THROW(shumkovskaya::Rectangle( 3.26, -7.15, { 15.32, 16.23 }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RotateTest)
{
  shumkovskaya::Rectangle rectangle( 2.3, 7.9, {2.9, 4.5 });
  rectangle.rotate(90);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.9, DELTA);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 2.3, DELTA);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, 2.9);
  BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, 4.5);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

BOOST_AUTO_TEST_CASE(MoveByDeltaTest)
{
  shumkovskaya::Circle circle( 1.0, { 5.0, 3.0 } );
  shumkovskaya::Rectangle rectangle( 2.0, 1.0, { 1.0, 0.5 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtr = std::make_shared< shumkovskaya::Circle >(circle);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtr = std::make_shared< shumkovskaya::Rectangle >(rectangle);
  shumkovskaya::CompositeShape compositeShape(circlePtr);
  compositeShape.addShape(rectanglePtr);
  compositeShape.move(1.2, 2.7);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), 2 + M_PI, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 6.0, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 4.0, DELTA);
}

BOOST_AUTO_TEST_CASE(MoveToPointTest)
{
  shumkovskaya::Circle circle( 1.0,{ 5.0, 3.0 } );
  shumkovskaya::Rectangle rectangle( 2.0, 1.0,{ 1.0, 0.5 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtr = std::make_shared< shumkovskaya::Circle >(circle);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtr = std::make_shared< shumkovskaya::Rectangle >(rectangle);
  shumkovskaya::CompositeShape compositeShape(circlePtr);
  compositeShape.addShape(rectanglePtr);
  compositeShape.move({ 1.2, 2.7 });
  BOOST_CHECK_CLOSE(compositeShape.getArea(), 2 + M_PI, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 6.0, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 4.0, DELTA);
}

BOOST_AUTO_TEST_CASE(ScaleTest)
{
  shumkovskaya::Circle circle( 1.0,{ 5.0, 3.0 } );
  shumkovskaya::Rectangle rectangle( 2.0, 1.0,{ 1.0, 0.5 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtr = std::make_shared< shumkovskaya::Circle >(circle);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtr = std::make_shared< shumkovskaya::Rectangle >(rectangle);
  shumkovskaya::CompositeShape compositeShape(circlePtr);
  compositeShape.addShape(rectanglePtr);
  compositeShape.scale(2);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), 8 + 4 * M_PI, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 12.0, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 8.0, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, 3, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, 2, DELTA);
  BOOST_CHECK_THROW(compositeShape.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RemoveShapeTest)
{
  shumkovskaya::Circle circle( 4.3, {3.6, 5.0 } );
  shumkovskaya::Rectangle rectangle( 7.0, 10.79, {2.0, 7.4 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtr = std::make_shared< shumkovskaya::Circle >(circle);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtr = std::make_shared< shumkovskaya::Rectangle >(rectangle);
  shumkovskaya::CompositeShape compositeShape(circlePtr);
  compositeShape.addShape(rectanglePtr);
  compositeShape.removeShape(0);
  BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
  BOOST_CHECK_EQUAL(compositeShape.getArea(), rectangle.getArea());
  BOOST_CHECK_EQUAL(compositeShape.getAmount(), 1);
  BOOST_CHECK_THROW(compositeShape.removeShape(2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(DeleteShapesTest)
{
  shumkovskaya::Circle circle( 4.3, {5.0, 6.32} );
  shumkovskaya::Rectangle rectangle( 7.0, 10.79,{ 19.64, 8.35 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtr = std::make_shared< shumkovskaya::Circle >(circle);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtr = std::make_shared< shumkovskaya::Rectangle >(rectangle);
  shumkovskaya::CompositeShape compositeShape(circlePtr);
  compositeShape.addShape(rectanglePtr);
  compositeShape.removeAll();
  BOOST_CHECK_EQUAL(compositeShape.getAmount(), 0);
}

BOOST_AUTO_TEST_CASE(InvalidIdenticalShapeTest)
{
  shumkovskaya::Circle circle( 4.3,{ 15.32, 1.23 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtr = std::make_shared< shumkovskaya::Circle >(circle);
  shumkovskaya::CompositeShape compositeShape(circlePtr);
  BOOST_CHECK_THROW(compositeShape.addShape(circlePtr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RotateTest)
{
  shumkovskaya::Circle circle( 1.0,{ 5.0, 3.0 } );
  shumkovskaya::Rectangle rectangle( 2.0, 1.0,{ 1.0, 0.5 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtr = std::make_shared< shumkovskaya::Circle >(circle);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtr = std::make_shared< shumkovskaya::Rectangle >(rectangle);
  shumkovskaya::CompositeShape compositeShape(circlePtr);
  compositeShape.addShape(rectanglePtr);
  compositeShape.rotate(90);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 4.0, DELTA);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 6.0, DELTA);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

BOOST_AUTO_TEST_CASE(MatrixSplitting)
{
  Circle circleM( 2.0, { -2.0, -2.0 } );
  shumkovskaya::Rectangle rectangleM1( 2.0, 2.0,{ -2.0, 0.0 } );
  shumkovskaya::Rectangle rectangleM2(  6.0, 3.0,{ 1.0, 1.0 });
  shumkovskaya::Rectangle rectangleM3( 2.0, 4.0, { 3.0, 1.0 } );
  shumkovskaya::Rectangle rectangleM4( 4.0, 4.0,{ 3.0, 3.0 } );
  std::shared_ptr< shumkovskaya::Shape > circlePtrM = std::make_shared< Circle >(circleM);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtrM1 = std::make_shared< shumkovskaya::Rectangle >(rectangleM1);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtrM2 = std::make_shared< shumkovskaya::Rectangle >(rectangleM2);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtrM3 = std::make_shared< shumkovskaya::Rectangle >(rectangleM3);
  std::shared_ptr< shumkovskaya::Shape > rectanglePtrM4 = std::make_shared< shumkovskaya::Rectangle >(rectangleM4);
  shumkovskaya::CompositeShape shapes(circlePtrM);
  shapes.addShape(rectanglePtrM1);
  shapes.addShape(rectanglePtrM2);
  shapes.addShape(rectanglePtrM3);
  shapes.addShape(rectanglePtrM4);
  shumkovskaya::Matrix matrix(shapes);
  BOOST_CHECK_CLOSE(matrix[0][0]->getFrameRect().pos.x, -2.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[0][1]->getFrameRect().pos.x, 3.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[1][0]->getFrameRect().pos.x, -2.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[1][1]->getFrameRect().pos.x, 3.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[2][0]->getFrameRect().pos.x, 1.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[0][0]->getFrameRect().pos.y, -2.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[0][1]->getFrameRect().pos.y, 1.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[1][0]->getFrameRect().pos.y, 0.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[1][1]->getFrameRect().pos.y, 3.0, DELTA);
  BOOST_CHECK_CLOSE(matrix[2][0]->getFrameRect().pos.y, 1.0, DELTA);
}

BOOST_AUTO_TEST_SUITE_END()
