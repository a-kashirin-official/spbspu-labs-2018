#define BOOST_TEST_MODULE MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace sokolova;
const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    point_t centre{2.0, 4.0};
    Rectangle rect(centre, 5.0, 6.0);
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    point_t newpos{5.0, 2.0};
    rect.move(newpos);
    BOOST_CHECK_CLOSE(areaBeforeMoving, rect.getArea(), EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.width, rect.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.height, rect.getFrameRect().height, EPS);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    point_t centre{2.0,4.0};
    Rectangle rect(centre, 5.0, 6.0) ;
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    rect.move(-10.0, 50.0);
    BOOST_CHECK_CLOSE(areaBeforeMoving, rect.getArea(), EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.width, rect.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.height, rect.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, -8.0, EPS);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, 54.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    point_t centre{2.0, 4.0};
    Rectangle rect(centre, 5.0, 6.0);
    double areaBeforeScaling = rect.getArea();
    const double factor = 3.3;

    rect.scale(factor);
    BOOST_CHECK_CLOSE(factor * factor * areaBeforeScaling, rect.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    point_t centre{10.0, 20.0};
    BOOST_CHECK_THROW( Rectangle rect(centre, 10.0, -15.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    point_t centre{2.0, 4.0};
    Rectangle rect(centre, 5.0, 6.0);
    BOOST_CHECK_THROW( rect.scale(-1.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();

    point_t newpos{15.0, 20.0};
    circle.move(newpos);
    BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.width/2, circle.getFrameRect().width/2, EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.height/2, circle.getFrameRect().height/2, EPS);

  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    rectangle_t rectBeforeMoving = circle.getFrameRect();
    double areaBeforeMoving = circle.getArea();

    circle.move(-10.0, 50.0);
    BOOST_CHECK_CLOSE(areaBeforeMoving, circle.getArea(), EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.width/2, circle.getFrameRect().width/2, EPS);
    BOOST_CHECK_CLOSE(rectBeforeMoving.height/2, circle.getFrameRect().height/2, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, -5.0, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 53.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    double areaBeforeScaling = circle.getArea();
    const double factor = 3.3;

    circle.scale(factor);
    BOOST_CHECK_CLOSE(factor * factor * areaBeforeScaling, circle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    point_t centre{10.0, 20.0};
    BOOST_CHECK_THROW(Circle circle(centre, -15.0), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    point_t centre{5.0, 3.0};
    Circle circle(centre, 22.0);
    BOOST_CHECK_THROW( circle.scale(-1.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testsOfCompShape)

  BOOST_AUTO_TEST_CASE(invalidConstructor)
  {
    std::shared_ptr<Shape> testRect = nullptr;
    BOOST_CHECK_THROW(CompositeShape testComp(testRect), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(copyConstructor)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    CompositeShape newComp(testComp);
    BOOST_CHECK_EQUAL(testComp[0], newComp[0]);
    BOOST_CHECK_EQUAL(testComp[1], newComp[1]);
  }

  BOOST_AUTO_TEST_CASE(moveConstructor)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    CompositeShape newComp(std::move(testComp));
    BOOST_CHECK_EQUAL(newComp[0], ptr1);
    BOOST_CHECK_EQUAL(newComp[1], ptr2);
  }

  BOOST_AUTO_TEST_CASE(copyOperator)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    std::shared_ptr< Shape > ptr3(new Rectangle({36.0, 36.0}, 6.0, 16.0));
    std::shared_ptr< Shape > ptr4(new Circle({3.6, 2.6}, 106));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    CompositeShape newComp;
    newComp.addShape(ptr3);
    newComp.addShape(ptr4);
    newComp = testComp;
    BOOST_CHECK_EQUAL(newComp[0],testComp[0]);
    BOOST_CHECK_EQUAL(newComp[1],testComp[1]);
  }

  BOOST_AUTO_TEST_CASE(moveOperator)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    std::shared_ptr< Shape > ptr3(new Rectangle({36.0, 36.0}, 6.0, 16.0));
    std::shared_ptr< Shape > ptr4(new Circle({3.6, 2.6}, 106));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    CompositeShape newComp;
    newComp.addShape(ptr3);
    newComp.addShape(ptr4);
    newComp = std::move(testComp);
    BOOST_CHECK_EQUAL(newComp[0],ptr1);
    BOOST_CHECK_EQUAL(newComp[1],ptr2);
  }

  BOOST_AUTO_TEST_CASE(GeneralPosition)
  {
    point_t position = {2.0, 4.0};
    double width = 10.0, height = 10.0;
    std::shared_ptr<Shape> testRect =
      std::make_shared<Rectangle>(Rectangle( position, width, height));
    CompositeShape testComp(testRect);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.x, position.x, EPS);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.y, position.y, EPS);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().width, width, EPS);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().height, height, EPS);
  }

  BOOST_AUTO_TEST_CASE(moveToNewPosition)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    double fstHeight = testComp.getFrameRect().height;
    double fstWidth = testComp.getFrameRect().width;
    double fstArea = testComp.getArea();
    point_t positionAfterMoving = {5.0, 5.0};
    testComp.move(positionAfterMoving);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.x, positionAfterMoving.x, EPS);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.y, positionAfterMoving.y, EPS);
    BOOST_CHECK_EQUAL(fstHeight, testComp.getFrameRect().height);
    BOOST_CHECK_EQUAL(fstWidth, testComp.getFrameRect().width);
    BOOST_CHECK_EQUAL(fstArea, testComp.getArea());
  }

  BOOST_AUTO_TEST_CASE(moveByDxAndDy)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    double fstHeight = testComp.getFrameRect().height;
    double fstWidth = testComp.getFrameRect().width;
    double fstArea = testComp.getArea();
    point_t positionAfterMoving = {testComp.getFrameRect().pos.x + 3.0,testComp.getFrameRect().pos.y + 5.0};
    testComp.move(3.0,5.0);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.x, positionAfterMoving.x, EPS);
    BOOST_CHECK_CLOSE(testComp.getFrameRect().pos.y, positionAfterMoving.y, EPS);
    BOOST_CHECK_EQUAL(fstHeight, testComp.getFrameRect().height);
    BOOST_CHECK_EQUAL(fstWidth, testComp.getFrameRect().width);
    BOOST_CHECK_EQUAL(fstArea, testComp.getArea());
  }

  BOOST_AUTO_TEST_CASE(scaling)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    double fstPosX = testComp.getFrameRect().pos.x;
    double fstPosY = testComp.getFrameRect().pos.y;
    point_t fstPosRect =  ptr1 ->getFrameRect().pos;
    point_t fstPosCircle = ptr2 ->getFrameRect().pos;
    double fstHeight = testComp.getFrameRect().height;
    double fstWidth = testComp.getFrameRect().width;
    double fstArea = testComp.getArea();
    testComp.scale(2.0);
    BOOST_CHECK_CLOSE(2.0 * 2.0 * fstArea, testComp.getArea(), EPS);
    BOOST_CHECK_CLOSE(2.0 * fstHeight, testComp.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(2.0 * fstWidth, testComp.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(fstPosX, testComp.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(fstPosY, testComp.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE(fstPosRect.x + (2.0-1.0) * (fstPosRect.x - fstPosX ) , ptr1 ->getFrameRect().pos.x , EPS);
    BOOST_CHECK_CLOSE(fstPosRect.y + (2.0-1.0) * (fstPosRect.y - fstPosY ) , ptr1 ->getFrameRect().pos.y , EPS);
    BOOST_CHECK_CLOSE(fstPosCircle.x + (2.0-1.0) * (fstPosCircle.x - fstPosX ) , ptr2 ->getFrameRect().pos.x , EPS);
    BOOST_CHECK_CLOSE(fstPosCircle.y + (2.0-1.0) * (fstPosCircle.y - fstPosY ) , ptr2 ->getFrameRect().pos.y , EPS);
  }

  BOOST_AUTO_TEST_CASE(invalidScaling)
  {
    std::shared_ptr< Shape > ptr1(new Rectangle({35.0, 35.0},5.0, 15.0));
    std::shared_ptr< Shape > ptr2(new Circle({3.0, 2.5}, 105));
    CompositeShape testComp;
    testComp.addShape(ptr1);
    testComp.addShape(ptr2);
    BOOST_CHECK_THROW(testComp.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
