#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
using namespace kulikov;

const double EPSILON = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(RectangleMoving)
  {
    Rectangle rect{ {{5.0, 7.0}, 10.0, 3.0} };
    double areaBeforeMoving = rect.getArea();
    rectangle_t objectBeforeMoving = rect.getFrameRect();
    rect.move(17.0, 12.0);
    BOOST_CHECK_EQUAL(areaBeforeMoving, rect.getArea());
    BOOST_CHECK_EQUAL(objectBeforeMoving.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(objectBeforeMoving.height, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(QvadroAreaDiff)
  {
    Rectangle rect{ {{10.0, 7.0}, 5.0, 2.0} };
    double areaBeforeScaling = rect.getArea();
    double koefficient = 5.5;
    rect.scale(koefficient);
    double result = koefficient * koefficient * areaBeforeScaling;
    BOOST_CHECK_CLOSE(result, rect.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW((Rectangle{ {{10.0, 7.0}, -4.0, 3.0} }), std::invalid_argument);
    BOOST_CHECK_THROW((Rectangle{ {{10.0, 7.0}, 4.0, -3.0} }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleKoeff)
  {
    Rectangle rect{ {{5.0, 7.0}, 10.0, 3.0} };
    double koefficient = -2.0;
    BOOST_CHECK_THROW(rect.scale(koefficient), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(ImmutabilityCharacteristicsOfObject)
  {
    Circle circ{ {1.0, 2.0}, 5.0 };
    double areaBeforeMoving = circ.getArea();
    rectangle_t squareBeforeMoving = circ.getFrameRect();
    point_t movement = {10.0, 5.0};
    circ.move(movement);
    BOOST_CHECK_EQUAL(areaBeforeMoving, circ.getArea());
    BOOST_CHECK_EQUAL(squareBeforeMoving.height, circ.getFrameRect().height);
    BOOST_CHECK_EQUAL(squareBeforeMoving.width, circ.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(QvadroAreaDifference)
  {
    Circle circ{ {1.0, 2.0}, 5.0 };
    double areaBeforeScaling = circ.getArea();
    double koefficient = 3.5;
    circ.scale(koefficient);
    double result = koefficient * koefficient * areaBeforeScaling;
    BOOST_CHECK_CLOSE(result, circ.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParams)
  {
    BOOST_CHECK_THROW((Circle{ {1.0, 2.0}, -100.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(NegativeScaling)
  {
    Circle circ{ {1.0, 2.0}, 5.0 };
    BOOST_CHECK_THROW(circ.scale(-4.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructorParams)
  {
    BOOST_CHECK_THROW(CompositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    Rectangle rect{ {{0.0, 0.0}, 50.0, 10.0} };
    Circle circ({0.0, 0.0}, 50.0);
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
    Rectangle rect{{ {0.0, 0.0}, 50.0, 10.0} };
    Circle circ({0.0, 0.0}, 50.0);
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
    Rectangle rect{{ {0.0, 0.0}, 50.0, 10.0} };
    Circle circ({0.0, 0.0}, 50.0);
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
    Rectangle rect{{ {0.0, 0.0}, 50.0, 10.0}};
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    rectangle_t initialValueRect = compositeshape.getFrameRect();
    double initialValueArea = compositeshape.getArea();
    rect.move(30.0, 20.0);
    BOOST_CHECK_CLOSE(initialValueRect.width, compositeshape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(initialValueRect.height, compositeshape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(initialValueArea, compositeshape.getArea(), EPSILON);
    compositeshape.clear();
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE(compositeshape.getArea(), rect.getArea() * 2 * 2 + circ.getArea() * 2 * 2, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
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
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 1);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 2);
  }

  BOOST_AUTO_TEST_CASE(deleteShape)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.deleteShape(1);
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 1);
  }

  BOOST_AUTO_TEST_CASE(clear)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.clear();
    BOOST_CHECK_EQUAL(compositeshape.getCounter(), 0);
  }

  BOOST_AUTO_TEST_CASE(addShape_invalid_argument)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    CompositeShape compositeshape(rectPtr);
    BOOST_CHECK_THROW(compositeshape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteShape_invalid_index)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_THROW(compositeshape.deleteShape(2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteShape_empty_array)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    compositeshape.clear();
    BOOST_CHECK_THROW(compositeshape.deleteShape(1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(scale_invalid_argument)
  {
    Rectangle rect({ {0.0, 0.0}, 50.0, 10.0});
    Circle circ({0.0, 0.0}, 50.0);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);
    compositeshape.addShape(circPtr);
    BOOST_CHECK_THROW(compositeshape.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
