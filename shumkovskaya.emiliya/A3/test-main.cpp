#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>  
#include <stdexcept>
#include <cmath>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace shumkovskaya;

const double DELTA = 0.000001;

BOOST_AUTO_TEST_SUITE(TestsForCompositeShape)

  BOOST_AUTO_TEST_CASE(CreateCompositeShape_invalid_argument)
  {
    BOOST_CHECK_THROW(CompositeShape compositeshape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Copy_constructor)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape1(rectPtr);
    compositeshape1.addShape(circPtr);
    CompositeShape compositeshape2(compositeshape1);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, compositeshape2.getFrameRect().width, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, compositeshape2.getFrameRect().height, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, compositeshape2.getFrameRect().pos.x, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, compositeshape2.getFrameRect().pos.y, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getArea(), compositeshape2.getArea(), DELTA);
  }

  BOOST_AUTO_TEST_CASE(Copy)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape1(rectPtr);
    compositeshape1.addShape(circPtr);
    CompositeShape compositeshape2(rectPtr);
    compositeshape2 = compositeshape1;
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, compositeshape2.getFrameRect().width, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, compositeshape2.getFrameRect().height, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, compositeshape2.getFrameRect().pos.x, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, compositeshape2.getFrameRect().pos.y, DELTA);
    BOOST_CHECK_CLOSE(compositeshape1.getArea(), compositeshape2.getArea(), DELTA);
  }

  BOOST_AUTO_TEST_CASE(MoveTo)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    double initialValueArea = compositeshape.getArea();
    compositeshape.move({60, 60});
    BOOST_CHECK_CLOSE(initialValueRect.width, compositeshape.getFrameRect().width, DELTA);
    BOOST_CHECK_CLOSE(initialValueRect.height, compositeshape.getFrameRect().height, DELTA);
    BOOST_CHECK_CLOSE(initialValueArea, compositeshape.getArea(), DELTA);
    compositeshape.removeAll();
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    double initialValueArea = compositeshape.getArea();
    rect.move(30, 20);
    BOOST_CHECK_CLOSE(initialValueRect.width, compositeshape.getFrameRect().width, DELTA);
    BOOST_CHECK_CLOSE(initialValueRect.height, compositeshape.getFrameRect().height, DELTA);
    BOOST_CHECK_CLOSE(initialValueArea, compositeshape.getArea(), DELTA);
    compositeshape.removeAll();
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE(compositeshape.getArea(), rect.getArea() * 2 * 2 + circ.getArea() * 2 * 2, DELTA);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE(initialValueRect.pos.x, compositeshape.getFrameRect().pos.x, DELTA);
    BOOST_CHECK_CLOSE(initialValueRect.pos.y, compositeshape.getFrameRect().pos.y, DELTA);
    BOOST_CHECK_CLOSE(initialValueRect.width * 2, compositeshape.getFrameRect().width, DELTA);
    BOOST_CHECK_CLOSE(initialValueRect.height * 2, compositeshape.getFrameRect().height, DELTA);
  }

  BOOST_AUTO_TEST_CASE(addShape)
  {
   Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    BOOST_CHECK_EQUAL(compositeshape.getAmount(), 1);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_EQUAL(compositeshape.getAmount(), 2);
  }

  BOOST_AUTO_TEST_CASE(deleteShape)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.removeShape(1);
    BOOST_CHECK_EQUAL(compositeshape.getAmount(), 1);
  }

  BOOST_AUTO_TEST_CASE(clear)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.removeAll();
    BOOST_CHECK_EQUAL(compositeshape.getAmount(), 0);
  }

  BOOST_AUTO_TEST_CASE(addShape_invalid_argument)
  {
    Rectangle rect(50, 10, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    CompositeShape compositeshape(rectPtr);
    BOOST_CHECK_THROW(compositeshape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteShape_invalid_index)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_THROW(compositeshape.removeShape(2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteShape_empty_array)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.removeAll();
    BOOST_CHECK_THROW(compositeshape.removeShape(1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scale_invalid_argument)
  {
    Rectangle rect(50, 10, {0, 0});
    Circle circ(50, {0, 0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_THROW(compositeshape.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
