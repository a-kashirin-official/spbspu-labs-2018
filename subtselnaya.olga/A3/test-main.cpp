#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double EPSILON = 0.00001;

using namespace std;
using namespace subtselnaya;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

BOOST_AUTO_TEST_CASE(MoveToPoint)
{
  Rectangle rect (3.5, 4.8, {4.3, 3.4});
  rectangle_t startRect = rect.getFrameRect();
  double startArea = rect.getArea();

  rect.move ({25, 10});
  BOOST_CHECK_EQUAL(startArea, rect.getArea());
  BOOST_CHECK_EQUAL(startRect.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(startRect.height, rect.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(MoveByAxis)
{
  Rectangle rect (3.5, 4.8, {4.3, 3.4});
  rectangle_t startRect = rect.getFrameRect();
  double startArea = rect.getArea();

  rect.move (15,5);
  BOOST_CHECK_EQUAL(startArea, rect.getArea());
  BOOST_CHECK_EQUAL(startRect.width, rect.getFrameRect().width);
  BOOST_CHECK_EQUAL(startRect.height, rect.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(Scaling)
{
  Rectangle rect (3.5, 4.8, {4.3, 3.4});
  double startArea = rect.getArea();
  const double value = 3.3;

  rect.scale(value);
  BOOST_CHECK_CLOSE(value * value * startArea, rect.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
{
  Rectangle rect (3.5, 4.8, { 4.3, 3.4 });
  BOOST_CHECK_THROW (rect.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CircleSuite)

BOOST_AUTO_TEST_CASE(MoveToPoint)
{
  Circle circ ({5.9, 7.1}, 3.0);
  rectangle_t startRect = circ.getFrameRect();
  double startArea = circ.getArea();

  circ.move ({20,10});
  BOOST_CHECK_EQUAL(startArea, circ.getArea());
  BOOST_CHECK_EQUAL(startRect.width, circ.getFrameRect().width);
  BOOST_CHECK_EQUAL(startRect.height, circ.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(MoveByAxis)
{
  Circle circ ({5.9, 7.1}, 3.0);
  rectangle_t startRect = circ.getFrameRect();
  double startArea = circ.getArea();

  circ.move (10,5);
  BOOST_CHECK_EQUAL(startArea, circ.getArea());
  BOOST_CHECK_EQUAL(startRect.width, circ.getFrameRect().width);
  BOOST_CHECK_EQUAL(startRect.height, circ.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(Scaling)
{
  Circle circ ({5.9, 7.1}, 3.0);
  double startArea = circ.getArea();
  const double value = 3.3;

  circ.scale(value);
  BOOST_CHECK_CLOSE(value * value * startArea, circ.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
{
  Circle circ ({5.9, 7.1}, 3.0);
  BOOST_CHECK_THROW(circ.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)

    BOOST_AUTO_TEST_CASE(InvarienceOfAreaTest)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        Circle circ ({2.0 , 2.0}, 1.0);
        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape::ptr_type circPtr = make_shared < Circle > (circ);
        CompositeShape composhape;
        composhape.addShape(rectPtr);
        composhape.addShape(circPtr);
        double area = composhape.getArea();
        composhape.move(3.0, 3.0);
        BOOST_CHECK_CLOSE_FRACTION(composhape.getArea(), area, EPSILON);
    }

    BOOST_AUTO_TEST_CASE(InvarienceOfCoordsTest)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        Circle circ ({2.0 , 2.0}, 1.0);

        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape::ptr_type circPtr = make_shared < Circle > (circ);
        CompositeShape composhape;
        composhape.addShape(rectPtr);
        composhape.addShape(circPtr);

        double posX = composhape.getFrameRect().pos.x,
               posY = composhape.getFrameRect().pos.y;

        composhape.scale(2.0);
        BOOST_CHECK_CLOSE_FRACTION(composhape.getFrameRect().pos.x, posX, EPSILON);
        BOOST_CHECK_CLOSE_FRACTION(composhape.getFrameRect().pos.y, posY, EPSILON);
    }

    BOOST_AUTO_TEST_CASE(Scaling)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        Circle circ ({2.0 , 2.0}, 1.0);
        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape::ptr_type circPtr = make_shared < Circle > (circ);
        CompositeShape composhape;
        composhape.addShape(rectPtr);
        composhape.addShape(circPtr);

        double area = composhape.getArea(),
               value = 2.0;

        composhape.scale(value);
        BOOST_CHECK_CLOSE_FRACTION(composhape.getArea(), area * value * value, EPSILON);
    }


    BOOST_AUTO_TEST_CASE(InvalidAddShapeArgument)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape composhape;
        composhape.addShape(rectPtr);

        BOOST_REQUIRE_THROW(composhape.addShape(nullptr), invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(InvalidScalingArgument)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        Circle circ ({2.0 , 2.0}, 1.0);
        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape::ptr_type circPtr = make_shared < Circle > (circ);
        CompositeShape composhape;
        composhape.addShape(rectPtr);
        composhape.addShape(circPtr);

        BOOST_REQUIRE_THROW(composhape.scale(-1.0), invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(OutOfRangeRemoveShape)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape composhape;
        composhape.addShape(rectPtr);
        BOOST_REQUIRE_THROW(composhape.removeShape(1), out_of_range);
    }

    BOOST_AUTO_TEST_CASE(CompositeShapeArrayOperator)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape composhape;
        composhape.addShape(rectPtr);

        BOOST_CHECK_EQUAL(composhape[0], rectPtr);
        BOOST_REQUIRE_THROW(composhape[1], out_of_range);
    }

    BOOST_AUTO_TEST_CASE(General)
    {
        Rectangle rect (1.0, 1.0, {4.0, 4.0});
        CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
        CompositeShape composhape;
        composhape.addShape(rectPtr);

        rectangle_t shapeFrameRect = composhape.getFrameRect(),
                    rectFrameRect = rectPtr -> getFrameRect();

        BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.pos.x, rectFrameRect.pos.x, EPSILON);
        BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.pos.y, rectFrameRect.pos.y, EPSILON);
        BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.width, rectFrameRect.width, EPSILON);
        BOOST_CHECK_CLOSE_FRACTION(shapeFrameRect.height, rectFrameRect.height, EPSILON);
    }

BOOST_AUTO_TEST_SUITE_END()

