#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(RectS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    strashko::rectangle_t rectangleBefore;
    strashko::point_t centre{3.0, -1.0};
    strashko::point_t newpos{8.0, 5.0};
    strashko::Rectangle rectangle(centre, 4.7, 1.3);
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
    strashko::rectangle_t rectangleBefore;
    strashko::point_t centre{3.0, -1.0};
    strashko::Rectangle rectangle(centre, 4.7, 1.3);
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
    strashko::point_t centre{4.2, 6.4};
    strashko::Rectangle rectangle(centre, 3.2, 1.0);
    areaBefore = rectangle.getArea();
    rectangle.scale(0.5);
    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBefore * 0.5 * 0.5, EPSILON);
   }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_90_Test_Rect)
  {
    strashko::point_t centre{3.5, -80.2};
    strashko::Rectangle rectangle(centre, 15.8, 20.4);
    rectangle.rotate(90);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, 20.4);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 15.8, EPSILON);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, centre.x);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, centre.y);
  }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_45_Test_Rect)
  {
    strashko::point_t centre{0.0, 0.0};
    strashko::Rectangle rectangle(centre, 2.0, 4.0);
    rectangle.rotate(45);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 4.2426406871192857, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 4.2426406871192857, EPSILON);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, centre.x);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, centre.y);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    strashko::point_t centre{4, 3};
    strashko::Rectangle rectangle(centre, 4, 2);
    for (int i = -90; i < 91; ++i) {
      strashko::Rectangle rectangle1(rectangle);
      rectangle.rotate(i);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, rectangle1.getFrameRect().pos.x, EPSILON);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, rectangle1.getFrameRect().pos.y, EPSILON);
      BOOST_CHECK_CLOSE(rectangle.getArea(), rectangle1.getArea(), EPSILON);
    }
  }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    strashko::point_t centre{0.0, 0.0};

    BOOST_CHECK_THROW(strashko::Rectangle rectangle(centre, -2.7, 3.1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    strashko::point_t centre{0.0, 0.0};
    strashko::Rectangle rectangle(centre, 4.2, 3.3);
    BOOST_CHECK_THROW(rectangle.scale(-4.8), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    strashko::rectangle_t circleBefore;
    strashko::point_t centre{3.0, -1.0};
    strashko::point_t newpos{8.0, 5.0};
    strashko::Circle circle(centre, 2.1);
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
    strashko::rectangle_t circleBefore;
    strashko::point_t centre{3.0, -1.0};
    strashko::Circle circle(centre, 1.3);
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
    strashko::point_t centre{4.2, 6.4};
    strashko::Circle circle(centre, 1.0);
    areaBefore = circle.getArea();
    circle.scale(0.5);
    BOOST_CHECK_CLOSE(circle.getArea(), areaBefore * 0.5 * 0.5, EPSILON);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    strashko::point_t centre{0.0, 0.0};
    BOOST_CHECK_THROW(strashko::Circle circle(centre, -2.7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    strashko::point_t centre{0.0, 0.0};
    strashko::Circle circle(centre, 4.2);
    BOOST_CHECK_THROW(circle.scale(-4.8), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_Test)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    strashko::point_t centre{3.0, -1.0};
    strashko::point_t centre_c{5.1, 2.0};
    strashko::point_t newpos{8.0, 5.0};
    strashko::Rectangle rectangle(centre, 11.7, 9.3);
    strashko::Circle circle(centre_c, 3.5);
    std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circlePtr = std::make_shared< strashko::Circle >(circle);
    strashko::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    strashko::rectangle_t rect = comp.getFrameRect();
    comp.move(newpos);

    BOOST_CHECK_CLOSE(comp.getArea(), rectangle.getArea() + circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(rect.height, comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(rect.width, comp.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompareMoveToXY)
  {
    strashko::point_t centre{3.0, -1.0};
    strashko::point_t centre_c{5.1, 2.0};
    strashko::Rectangle rectangle(centre, 10.7, 8.3);
    strashko::Circle circle(centre_c, 3.5);
    std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circlePtr = std::make_shared< strashko::Circle >(circle);
    strashko::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    strashko::rectangle_t rect = comp.getFrameRect();
    comp.move(1.44, 3.1);

    BOOST_CHECK_CLOSE(comp.getArea(), rectangle.getArea() + circle.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(rect.height, comp.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(rect.width, comp.getFrameRect().width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(EnlargementOfArea)
  {
    strashko::point_t centre{4.2, 6.4};
    strashko::point_t centre_c{5.1, 2.0};
    strashko::Rectangle rectangle(centre, 10.0, 10.0);
    strashko::Circle circle(centre_c, 5);
    std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circlePtr = std::make_shared< strashko::Circle >(circle);
    strashko::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    strashko::rectangle_t rect = comp.getFrameRect();
    comp.scale(0.5);
    BOOST_CHECK_CLOSE(comp.getArea(), (rectangle.getArea() + circle.getArea()) * 0.5 * 0.5, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, rect.height * 0.5, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, rect.width * 0.5, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, rect.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, rect.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RemoveTest)
  {
    strashko::point_t centre{6.0, 2.5};
    strashko::point_t centre_c{3.5, 1.8};
    strashko::Rectangle rectangle(centre, 6.0, 3.0);
    strashko::Circle circle(centre_c, 3.6);
    std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circlePtr = std::make_shared< strashko::Circle >(circle);
    strashko::CompositeShape comp(circlePtr);
    comp.addShape(rectPtr);
    comp.removeShape(1);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
    BOOST_REQUIRE_EQUAL(comp.getArea(), rectangle.getArea());
    BOOST_REQUIRE_EQUAL(comp.getCount(), 1);
  }

  BOOST_AUTO_TEST_CASE(CorrectnessOfDelete)
   {
     strashko::point_t centre{0.0, 2.5};
     strashko::point_t centre_c{3.5, 1.8};
     strashko::Rectangle rectangle(centre, 6.0, 3.0);
     strashko::Circle circle(centre_c, 3.6);
     std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
     std::shared_ptr< strashko::Shape > circlePtr = std::make_shared< strashko::Circle >(circle);
     strashko::CompositeShape comp(circlePtr);
     comp.addShape(rectPtr);
     comp.deleteAllShapes();
     BOOST_REQUIRE_EQUAL(comp.getCount(), 0);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    strashko::point_t centre{4.2, 6.4};
    strashko::point_t centre_c{5.1, 2.0};
    strashko::Rectangle rectangle(centre, 3.2, 1.0);
    strashko::Circle circle(centre_c, 3.5);
    std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circlePtr = std::make_shared< strashko::Circle >(circle);
    strashko::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    BOOST_CHECK_THROW(comp.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectShapeNumberRemove)
  {
    strashko::point_t centre{4.2, 6.4};
    strashko::Rectangle rectangle(centre, 3.2, 1.0);
    std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
    strashko::CompositeShape comp(rectPtr);
    BOOST_CHECK_THROW(comp.removeShape(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(IncorrectRemoveInCompositeShape)
  {
    strashko::point_t centre{4.2, 6.4};
    strashko::point_t centre_c{5.1, 2.0};
    strashko::Rectangle rectangle(centre, 3.2, 1.0);
    strashko::Circle circle(centre_c, 3.5);
    std::shared_ptr< strashko::Shape > rectPtr = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circlePtr = std::make_shared< strashko::Circle >(circle);
    strashko::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    comp.deleteAllShapes();
    BOOST_CHECK_THROW(comp.removeShape(1), std::out_of_range);
  }


  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    strashko::point_t centre{4.1, 0.0};
    strashko::Rectangle rectangle(centre, 7.0, 3.2);
    strashko::Circle circ(centre, 2.2);
    std::shared_ptr< strashko::Shape > rect = std::make_shared< strashko::Rectangle >(rectangle);
    strashko::CompositeShape compsh(rect);
    std::shared_ptr< strashko::Shape > circle = std::make_shared< strashko::Circle >(circ);
    compsh.addShape(circle);

    strashko::CompositeShape comp{compsh};

    BOOST_CHECK_EQUAL(comp.getArea(), compsh.getArea());
    strashko::rectangle_t rect1 = comp.getFrameRect();
    strashko::rectangle_t rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructor)
  {
    strashko::point_t centre{4.1, 0.0};
    strashko::Rectangle rectangle(centre, 7.0, 3.2);
    strashko::Circle circl(centre, 2.2);
    std::shared_ptr< strashko::Shape > rect = std::make_shared< strashko::Rectangle >(rectangle);
    strashko::CompositeShape compsh(rect);

    std::shared_ptr< strashko::Shape > circle = std::make_shared< strashko::Circle >(circl);
    compsh.addShape(circle);

    double beforeMovingArea = compsh.getArea();
    strashko::rectangle_t rect2 = compsh.getFrameRect();

    strashko::CompositeShape comp{ std::move(compsh) };

    BOOST_CHECK_EQUAL(comp.getArea(), beforeMovingArea);
    strashko::rectangle_t rect1 = comp.getFrameRect();
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
    strashko::CompositeShape comp;
    strashko::point_t centre{4.1, 0.0};
    strashko::Rectangle rectangle(centre, 7.0, 3.2);
    strashko::Circle circl(centre, 2.2);
    std::shared_ptr< strashko::Shape > rect = std::make_shared< strashko::Rectangle >(rectangle);
    strashko::CompositeShape compsh(rect);

    std::shared_ptr< strashko::Shape > circle = std::make_shared< strashko::Circle >(circl);
    compsh.addShape(circle);

    comp = compsh;

    BOOST_CHECK_EQUAL(comp.getArea(), compsh.getArea());
    strashko::rectangle_t rect1 = comp.getFrameRect();
    strashko::rectangle_t rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
  }

  BOOST_AUTO_TEST_CASE(AssignmentMove)
  {
    strashko::CompositeShape comp;
    strashko::point_t centre{4.1, 0.0};
    strashko::Rectangle rectangle(centre, 7.0, 3.2);
    strashko::Circle circl(centre, 2.2);
    std::shared_ptr< strashko::Shape > rect = std::make_shared< strashko::Rectangle >(rectangle);
    strashko::CompositeShape compsh(rect);

    std::shared_ptr< strashko::Shape > circle = std::make_shared< strashko::Circle >(circl);
    compsh.addShape(circle);

    double beforeMovingArea = compsh.getArea();
    strashko::rectangle_t rect2 = compsh.getFrameRect();

    comp = std::move(compsh);

    BOOST_CHECK_EQUAL(comp.getArea(), beforeMovingArea);
    strashko::rectangle_t rect1 = comp.getFrameRect();
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
    strashko::point_t centre{0.0, 3.8};
    strashko::Rectangle rectangle(centre, 5.7, 8.1);
    std::shared_ptr< strashko::Shape > rectanglePtr = std::make_shared< strashko::Rectangle >(rectangle);
    strashko::CompositeShape comp(rectanglePtr);
    BOOST_CHECK_THROW(comp[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_90_Test_CS)
  {
    strashko::point_t centre{1.0, 1.0};
    strashko::point_t centre_r{3.0, 1.0};
    strashko::Rectangle rectangle(centre, 2.0, 2.0);
    strashko::Rectangle rect(centre_r, 2.0, 2.0);
    std::shared_ptr<strashko::Shape> rectanglePtr = std::make_shared<strashko::Rectangle>(rectangle);
    std::shared_ptr<strashko::Shape> rectPtr = std::make_shared<strashko::Rectangle>(rect);
    strashko::CompositeShape compositeShape(rectanglePtr);
    compositeShape.addShape(rectPtr);

    strashko::CompositeShape compsh = compositeShape;
    compositeShape.rotate(90);
    BOOST_CHECK_EQUAL(compositeShape.getArea(), compsh.getArea());
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.x, compsh.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.y, compsh.getFrameRect().pos.y);
    BOOST_CHECK_EQUAL(compositeShape[0]->getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(compositeShape[0]->getFrameRect().pos.y, 0.0);
    BOOST_CHECK_EQUAL(compositeShape[1]->getFrameRect().pos.x, 2.0);
    BOOST_CHECK_EQUAL(compositeShape[1]->getFrameRect().pos.y, 2.0);
  }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_45_Test_CS)
  {

    strashko::point_t centre{3.0, 8.55};
    strashko::point_t centre_c{11.0, 71.3};
    strashko::point_t centre_r{-5.6, -4.7};
    strashko::Rectangle rectangle(centre, 18.0, 7.0);
    strashko::Circle circle(centre_c, 20.1);
    strashko::Rectangle rect(centre_r, 4.8, 5.8);
    std::shared_ptr<strashko::Shape> rectanglePtr = std::make_shared<strashko::Rectangle>(rectangle);
    std::shared_ptr<strashko::Shape> circlePtr = std::make_shared<strashko::Circle>(circle);
    std::shared_ptr<strashko::Shape> rectPtr = std::make_shared<strashko::Rectangle>(rect);
    strashko::CompositeShape compositeShape(rectanglePtr);
    compositeShape.addShape(circlePtr);
    compositeShape.addShape(rectPtr);
    strashko::CompositeShape compsh = compositeShape;
    compositeShape.rotate(45);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.x, compsh.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.y, compsh.getFrameRect().pos.y);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

  BOOST_AUTO_TEST_CASE(addElementsFromCompSh)
  {
    strashko::point_t centre_r1{2.8, 3.0};
    strashko::Rectangle rectangle1(centre_r1, 5.8, 7.2);
    strashko::point_t centre_c{0.0, -4.9};
    strashko::Circle circle1(centre_c, 2.0);
    strashko::point_t centre_r2{-8.9, -12.6};
    strashko::Rectangle rectangle2(centre_r2, 24.03, 14.5);
    std::shared_ptr<strashko::Shape> rectanglePtr = std::make_shared<strashko::Rectangle>(rectangle1);
    std::shared_ptr<strashko::Shape> circlePtr = std::make_shared<strashko::Circle>(circle1);
    std::shared_ptr<strashko::Shape> rectPtr = std::make_shared<strashko::Rectangle>(rectangle2);
    strashko::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);
    compSh.addShape(rectPtr);

    strashko::Matrix matrix;
    matrix.addElementsFromCompSh(compSh);
    strashko::rectangle_t FrameRectangle[3];
    FrameRectangle[0] = rectangle1.getFrameRect();
    FrameRectangle[1] = circle1.getFrameRect();
    FrameRectangle[2] = rectangle2.getFrameRect();

    BOOST_CHECK_EQUAL(matrix.getLayerCount(), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(1), 1);
    for (int i = 0; i < matrix.getLayerCount(); ++i) {
      for (int j = 0; j < matrix.getLayerSize(i); ++j) {
        strashko:: rectangle_t rectangle = matrix[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, FrameRectangle[i * 2 + j].pos.x, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.pos.y, FrameRectangle[i * 2 + j].pos.y, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.width, FrameRectangle[i * 2 + j].width, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.height, FrameRectangle[i * 2 + j].height, EPSILON);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(add)
  {
    strashko::point_t centre_r1{3.0, -3.0};
    strashko::Rectangle rectangle1(centre_r1, 4.0, 2.0);
    strashko::point_t centre_c{7.0, -3.0};
    strashko::Circle circle1(centre_c, 1.0);
    std::shared_ptr<strashko::Shape> rectanglePtr = std::make_shared<strashko::Rectangle>(rectangle1);
    std::shared_ptr<strashko::Shape> circlePtr = std::make_shared<strashko::Circle>(circle1);
    strashko::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);
    strashko::point_t centre_r2{2.0, 1.0};
    strashko::Rectangle rectangle2(centre_r2, 2.0, 4.0);
    std::shared_ptr<strashko::Shape> rectPtr = std::make_shared<strashko::Rectangle>(rectangle2);
    strashko::point_t centre_c2{5.0, 3.0};
    strashko::Circle circle2(centre_c2, 1.0);
    std::shared_ptr<strashko::Shape> circlePtr2 = std::make_shared<strashko::Circle>(circle2);

    strashko::Matrix matrix;
    matrix.addElementsFromCompSh(compSh);
    matrix.add(rectPtr);
    matrix.add(circlePtr2);
    matrix.addElementsFromCompSh(compSh);

    strashko::rectangle_t FrameRectangle[6];
    FrameRectangle[0] = rectangle1.getFrameRect();
    FrameRectangle[1] = circle1.getFrameRect();
    FrameRectangle[2] = rectangle2.getFrameRect();
    FrameRectangle[3] = circle2.getFrameRect();
    FrameRectangle[4] = rectangle1.getFrameRect();
    FrameRectangle[5] = circle1.getFrameRect();

    BOOST_CHECK_EQUAL(matrix.getLayerCount(), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), 4);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(1), 2);
    for (int i = 0; i < matrix.getLayerCount(); ++i) {
      for (int j = 0; j < matrix.getLayerSize(i); ++j) {
        strashko::rectangle_t rectangle = matrix[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, FrameRectangle[i * 4 + j].pos.x, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.pos.y, FrameRectangle[i * 4 + j].pos.y, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.width, FrameRectangle[i * 4 + j].width, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.height, FrameRectangle[i * 4 + j].height, EPSILON);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(Constructor_Copy)
  {
    strashko::point_t centre_r1{2.8, 3.0};
    strashko::Rectangle rectangle1(centre_r1, 5.8, 7.2);
    strashko::point_t centre_c{0.0, -4.9};
    strashko::Circle circle1(centre_c, 2.0);
    std::shared_ptr<strashko::Shape> rectanglePtr = std::make_shared<strashko::Rectangle>(rectangle1);
    std::shared_ptr<strashko::Shape> circlePtr = std::make_shared<strashko::Circle>(circle1);
    strashko::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);

    strashko::Matrix matrix;
    strashko::point_t centre_r2{0.0, 0.0};
    strashko::Rectangle rectangle2(centre_r2, 8.1, 3.5);
    std::shared_ptr<strashko::Shape> rectPtr = std::make_shared<strashko::Rectangle>(rectangle2);
    strashko::point_t centre_c2{-6.4, 3.5};
    strashko::Circle circle2(centre_c2, 5.9);
    std::shared_ptr<strashko::Shape> circlPtr = std::make_shared<strashko::Circle>(circle2);
    matrix.add(rectPtr);
    matrix.add(circlPtr);
    matrix.addElementsFromCompSh(compSh);

    strashko::Matrix matrix1(matrix);
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), matrix1.getLayerCount());
    for (int i = 0; i < matrix.getLayerCount(); ++i) {
      BOOST_CHECK_EQUAL(matrix.getLayerSize(i), matrix1.getLayerSize(i));
      for (int j = 0; j < matrix.getLayerSize(i); ++j) {
        strashko::rectangle_t rectangle = matrix[i][j].getFrameRect();
        strashko::rectangle_t rectangle1 = matrix1[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, rectangle1.pos.x, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.pos.y, rectangle1.pos.y, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.width, rectangle1.width, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.height, rectangle1.height, EPSILON);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(Assignment_Copy)//copying operator=
  {
    strashko::point_t centre_r1{2.8, 3.0};
    strashko::Rectangle rectangle1(centre_r1, 5.8, 7.2);
    strashko::point_t centre_c{0.0, -4.9};
    strashko::Circle circle1(centre_c, 2.0);
    std::shared_ptr<strashko::Shape> rectanglePtr = std::make_shared<strashko::Rectangle>(rectangle1);
    std::shared_ptr<strashko::Shape> circlePtr = std::make_shared<strashko::Circle>(circle1);
    strashko::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);

    strashko::Matrix matrix;
    strashko::point_t centre_r2{0.0, 0.0};
    strashko::Rectangle rectangle2(centre_r2, 8.1, 3.5);
    strashko::point_t centre_c2{-6.4, 3.5};
    strashko::Circle circle2(centre_c2, 5.9);
    std::shared_ptr<strashko::Shape> rectPtr = std::make_shared<strashko::Rectangle>(rectangle2);
    std::shared_ptr<strashko::Shape> circlPtr = std::make_shared<strashko::Circle>(circle2);
    matrix.add(rectPtr);
    matrix.add(circlPtr);
    matrix.addElementsFromCompSh(compSh);
    matrix.addElementsFromCompSh(compSh);

    strashko::Matrix matrix1;
    matrix1 = matrix;
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), matrix1.getLayerCount());
    for (int i = 0; i < matrix.getLayerCount(); ++i) {
      BOOST_CHECK_EQUAL(matrix.getLayerSize(i), matrix1.getLayerSize(i));
      for (int j = 0; j < matrix.getLayerSize(i); ++j) {
        strashko::rectangle_t rectangle = matrix[i][j].getFrameRect();
        strashko::rectangle_t rectangle1 = matrix1[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, rectangle1.pos.x, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.pos.y, rectangle1.pos.y, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.width, rectangle1.width, EPSILON);
        BOOST_CHECK_CLOSE(rectangle.height, rectangle1.height, EPSILON);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(Taking_by_index)//operator[]
  {
    strashko::point_t centre_r1{3.0, -3.0};
    strashko::Rectangle rectangle1(centre_r1, 4.0, 2.0);
    strashko::point_t centre_c{7.0, -3.0};
    strashko::Circle circle1(centre_c, 1.0);
    std::shared_ptr<strashko::Shape> rectanglePtr = std::make_shared<strashko::Rectangle>(rectangle1);
    std::shared_ptr<strashko::Shape> circlePtr = std::make_shared<strashko::Circle>(circle1);
    strashko::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);

    strashko::Matrix matrix;
    strashko::point_t centre_r2{2.0, 1.0};
    strashko::Rectangle rectangle2(centre_r2, 2.0, 4.0);
    strashko::point_t centre_c2{5.0, 3.0};
    strashko::Circle circle2(centre_c2, 1.0);
    matrix.addElementsFromCompSh(compSh);
    std::shared_ptr<strashko::Shape> rectPtr = std::make_shared<strashko::Rectangle>(rectangle2);
    std::shared_ptr<strashko::Shape> circlPtr = std::make_shared<strashko::Circle>(circle2);
    matrix.add(rectPtr);
    matrix.add(circlPtr);
    matrix.addElementsFromCompSh(compSh);

    BOOST_REQUIRE_EQUAL(matrix[0][2].getFrameRect().pos.x, rectangle2.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(matrix[0][3].getFrameRect().pos.y, circle2.getFrameRect().pos.y);
    BOOST_REQUIRE_THROW(matrix[3][0], std::out_of_range);
    BOOST_REQUIRE_THROW(matrix[0][4], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(AssignmentMove)
  {
    strashko::Matrix matrix1;
    strashko::point_t centre{0.0, 0.0};
    strashko::Rectangle rectangle(centre, 2.0, 2.0);
    strashko::Circle circl(centre, 3.0);
    std::shared_ptr< strashko::Shape > rect = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circle = std::make_shared< strashko::Circle >(circl);
    strashko::Matrix matrix;
    matrix.add(rect);
    matrix.add(circle);

    strashko::Matrix matrix2;
    matrix2.add(rect);
    matrix2.add(circle);

    matrix1 = std::move(matrix);

    BOOST_CHECK_EQUAL(matrix1[0][0].getFrameRect().width, matrix2[0][0].getFrameRect().width);
    BOOST_CHECK_EQUAL(matrix1[1][0].getFrameRect().width, matrix2[1][0].getFrameRect().width);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructor)
  {
    strashko::point_t centre{0.0, 0.0};
    strashko::Rectangle rectangle(centre, 2.0, 2.0);
    strashko::Circle circl(centre, 3.0);
    std::shared_ptr< strashko::Shape > rect = std::make_shared< strashko::Rectangle >(rectangle);
    std::shared_ptr< strashko::Shape > circle = std::make_shared< strashko::Circle >(circl);
    strashko::Matrix matrix;
    matrix.add(rect);
    matrix.add(circle);

    strashko::Matrix matrix1;
    matrix1.add(rect);
    matrix1.add(circle);

    strashko::Matrix matrix2{ std::move(matrix) };

    BOOST_CHECK_EQUAL(matrix1[0][0].getFrameRect().width, matrix2[0][0].getFrameRect().width);
    BOOST_CHECK_EQUAL(matrix1[1][0].getFrameRect().width, matrix2[1][0].getFrameRect().width);
  }

BOOST_AUTO_TEST_SUITE_END()
