#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 1e-8;

BOOST_AUTO_TEST_SUITE(testsOfCompShape)

BOOST_AUTO_TEST_CASE(invalidConstructor)
{
  std::shared_ptr<marchenko::Shape> testRect = nullptr;
  BOOST_CHECK_THROW(marchenko::CompositeShape testComp(testRect), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(copyConstructor)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  marchenko::CompositeShape newComp(testComp);
  BOOST_CHECK_EQUAL(testComp[0], newComp[0]);
  BOOST_CHECK_EQUAL(testComp[1], newComp[1]);
}

BOOST_AUTO_TEST_CASE(moveConstructor)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  marchenko::CompositeShape newComp(std::move(testComp));
  BOOST_CHECK_EQUAL(newComp[0], ptr1);
  BOOST_CHECK_EQUAL(newComp[1], ptr2);
  BOOST_CHECK_EQUAL(newComp.getSize(), 2);
}

BOOST_AUTO_TEST_CASE(copyOperator)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  std::shared_ptr< marchenko::Shape > ptr3(new marchenko::Rectangle(6.0, 16.0, {36.0, 36.0}));
  std::shared_ptr< marchenko::Shape > ptr4(new marchenko::Circle({3.6, 2.6}, 106));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  marchenko::CompositeShape newComp;
  newComp.addShape(ptr3);
  newComp.addShape(ptr4);
  newComp = testComp;
  BOOST_CHECK_EQUAL(newComp[0],testComp[0]);
  BOOST_CHECK_EQUAL(newComp[1],testComp[1]);
}

BOOST_AUTO_TEST_CASE(moveOperator)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  std::shared_ptr< marchenko::Shape > ptr3(new marchenko::Rectangle(6.0, 16.0, {36.0, 36.0}));
  std::shared_ptr< marchenko::Shape > ptr4(new marchenko::Circle({3.6, 2.6}, 106));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  marchenko::CompositeShape newComp;
  newComp.addShape(ptr3);
  newComp.addShape(ptr4);
  newComp = std::move(testComp);
  BOOST_CHECK_EQUAL(newComp[0],ptr1);
  BOOST_CHECK_EQUAL(newComp[1],ptr2);
}

BOOST_AUTO_TEST_CASE(GeneralPosition)
{
  marchenko::point_t position = {2.0, 4.0};
  double width = 10.0, height = 10.0;
  std::shared_ptr<marchenko::Shape> testRect =
    std::make_shared<marchenko::Rectangle>(marchenko::Rectangle(width, height, position));
  marchenko::CompositeShape testComp(testRect);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.x, position.x, EPSILON);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.y, position.y, EPSILON);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().width, width, EPSILON);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().height, height, EPSILON);
}

BOOST_AUTO_TEST_CASE(moveToNewPosition)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  double fstHeight = testComp.getFrameRect().height;
  double fstWidth = testComp.getFrameRect().width;
  double fstArea = testComp.getArea();
  marchenko::point_t positionAfterMoving = {5.0, 5.0};
  testComp.move(positionAfterMoving);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.x, positionAfterMoving.x, EPSILON);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.y, positionAfterMoving.y, EPSILON);
  BOOST_CHECK_EQUAL(fstHeight, testComp.getFrameRect().height);
  BOOST_CHECK_EQUAL(fstWidth, testComp.getFrameRect().width);
  BOOST_CHECK_EQUAL(fstArea, testComp.getArea());
}

BOOST_AUTO_TEST_CASE(moveByDxAndDy)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  double fstHeight = testComp.getFrameRect().height;
  double fstWidth = testComp.getFrameRect().width;
  double fstArea = testComp.getArea();
  marchenko::point_t positionAfterMoving = {testComp.getFrameRect().pos.x + 3.0,testComp.getFrameRect().pos.y + 5.0};
  testComp.move(3.0,5.0);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.x, positionAfterMoving.x, EPSILON);
  BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.y, positionAfterMoving.y, EPSILON);
  BOOST_CHECK_EQUAL(fstHeight, testComp.getFrameRect().height);
  BOOST_CHECK_EQUAL(fstWidth, testComp.getFrameRect().width);
  BOOST_CHECK_EQUAL(fstArea, testComp.getArea());
}

BOOST_AUTO_TEST_CASE(scaling)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  double fstPosX = testComp.getFrameRect().pos.x;
  double fstPosY = testComp.getFrameRect().pos.y;
  marchenko::point_t fstPosRect =  ptr1 ->getFrameRect().pos;
  marchenko::point_t fstPosCircle = ptr2 ->getFrameRect().pos;
  double fstHeight = testComp.getFrameRect().height;
  double fstWidth = testComp.getFrameRect().width;
  double fstArea = testComp.getArea();
  testComp.scale(2.0);
  BOOST_CHECK_CLOSE(2.0 * 2.0 * fstArea, testComp.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(2.0 * fstHeight, testComp.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(2.0 * fstWidth, testComp.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(fstPosX, testComp.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(fstPosY, testComp.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE(fstPosRect.x + (2.0-1.0) * (fstPosRect.x - fstPosX ) , ptr1 ->getFrameRect().pos.x , EPSILON);
  BOOST_CHECK_CLOSE(fstPosRect.y + (2.0-1.0) * (fstPosRect.y - fstPosY ) , ptr1 ->getFrameRect().pos.y , EPSILON);
  BOOST_CHECK_CLOSE(fstPosCircle.x + (2.0-1.0) * (fstPosCircle.x - fstPosX ) , ptr2 ->getFrameRect().pos.x , EPSILON);
  BOOST_CHECK_CLOSE(fstPosCircle.y + (2.0-1.0) * (fstPosCircle.y - fstPosY ) , ptr2 ->getFrameRect().pos.y , EPSILON);
}

BOOST_AUTO_TEST_CASE(invalidScaling)
{
  std::shared_ptr< marchenko::Shape > ptr1(new marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr< marchenko::Shape > ptr2(new marchenko::Circle({3.0, 2.5}, 105));
  marchenko::CompositeShape testComp;
  testComp.addShape(ptr1);
  testComp.addShape(ptr2);
  BOOST_CHECK_THROW(testComp.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
