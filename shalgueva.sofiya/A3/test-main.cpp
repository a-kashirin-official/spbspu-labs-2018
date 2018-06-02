#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"


const double EPSILON = 1e-8;

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{21.0, 10.0, {3.0, 7.0}});
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::point_t{0.0, 0.0}, 5.0);
    shalgueva::CompositeShape testObject(rectangle1);
    testObject.addShape(circle1);
    shalgueva::CompositeShape newTest(testObject);
    BOOST_CHECK_EQUAL(testObject[0], newTest[0]);
    BOOST_CHECK_EQUAL(testObject[1], newTest[1]);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructor)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{21.0, 10.0, {3.0, 7.0}});
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::point_t{0.0, 0.0}, 5.0);
    shalgueva::CompositeShape testObject(rectangle1);
    testObject.addShape(circle1);
    shalgueva::CompositeShape newTest(std::move(testObject));
    BOOST_CHECK_EQUAL(newTest[0], rectangle1);
    BOOST_CHECK_EQUAL(newTest[1], circle1);
    size_t quantity = 2;
    BOOST_CHECK_EQUAL(newTest.getLength(), quantity);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{21.0, 10.0, {3.0, 7.0}});
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::point_t{0.0, 0.0}, 5.0);
    shalgueva::CompositeShape testObject(rectangle1);
    testObject.addShape(circle1);
    double tmpHeight = testObject.getFrameRect().height;
    double tmpWidth = testObject.getFrameRect().width;
    double tmpArea = testObject.getArea();
    shalgueva::point_t positionAfterMoving = {5.0, 5.0};
    testObject.move(positionAfterMoving);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, positionAfterMoving.x, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, positionAfterMoving.y, EPSILON);
    BOOST_CHECK_EQUAL(tmpHeight, testObject.getFrameRect().height);
    BOOST_CHECK_EQUAL(tmpWidth, testObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(tmpArea, testObject.getArea());
    BOOST_CHECK_CLOSE(tmpHeight, testObject.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(tmpWidth, testObject.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(tmpArea, testObject.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveByAxes)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{2.0, 2.0, {2.0, 2.0}});
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::point_t{0.0, 0.0},1.0);
    shalgueva::CompositeShape testObject(rectangle1);
    testObject.addShape(circle1);
    double tmpHeight = testObject.getFrameRect().height;
    double tmpWidth = testObject.getFrameRect().width;
    double tmpArea = testObject.getArea();
    shalgueva::point_t positionAfterMoving = {4.0, 3.0};
    testObject.move(3.0, 2.0);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, positionAfterMoving.x, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, positionAfterMoving.y, EPSILON);
    BOOST_CHECK_EQUAL(tmpHeight, testObject.getFrameRect().height);
    BOOST_CHECK_EQUAL(tmpWidth, testObject.getFrameRect().width);
    BOOST_CHECK_EQUAL(tmpArea, testObject.getArea());
  }

  BOOST_AUTO_TEST_CASE(InvalidParametrsScaling)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{10.0, 10.0, {2.0, 4.0}});
    shalgueva::CompositeShape testObject(rectangle1);
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::point_t{0.0, 0.0},5.0);
    testObject.addShape(circle1);
    BOOST_CHECK_THROW(testObject.scale(-2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{10.0, 10.0, {2.0, 4.0}});
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::point_t{0.0, 0.0},5.0);
    shalgueva::CompositeShape testObject(rectangle1);
    testObject.addShape(circle1);
    double tmpArea = testObject.getArea();
    testObject.scale(2.0);
    BOOST_CHECK_CLOSE(2.0 * 2.0 * tmpArea, testObject.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentAdd)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{10.0, 10.0, {2.0, 4.0}});
    shalgueva::CompositeShape testObject(rectangle1);
    std::shared_ptr<shalgueva::Shape> circle1 = nullptr;
    BOOST_CHECK_THROW(testObject.addShape(circle1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentConstructorTest)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 = nullptr;
    BOOST_CHECK_THROW(shalgueva::CompositeShape testObject(rectangle1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvariantCoordinatesTest)
  {
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{10.0, 10.0, {2.0, 4.0}});
    shalgueva::CompositeShape testObject(rectangle1);
    double posX = testObject.getFrameRect().pos.x;
    double posY = testObject.getFrameRect().pos.y;
    testObject.scale(2.0);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, posX, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, posY, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(GeneralPosition)
  {
    shalgueva::point_t position = {2.0, 4.0};
    double width = 10.0, height = 10.0;
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{width, height, position});
    shalgueva::CompositeShape testObject(rectangle1);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.x, position.x, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().pos.y, position.y, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE(testObject.getFrameRect().height, height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CommonArea)
  {
    const double width = 2.0, height = 1.0;
    shalgueva::point_t position = {2.0, 4.0};
    std::shared_ptr<shalgueva::Shape> rectangle1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::rectangle_t{width, height, position});
    const double radius = 3.0;
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::point_t{0.0, 0.0},radius);
    shalgueva::CompositeShape testObject(rectangle1);
    testObject.addShape(circle1);
    BOOST_CHECK_CLOSE(testObject.getArea(), width * height + M_PI * radius * radius, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
