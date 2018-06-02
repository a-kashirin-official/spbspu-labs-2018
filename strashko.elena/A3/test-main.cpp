#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 0.001;

using namespace strashko;

BOOST_AUTO_TEST_SUITE(RectS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    rectangle_t rectangleBefore;
    point_t centre{3.0, -1.0};
    point_t newpos{8.0, 5.0};
    Rectangle rectangle(centre, 4.7, 1.3);
    areaBefore = rectangle.getArea();
    rectangleBefore = rectangle.getFrameRect();
    rectangle.move(newpos);

    BOOST_CHECK_EQUAL(areaBefore, rectangle.getArea());
    BOOST_CHECK_EQUAL(rectangleBefore.height, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(rectangleBefore.width, rectangle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(CompareMoveToXY)
  {
    double areaBefore;
    rectangle_t rectangleBefore;
    point_t centre{3.0, -1.0};
    Rectangle rectangle(centre, 4.7, 1.3);
    areaBefore = rectangle.getArea();
    rectangleBefore = rectangle.getFrameRect();
    rectangle.move(4.5, -2.7);

    BOOST_CHECK_EQUAL(areaBefore, rectangle.getArea());
    BOOST_CHECK_EQUAL(rectangleBefore.height, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(rectangleBefore.width, rectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, 7.5);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, -3.7);
  }

  BOOST_AUTO_TEST_CASE(EnlargementOfArea)
  {
    double areaBefore;
    point_t centre{4.2, 6.4};
    Rectangle rectangle(centre, 3.2, 1.0);
    areaBefore = rectangle.getArea();
    rectangle.scale(0.5);
    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBefore * 0.5 * 0.5, EPSILON);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    point_t centre{0.0, 0.0};

    BOOST_CHECK_THROW(Rectangle rectangle(centre, -2.7, 3.1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    point_t centre{0.0, 0.0};
    Rectangle rectangle(centre, 4.2, 3.3);
    BOOST_CHECK_THROW(rectangle.scale(-4.8), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    rectangle_t circleBefore;
    point_t centre{3.0, -1.0};
    point_t newpos{8.0, 5.0};
    Circle circle(centre, 2.1);
    areaBefore = circle.getArea();
    circleBefore = circle.getFrameRect();
    circle.move(newpos);

    BOOST_CHECK_EQUAL(areaBefore, circle.getArea());
    BOOST_CHECK_EQUAL(circleBefore.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(circleBefore.width, circle.getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(CompareMoveToXY)
  {
    double areaBefore;
    rectangle_t circleBefore;
    point_t centre{3.0, -1.0};
    Circle circle(centre, 1.3);
    areaBefore = circle.getArea();
    circleBefore = circle.getFrameRect();
    circle.move(4.5, -2.7);

    BOOST_CHECK_EQUAL(areaBefore, circle.getArea());
    BOOST_CHECK_EQUAL(circleBefore.height, circle.getFrameRect().height);
    BOOST_CHECK_EQUAL(circleBefore.width, circle.getFrameRect().width);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, 7.5);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, -3.7);
  }

  BOOST_AUTO_TEST_CASE(EnlargementOfArea)
  {
    double areaBefore;
    point_t centre{4.2, 6.4};
    Circle circle(centre, 1.0);
    areaBefore = circle.getArea();
    circle.scale(0.5);
    BOOST_CHECK_CLOSE(circle.getArea(), areaBefore * 0.5 * 0.5, EPSILON);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    point_t centre{0.0, 0.0};
    BOOST_CHECK_THROW(Circle circle(centre, -2.7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    point_t centre{0.0, 0.0};
    Circle circle(centre, 4.2);
    BOOST_CHECK_THROW(circle.scale(-4.8), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_Test)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    point_t centre{3.0, -1.0};
    point_t centre_c{5.1, 2.0};
    point_t newpos{8.0, 5.0};
    Rectangle rectangle(centre, 11.7, 9.3);
    Circle circle(centre_c, 3.5);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
    std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
    CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    rectangle_t rect = comp.getFrameRect();
    comp.move(newpos);

    BOOST_CHECK_CLOSE(comp.getArea(), rectangle.getArea() + circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(rect.height, comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(rect.width, comp.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompareMoveToXY)
  {
    point_t centre{3.0, -1.0};
    point_t centre_c{5.1, 2.0};
    Rectangle rectangle(centre, 10.7, 8.3);
    Circle circle(centre_c, 3.5);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
    std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
    CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    rectangle_t rect = comp.getFrameRect();
    comp.move(1.44, 3.1);

    BOOST_CHECK_CLOSE(comp.getArea(), rectangle.getArea() + circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(rect.height, comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(rect.width, comp.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(EnlargementOfArea)
  {
    point_t centre{4.2, 6.4};
    point_t centre_c{5.1, 2.0};
    Rectangle rectangle(centre, 10.0, 10.0);
    Circle circle(centre_c, 5);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
    std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
    CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    rectangle_t rect = comp.getFrameRect();
    comp.scale(0.5);
    BOOST_CHECK_CLOSE(comp.getArea(), (rectangle.getArea() + circle.getArea()) * 0.5 * 0.5, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, rect.height * 0.5, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, rect.width * 0.5, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, rect.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, rect.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RemoveTest)
  {
    point_t centre{6.0, 2.5};
    point_t centre_c{3.5, 1.8};
    Rectangle rectangle(centre, 6.0, 3.0);
    Circle circle(centre_c, 3.6);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
    std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
    CompositeShape comp(circlePtr);
    comp.addShape(rectPtr);
    comp.removeShape(1);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
    BOOST_REQUIRE_EQUAL(comp.getArea(), rectangle.getArea());
    BOOST_REQUIRE_EQUAL(comp.getCount(), 1);
  }

  BOOST_AUTO_TEST_CASE(CorrectnessOfDelete)
   {
     point_t centre{0.0, 2.5};
     point_t centre_c{3.5, 1.8};
     Rectangle rectangle(centre, 6.0, 3.0);
     Circle circle(centre_c, 3.6);
     std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
     std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
     CompositeShape comp(circlePtr);
     comp.addShape(rectPtr);
     comp.deleteAllShapes();
     BOOST_REQUIRE_EQUAL(comp.getCount(), 0);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    point_t centre{4.2, 6.4};
    point_t centre_c{5.1, 2.0};
    Rectangle rectangle(centre, 3.2, 1.0);
    Circle circle(centre_c, 3.5);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
    std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
    CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    BOOST_CHECK_THROW(comp.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectShapeNumberRemove)
  {
    point_t centre{4.2, 6.4};
    Rectangle rectangle(centre, 3.2, 1.0);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
    CompositeShape comp(rectPtr);
    BOOST_CHECK_THROW(comp.removeShape(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(IncorrectRemoveInCompositeShape)
  {
    point_t centre{4.2, 6.4};
    point_t centre_c{5.1, 2.0};
    Rectangle rectangle(centre, 3.2, 1.0);
    Circle circle(centre_c, 3.5);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
    std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
    CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    comp.deleteAllShapes();
    BOOST_CHECK_THROW(comp.removeShape(1), std::out_of_range);
  }


  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    point_t centre{4.1, 0.0};
    Rectangle rectangle(centre, 7.0, 3.2);
    Circle circ(centre, 2.2);
    std::shared_ptr< Shape > rect = std::make_shared< Rectangle >(rectangle);
    CompositeShape compsh(rect);
    std::shared_ptr< Shape > circle = std::make_shared< Circle >(circ);
    compsh.addShape(circle);

    CompositeShape comp{compsh};

    BOOST_CHECK_EQUAL(comp.getArea(), compsh.getArea());
    rectangle_t rect1 = comp.getFrameRect();
    rectangle_t rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructor)
  {
    point_t centre{4.1, 0.0};
    Rectangle rectangle(centre, 7.0, 3.2);
    Circle circl(centre, 2.2);
    std::shared_ptr< Shape > rect = std::make_shared< Rectangle >(rectangle);
    CompositeShape compsh(rect);

    std::shared_ptr< Shape > circle = std::make_shared< Circle >(circl);
    compsh.addShape(circle);

    double beforeMovingArea = compsh.getArea();
    rectangle_t rect2 = compsh.getFrameRect();

    CompositeShape comp{ std::move(compsh) };

    BOOST_CHECK_EQUAL(comp.getArea(), beforeMovingArea);
    rectangle_t rect1 = comp.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);

    BOOST_CHECK_EQUAL(compsh.getArea(), 0.0);
    rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect2.width, 0.0);
    BOOST_CHECK_EQUAL(rect2.height, 0.0);
    BOOST_CHECK_EQUAL(rect2.pos.x, 0.0);
    BOOST_CHECK_EQUAL(rect2.pos.y, 0.0);
  }

  BOOST_AUTO_TEST_CASE(AssignmentCopy)
  {
    CompositeShape comp;
    point_t centre{4.1, 0.0};
    Rectangle rectangle(centre, 7.0, 3.2);
    Circle circl(centre, 2.2);
    std::shared_ptr< Shape > rect = std::make_shared< Rectangle >(rectangle);
    CompositeShape compsh(rect);

    std::shared_ptr< Shape > circle = std::make_shared< Circle >(circl);
    compsh.addShape(circle);

    comp = compsh;

    BOOST_CHECK_EQUAL(comp.getArea(), compsh.getArea());
    rectangle_t rect1 = comp.getFrameRect();
    rectangle_t rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
  }

  BOOST_AUTO_TEST_CASE(AssignmentMove)
  {
    CompositeShape comp;
    point_t centre{4.1, 0.0};
    Rectangle rectangle(centre, 7.0, 3.2);
    Circle circl(centre, 2.2);
    std::shared_ptr< Shape > rect = std::make_shared< Rectangle >(rectangle);
    CompositeShape compsh(rect);

    std::shared_ptr< Shape > circle = std::make_shared< Circle >(circl);
    compsh.addShape(circle);

    double beforeMovingArea = compsh.getArea();
    rectangle_t rect2 = compsh.getFrameRect();

    comp = std::move(compsh);

    BOOST_CHECK_EQUAL(comp.getArea(), beforeMovingArea);
    rectangle_t rect1 = comp.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);

    BOOST_CHECK_EQUAL(compsh.getArea(), 0.0);
    rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect2.width, 0.0);
    BOOST_CHECK_EQUAL(rect2.height, 0.0);
    BOOST_CHECK_EQUAL(rect2.pos.x, 0.0);
    BOOST_CHECK_EQUAL(rect2.pos.y, 0.0);
  }

  BOOST_AUTO_TEST_CASE(Index_capture)//operator[]
  {
    point_t centre{0.0, 3.8};
    Rectangle rectangle(centre, 5.7, 8.1);
    std::shared_ptr< Shape > rectanglePtr = std::make_shared< Rectangle >(rectangle);
    CompositeShape comp(rectanglePtr);
    BOOST_CHECK_THROW(comp[1], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
