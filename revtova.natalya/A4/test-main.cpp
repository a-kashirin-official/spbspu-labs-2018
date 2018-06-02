#define BOOST_TEST_MODULE main_test

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace revtova;

const double DELTA = 0.00001;
const double KSCALE = 2.0;

BOOST_AUTO_TEST_SUITE(TestCompositeShp)
  BOOST_AUTO_TEST_CASE(TestMoveToPoint)
  {
    revtova::Rectangle rect ({5.5, 5.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({6.5, 6.5}, 1.0, 1.0);
    std::shared_ptr<revtova::Shape> rectPtr = std::make_shared<revtova::Rectangle>(rect);
    std::shared_ptr<revtova::Shape> rect1Ptr = std::make_shared<revtova::Rectangle>(rect1);
    CompositeShape CompShp(rect1Ptr);
    CompShp.addShape(rect1Ptr);
    CompShp.move({2.1, 5.6});
    BOOST_CHECK_CLOSE(CompShp.getPos().x, CompShp.getFrameRect().pos.x, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getPos().y, CompShp.getFrameRect().pos.y, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getArea(), rect.getArea() + rect1.getArea(), DELTA);
  }
  BOOST_AUTO_TEST_CASE(TestMoveToXY)
  {
    revtova::Rectangle rect ({5.5, 5.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({6.5, 6.5}, 1.0, 1.0);
    std::shared_ptr<revtova::Shape> rectPtr = std::make_shared<revtova::Rectangle>(rect);
    std::shared_ptr<revtova::Shape> rect1Ptr = std::make_shared<revtova::Rectangle>(rect1);
    CompositeShape CompShp(rectPtr);
    CompShp.addShape(rect1Ptr);
    CompShp.move(4.1, 6.3);
    BOOST_CHECK_CLOSE(CompShp.getFrameRect().pos.x, 10.1, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getFrameRect().pos.y, 12.3, DELTA);
    BOOST_CHECK_CLOSE(CompShp.getArea(), rect.getArea() + rect1.getArea(), DELTA);
  }
  BOOST_AUTO_TEST_CASE(TestScaleFrameRect)
  {
    revtova::Rectangle rect ({5.5, 5.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({6.5, 6.5}, 1.0, 1.0);
    std::shared_ptr<revtova::Shape> rectPtr = std::make_shared<revtova::Rectangle>(rect);
    std::shared_ptr<revtova::Shape> rect1Ptr = std::make_shared<revtova::Rectangle>(rect1);
    CompositeShape CompShp(rectPtr);
    CompShp.addShape(rect1Ptr);
    CompShp.scale(KSCALE);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getPos().x, CompShp.getFrameRect().pos.x, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getPos().y, CompShp.getFrameRect().pos.y, DELTA);
  }
  BOOST_AUTO_TEST_CASE(TestFrameRect)
  {
    revtova::Rectangle rect ({1.0, 2.0}, 3.0, 4.0);
    revtova::Circle circ ({1.0, 2.0}, 10.0);
    std::shared_ptr<revtova::Shape> rectPtr = std::make_shared<revtova::Rectangle>(rect);
    std::shared_ptr<revtova::Shape> circPtr = std::make_shared<revtova::Circle>(circ);
    CompositeShape CompShp(rectPtr);
    CompShp.addShape(circPtr);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getPos().x, CompShp.getFrameRect().pos.x, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getPos().y, CompShp.getFrameRect().pos.y, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().width, 20, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().height, 20, DELTA);
  }
  BOOST_AUTO_TEST_CASE(TestCount)
  {
    revtova::Rectangle rect({2.5, 5.3}, 5.0, 4.1);
    revtova::Rectangle rect1({2.6, 1.4}, 9.2, 3.3);
    std::shared_ptr<revtova::Shape> rectPtr = std::make_shared<revtova::Rectangle>(rect);
    std::shared_ptr<revtova::Shape> rect1Ptr = std::make_shared<revtova::Rectangle>(rect1);
    CompositeShape CompShp(rectPtr);
    CompShp.addShape(rect1Ptr);
    Circle circ({3.2, 4.1}, 10.2);
    Circle circ1({3.3, 4.8}, 4.2);
    std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(circ);
    std::shared_ptr<Shape> circ1Ptr = std::make_shared<Circle>(circ1);
    CompShp.addShape(circPtr);
    CompShp.addShape(circ1Ptr);
    BOOST_REQUIRE_EQUAL(CompShp.getCount(), 4);
    CompShp.remove(2);
    BOOST_REQUIRE_EQUAL(CompShp.getCount(), 3);
  }
  BOOST_AUTO_TEST_CASE(RotateTest)
  {
    revtova::Rectangle rect ({5.5, 5.5}, 1.0, 1.0);
    revtova::Rectangle rect1 ({6.5, 6.5}, 1.0, 1.0);
    std::shared_ptr<revtova::Shape> rectPtr = std::make_shared<revtova::Rectangle>(rect);
    std::shared_ptr<revtova::Shape> rect1Ptr = std::make_shared<revtova::Rectangle>(rect1);
    CompositeShape CompShp(rectPtr);
    CompShp.addShape(rect1Ptr);
    CompShp.rotate(90);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().width, 2.0, DELTA);
    BOOST_CHECK_CLOSE_FRACTION(CompShp.getFrameRect().height, 2.0, DELTA);
  }
  BOOST_AUTO_TEST_CASE(IncorValueScale)
  {
    revtova::Rectangle rect({0.0, 0.0}, 10.0, 15.0);
    std::shared_ptr<revtova::Shape> rectPtr = std::make_shared<revtova::Rectangle>(rect);
    CompositeShape CompShp(rectPtr);
    BOOST_CHECK_THROW(CompShp.scale(-1), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTest)
  BOOST_AUTO_TEST_CASE(AddShapeMatrix)
  {
    revtova::Circle circ( { -2.0, -2.0 }, 2.0 );
    revtova::Rectangle rect1( { -2.0, 0.0 }, 2.0, 2.0 );
    revtova::Rectangle rect2( { 1.0, 1.0 }, 6.0, 3.0 );
    revtova::Rectangle rect3( { 3.0, 1.0 }, 2.0, 4.0 );

    std::shared_ptr<revtova::Shape> circPtr = std::make_shared<revtova::Circle>(circ);
    std::shared_ptr<revtova::Shape> rect1Ptr = std::make_shared<revtova::Rectangle>(rect1);
    std::shared_ptr<revtova::Shape> rect2Ptr = std::make_shared<revtova::Rectangle>(rect2);
    std::shared_ptr<revtova::Shape> rect3Ptr = std::make_shared<revtova::Rectangle>(rect3);

    Matrix matrix(circPtr);
    matrix.addShape(rect1Ptr);
    matrix.addShape(rect2Ptr);
    matrix.addShape(rect3Ptr);

    std::unique_ptr<std::shared_ptr<revtova::Shape>[]> layer1 = matrix[0];
    std::unique_ptr<std::shared_ptr<revtova::Shape>[]> layer2 = matrix[1];
    std::unique_ptr<std::shared_ptr<revtova::Shape>[]> layer3 = matrix[2];

    BOOST_CHECK(layer1[0] == circPtr);
    BOOST_CHECK(layer1[1] == rect3Ptr);
    BOOST_CHECK(layer2[0] == rect1Ptr);
    BOOST_CHECK(layer3[0] == rect2Ptr);
  }
BOOST_AUTO_TEST_SUITE_END()
