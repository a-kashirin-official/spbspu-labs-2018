#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include <circle.hpp>
#include <rectangle.hpp>
#include <composite-shape.hpp>

using namespace vasilev;
const double EPSILON = 0.0001;
BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(XYMoveTest)
  {
    Circle testCircle(20, {100, 100});
    testCircle.move(50, 50);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getRadius(), 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), 400*M_PI, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(PointMoveTest)
  {
    Circle testCircle(20, {100, 100});
    testCircle.move({150, 150});
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getRadius(), 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), 400*M_PI, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Circle testCircle(20, {100, 100});
    testCircle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), 400*4*M_PI, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MultiplierTest)
  {
    Circle testCircle(20, {10, 10});
    BOOST_CHECK_THROW(testCircle.scale(-2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InitValuesTest)
  {
    BOOST_CHECK_THROW(Circle(-20, {100, 100}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(XYMoveTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    testRectangle.move(50, 50);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().height, 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().width, 40, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 800, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(PointMoveTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    testRectangle.move({150, 150});
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().height, 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().width, 40, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 800, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    testRectangle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 800*4, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MultiplierTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    BOOST_CHECK_THROW(testRectangle.scale(-2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InitValuesTest)
  {
    BOOST_CHECK_THROW(Rectangle(-40, 20, {100, 100}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle(40, -20, {100, 100}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle(-40, -20, {100,100}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    std::shared_ptr<Shape> rect_1 = std::make_shared<Rectangle>(Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect_2 = std::make_shared<Rectangle>(Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp_1(rect_1);
    CompositeShape Comp_2(rect_2);
    rectangle_t frame = Comp_1.getFrameRect();
    Comp_2 = std::move(Comp_1);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.x, frame.pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.y, frame.pos.y, EPSILON);
  }


  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr<Shape> rect_1 = std::make_shared<Rectangle>(Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect_2 = std::make_shared<Rectangle>(Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp_1(rect_1);
    rectangle_t frame = Comp_1.getFrameRect();
    CompositeShape Comp_2(std::move(Comp_1));
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.x, frame.pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.y, frame.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr<Shape> rect_1 = std::make_shared<Rectangle>(Rectangle(1, 1, { 0,0 }));
    std::shared_ptr<Shape> rect_2 = std::make_shared<Rectangle>(Rectangle(2, 2, { 0,0 }));
    CompositeShape Comp_1(rect_1);
    CompositeShape Comp_2(Comp_1);
    rectangle_t frame = Comp_1.getFrameRect();
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.x, frame.pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.y, frame.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CorrectCopyOperator)
  {
    std::shared_ptr<Shape> rect_1 = std::make_shared<Rectangle>(Rectangle(1,1, { 0,0 }));
    std::shared_ptr<Shape> rect_2 = std::make_shared<Rectangle>(Rectangle(2, 2, { 0,0 }));
    std::shared_ptr<Shape> rect_3 = std::make_shared<Rectangle>(Rectangle(3, 3, { 0,0 }));
    CompositeShape Comp_1(rect_1);
    Comp_1.addShape(rect_2);
    CompositeShape Comp_2(rect_1);
    Comp_2.addShape(rect_3);
    Comp_1 = Comp_2;
    BOOST_CHECK_CLOSE(Comp_2.getArea(), Comp_1.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(PointMoveTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(2, { 0,0 }));
    CompositeShape Comp(rect);
    Comp.addShape(circ);
    double height = Comp.getFrameRect().height;
    double width = Comp.getFrameRect().width;
    double area = Comp.getArea();
    Comp.move(2, 2);
    BOOST_CHECK_CLOSE(height, Comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(width, Comp.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(area, Comp.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.x, 2.0, EPSILON);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.y, 2.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveCompositeShapeTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(2, { 0,0 }));
    CompositeShape Comp(rect);
    Comp.addShape(circ);
    double height = Comp.getFrameRect().height;
    double width = Comp.getFrameRect().width;
    double area = Comp.getArea();
    Comp.move({ 2, 2 });
    BOOST_CHECK_CLOSE(height, Comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(width, Comp.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(area, Comp.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.x, 2.0, EPSILON);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.y, 2.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CorrectScale)
  {
    Rectangle rect(4, 4, { 2,2 });
    Circle circ(2, { -2,-2 });
    std::shared_ptr<Shape> rectptr = std::make_shared<Rectangle>(rect);
    std::shared_ptr<Shape> circptr = std::make_shared<Circle>(circ);
    CompositeShape Comp(rectptr);
    Comp.addShape(circptr);
    rectangle_t frame = Comp.getFrameRect();
    Comp.scale(2);
    BOOST_CHECK_CLOSE(4.0*(rect.getArea()+circ.getArea()), Comp.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().height, frame.height * 2, EPSILON);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().width, frame.width * 2, EPSILON);
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().pos.x, 4.0, EPSILON); //Rectangle
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().pos.y, 4.0, EPSILON);
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().width, 8.0, EPSILON);
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().height, 8.0, EPSILON);
    BOOST_CHECK_CLOSE(Comp.getShape(1)->getFrameRect().pos.x, -4.0, EPSILON); //Circle
    BOOST_CHECK_CLOSE(Comp.getShape(1)->getFrameRect().pos.y, -4.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(IncorrectScaleTest)
  {
    std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle(4, 4, { 0,0 }));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(2, { 0,0 }));
    CompositeShape Comp(rect);
    Comp.addShape(circ);
    BOOST_CHECK_THROW(Comp.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
