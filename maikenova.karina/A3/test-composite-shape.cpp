#include <boost/test/unit_test.hpp>
#include <cmath>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(Composite_Shape)

const double epsilon = 0.00001;

  BOOST_AUTO_TEST_CASE(CompShape_DefConstr)
  {
    maikenova::CompositeShape compShape;
    BOOST_CHECK_EQUAL(compShape.getAmount(), size_t(0));
    BOOST_CHECK_CLOSE(compShape.getPos().x, 0, epsilon);
    BOOST_CHECK_CLOSE(compShape.getPos().y, 0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(CompShape_CopyConstr)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({1.0, 1.0}, 2);
    maikenova::Rectangle myRectangle({10.0, 10.0}, 10.0, 15.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    maikenova::CompositeShape compShape(testShape);
    BOOST_CHECK_EQUAL(compShape.getAmount(), testShape.getAmount());
    BOOST_CHECK_CLOSE(compShape.getPos().x, testShape.getPos().x, epsilon);
    BOOST_CHECK_CLOSE(compShape.getPos().y, testShape.getPos().y, epsilon);
    BOOST_CHECK_EQUAL(compShape[0], testShape[0]);
    BOOST_CHECK_EQUAL(compShape[1], testShape[1]);
  }

  BOOST_AUTO_TEST_CASE(CompShape_MoveConstr)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({1.0, 1.0}, 5);
    maikenova::Rectangle myRectangle({10.0, 10.0}, 10.0, 15.0);

    testShape.pushBack(&myCircle);
    testShape.pushBack(&myRectangle);
    maikenova::point_t testPos = testShape.getPos();

    maikenova::CompositeShape compShape(std::move(testShape));

    BOOST_CHECK_EQUAL(compShape.getAmount(), size_t(2));
    BOOST_CHECK_EQUAL(compShape.getPos().x, testPos.x);
    BOOST_CHECK_EQUAL(compShape.getPos().y, testPos.y);
    BOOST_CHECK_EQUAL(compShape[0], &myCircle);
    BOOST_CHECK_EQUAL(compShape[1], &myRectangle);

    BOOST_CHECK_EQUAL(testShape.getAmount(), size_t(0));
    BOOST_CHECK_CLOSE(testShape.getPos().x, 0, epsilon);
    BOOST_CHECK_CLOSE(testShape.getPos().y, 0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Square_Brackets_Operator)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    BOOST_CHECK_EQUAL(& myCircle, testShape[0]);
    BOOST_CHECK_EQUAL(& myRectangle, testShape[1]);
    BOOST_CHECK_THROW(testShape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Copy_Operator)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({1.0, 1.0}, 5.0);
    maikenova::Rectangle myRectangle({10.0, 10.0}, 10.0, 15.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    maikenova::CompositeShape compShape;

    compShape = testShape;
    BOOST_CHECK_EQUAL(compShape.getAmount(), testShape.getAmount());
    BOOST_CHECK_CLOSE(compShape.getPos().x, testShape.getPos().x, epsilon);
    BOOST_CHECK_CLOSE(compShape.getPos().y, testShape.getPos().y, epsilon);
    BOOST_CHECK_EQUAL(compShape[0], testShape[0]);
    BOOST_CHECK_EQUAL(compShape[1], testShape[1]);
  }

  BOOST_AUTO_TEST_CASE(Move_Operator)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);
    maikenova::point_t testPos = testShape.getPos();

    maikenova::CompositeShape compShape;

    compShape = std::move(testShape);

    BOOST_CHECK_EQUAL(compShape.getAmount(), size_t(2));
    BOOST_CHECK_CLOSE(compShape.getPos().x, testPos.x, epsilon);
    BOOST_CHECK_CLOSE(compShape.getPos().y, testPos.y, epsilon);
    BOOST_CHECK_EQUAL(compShape[0], & myCircle);
    BOOST_CHECK_EQUAL(compShape[1], & myRectangle);

    BOOST_CHECK_EQUAL(testShape.getAmount(), size_t(0));
    BOOST_CHECK_CLOSE(testShape.getPos().x, 0, epsilon);
    BOOST_CHECK_CLOSE(testShape.getPos().y, 2, epsilon);
  }

  BOOST_AUTO_TEST_CASE(pushBack_Test)
  {
    maikenova::CompositeShape testShape;
    maikenova::Shape * Shape = nullptr;

    BOOST_CHECK_THROW(testShape.pushBack(Shape), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getInfo_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    BOOST_CHECK_CLOSE(testShape.getPos().x, 0, epsilon);
    BOOST_CHECK_CLOSE(testShape.getPos().y, 2, epsilon);
    BOOST_CHECK_EQUAL(testShape.getAmount(), size_t(2));
  }

  BOOST_AUTO_TEST_CASE(Move_Shift_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    maikenova::point_t posBefore = testShape.getPos();
    const double frameWBefore = testShape.getFrameRect().width;
    const double frameHBefore = testShape.getFrameRect().height;
    const double areaBefore = testShape.getArea();

    testShape.move(10.0, 5.0);

    BOOST_CHECK_CLOSE(testShape.getPos().x, (posBefore.x + 10.0), epsilon);
    BOOST_CHECK_CLOSE(testShape.getPos().y, (posBefore.y + 5.0), epsilon);

    double frameW = testShape.getFrameRect().width;
    double frameH = testShape.getFrameRect().height;
    double area = testShape.getArea();

    BOOST_CHECK_CLOSE(frameWBefore, frameW, epsilon);
    BOOST_CHECK_CLOSE(frameHBefore, frameH, epsilon);
    BOOST_CHECK_CLOSE(areaBefore, area, epsilon);

    testShape.move(-10.0, -5.0);

    BOOST_CHECK_CLOSE(testShape.getPos().x, posBefore.x, epsilon);
    BOOST_CHECK_CLOSE(testShape.getPos().y, posBefore.y, epsilon);

    frameW = testShape.getFrameRect().width;
    frameH = testShape.getFrameRect().height;
    area = testShape.getArea();

    BOOST_CHECK_CLOSE(frameWBefore, frameW, epsilon);
    BOOST_CHECK_CLOSE(frameHBefore, frameH, epsilon);
    BOOST_CHECK_CLOSE(areaBefore, area, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Move_toPoint_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    maikenova::point_t posBefore = testShape.getPos();
    const double frameWBefore = testShape.getFrameRect().width;
    const double frameHBefore = testShape.getFrameRect().height;
    const double areaBefore = testShape.getArea();

    maikenova::point_t newPos{15.0, 19.0};
    testShape.move(newPos);

    const double dx = newPos.x - posBefore.x;
    const double dy = newPos.y - posBefore.y;
    BOOST_CHECK_CLOSE(testShape.getPos().x, (posBefore.x + dx), epsilon);
    BOOST_CHECK_CLOSE(testShape.getPos().y, (posBefore.y + dy), epsilon);

    double frameW = testShape.getFrameRect().width;
    double frameH = testShape.getFrameRect().height;
    double area = testShape.getArea();

    BOOST_CHECK_CLOSE(frameWBefore, frameW, epsilon);
    BOOST_CHECK_CLOSE(frameHBefore, frameH, epsilon);
    BOOST_CHECK_CLOSE(areaBefore, area, epsilon);

    testShape.move(posBefore);

    BOOST_CHECK_CLOSE(testShape.getPos().x, posBefore.x, epsilon);
    BOOST_CHECK_CLOSE(testShape.getPos().y, posBefore.y, epsilon);

    frameW = testShape.getFrameRect().width;
    frameH = testShape.getFrameRect().height;
    area = testShape.getArea();

    BOOST_CHECK_CLOSE(frameWBefore, frameW, epsilon);
    BOOST_CHECK_CLOSE(frameHBefore, frameH, epsilon);
    BOOST_CHECK_CLOSE(areaBefore, area, epsilon);
  }

  BOOST_AUTO_TEST_CASE(scale_Invalid_Argument_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({1.0, 1.0}, 5.0);
    maikenova::Rectangle myRectangle({10.0, 10.0}, 10.0, 15.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    BOOST_CHECK_THROW(testShape.scale(-5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Position_after_scaling_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    testShape.scale(2);

    BOOST_CHECK_CLOSE(testShape[0]->getPos().x, -6, epsilon);
    BOOST_CHECK_CLOSE(testShape[0]->getPos().y, 2, epsilon);

    BOOST_CHECK_CLOSE(testShape[1]->getPos().x, 4, epsilon);
    BOOST_CHECK_CLOSE(testShape[1]->getPos().y, 2, epsilon);
  }

  BOOST_AUTO_TEST_CASE(getArea_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    const double area = M_PI+16;
    BOOST_CHECK_CLOSE(testShape.getArea(), area, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Area_after_scaling_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({1.0, 1.0}, 5.0);
    maikenova::Rectangle myRectangle({10.0, 10.0}, 10.0, 15.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    const double areaBefore = testShape.getArea();
    const double k = 5;
    testShape.scale(k);
    const double area = testShape.getArea();

    BOOST_CHECK_CLOSE(areaBefore*k*k, area, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Proportion_after_scaling_Test)
  {
    maikenova::CompositeShape testShape;

    maikenova::Circle myCircle({-3.0, 2.0}, 1.0);
    maikenova::Rectangle myRectangle({2.0, 2.0}, 4.0, 4.0);

    testShape.pushBack(& myCircle);
    testShape.pushBack(& myRectangle);

    maikenova::point_t posBefore = testShape.getPos();
    const double widthBefore = testShape.getFrameRect().width;
    const double heightBefore = testShape.getFrameRect().height;
    const double k = 7;

    testShape.scale(k);

    maikenova::point_t pos = testShape.getPos();
    const double width = testShape.getFrameRect().width;
    const double height = testShape.getFrameRect().height;

    BOOST_CHECK_CLOSE(widthBefore, width/k, epsilon);
    BOOST_CHECK_CLOSE(heightBefore, height/k, epsilon);
    BOOST_CHECK_CLOSE(posBefore.x, pos.x, epsilon);
    BOOST_CHECK_CLOSE(posBefore.y, pos.y, epsilon);
  }

  BOOST_AUTO_TEST_CASE(Empty_frame_Test)
  {
    maikenova::CompositeShape testShape;
    BOOST_CHECK_THROW(testShape.getFrameRect(), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
