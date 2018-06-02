#define BOOST_TEST_MODULE Main

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(RectS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    sokolova::rectangle_t rectangleBefore;
    sokolova::point_t centre{3.0, -1.0};
    sokolova::point_t newpos{8.0, 5.0};
    sokolova::Rectangle rectangle(centre, 4.7, 1.3);
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
    sokolova::rectangle_t rectangleBefore;
    sokolova::point_t centre{3.0, -1.0};
    sokolova::Rectangle rectangle(centre, 4.7, 1.3);
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
    sokolova::point_t centre{4.2, 6.4};
    sokolova::Rectangle rectangle(centre, 3.2, 1.0);
    areaBefore = rectangle.getArea();
    rectangle.scale(0.5);
    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBefore * 0.5 * 0.5, EPS);
   }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_90_Test_Rect)
  {
    sokolova::point_t centre{3.5, -80.2};
    sokolova::Rectangle rectangle(centre, 15.8, 20.4);
    rectangle.rotate(90);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, 20.4);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 15.8, EPS);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, centre.x);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, centre.y);
  }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_45_Test_Rect)
  {
    sokolova::point_t centre{1.0, 1.0};
    double w = sqrt(2.0);
    double h = sqrt(2.0);
    sokolova::Rectangle rectangle(centre, w, h);
    rectangle.rotate(45);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width * w, 2.8284, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height * h, 2.8284, EPS);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.x, centre.x);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().pos.y, centre.y);
  }

  BOOST_AUTO_TEST_CASE(rotate)
  {
    sokolova::Rectangle rectangle({4.0, 3.0}, 4.0, 2.0);
    for (int i = -90; i < 91; ++i) {
      sokolova::Rectangle rectangle1(rectangle);
      rectangle.rotate(i);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, rectangle1.getFrameRect().pos.x, EPS);
      BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, rectangle1.getFrameRect().pos.y, EPS);
      BOOST_CHECK_CLOSE(rectangle.getArea(), rectangle1.getArea(), EPS);
    }
  }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    sokolova::point_t centre{0.0, 0.0};

    BOOST_CHECK_THROW(sokolova::Rectangle rectangle(centre, -2.7, 3.1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    sokolova::point_t centre{0.0, 0.0};
    sokolova::Rectangle rectangle(centre, 4.2, 3.3);
    BOOST_CHECK_THROW(rectangle.scale(-4.8), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircS)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    double areaBefore;
    sokolova::rectangle_t circleBefore;
    sokolova::point_t centre{3.0, -1.0};
    sokolova::point_t newpos{8.0, 5.0};
    sokolova::Circle circle(centre, 2.1);
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
    sokolova::rectangle_t circleBefore;
    sokolova::point_t centre{3.0, -1.0};
    sokolova::Circle circle(centre, 1.3);
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
    sokolova::point_t centre{4.2, 6.4};
    sokolova::Circle circle(centre, 1.0);
    areaBefore = circle.getArea();
    circle.scale(0.5);
    BOOST_CHECK_CLOSE(circle.getArea(), areaBefore * 0.5 * 0.5, EPS);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValue)
  {
    sokolova::point_t centre{0.0, 0.0};
    BOOST_CHECK_THROW(sokolova::Circle circle(centre, -2.7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    sokolova::point_t centre{0.0, 0.0};
    sokolova::Circle circle(centre, 4.2);
    BOOST_CHECK_THROW(circle.scale(-4.8), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_Test)
  BOOST_AUTO_TEST_CASE(CompareMoveToPoint)
  {
    sokolova::point_t centre{3.0, -1.0};
    sokolova::point_t centre_c{5.1, 2.0};
    sokolova::point_t newpos{8.0, 5.0};
    sokolova::Rectangle rectangle(centre, 11.7, 9.3);
    sokolova::Circle circle(centre_c, 3.5);
    std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
    std::shared_ptr< sokolova::Shape > circlePtr = std::make_shared< sokolova::Circle >(circle);
    sokolova::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    sokolova::rectangle_t rect = comp.getFrameRect();
    comp.move(newpos);

    BOOST_CHECK_CLOSE(comp.getArea(), rectangle.getArea() + circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(rect.height, comp.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(rect.width, comp.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(CompareMoveToXY)
  {
    sokolova::point_t centre{3.0, -1.0};
    sokolova::point_t centre_c{5.1, 2.0};
    sokolova::Rectangle rectangle(centre, 10.7, 8.3);
    sokolova::Circle circle(centre_c, 3.5);
    std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
    std::shared_ptr< sokolova::Shape > circlePtr = std::make_shared< sokolova::Circle >(circle);
    sokolova::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    sokolova::rectangle_t rect = comp.getFrameRect();
    comp.move(1.44, 3.1);

    BOOST_CHECK_CLOSE(comp.getArea(), rectangle.getArea() + circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(rect.height, comp.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(rect.width, comp.getFrameRect().width, EPS);
  }

  BOOST_AUTO_TEST_CASE(EnlargementOfArea)
  {
    sokolova::point_t centre{4.2, 6.4};
    sokolova::point_t centre_c{5.1, 2.0};
    sokolova::Rectangle rectangle(centre, 10.0, 10.0);
    sokolova::Circle circle(centre_c, 5);
    std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
    std::shared_ptr< sokolova::Shape > circlePtr = std::make_shared< sokolova::Circle >(circle);
    sokolova::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    sokolova::rectangle_t rect = comp.getFrameRect();
    comp.scale(0.5);
    BOOST_CHECK_CLOSE(comp.getArea(), (rectangle.getArea() + circle.getArea()) * 0.5 * 0.5, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, rect.height * 0.5, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, rect.width * 0.5, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, rect.pos.x, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, rect.pos.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(RemoveTest)
  {
    sokolova::point_t centre{6.0, 2.5};
    sokolova::point_t centre_c{3.5, 1.8};
    sokolova::Rectangle rectangle(centre, 6.0, 3.0);
    sokolova::Circle circle(centre_c, 3.6);
    std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
    std::shared_ptr< sokolova::Shape > circlePtr = std::make_shared< sokolova::Circle >(circle);
    sokolova::CompositeShape comp(circlePtr);
    comp.addShape(rectPtr);
    comp.removeShape(1);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(comp.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
    BOOST_REQUIRE_EQUAL(comp.getArea(), rectangle.getArea());
    BOOST_REQUIRE_EQUAL(comp.getCount(), 1);
  }

  BOOST_AUTO_TEST_CASE(CorrectnessOfDelete)
   {
     sokolova::point_t centre{0.0, 2.5};
     sokolova::point_t centre_c{3.5, 1.8};
     sokolova::Rectangle rectangle(centre, 6.0, 3.0);
     sokolova::Circle circle(centre_c, 3.6);
     std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
     std::shared_ptr< sokolova::Shape > circlePtr = std::make_shared< sokolova::Circle >(circle);
     sokolova::CompositeShape comp(circlePtr);
     comp.addShape(rectPtr);
     comp.deleteAllShapes();
     BOOST_REQUIRE_EQUAL(comp.getCount(), 0);
   }

  BOOST_AUTO_TEST_CASE(IncorrectValueOfFactor)
  {
    sokolova::point_t centre{4.2, 6.4};
    sokolova::point_t centre_c{5.1, 2.0};
    sokolova::Rectangle rectangle(centre, 3.2, 1.0);
    sokolova::Circle circle(centre_c, 3.5);
    std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
    std::shared_ptr< sokolova::Shape > circlePtr = std::make_shared< sokolova::Circle >(circle);
    sokolova::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    BOOST_CHECK_THROW(comp.scale(-1.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectShapeNumberRemove)
  {
    sokolova::point_t centre{4.2, 6.4};
    sokolova::Rectangle rectangle(centre, 3.2, 1.0);
    std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
    sokolova::CompositeShape comp(rectPtr);
    BOOST_CHECK_THROW(comp.removeShape(2), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(IncorrectRemoveInCompositeShape)
  {
    sokolova::point_t centre{4.2, 6.4};
    sokolova::point_t centre_c{5.1, 2.0};
    sokolova::Rectangle rectangle(centre, 3.2, 1.0);
    sokolova::Circle circle(centre_c, 3.5);
    std::shared_ptr< sokolova::Shape > rectPtr = std::make_shared< sokolova::Rectangle >(rectangle);
    std::shared_ptr< sokolova::Shape > circlePtr = std::make_shared< sokolova::Circle >(circle);
    sokolova::CompositeShape comp(rectPtr);
    comp.addShape(circlePtr);
    comp.deleteAllShapes();
    BOOST_CHECK_THROW(comp.removeShape(1), std::out_of_range);
  }


  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    sokolova::point_t centre{4.1, 0.0};
    sokolova::Rectangle rectangle(centre, 7.0, 3.2);
    sokolova::Circle circ(centre, 2.2);
    std::shared_ptr< sokolova::Shape > rect = std::make_shared< sokolova::Rectangle >(rectangle);
    sokolova::CompositeShape compsh(rect);
    std::shared_ptr< sokolova::Shape > circle = std::make_shared< sokolova::Circle >(circ);
    compsh.addShape(circle);

    sokolova::CompositeShape comp{compsh};

    BOOST_CHECK_EQUAL(comp.getArea(), compsh.getArea());
    sokolova::rectangle_t rect1 = comp.getFrameRect();
    sokolova::rectangle_t rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructor)
  {
    sokolova::point_t centre{4.1, 0.0};
    sokolova::Rectangle rectangle(centre, 7.0, 3.2);
    sokolova::Circle circl(centre, 2.2);
    std::shared_ptr< sokolova::Shape > rect = std::make_shared< sokolova::Rectangle >(rectangle);
    sokolova::CompositeShape compsh(rect);

    std::shared_ptr< sokolova::Shape > circle = std::make_shared< sokolova::Circle >(circl);
    compsh.addShape(circle);

    double beforeMovingArea = compsh.getArea();
    sokolova::rectangle_t rect2 = compsh.getFrameRect();

    sokolova::CompositeShape comp{ std::move(compsh) };

    BOOST_CHECK_EQUAL(comp.getArea(), beforeMovingArea);
    sokolova::rectangle_t rect1 = comp.getFrameRect();
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
    sokolova::CompositeShape comp;
    sokolova::point_t centre{4.1, 0.0};
    sokolova::Rectangle rectangle(centre, 7.0, 3.2);
    sokolova::Circle circl(centre, 2.2);
    std::shared_ptr< sokolova::Shape > rect = std::make_shared< sokolova::Rectangle >(rectangle);
    sokolova::CompositeShape compsh(rect);

    std::shared_ptr< sokolova::Shape > circle = std::make_shared< sokolova::Circle >(circl);
    compsh.addShape(circle);

    comp = compsh;

    BOOST_CHECK_EQUAL(comp.getArea(), compsh.getArea());
    sokolova::rectangle_t rect1 = comp.getFrameRect();
    sokolova::rectangle_t rect2 = compsh.getFrameRect();
    BOOST_CHECK_EQUAL(rect1.width, rect2.width);
    BOOST_CHECK_EQUAL(rect1.height, rect2.height);
    BOOST_CHECK_EQUAL(rect1.pos.x, rect2.pos.x);
    BOOST_CHECK_EQUAL(rect1.pos.y, rect2.pos.y);
  }

  BOOST_AUTO_TEST_CASE(AssignmentMove)
  {
    sokolova::CompositeShape comp;
    sokolova::point_t centre{4.1, 0.0};
    sokolova::Rectangle rectangle(centre, 7.0, 3.2);
    sokolova::Circle circl(centre, 2.2);
    std::shared_ptr< sokolova::Shape > rect = std::make_shared< sokolova::Rectangle >(rectangle);
    sokolova::CompositeShape compsh(rect);

    std::shared_ptr< sokolova::Shape > circle = std::make_shared< sokolova::Circle >(circl);
    compsh.addShape(circle);

    double beforeMovingArea = compsh.getArea();
    sokolova::rectangle_t rect2 = compsh.getFrameRect();

    comp = std::move(compsh);

    BOOST_CHECK_EQUAL(comp.getArea(), beforeMovingArea);
    sokolova::rectangle_t rect1 = comp.getFrameRect();
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
    sokolova::point_t centre{0.0, 3.8};
    sokolova::Rectangle rectangle(centre, 5.7, 8.1);
    std::shared_ptr< sokolova::Shape > rectanglePtr = std::make_shared< sokolova::Rectangle >(rectangle);
    sokolova::CompositeShape comp(rectanglePtr);
    BOOST_CHECK_THROW(comp[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_90_Test_CS)
  {
    sokolova::Rectangle rectangle({2.0, 2.0}, 2.0, 2.0);
    sokolova::Rectangle rectangle2({4.0, 2.0}, 2.0, 2.0);
    std::shared_ptr<sokolova::Shape> rect1 = std::make_shared<sokolova::Rectangle>(rectangle);
    std::shared_ptr<sokolova::Shape> rect2 = std::make_shared<sokolova::Rectangle>(rectangle2);
    sokolova::CompositeShape compositeShape(rect1);
    compositeShape.addShape(rect2);
    sokolova::CompositeShape compsh = compositeShape;
    compositeShape.rotate(90);


    BOOST_CHECK_EQUAL(compositeShape.getArea(), compsh.getArea());
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.x, compsh.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.y, compsh.getFrameRect().pos.y);

    BOOST_CHECK_EQUAL(compositeShape[1]->getFrameRect().pos.x, 3.0);
    BOOST_CHECK_EQUAL(compositeShape[1]->getFrameRect().pos.y, 3.0);
    BOOST_CHECK_EQUAL(compositeShape[0]->getFrameRect().pos.x, 3.0);
    BOOST_CHECK_EQUAL(compositeShape[0]->getFrameRect().pos.y, 1.0);
  }

  BOOST_AUTO_TEST_CASE(Change_FrameRect_Rotate_45_Test_CS)
  {

    sokolova::point_t centre{3.0, 8.55};
    sokolova::point_t centre_c{11.0, 71.3};
    sokolova::point_t centre_r{-5.6, -4.7};
    sokolova::Rectangle rectangle(centre, 18.0, 7.0);
    sokolova::Circle circle(centre_c, 20.1);
    sokolova::Rectangle rect(centre_r, 4.8, 5.8);
    std::shared_ptr<sokolova::Shape> rectanglePtr = std::make_shared<sokolova::Rectangle>(rectangle);
    std::shared_ptr<sokolova::Shape> circlePtr = std::make_shared<sokolova::Circle>(circle);
    std::shared_ptr<sokolova::Shape> rectPtr = std::make_shared<sokolova::Rectangle>(rect);
    sokolova::CompositeShape compositeShape(rectanglePtr);
    compositeShape.addShape(circlePtr);
    compositeShape.addShape(rectPtr);
    sokolova::CompositeShape compsh = compositeShape;
    compositeShape.rotate(45);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.x, compsh.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(compositeShape.getFrameRect().pos.y, compsh.getFrameRect().pos.y);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

  BOOST_AUTO_TEST_CASE(addElementsFromCompSh)
  {
    sokolova::point_t centre_r1{2.8, 3.0};
    sokolova::Rectangle rectangle1(centre_r1, 5.8, 7.2);
    sokolova::point_t centre_c{0.0, -4.9};
    sokolova::Circle circle1(centre_c, 2.0);
    sokolova::point_t centre_r2{-8.9, -12.6};
    sokolova::Rectangle rectangle2(centre_r2, 24.03, 14.5);
    std::shared_ptr<sokolova::Shape> rectanglePtr = std::make_shared<sokolova::Rectangle>(rectangle1);
    std::shared_ptr<sokolova::Shape> circlePtr = std::make_shared<sokolova::Circle>(circle1);
    std::shared_ptr<sokolova::Shape> rectPtr = std::make_shared<sokolova::Rectangle>(rectangle2);
    sokolova::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);
    compSh.addShape(rectPtr);

    sokolova::Matrix matrix;
    matrix.addElementsFromCompSh(compSh);
    sokolova::rectangle_t FrameRectangle[3];
    FrameRectangle[0] = rectangle1.getFrameRect();
    FrameRectangle[1] = circle1.getFrameRect();
    FrameRectangle[2] = rectangle2.getFrameRect();

    BOOST_CHECK_EQUAL(matrix.getLayerCount(), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), 2);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(1), 1);
    for (int i = 0; i < matrix.getLayerCount(); ++i) {
      for (int j = 0; j < matrix.getLayerSize(i); ++j) {
        sokolova:: rectangle_t rectangle = matrix[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, FrameRectangle[i * 2 + j].pos.x, EPS);
        BOOST_CHECK_CLOSE(rectangle.pos.y, FrameRectangle[i * 2 + j].pos.y, EPS);
        BOOST_CHECK_CLOSE(rectangle.width, FrameRectangle[i * 2 + j].width, EPS);
        BOOST_CHECK_CLOSE(rectangle.height, FrameRectangle[i * 2 + j].height, EPS);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(add)
  {
    sokolova::point_t centre_r1{3.0, -3.0};
    sokolova::Rectangle rectangle1(centre_r1, 4.0, 2.0);
    sokolova::point_t centre_c{7.0, -3.0};
    sokolova::Circle circle1(centre_c, 1.0);
    std::shared_ptr<sokolova::Shape> rectanglePtr = std::make_shared<sokolova::Rectangle>(rectangle1);
    std::shared_ptr<sokolova::Shape> circlePtr = std::make_shared<sokolova::Circle>(circle1);

    sokolova::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);
    sokolova::point_t centre_r2{2.0, 1.0};
    sokolova::Rectangle rectangle2(centre_r2, 2.0, 4.0);
    sokolova::point_t centre_c2{5.0, 3.0};
    sokolova::Circle circle2(centre_c2, 1.0);
    std::shared_ptr<sokolova::Shape> circ2 = std::make_shared<sokolova::Circle>(circle2);
    std::shared_ptr<sokolova::Shape> rect2 = std::make_shared<sokolova::Rectangle>(rectangle2);

    sokolova::Matrix matrix;
    matrix.addElementsFromCompSh(compSh);
    matrix.add(rect2);
    matrix.add(circ2);
    matrix.addElementsFromCompSh(compSh);

    sokolova::rectangle_t FrameRectangle[6];
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
        sokolova::rectangle_t rectangle = matrix[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, FrameRectangle[i * 4 + j].pos.x, EPS);
        BOOST_CHECK_CLOSE(rectangle.pos.y, FrameRectangle[i * 4 + j].pos.y, EPS);
        BOOST_CHECK_CLOSE(rectangle.width, FrameRectangle[i * 4 + j].width, EPS);
        BOOST_CHECK_CLOSE(rectangle.height, FrameRectangle[i * 4 + j].height, EPS);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(Constructor_Copy)
  {
    sokolova::point_t centre_r1{2.8, 3.0};
    sokolova::Rectangle rectangle1(centre_r1, 5.8, 7.2);
    sokolova::point_t centre_c{0.0, -4.9};
    sokolova::Circle circle1(centre_c, 2.0);
    std::shared_ptr<sokolova::Shape> rectanglePtr = std::make_shared<sokolova::Rectangle>(rectangle1);
    std::shared_ptr<sokolova::Shape> circlePtr = std::make_shared<sokolova::Circle>(circle1);
    sokolova::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);

    sokolova::Matrix matrix;
    sokolova::point_t centre_r2{0.0, 0.0};
    sokolova::Rectangle rectangle2(centre_r2, 8.1, 3.5);
    sokolova::point_t centre_c2{-6.4, 3.5};
    sokolova::Circle circle2(centre_c2, 5.9);
    std::shared_ptr<sokolova::Shape> circ2 = std::make_shared<sokolova::Circle>(circle2);
    std::shared_ptr<sokolova::Shape> rect2 = std::make_shared<sokolova::Rectangle>(rectangle2);
    matrix.add(rect2);
    matrix.add(circ2);
    matrix.addElementsFromCompSh(compSh);

    sokolova::Matrix matrix1(matrix);
    BOOST_CHECK_EQUAL(matrix.getLayerCount(), matrix1.getLayerCount());
    for (int i = 0; i < matrix.getLayerCount(); ++i) {
      BOOST_CHECK_EQUAL(matrix.getLayerSize(i), matrix1.getLayerSize(i));
      for (int j = 0; j < matrix.getLayerSize(i); ++j) {
        sokolova::rectangle_t rectangle = matrix[i][j].getFrameRect();
        sokolova::rectangle_t rectangle1 = matrix1[i][j].getFrameRect();
        BOOST_CHECK_CLOSE(rectangle.pos.x, rectangle1.pos.x, EPS);
        BOOST_CHECK_CLOSE(rectangle.pos.y, rectangle1.pos.y, EPS);
        BOOST_CHECK_CLOSE(rectangle.width, rectangle1.width, EPS);
        BOOST_CHECK_CLOSE(rectangle.height, rectangle1.height, EPS);
      }
    }
  }

  BOOST_AUTO_TEST_CASE(MatrixRotate)
  {
    sokolova::Rectangle rectangle1({0.0, 1.0}, 2.0, 2.0);
    sokolova::Rectangle rectangle2({3.0, 1.0}, 2.0, 2.0);
    std::shared_ptr<sokolova::Shape> rect1 = std::make_shared<sokolova::Rectangle>(rectangle1);
    std::shared_ptr<sokolova::Shape> rect2 = std::make_shared<sokolova::Rectangle>(rectangle2);
    sokolova::CompositeShape compSh(rect1);
    compSh.addShape(rect2);

    sokolova::Matrix matrix;
    matrix.addElementsFromCompSh(compSh);

    compSh.rotate(45);
    sokolova::Matrix matrix2;
    matrix2.addElementsFromCompSh(compSh);
    BOOST_CHECK_EQUAL(matrix.getLayerSize(0), 2);
    BOOST_CHECK_EQUAL(matrix2.getLayerSize(0), 1);
  }

  BOOST_AUTO_TEST_CASE(Taking_by_index)//operator[]
   {
    sokolova::point_t centre_r1{3.0, -3.0};
    sokolova::Rectangle rectangle1(centre_r1, 4.0, 2.0);
    sokolova::point_t centre_c{7.0, -3.0};
    sokolova::Circle circle1(centre_c, 1.0);
    std::shared_ptr<sokolova::Shape> rectanglePtr = std::make_shared<sokolova::Rectangle>(rectangle1);
    std::shared_ptr<sokolova::Shape> circlePtr = std::make_shared<sokolova::Circle>(circle1);
    sokolova::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);

    sokolova::Matrix matrix;
    sokolova::point_t centre_r2{2.0, 1.0};
    sokolova::Rectangle rectangle2(centre_r2, 2.0, 4.0);
    sokolova::point_t centre_c2{5.0, 3.0};
    sokolova::Circle circle2(centre_c2, 1.0);
    std::shared_ptr<sokolova::Shape> circ2 = std::make_shared<sokolova::Circle>(circle2);
    std::shared_ptr<sokolova::Shape> rect2 = std::make_shared<sokolova::Rectangle>(rectangle2);
    matrix.addElementsFromCompSh(compSh);
    matrix.add(rect2);
    matrix.add(circ2);
    matrix.addElementsFromCompSh(compSh);

    BOOST_REQUIRE_EQUAL(matrix[0][2].getFrameRect().pos.x, rectangle2.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(matrix[0][3].getFrameRect().pos.y, circle2.getFrameRect().pos.y);
    BOOST_REQUIRE_THROW(matrix[3][0], std::out_of_range);
    BOOST_REQUIRE_THROW(matrix[0][4], std::out_of_range);
   }

BOOST_AUTO_TEST_SUITE_END()
