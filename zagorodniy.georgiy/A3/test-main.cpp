#define BOOST_TEST_MODULE main
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

BOOST_AUTO_TEST_SUITE(MovingToPointTests)

BOOST_AUTO_TEST_CASE(testRectangleInMovingToPoint)
  {
    zagorodniy::Rectangle myRectangle({5.0, 6.0}, 7.0, 8.0);
  zagorodniy::rectangle_t rectangleOne = myRectangle.getFrameRect();
  double areaOne = myRectangle.getArea();

  myRectangle.move({1.0,2.5});

  BOOST_CHECK_EQUAL(areaOne, myRectangle.getArea());
  BOOST_CHECK_EQUAL(rectangleOne.width, myRectangle.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectangleOne.height, myRectangle.getFrameRect().height);
  }

BOOST_AUTO_TEST_CASE(testCircleInMovingToPoint)
  {
    zagorodniy::Circle myCircle({10.0, 11.0}, 9.0);
  zagorodniy::rectangle_t circleOne = myCircle.getFrameRect();
  double areaOne = myCircle.getArea();

  myCircle.move({1.0,2.5});

  BOOST_CHECK_EQUAL(areaOne, myCircle.getArea());
  BOOST_CHECK_EQUAL(circleOne.width, myCircle.getFrameRect().width);
  BOOST_CHECK_EQUAL(circleOne.height, myCircle.getFrameRect().height);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MovingTests)

BOOST_AUTO_TEST_CASE(testRectangleInMoving)
  {
    zagorodniy::Rectangle myRectangle({5.0, 6.0}, 7.0, 8.0);
  zagorodniy::rectangle_t rectangleOne = myRectangle.getFrameRect();
  double areaOne = myRectangle.getArea();

  myRectangle.move(3.5,4.3);

  BOOST_CHECK_EQUAL(areaOne, myRectangle.getArea());
  BOOST_CHECK_EQUAL(rectangleOne.width, myRectangle.getFrameRect().width);
  BOOST_CHECK_EQUAL(rectangleOne.height, myRectangle.getFrameRect().height);
  }

BOOST_AUTO_TEST_CASE(testCircleInMoving)
  {
    zagorodniy::Circle myCircle({10.0, 11.0}, 9.0);
  zagorodniy::rectangle_t circleOne = myCircle.getFrameRect();
  double areaOne = myCircle.getArea();

  myCircle.move(3.5,4.3);

  BOOST_CHECK_EQUAL(areaOne, myCircle.getArea());
  BOOST_CHECK_EQUAL(circleOne.width, myCircle.getFrameRect().width);
  BOOST_CHECK_EQUAL(circleOne.height, myCircle.getFrameRect().height);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ScalingTests)

BOOST_AUTO_TEST_CASE(testRectangleInScaling)
  {
    zagorodniy::Rectangle myRectangle({5.0, 6.0}, 7.0, 8.0);
  double areaOne = myRectangle.getArea();

  myRectangle.scale(2.0);

  BOOST_CHECK_CLOSE(2.0 * 2.0 * areaOne, myRectangle.getArea(), 0.001);
  }

BOOST_AUTO_TEST_CASE(testCircleInScaling)
  {
    zagorodniy::Circle myCircle({10.0, 11.0}, 9.0);
  double areaOne = myCircle.getArea();

  myCircle.scale(2.0);

  BOOST_CHECK_CLOSE(2.0 * 2.0 * areaOne, myCircle.getArea(), 0.001);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ParametersTests)

BOOST_AUTO_TEST_CASE(testRectangleParameters)
  {
    BOOST_CHECK_THROW( zagorodniy::Rectangle({5.0, 6.0}, 7.0, -8.0), std::invalid_argument );
  BOOST_CHECK_THROW( zagorodniy::Rectangle({5.0, 6.0}, -7.0, 8.0), std::invalid_argument );
  BOOST_CHECK_THROW( zagorodniy::Rectangle({5.0, 6.0}, -7.0, -8.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_CASE(testCircleParameters)
  {
    BOOST_CHECK_THROW( zagorodniy::Circle({10.0, 11.0}, -9.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IncreaseCoefficientTests)

BOOST_AUTO_TEST_CASE(testIncreaseCoefficientInRectangle)
  {
    zagorodniy::Rectangle myRectangle({5.0, 6.0}, 7.0, 8.0);
  BOOST_CHECK_THROW( myRectangle.scale(-2.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_CASE(testIncreaseCoefficientInCircle)
  {
    zagorodniy::Circle myCircle({10.0, 11.0}, 9.0);
  BOOST_CHECK_THROW( myCircle.scale(-2.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  zagorodniy::Circle myCircle({10.0, 11.0}, 5.0);
  zagorodniy::Rectangle myRectangle({5.0, 6.0}, 7.0, 8.0);
  std::shared_ptr< zagorodniy::Shape > circlePtr = std::make_shared< zagorodniy::Circle >(myCircle);
  std::shared_ptr< zagorodniy::Shape > rectanglePtr = std::make_shared< zagorodniy::Rectangle >
    (myRectangle);

  BOOST_AUTO_TEST_CASE(testConstructorAndAdding)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    BOOST_CHECK_EQUAL(myCS.getCount(), 2);
  }

  BOOST_AUTO_TEST_CASE(wrongConstructorParameter)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    BOOST_CHECK_THROW(zagorodniy::CompositeShape myCS(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(areaTest)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    BOOST_CHECK_CLOSE(myCS.getArea(), myRectangle.getArea() + myCircle.getArea(), 0.001);
  }

  BOOST_AUTO_TEST_CASE(frameRectTest)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.x, 8.25);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.y, 9.0);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().width, 13.5);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().height, 14.0);
  }

  BOOST_AUTO_TEST_CASE(moveFor)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    zagorodniy::rectangle_t rectangleOne = myCS.getFrameRect();
    myCS.move(4.5, 5.5);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.x, rectangleOne.pos.x + 4.5);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.y, rectangleOne.pos.y + 5.5);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().width, rectangleOne.width);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().height, rectangleOne.height);
  }

  BOOST_AUTO_TEST_CASE(moveTo)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    zagorodniy::rectangle_t rectangleOne = myCS.getFrameRect();
    myCS.move({2.0, 3.0});
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().width, rectangleOne.width);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().height, rectangleOne.height);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    zagorodniy::rectangle_t rectangleOne = myCS.getFrameRect();
    myCS.scale(2.0);
    myCS.getFrameRect();
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.x, rectangleOne.pos.x);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().pos.y, rectangleOne.pos.y);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().width, rectangleOne.width * 2.0);
    BOOST_CHECK_EQUAL(myCS.getFrameRect().height, rectangleOne.height * 2.0);
  }

  BOOST_AUTO_TEST_CASE(negativeScaleParameters)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    BOOST_CHECK_THROW(myCS.scale(-2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(removeShape)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    myCS.removeShape(1);
    BOOST_CHECK_EQUAL(myCS.getCount(), 1);
  }

  BOOST_AUTO_TEST_CASE(removeBiggerShape)
  {
    zagorodniy::CompositeShape myCS(circlePtr);
    myCS.addShape(rectanglePtr);
    BOOST_CHECK_THROW(myCS.removeShape(8), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
