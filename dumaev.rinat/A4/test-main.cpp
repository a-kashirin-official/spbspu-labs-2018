#define BOOST_TEST_MODULE Main
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

const double EPSILON = 1e-4;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    dumaev::Rectangle rect({2, 3}, 1, 3);
    dumaev::rectangle_t frameRectBefore = rect.getFrameRect();
    double areaBefore = rect.getArea();

    rect.move({2, 5});

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, rect.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, rect.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    dumaev::Rectangle rect({1, 1}, 2, 4);
    dumaev::rectangle_t frameRectBefore = rect.getFrameRect();
    double areaBefore = rect.getArea();

    rect.move(2, 4);

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, rect.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, rect.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, rect.getArea());
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    dumaev::Rectangle rect({3, 3}, 5, 5);
    double areaBefore = rect.getArea();
    const double coefficient = 4;
    rect.scale(coefficient);

    BOOST_CHECK_CLOSE(coefficient * coefficient * areaBefore, rect.getArea(), EPSILON);
  }
  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( dumaev::Rectangle rectangle({1, 2}, 10, -15), std::invalid_argument);
    BOOST_CHECK_THROW( dumaev::Rectangle rectangle({1, 2}, -10, 15), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    dumaev::Rectangle rectangle({5, 6}, 3, 3);
    BOOST_CHECK_THROW( rectangle.scale(-15), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(FrameRectRotate)
  {
    dumaev::Rectangle rectangle({0,0}, 4, 2);
    rectangle.rotate(90);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 2, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 4, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    dumaev::Circle circle({2, 3}, 3);
    dumaev::rectangle_t frameRectBefore = circle.getFrameRect();
    double areaBefore = circle.getArea();

    circle.move({1, 1});

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    dumaev::Circle circle({0, 0}, 2);
    dumaev::rectangle_t frameRectBefore = circle.getFrameRect();
    double areaBefore = circle.getArea();

    circle.move(10, 14);

    BOOST_REQUIRE_EQUAL(frameRectBefore.height, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(frameRectBefore.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(areaBefore, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    dumaev::Circle circle({3, 3}, 3);
    double areaBefore = circle.getArea();
    const double coefficient = 5;
    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(coefficient * coefficient * areaBefore, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
  {
    BOOST_CHECK_THROW( dumaev::Circle circle({10.0, 20.0}, -15), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    dumaev::Circle circle({5, 6}, 3);
    BOOST_CHECK_THROW( circle.scale(1-15), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    dumaev::Circle circle({1, 1}, 9);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double areaBefore = compositeShape.getArea();

    compositeShape.move({2, 3});

    BOOST_CHECK_CLOSE(areaBefore, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double areaBefore = compositeShape.getArea();

    compositeShape.move(2, 3);

    BOOST_CHECK_CLOSE(areaBefore, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(IncorrectCreation)
  {
    BOOST_CHECK_THROW(dumaev::CompositeShape compositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectAddition)
  {
    dumaev::Circle circle({2, 2}, 2);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    dumaev::CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_THROW(compositeShape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ParametersAfterScaling)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double areaBefore = compositeShape.getArea();
    const double heightBefore = compositeShape.getFrameRect().height;
    const double widthBefore = compositeShape.getFrameRect().width;
    dumaev::rectangle_t coordinatesBefore = compositeShape.getFrameRect();

    compositeShape.scale(2);

    BOOST_CHECK_CLOSE(areaBefore * 2 * 2, compositeShape.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(heightBefore * 2, compositeShape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(widthBefore * 2, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(coordinatesBefore.pos.x, compositeShape.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(coordinatesBefore.pos.y, compositeShape.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ParametersAfterMoving)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double widthBefore = compositeShape.getFrameRect().width;
    const double heightBefore = compositeShape.getFrameRect().height;

    compositeShape.move({3, 3});

    BOOST_CHECK_CLOSE(widthBefore, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(heightBefore, compositeShape.getFrameRect().height, EPSILON);

    compositeShape.move(3, 3);

    BOOST_CHECK_CLOSE(widthBefore, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(heightBefore, compositeShape.getFrameRect().height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    BOOST_CHECK_THROW(compositeShape.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(FrameRectRotate)
  {
    dumaev::Rectangle rectangle({0, 0}, 5, 2);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(rectanglePtr);
    compositeShape.rotate(90);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 2, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 5, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixSuite)

  BOOST_AUTO_TEST_CASE(MatrixSplitting)
  {
    dumaev::Circle circleM1({-2,2}, 1);
    dumaev::Rectangle rectangleM1({-1, 1}, 2, 2);
    dumaev::Rectangle rectangleM2({-2, 0}, 2, 4);
    dumaev::Rectangle rectangleM3({-4, -2}, 4, 2);
    dumaev::Rectangle rectangleM4({-3, -3}, 4, 4);
    std::shared_ptr< dumaev::Shape > circlePtrM1 = std::make_shared< dumaev::Circle >(circleM1);
    std::shared_ptr< dumaev::Shape > rectanglePtrM1 =std::make_shared< dumaev::Rectangle >(rectangleM1);
    std::shared_ptr< dumaev::Shape > rectanglePtrM2 =std::make_shared< dumaev::Rectangle >(rectangleM2);
    std::shared_ptr< dumaev::Shape > rectanglePtrM3 =std::make_shared< dumaev::Rectangle >(rectangleM3);
    std::shared_ptr< dumaev::Shape > rectanglePtrM4 =std::make_shared< dumaev::Rectangle >(rectangleM4);

    dumaev::Matrix matrix(circlePtrM1);
    matrix.addShape(rectanglePtrM1);
    matrix.addShape(rectanglePtrM2);
    matrix.addShape(rectanglePtrM3);
    matrix.addShape(rectanglePtrM4);

    std::unique_ptr< std::shared_ptr< dumaev::Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< dumaev::Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< dumaev::Shape >[] > layer3 = matrix[2];

    BOOST_CHECK(layer1[0] == circlePtrM1);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, -2.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.x, -4.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, -1.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer2[1]->getFrameRect().pos.x, -3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().pos.x, -2.0, EPSILON);

    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 2.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.y, -2.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 1.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer2[1]->getFrameRect().pos.y, -3.0, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(layer3[0]->getFrameRect().pos.y, 0.0, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
