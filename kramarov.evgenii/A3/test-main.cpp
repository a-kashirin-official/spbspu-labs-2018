#define BOOST_TEST_MODULE Main
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double delta = 0.000001;

BOOST_AUTO_TEST_SUITE(MainCheck)
  BOOST_AUTO_TEST_CASE(ReinitializingMovement)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    double baseHeight = rectangle.getFrameRect().height;
    double baseWidth = rectangle.getFrameRect().width;
    double baseArea = rectangle.getArea();
    rectangle.move({20.0, 20.0});
    BOOST_CHECK_EQUAL(baseHeight, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(baseWidth, rectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(baseArea, rectangle.getArea());
    //finished checking rectangle

    kramarov::Circle circle ({50.0,30.0}, 20.0);
    double baseRadius = circle.getFrameRect().height / 2;
    baseArea = circle.getArea();
    circle.move({35.0, 35.0});
    BOOST_CHECK_EQUAL(baseRadius, circle.getFrameRect().height / 2);
    BOOST_CHECK_EQUAL(baseArea, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(DifferencialMovement)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    double baseHeight = rectangle.getFrameRect().height;
    double baseWidth = rectangle.getFrameRect().width;
    double baseArea = rectangle.getArea();
    rectangle.move(20.0, 20.0);
    BOOST_CHECK_EQUAL(baseHeight, rectangle.getFrameRect().height);
    BOOST_CHECK_EQUAL(baseWidth, rectangle.getFrameRect().width);
    BOOST_CHECK_EQUAL(baseArea, rectangle.getArea());
    //finished checking rectangle

    kramarov::Circle circle ({50.0,30.0}, 20.0);
    double baseRadius = circle.getFrameRect().height / 2;
    baseArea = circle.getArea();
    circle.move(35.0, 35.0);
    BOOST_CHECK_EQUAL(baseRadius, circle.getFrameRect().height / 2);
    BOOST_CHECK_EQUAL(baseArea, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(Resizing)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    double baseArea = rectangle.getArea();
    const double scaleRate = 3.35;
    rectangle.scale(scaleRate);
    BOOST_CHECK_CLOSE(baseArea * scaleRate * scaleRate, rectangle.getArea(), delta);
    //finished checking rectangle

    kramarov::Circle circle ({50.0,30.0}, 20.0);
    baseArea = circle.getArea();
    circle.scale(scaleRate);
    BOOST_CHECK_CLOSE(baseArea * scaleRate * scaleRate, circle.getArea(), delta);
  }

  BOOST_AUTO_TEST_CASE(ConstructorParameters)
  {
    BOOST_CHECK_THROW (kramarov::Rectangle(-1.5, 2.0, {10.0, 10.0}), std::invalid_argument);
    BOOST_CHECK_THROW (kramarov::Rectangle(1.5, -2.0, {10.0, 10.0}), std::invalid_argument);
    BOOST_CHECK_THROW (kramarov::Rectangle(-1.5, -2.0, {10.0, 10.0}), std::invalid_argument);
    BOOST_CHECK_THROW (kramarov::Circle({50.0, 30.0}, -20.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ResizingParameters)
  {
    kramarov::Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    BOOST_CHECK_THROW (rectangle.scale(-1.5), std::invalid_argument);
    kramarov::Circle circle({50.0,30.0}, 20.0);
    BOOST_CHECK_THROW (circle.scale(-1.5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositionCheck)

  BOOST_AUTO_TEST_CASE(Creation)
  {
    BOOST_CHECK_THROW (kramarov::CompositeShape comp(nullptr), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(AdditionParameters)
  {
    kramarov::Circle circle({0.0, 0.0}, 10.0);
    kramarov::CompositeShape comp(&circle);
    BOOST_CHECK_THROW (comp.addShape(nullptr), std::invalid_argument);
    comp.clear();
  }

  BOOST_AUTO_TEST_CASE(DeletionParameters)
  {
    kramarov::Circle circle({0.0, 0.0}, 10.0);
    kramarov::CompositeShape comp(&circle);
    BOOST_CHECK_THROW (comp.deleteShape(-3), std::out_of_range);
    comp.clear();
  }

  BOOST_AUTO_TEST_CASE(DiffMovementCheck)
  {
    kramarov::Rectangle rect0(4.0, 6.0, {0.0, 0.0});
    kramarov::CompositeShape comp(&rect0);
    kramarov::Rectangle rect1(6.0, 8.0, {1.0, 1.0});
    comp.addShape (&rect1);
    const double baseX = comp.getXY().x;
    const double baseY = comp.getXY().y;
    const double baseArea = comp.getArea();
    const kramarov::rectangle_t baseFrame = comp.getFrameRect();
    comp.move (-1.0, -1.0);
    //XY check
    BOOST_CHECK_EQUAL (comp.getXY().x, baseX - 1.0);
    BOOST_CHECK_EQUAL (comp.getXY().y, baseY - 1.0);
    //Area Check
    BOOST_CHECK_EQUAL (comp.getArea(), baseArea);
    //Frame Rectangle Check
    BOOST_CHECK_EQUAL (comp.getFrameRect().pos.x, baseFrame.pos.x - 1.0);
    BOOST_CHECK_EQUAL (comp.getFrameRect().pos.y, baseFrame.pos.y - 1.0);
    BOOST_CHECK_EQUAL (comp.getFrameRect().width, baseFrame.width);
    BOOST_CHECK_EQUAL (comp.getFrameRect().height, baseFrame.height);
    comp.clear();
  }

  BOOST_AUTO_TEST_CASE(ReinitializingMovementCheck)
  {
    kramarov::Rectangle rect0(4.0, 6.0, {0.0, 0.0});
    kramarov::CompositeShape comp(&rect0);
    kramarov::Rectangle rect1(6.0, 8.0, {1.0, 1.0});
    comp.addShape (&rect1);
    const double baseArea = comp.getArea();
    const kramarov::rectangle_t baseFrame = comp.getFrameRect();
    comp.move ({-1.0, -1.0});
    //XY check
    BOOST_CHECK_CLOSE (comp.getXY().x, -1.0, delta);
    BOOST_CHECK_CLOSE (comp.getXY().y, -1.0, delta);
    //Area Check
    BOOST_CHECK_EQUAL (comp.getArea(), baseArea);
    //Frame Rectangle Check
    BOOST_CHECK_EQUAL (comp.getFrameRect().width, baseFrame.width);
    BOOST_CHECK_EQUAL (comp.getFrameRect().height, baseFrame.height);
    comp.clear();
  }

  BOOST_AUTO_TEST_CASE(QuantityCheck)
  {
    kramarov::Rectangle rect0(4.0, 6.0, {0.0, 0.0});
    kramarov::CompositeShape comp(&rect0);
    kramarov::Rectangle rect1(6.0, 8.0, {1.0, 1.0});
    comp.addShape (&rect1);
    BOOST_CHECK_EQUAL (comp.getQtt(), 2);
    comp.deleteShape (0);
    BOOST_CHECK_EQUAL (comp.getQtt(), 1);
    comp.clear();
  }

  BOOST_AUTO_TEST_CASE(ScalingCheck)
  {
    kramarov::Rectangle rect0(4.0, 6.0, {0.0, 0.0});
    kramarov::CompositeShape comp(&rect0);
    kramarov::Rectangle rect1(6.0, 8.0, {1.0, 1.0});
    comp.addShape (&rect1);
    const double baseX = comp.getXY().x;
    const double baseY = comp.getXY().y;
    const double baseArea = comp.getArea();
    const double baseFrameX = comp.getFrameRect().pos.x;
    const double baseFrameY = comp.getFrameRect().pos.y;
    const double baseFrameWidth = comp.getFrameRect().width;
    const double baseFrameHeight = comp.getFrameRect().height;
    comp.scale (2.0);
    //Frame Rectangle Check
    BOOST_CHECK_EQUAL (comp.getFrameRect().pos.x, baseFrameX);
    BOOST_CHECK_EQUAL (comp.getFrameRect().pos.y, baseFrameY);
    BOOST_CHECK_CLOSE (comp.getFrameRect().width, baseFrameWidth * 2.0, delta);
    BOOST_CHECK_CLOSE (comp.getFrameRect().height, baseFrameHeight * 2.0, delta);
    //Area Check
    BOOST_CHECK_CLOSE (comp.getArea(), baseArea * 4, delta);
    //XY check
    BOOST_CHECK_EQUAL (comp.getXY().x, baseX);
    BOOST_CHECK_EQUAL (comp.getXY().y, baseY);
    comp.clear();
  }

  BOOST_AUTO_TEST_CASE(GetShapeCheck)
  {
    kramarov::Rectangle rect0(4.0, 6.0, {0.0, 0.0});
    kramarov::CompositeShape comp(&rect0);
    kramarov::Rectangle rect1(6.0, 8.0, {1.0, 1.0});
    comp.addShape (&rect1);
    BOOST_CHECK_CLOSE (comp[0]->getXY().x, 0.0, delta);
    BOOST_CHECK_CLOSE (comp[0]->getXY().y, 0.0, delta);
    BOOST_CHECK_CLOSE (comp[0]->getFrameRect().width, rect0.getFrameRect().width, delta);
    BOOST_CHECK_CLOSE (comp[0]->getFrameRect().height, rect0.getFrameRect().height, delta);
    comp.clear();
  }

  BOOST_AUTO_TEST_CASE(AreaCheck)
  {
    kramarov::Rectangle rect0(4.0, 6.0, {0.0, 0.0});
    kramarov::CompositeShape comp(&rect0);
    kramarov::Rectangle rect1(6.0, 8.0, {1.0, 1.0});
    comp.addShape (&rect1);
    BOOST_CHECK_CLOSE (comp.getArea(), 72.0, delta);
    comp.clear();
  }

BOOST_AUTO_TEST_SUITE_END()
