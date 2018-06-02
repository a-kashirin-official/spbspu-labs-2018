#define BOOST_TEST_MAIN
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"


using namespace reznik;
const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(2, 2, { 0,0 }));
    reznik::CompositeShape Comp1;
    Comp1.addShape(rect1);
    Comp1.addShape(rect2);
    rectangle_t frame = Comp1.getFrameRect();
    CompositeShape Comp2;
    Comp2= std::move(Comp1);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().pos.x, frame.pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().pos.y, frame.pos.y, EPSILON);
  }


  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp1;
    Comp1.addShape(rect1);
    Comp1.addShape(rect2);
    rectangle_t frame = Comp1.getFrameRect();
    CompositeShape Comp2(std::move(Comp1));
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().pos.x, frame.pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().pos.y, frame.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp1;
    Comp1.addShape(rect1);
    Comp1.addShape(rect2);
    rectangle_t frame = Comp1.getFrameRect();
    CompositeShape Comp2(Comp1);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().pos.x, frame.pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getFrameRect().pos.y, frame.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CorrectCopyOperator)
  {
    std::shared_ptr<Shape> rect = std::make_shared<reznik::Rectangle>(reznik::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> rect1 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(1,1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<reznik::Rectangle>(reznik::Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp1;
    Comp1.addShape(rect);
    Comp1.addShape(rect1);
    CompositeShape Comp2;
    Comp2.addShape(rect);
    Comp2.addShape(rect2);
    Comp1 = Comp2;
    BOOST_CHECK_CLOSE_FRACTION(Comp2.getArea(), Comp1.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MOVEINPOINT)
  {
    std::shared_ptr<Shape> rect = std::make_shared<reznik::Rectangle>(reznik::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(5, { 0,0 }));
    CompositeShape Composite;
    Composite.addShape(rect);
    Composite.addShape(circ);
    double height = Composite.getFrameRect().height;
    double width = Composite.getFrameRect().width;
    double area = Composite.getArea();
    Composite.move(2, 2);
    BOOST_CHECK_CLOSE_FRACTION(Composite.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Composite.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Composite.getArea(), area, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MOVE)
  {
    std::shared_ptr<Shape> rect = std::make_shared<reznik::Rectangle>(reznik::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<reznik::Circle>(reznik::Circle(5, { 0,0 }));
    CompositeShape Composite;
    Composite.addShape(rect);
    Composite.addShape(circ);
    double height = Composite.getFrameRect().height;
    double width = Composite.getFrameRect().width;
    double area = Composite.getArea();
    Composite.move({ 2, 2 });
    BOOST_CHECK_CLOSE_FRACTION(Composite.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Composite.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Composite.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Composite.getFrameRect().pos.x, 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Composite.getFrameRect().pos.y, 2, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Correct_scale)
  {
    std::shared_ptr<Shape> rect = std::make_shared<reznik::Rectangle>(reznik::Rectangle(20, 20, { 10,30 }));
    std::shared_ptr<Shape> circ = std::make_shared<reznik::Circle>(reznik::Circle(10, { 30,10 }));
    CompositeShape Composite;
    Composite.addShape(rect);
    Composite.addShape(circ);
    double area = Composite.getArea();
    Composite.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(2 * 2 * area, Composite.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(Composite.getFrameRect().width, 80.0, EPSILON);
    BOOST_CHECK_CLOSE(Composite.getFrameRect().height, 80.0, EPSILON);
    BOOST_CHECK_CLOSE(rect->getFrameRect().width, 40.0, EPSILON);
    BOOST_CHECK_CLOSE(rect->getFrameRect().height, 40.0, EPSILON);
    BOOST_CHECK_CLOSE(circ->getFrameRect().width/2, 20.0, EPSILON);
    BOOST_CHECK_CLOSE(circ->getFrameRect().pos.x, 40.0, EPSILON);
    BOOST_CHECK_CLOSE(circ->getFrameRect().pos.y, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(rect->getFrameRect().pos.x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(rect->getFrameRect().pos.y, 40.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Incorrect_test_scale)
  {
    std::shared_ptr<Shape> rect = std::make_shared<reznik::Rectangle>(reznik::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<reznik::Circle>(reznik::Circle(5, { 0,0 }));
    CompositeShape Composite;
    Composite.addShape(rect);
    Composite.addShape(circ);
    BOOST_CHECK_THROW(Composite.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
