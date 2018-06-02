#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(TestCompositeShape)

  BOOST_AUTO_TEST_CASE(InvalidPointeerCompositeShape)
  {
    BOOST_CHECK_THROW(grigorev::CompositeShape comp(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidAddingCompositeShape)
  {
    grigorev::Rectangle rectangle({3.0, 3.0}, 5.0, 6.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    grigorev::CompositeShape comp(rectanglePtr);
    BOOST_CHECK_THROW(comp.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidIndexOfCompositeShape)
  {
    grigorev::Rectangle rectangle({3.0, 3.0}, 5.0, 6.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    grigorev::CompositeShape comp(rectanglePtr);
    BOOST_CHECK_THROW(comp[5], std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidCompositeShapeScale)
  {
    grigorev::Rectangle rectangle({3.0, 3.0}, 5.0, 6.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    grigorev::CompositeShape comp(rectanglePtr);
    BOOST_CHECK_THROW(comp.scale(-5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidShapeNumberRemove)
  {
    grigorev::Rectangle rectangle({3.0, 3.0}, 5.0, 6.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    grigorev::CompositeShape comp(rectanglePtr);
    BOOST_CHECK_THROW(comp.removeShape(2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestEmptyCompositeShape)
  {
    grigorev::CompositeShape comp;
    BOOST_REQUIRE_EQUAL(comp.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeParametrsAfterMovingToPoint)
  {
    grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
    grigorev::Circle circle({5.0, 5.0}, 3.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);
    grigorev::CompositeShape comp(rectanglePtr);
    comp.addShape(circlePtr);
    comp.move({3.0, 3.0});
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, 9.5 , EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, 10.0 , EPSILON);
    BOOST_CHECK_CLOSE(comp.getArea(), 58.274 , EPSILON);
    BOOST_REQUIRE_EQUAL(comp.getSize(), 2);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeParametrsAfterMovingDxDy)
  {
    grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
    grigorev::Circle circle({5.0, 5.0}, 3.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);
    grigorev::CompositeShape comp(rectanglePtr);
    comp.addShape(circlePtr);
    comp.move(4.0, 4.0);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, 9.5 , EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, 10.0 , EPSILON);
    BOOST_CHECK_CLOSE(comp.getArea(), 58.274 , EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeParametrsAfterScaling)
  {
    grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
    grigorev::Circle circle({5.0, 5.0}, 3.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);
    grigorev::CompositeShape comp(rectanglePtr);
    comp.addShape(circlePtr);
    comp.scale(2.0);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, 19.0 , EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, 20.0 , EPSILON);
    BOOST_CHECK_CLOSE(comp.getArea(), 233.097 , EPSILON);
  }

  BOOST_AUTO_TEST_CASE(TestRemoveShape)
  {
    grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
    grigorev::Circle circle({5.0, 5.0}, 3.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);
    grigorev::CompositeShape comp(rectanglePtr);
    comp.addShape(circlePtr);
    comp.removeShape(2);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
    BOOST_REQUIRE_EQUAL(comp.getArea(), rectangle.getArea());
    BOOST_REQUIRE_EQUAL(comp.getSize(), 1);
  }

  BOOST_AUTO_TEST_CASE(TestDeleteShapes)
  {
    grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
    grigorev::Circle circle({5.0, 5.0}, 3.0);
    std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
    std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);
    grigorev::CompositeShape comp(rectanglePtr);
    comp.addShape(circlePtr);
    comp.deleteShapes();
    BOOST_REQUIRE_EQUAL(comp.getSize(), 0);
  }

BOOST_AUTO_TEST_SUITE_END()
