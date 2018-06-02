#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace volohov;

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_SUITE(TestsForCompositeShape)

  BOOST_AUTO_TEST_CASE(CreateCompositeShape_invalid_argument)
  {
    BOOST_CHECK_THROW(CompositeShape compositeshape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Copy_constructor)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape1(rectanglePtr);
    compositeshape1.addShape(circlePtr);
    CompositeShape compositeshape2(compositeshape1);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, compositeshape2.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, compositeshape2.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, compositeshape2.getFrameRect().pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, compositeshape2.getFrameRect().pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getArea(), compositeshape2.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Copy)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape1(rectanglePtr);
    compositeshape1.addShape(circlePtr);
    CompositeShape compositeshape2(rectanglePtr);
    compositeshape2 = compositeshape1;
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, compositeshape2.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, compositeshape2.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, compositeshape2.getFrameRect().pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, compositeshape2.getFrameRect().pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape1.getArea(), compositeshape2.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(MoveTo)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    double initialValueArea = compositeshape.getArea();
    compositeshape.move({5.0, 5.0});
    BOOST_CHECK_CLOSE(initialValueRect.width, compositeshape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(initialValueRect.height, compositeshape.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(initialValueArea, compositeshape.getArea(), ACCURACY);
    compositeshape.removeAll();
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    double initialValueArea = compositeshape.getArea();
    rectangle.move(10.0, 10.0);
    BOOST_CHECK_CLOSE(initialValueRect.width, compositeshape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(initialValueRect.height, compositeshape.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(initialValueArea, compositeshape.getArea(), ACCURACY);
    compositeshape.removeAll();
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    compositeshape.scale(2.0);
    BOOST_CHECK_CLOSE(compositeshape.getArea(), rectangle.getArea() * 2 * 2 + circle.getArea() * 2 * 2, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rectangle( {1.1, 2.2} , 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE(initialValueRect.pos.x, compositeshape.getFrameRect().pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(initialValueRect.pos.y, compositeshape.getFrameRect().pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(initialValueRect.width * 2, compositeshape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(initialValueRect.height * 2, compositeshape.getFrameRect().height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(addShape)
  {
   Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    BOOST_CHECK_EQUAL(compositeshape.getCount(), 1);
    compositeshape.addShape(circlePtr);
    BOOST_CHECK_EQUAL(compositeshape.getCount(), 2);
  }

  BOOST_AUTO_TEST_CASE(removeShape)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    compositeshape.removeShape(1);
    BOOST_CHECK_EQUAL(compositeshape.getCount(), 1);
  }

  BOOST_AUTO_TEST_CASE(clear)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    compositeshape.removeAll();
    BOOST_CHECK_EQUAL(compositeshape.getCount(), 0);
  }

  BOOST_AUTO_TEST_CASE(addShape_invalid_argument)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    CompositeShape compositeshape(rectanglePtr);
    BOOST_CHECK_THROW(compositeshape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(removeShape_invalid_index)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    BOOST_CHECK_THROW(compositeshape.removeShape(2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(removeShape_empty_array)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    compositeshape.removeAll();
    BOOST_CHECK_THROW(compositeshape.removeShape(1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scale_invalid_argument)
  {
    Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
    Circle circle({1.0, 2.0}, 3.0);
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.addShape(circlePtr);
    BOOST_CHECK_THROW(compositeshape.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
