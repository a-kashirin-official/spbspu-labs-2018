#define BOOST_TEST_MODULE A2_Test
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(TestCircle)
  BOOST_AUTO_TEST_CASE(ConstantParametersAfterMoveToPoint)
  {
    ivanov::Circle testCir({3.0,4.0},5.0);
    testCir.move({6.0,7.0});
    BOOST_CHECK_EQUAL(testCir.getFrameRect().width,10.0);
    BOOST_CHECK_EQUAL(testCir.getFrameRect().height,10.0);
    BOOST_CHECK_CLOSE(testCir.getArea(),M_PI*5.0*5.0,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(ConstantParametersAfterMoveOnDXandDY)
  {
    ivanov::Circle testCir({3.0,4.0},5.0);
    testCir.move(8.0,9.0);
    BOOST_CHECK_EQUAL(testCir.getFrameRect().width,10.0);
    BOOST_CHECK_EQUAL(testCir.getFrameRect().height,10.0);
    BOOST_CHECK_CLOSE(testCir.getArea(),M_PI*5.0*5.0,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(AreaAfterScale)
  {
    ivanov::Circle testCir({3.0,4.0},5.0);
    testCir.scale(10.0);
    BOOST_CHECK_CLOSE(testCir.getArea(),10.0*10.0*M_PI*5.0*5.0,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(InvalidParametersInConstructor)
  {
    BOOST_CHECK_THROW(ivanov::Circle testCir({3.0,4.0},-6.0),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InvalidParametersInScale)
  {
    ivanov::Circle testCir({3.0,4.0},5.0);
    BOOST_CHECK_THROW(testCir.scale(-9.0),std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestRectangle)
  BOOST_AUTO_TEST_CASE(ConstantParametersAfterMoveToPoint)
  {
    ivanov::Rectangle testRec({3.0,4.0},5.0,6.0);
    testRec.move({6.0,7.0});
    BOOST_CHECK_EQUAL(testRec.getFrameRect().width,5.0);
    BOOST_CHECK_EQUAL(testRec.getFrameRect().height,6.0);
    BOOST_CHECK_EQUAL(testRec.getArea(),5.0*6.0);
  }
  BOOST_AUTO_TEST_CASE(ConstantParametersAfterMoveOnDXandDY)
  {
    ivanov::Rectangle testRec({3.0,4.0},5.0,6.0);
    testRec.move(8.0,9.0);
    BOOST_CHECK_EQUAL(testRec.getFrameRect().width,5.0);
    BOOST_CHECK_EQUAL(testRec.getFrameRect().height,6.0);
    BOOST_CHECK_EQUAL(testRec.getArea(),5.0*6.0);
  }
  BOOST_AUTO_TEST_CASE(AreaAfterScale)
  {
    ivanov::Rectangle testRec({3.0,4.0},5.0,6.0);
    testRec.scale(4.5);
    BOOST_CHECK_EQUAL(testRec.getArea(),4.5*4.5*5.0*6.0);
  }
  BOOST_AUTO_TEST_CASE(InvalidParametersInConstructor)
  {
    BOOST_CHECK_THROW(ivanov::Rectangle testRec({3.0,4.0},-6.0,9.0),std::invalid_argument);
    BOOST_CHECK_THROW(ivanov::Rectangle testRec({3.0,4.0},6.0,-9.0),std::invalid_argument);
    BOOST_CHECK_THROW(ivanov::Rectangle testRec({3.0,4.0},-6.0,-9.0),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InvalidParametersInScale)
  {
    ivanov::Rectangle testRec({3.0,4.0},5.0,6.0);
    BOOST_CHECK_THROW(testRec.scale(-9.0),std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestTriangle)
  BOOST_AUTO_TEST_CASE(ConstantParametersAfterMoveToPoint)
  {
    ivanov::Triangle testTri({1.0,3.0},{4.0,1.0},{6.0,4.0});
    double initialWidth = testTri.getFrameRect().width;
    double initialHeight = testTri.getFrameRect().height;
    double initialArea = testTri.getArea();
    testTri.move({6.0,7.0});
    BOOST_CHECK_CLOSE(testTri.getFrameRect().width,initialWidth,EPSILON);
    BOOST_CHECK_CLOSE(testTri.getFrameRect().height,initialHeight,EPSILON);
    BOOST_CHECK_CLOSE(testTri.getArea(),initialArea,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(ConstantParametersAfterMoveOnDXandDY)
  {
    ivanov::Triangle testTri({1.0,3.0},{4.0,1.0},{6.0,4.0});
    double initialWidth = testTri.getFrameRect().width;
    double initialHeight = testTri.getFrameRect().height;
    double initialArea = testTri.getArea();
    testTri.move(8.0,7.0);
    BOOST_CHECK_CLOSE(testTri.getFrameRect().width,initialWidth,EPSILON);
    BOOST_CHECK_CLOSE(testTri.getFrameRect().height,initialHeight,EPSILON);
    BOOST_CHECK_CLOSE(testTri.getArea(),initialArea,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(AreaAfterScale)
  {
    ivanov::Triangle testTri({1.0,3.0},{4.0,1.0},{6.0,4.0});
    double initialArea = testTri.getArea();
    testTri.scale(6.0);
    BOOST_CHECK_EQUAL(testTri.getArea(),6.0*6.0*initialArea);
  }
  BOOST_AUTO_TEST_CASE(InvalidParametersInScale)
  {
    ivanov::Triangle testTri({1.0,3.0},{4.0,1.0},{6.0,4.0});
    BOOST_CHECK_THROW(testTri.scale(-9.0),std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
