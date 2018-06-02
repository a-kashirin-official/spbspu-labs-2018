#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 0.001;

using namespace semakina;

BOOST_AUTO_TEST_SUITE(TestsForRectangle)

  BOOST_AUTO_TEST_CASE(MoveTo)
  {
    Rectangle rect({0, 0}, 50, 10);
    rectangle_t initialValueRect = rect.getFrameRect();
    double initialValueArea = rect.getArea();
    rect.move({60, 60});
    BOOST_CHECK_EQUAL(initialValueRect.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    Rectangle rect({0, 0}, 50, 10);
    rectangle_t initialValueRect = rect.getFrameRect();
    double initialValueArea = rect.getArea();
    rect.move(30, 20);
    BOOST_CHECK_EQUAL(initialValueRect.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, rect.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Rectangle rect({0, 0}, 50, 10);
    double initialValueArea = rect.getArea();
    double coefficient = 2;
    rect.scale(coefficient);
    BOOST_CHECK_CLOSE(initialValueArea * coefficient * coefficient, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Parameters)
  {
    BOOST_CHECK_THROW(Rectangle({0, 0}, -50, -10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Rectangle rect({0, 0}, 50, 10);
    BOOST_CHECK_THROW(rect.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestsForCircle)

  BOOST_AUTO_TEST_CASE(MoveTo)
  {
    Circle circ({0, 0}, 50);
    rectangle_t initialValueRect = circ.getFrameRect();
    double initialValueArea = circ.getArea();
    circ.move({60, 60});
    BOOST_CHECK_EQUAL(initialValueRect.width, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, circ.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, circ.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    Circle circ({0, 0}, 50);
    rectangle_t initialValueRect = circ.getFrameRect();
    double initialValueArea = circ.getArea();
    circ.move(30, 20);
    BOOST_CHECK_EQUAL(initialValueRect.width, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(initialValueRect.height, circ.getFrameRect().height);
    BOOST_CHECK_EQUAL(initialValueArea, circ.getArea());
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Circle circ({0, 0}, 50);
    double initialValueArea = circ.getArea();
    double coefficient = 2;
    circ.scale(coefficient);
    BOOST_CHECK_CLOSE(initialValueArea * coefficient * coefficient, circ.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Parameters)
  {
    BOOST_CHECK_THROW(Circle({0,0}, -50), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Circle circ({0,0}, 50);
    BOOST_CHECK_THROW(circ.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(TestsForCompositeShape)

  BOOST_AUTO_TEST_CASE(CreateCompositeShape_invalid_argument)
  {
    BOOST_CHECK_THROW(CompositeShape compositeshape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Copy_constructor)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape1(rectPtr);
    compositeshape1.addShape(circPtr);
    CompositeShape compositeshape2(compositeshape1);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, compositeshape2.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, compositeshape2.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, compositeshape2.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, compositeshape2.getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getArea(), compositeshape2.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Copy)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape1(rectPtr);
    compositeshape1.addShape(circPtr);
    CompositeShape compositeshape2(rectPtr);
    compositeshape2 = compositeshape1;
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, compositeshape2.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, compositeshape2.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, compositeshape2.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, compositeshape2.getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(compositeshape1.getArea(), compositeshape2.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveTo)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    double initialValueArea = compositeshape.getArea();
    compositeshape.move({60, 60});
    BOOST_CHECK_CLOSE(initialValueRect.width, compositeshape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initialValueRect.height, compositeshape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initialValueArea, compositeshape.getArea(), EPSILON);
    compositeshape.clear();
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    double initialValueArea = compositeshape.getArea();
    rect.move(30, 20);
    BOOST_CHECK_CLOSE(initialValueRect.width, compositeshape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initialValueRect.height, compositeshape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initialValueArea, compositeshape.getArea(), EPSILON);
    compositeshape.clear();
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE(compositeshape.getArea(), rect.getArea() * 2 * 2 + circ.getArea() * 2 * 2, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE(initialValueRect.pos.x, compositeshape.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(initialValueRect.pos.y, compositeshape.getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(initialValueRect.width * 2, compositeshape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initialValueRect.height * 2, compositeshape.getFrameRect().height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(addShape)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 1);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 2);
  }

  BOOST_AUTO_TEST_CASE(deleteShape)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.deleteShape(1);
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 1);
  }

  BOOST_AUTO_TEST_CASE(clear)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.clear();
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 0);
  }

  BOOST_AUTO_TEST_CASE(addShape_invalid_argument)
  {
    Rectangle rect({0, 0}, 50, 10);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    CompositeShape compositeshape(rectPtr);
    BOOST_CHECK_THROW(compositeshape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteShape_invalid_index)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_THROW(compositeshape.deleteShape(2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteShape_empty_array)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.clear();
    BOOST_CHECK_THROW(compositeshape.deleteShape(1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(scale_invalid_argument)
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_THROW(compositeshape.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
