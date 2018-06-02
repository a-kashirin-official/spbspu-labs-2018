#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include <stdexcept>

using namespace usov;
const double epsilon = 0.001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)
  
  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<usov::Rectangle>(usov::Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<usov::Rectangle>(usov::Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp1(rect1);
    Comp1.addShape(rect2);
    rectangle_t frame = Comp1.getFrameRect();
    usov::CompositeShape Comp2(rect2);
    Comp2 = std::move(Comp1);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().width, frame.width, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().height, frame.height, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().pos.x, frame.pos.x, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().pos.y, frame.pos.y, epsilon);
  }


  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<usov::Rectangle>(usov::Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<usov::Rectangle>(usov::Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp1(rect1);
    Comp1.addShape(rect2);
    rectangle_t frame = Comp1.getFrameRect();
    CompositeShape Comp2(std::move(Comp1));
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().width, frame.width, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().height, frame.height, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().pos.x, frame.pos.x, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().pos.y, frame.pos.y, epsilon);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<usov::Rectangle>(usov::Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<usov::Rectangle>(usov::Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp1(rect1);
    Comp1.addShape(rect2);
    rectangle_t frame = Comp1.getFrameRect();
    CompositeShape Comp2(Comp1);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().width, frame.width, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().height, frame.height, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().pos.x, frame.pos.x, epsilon);
    BOOST_CHECK_CLOSE(Comp2.getFrameRect().pos.y, frame.pos.y, epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(IncorrectCopyOperator)
  {
    std::shared_ptr<Shape> rect = std::make_shared<usov::Rectangle>(usov::Rectangle(4, 4, { 0,0 }));
    CompositeShape Comp1(rect);
    BOOST_CHECK_THROW(Comp1 = Comp1, std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CorrectCopyOperator)
  {
    std::shared_ptr<Shape> rect = std::make_shared<usov::Rectangle>(usov::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> rect1 = std::make_shared<usov::Rectangle>(usov::Rectangle(1,1, { 0,0 }));
    std::shared_ptr<Shape> rect2 = std::make_shared<usov::Rectangle>(usov::Rectangle(2, 2, { 0,0 }));
    std::shared_ptr<Shape> rect3 = std::make_shared<usov::Rectangle>(usov::Rectangle(3, 3, { 0,0 }));
    CompositeShape Comp1(rect);
    Comp1.addShape(rect2);
    CompositeShape Comp2(rect1);
    Comp2.addShape(rect3);
    Comp1 = Comp2;
    BOOST_CHECK_CLOSE(Comp2.getArea(), Comp1.getArea(), epsilon);
  }

  BOOST_AUTO_TEST_CASE(MOVEINPOINT)
  {
    std::shared_ptr<Shape> rect = std::make_shared<usov::Rectangle>(usov::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(2, { 0,0 }));
    CompositeShape Composite(rect);
    Composite.addShape(circ);
    double height = Composite.getFrameRect().height;
    double width = Composite.getFrameRect().width;
    double area = Composite.getArea();
    Composite.move(2, 2);
    BOOST_CHECK_CLOSE(height, Composite.getFrameRect().height, epsilon);
    BOOST_CHECK_CLOSE(width, Composite.getFrameRect().width, epsilon);
    BOOST_CHECK_CLOSE(area, Composite.getArea(), epsilon);
  }

  BOOST_AUTO_TEST_CASE(MOVE)
  {
    std::shared_ptr<Shape> rect = std::make_shared<usov::Rectangle>(usov::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(2, { 0,0 }));
    CompositeShape Composite(rect);
    Composite.addShape(circ);
    double height = Composite.getFrameRect().height;
    double width = Composite.getFrameRect().width;
    double area = Composite.getArea();
    Composite.move({ 2, 2 });
    BOOST_CHECK_CLOSE(height, Composite.getFrameRect().height, epsilon);
    BOOST_CHECK_CLOSE(width, Composite.getFrameRect().width, epsilon);
    BOOST_CHECK_CLOSE(area, Composite.getArea(), epsilon);
    BOOST_CHECK_CLOSE(Composite.getFrameRect().pos.x, 2.0, epsilon);
    BOOST_CHECK_CLOSE(Composite.getFrameRect().pos.y, 2.0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Correct_scale)
  {
    usov::Rectangle rect(4, 4, { 2,2 });
    Circle circ(2, { -2,-2 });
    std::shared_ptr<Shape> rectptr = std::make_shared<usov::Rectangle>(rect);
    std::shared_ptr<Shape> circptr = std::make_shared<Circle>(circ);
    CompositeShape Composite(rectptr);
    Composite.addShape(circptr);
    rectangle_t frame = Composite.getFrameRect();
    Composite.scale(2);
    BOOST_CHECK_CLOSE(4.0*(rect.getArea()+circ.getArea()), Composite.getArea(), epsilon);
    BOOST_CHECK_CLOSE(Composite.getFrameRect().height, frame.height * 2, epsilon);
    BOOST_CHECK_CLOSE(Composite.getFrameRect().width, frame.width * 2, epsilon);
    BOOST_CHECK_CLOSE(Composite.getInfoShape(0)->getFrameRect().pos.x, 4.0, epsilon); //Rectangle
    BOOST_CHECK_CLOSE(Composite.getInfoShape(0)->getFrameRect().pos.y, 4.0, epsilon);
    BOOST_CHECK_CLOSE(Composite.getInfoShape(0)->getFrameRect().width, 8.0, epsilon);
    BOOST_CHECK_CLOSE(Composite.getInfoShape(0)->getFrameRect().height, 8.0, epsilon);
    BOOST_CHECK_CLOSE(Composite.getInfoShape(1)->getFrameRect().pos.x, -4.0, epsilon); //Circle
    BOOST_CHECK_CLOSE(Composite.getInfoShape(1)->getFrameRect().pos.y, -4.0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Incorrect_test_scale)
  {
    std::shared_ptr<Shape> rect = std::make_shared<usov::Rectangle>(usov::Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(2, { 0,0 }));
    CompositeShape Composite(rect);
    Composite.addShape(circ);
    BOOST_CHECK_THROW(Composite.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
