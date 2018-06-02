#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double epsilon = 0.0000001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(GetFrameRectTest)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 }, 4.0, 2.0);
    pichugina::Circle circ_n({0.0, 0.0}, 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 1.0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(MoveToXY)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 }, 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0 , 0.0}, 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.move(1.0, 2.0);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 2.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 3.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 11.1415926535, epsilon);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    pichugina::Rectangle rect_n( {1.0, 2.0}, 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 }, 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.move( {2.0, 1.0 } );
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 2.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 11.1415926535, epsilon);
  }
    BOOST_AUTO_TEST_CASE(MoveInformation)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    pichugina::CompositeShape compositeshape1 = std::move(composite_shape);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, 4.0, epsilon);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, 4.0, epsilon);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, 1.0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(MoveInformationOperator)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    pichugina::CompositeShape composite_shape_n(rect);
    composite_shape = std::move(composite_shape_n);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 2.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 2.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().height, 0.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().width, 0.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.x, 0.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.y, 0.0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(CopyInformation)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    pichugina::CompositeShape composite_shape_n = composite_shape;
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().height, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().width, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.y, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, composite_shape_n.getFrameRect().height, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, composite_shape_n.getFrameRect().width, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, composite_shape_n.getFrameRect().pos.x, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, composite_shape_n.getFrameRect().pos.y, epsilon);
  }

BOOST_AUTO_TEST_CASE(CopyInformationOperator)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 }, 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    pichugina::CompositeShape composite_shape_n(rect);
    composite_shape = composite_shape_n;
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 2.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 2.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, composite_shape_n.getFrameRect().height, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, composite_shape_n.getFrameRect().width, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, composite_shape_n.getFrameRect().pos.x, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, composite_shape_n.getFrameRect().pos.y, epsilon);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScale)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.scale(5);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 20.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 20.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getShape(0)->getFrameRect().pos.x, -4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getShape(0)->getFrameRect().pos.y, -4.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getShape(1)->getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getShape(1)->getFrameRect().pos.y, 6.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 11.1415926535 * 5.0 * 5.0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(RemoveShape)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.removeShape(1);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 8.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 2.0, epsilon);
    BOOST_REQUIRE_EQUAL(composite_shape.getSize(), 1);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapes)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.deleteShapes();
    BOOST_REQUIRE_EQUAL(composite_shape.getSize(), 0.0);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 0.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 0.0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 0.0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidCompositeShapeScale)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    BOOST_CHECK_THROW(composite_shape.scale(-5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRemovingShapeNumber)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    BOOST_CHECK_THROW(composite_shape.removeShape(-5), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(EmptyCompositeShapeWhenRemoving)
  {
    pichugina::Rectangle rect_n( { 1.0, 2.0 } , 4.0, 2.0);
    pichugina::Circle circ_n( { 0.0, 0.0 } , 1.0);
    std::shared_ptr <pichugina::Shape> rect = std::make_shared <pichugina::Rectangle> (rect_n);
    std::shared_ptr <pichugina::Shape> circ = std::make_shared <pichugina::Circle> (circ_n);
    pichugina::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.deleteShapes();
    BOOST_CHECK_THROW(composite_shape.removeShape(1), std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
