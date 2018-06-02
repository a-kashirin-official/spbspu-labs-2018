#define BOOST_TEST_MODULE MAIN
#include <stdexcept>
#include <memory>
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
using namespace gremiachenskii;
using namespace std;


const double EPSILON = 1e-8;

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{{ 10.0, 10.0 }, 50.0, 30.0});
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{0.0, 0.0}, 5.0);

    CompositeShape testObject(rectPtr);
    testObject.addElement(circPtr);

    CompositeShape newTest(testObject);
    BOOST_CHECK_EQUAL(testObject[0], newTest[0]);
    BOOST_CHECK_EQUAL(testObject[1], newTest[1]);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructor)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ {30.0, 45.0}, 45.0, 65.0 });
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{0.0, 0.0}, 5.0);

    CompositeShape testObject( rectPtr );
    testObject.addElement( circPtr );
    CompositeShape newTest( move(testObject) );
    BOOST_CHECK_EQUAL( newTest[0], rectPtr );
    BOOST_CHECK_EQUAL( newTest[1], circPtr );

    size_t quantity = 2;
    BOOST_CHECK_EQUAL(newTest.getSize(), quantity);
  }

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ {56.0, 10.0}, 80.0, 10.0 });
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{0.0, 0.0}, 5.0);
    CompositeShape testObject( rectPtr );
    testObject.addElement( circPtr );

    double tmpHeight = testObject.getFrameRect().height;
    double tmpWidth = testObject.getFrameRect().width;
    double tmpArea = testObject.getArea();

    point_t newPos = { 5.0, 5.0 };

    testObject.move(newPos);

    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, newPos.x, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, newPos.y, EPSILON);
    BOOST_CHECK_CLOSE(tmpHeight, testObject.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, testObject.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(tmpArea, testObject.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ {10.0, 45.0}, 56.0, 5.0 });
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{0.0, 0.0}, 1.0);

    CompositeShape testObject(rectPtr);
    testObject.addElement(circPtr);

    double tmpHeight = testObject.getFrameRect().height;
    double tmpWidth = testObject.getFrameRect().width;
    double tmpArea = testObject.getArea();
    double dx = 10.0;
    double dy = 15.0;
    point_t pos = testObject.getFrameRect().pos;
    testObject.move(dx, dy);

    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, pos.x + dx, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, pos.y + dy, EPSILON);

    BOOST_CHECK_EQUAL(tmpHeight, testObject.getFrameRect().height);
    BOOST_CHECK_EQUAL(tmpWidth, testObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(tmpArea, testObject.getArea());
  }

  BOOST_AUTO_TEST_CASE(ScalingParameter)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ {10.0, 10.0}, 10.0, 8.0 });
    CompositeShape testObject( rectPtr );
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{0.0, 0.0}, 5.0);
    testObject.addElement( circPtr );
    BOOST_CHECK_THROW(testObject.scale(-2.0), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ {15.0, 19.0}, 5.0, 5.0 });
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{0.0, 0.0}, 5.0);
    CompositeShape testObject(rectPtr);
    testObject.addElement(circPtr);
    double tmpArea = testObject.getArea();
    testObject.scale(2.0);
    BOOST_CHECK_CLOSE(2.0 * 2.0 * tmpArea, testObject.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ScalingCoordinatesTest)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ {10.0, 10.0}, 5.0, 5.0 });
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{ 50.0, 50.0 }, 10.0);
    CompositeShape testObject(rectPtr);
    testObject.addElement(circPtr);

    double posX = testObject.getFrameRect().pos.x;
    double posY = testObject.getFrameRect().pos.y;

    testObject.scale(2.0);

    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, posX, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, posY, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AddingParameter)
  {
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ {15.0, 15.0}, 6.0, 3.0 });
    CompositeShape testObject(rectPtr);
    shared_ptr<Shape> circPtr = nullptr;
    BOOST_CHECK_THROW(testObject.addElement(circPtr), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Constructing)
  {
    shared_ptr<Shape> rectPtr = nullptr;
    BOOST_CHECK_THROW(CompositeShape testObject(rectPtr), invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Position)
  {
    point_t pos{ 10.0, 8.0 };
    double width = 15.0, height = 20.0;
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ pos, height, width });
    CompositeShape testObject(rectPtr);

    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, pos.x, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, pos.y, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().height, height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Area)
  {
    double width = 2.0, height = 1.0;
    point_t pos = {2.0, 4.0};
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(rectangle_t{ pos, height, width });

    double radius = 3.0;
    shared_ptr<Shape> circPtr = make_shared<Circle>(point_t{0.0, 0.0}, radius);
    CompositeShape testObject(rectPtr);
    testObject.addElement(circPtr);
    BOOST_CHECK_CLOSE(testObject.getArea(), width * height + M_PI * radius * radius, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
