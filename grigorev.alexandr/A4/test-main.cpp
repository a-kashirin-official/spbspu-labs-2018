#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <memory>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(TestRotating)

  BOOST_AUTO_TEST_CASE(RectangleRotate)
  {
    grigorev::Rectangle rectangle({3.0, 3.0}, 5.0, 6.0);
    rectangle.rotate(90);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 6.0 , EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 5.0 , EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRotate)
  {
    grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
    grigorev::Circle circle({5.0, 5.0}, 3.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);
    grigorev::CompositeShape comp(rectanglePtr);
    comp.addShape(circlePtr);
    comp.rotate(90);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, 10.0 , EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, 9.5 , EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestMatrix)

  BOOST_AUTO_TEST_CASE(TestingLayersMatrix)
  {
    grigorev::Rectangle rectangle1({3.0, 2.0}, 10.0, 10.0);
    grigorev::Rectangle rectangle2({4.0, 3.0}, 5.0, 6.0);
    grigorev::Circle circle1({50.0, 50.0}, 3.0);

    std::shared_ptr< grigorev::Shape > rectanglePtr1 = std::make_shared< grigorev::Rectangle >(rectangle1);
    std::shared_ptr< grigorev::Shape > rectanglePtr2 = std::make_shared< grigorev::Rectangle >(rectangle2);
    std::shared_ptr< grigorev::Shape > circlePtr1 = std::make_shared< grigorev::Circle >(circle1);

    grigorev::Matrix matrix(rectanglePtr1);
    matrix.addShape(rectanglePtr2);
    matrix.addShape(circlePtr1);

    std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< grigorev::Shape >[] > layer2 = matrix[1];

    BOOST_CHECK_CLOSE(layer1[0]->getFrameRect().pos.x, 3.0 , EPSILON);
    BOOST_CHECK_CLOSE(layer1[0]->getFrameRect().pos.y, 2.0 , EPSILON);
    BOOST_CHECK_CLOSE(layer1[1]->getFrameRect().pos.x, 50.0 , EPSILON);
    BOOST_CHECK_CLOSE(layer1[1]->getFrameRect().pos.y, 50.0 , EPSILON);
    BOOST_CHECK_CLOSE(layer2[0]->getFrameRect().pos.x, 4.0 , EPSILON);
    BOOST_CHECK_CLOSE(layer2[0]->getFrameRect().pos.y, 3.0 , EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
