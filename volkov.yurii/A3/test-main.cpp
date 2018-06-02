#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(GetFrameRectTest)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 1, epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(MoveToXY)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.move(1, 2);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 2, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 3, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 11.1416, epsilon);
  }
  
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.move({2, 1});
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 2, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 11.1416, epsilon);
  }
    BOOST_AUTO_TEST_CASE(MoveInformation)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    volkov::CompositeShape compositeshape1 = std::move(composite_shape);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().height, 4, epsilon);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().width, 4, epsilon);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(compositeshape1.getFrameRect().pos.y, 1, epsilon);
  }

  BOOST_AUTO_TEST_CASE(MoveInformationOperator)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    volkov::CompositeShape composite_shape_n(rect);
    composite_shape = std::move(composite_shape_n);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 2, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 2, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().height, 0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().width, 0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.x, 0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.y, 0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(CopyInformation)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    volkov::CompositeShape composite_shape_n = composite_shape;
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().height, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().width, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape_n.getFrameRect().pos.y, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, composite_shape_n.getFrameRect().height, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, composite_shape_n.getFrameRect().width, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, composite_shape_n.getFrameRect().pos.x, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, composite_shape_n.getFrameRect().pos.y, epsilon);
  }

BOOST_AUTO_TEST_CASE(CopyInformationOperator)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    volkov::CompositeShape composite_shape_n(rect);
    composite_shape = composite_shape_n;
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 2, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 2, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, composite_shape_n.getFrameRect().height, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, composite_shape_n.getFrameRect().width, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, composite_shape_n.getFrameRect().pos.x, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, composite_shape_n.getFrameRect().pos.y, epsilon);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScale)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.scale(5);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, 20, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, 20, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getShape(0)->getFrameRect().pos.x, -4, epsilon); 
    BOOST_CHECK_CLOSE(composite_shape.getShape(0)->getFrameRect().pos.y, -4, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getShape(1)->getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getShape(1)->getFrameRect().pos.y, 6, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 11.1416 * 5 * 5, epsilon);
  }

  BOOST_AUTO_TEST_CASE(RemoveShape)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.removeShape(1);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 8, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 1, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 2, epsilon);
    BOOST_REQUIRE_EQUAL(composite_shape.getSize(), 1);
  }

  BOOST_AUTO_TEST_CASE(DeleteShapes)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.deleteShapes();
    BOOST_REQUIRE_EQUAL(composite_shape.getSize(), 0);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), 0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 0, epsilon);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 0, epsilon);
  }

  BOOST_AUTO_TEST_CASE(InvalidCompositeShapeScale)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    BOOST_CHECK_THROW(composite_shape.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRemovingShapeNumber)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    BOOST_CHECK_THROW(composite_shape.removeShape(-5), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(EmptyCompositeShapeWhenRemoving)
  {
    volkov::Rectangle rect_n({1, 2}, 4, 2);
    volkov::Circle circ_n({0, 0}, 1);
    std::shared_ptr <volkov::Shape> rect = std::make_shared <volkov::Rectangle> (rect_n);
    std::shared_ptr <volkov::Shape> circ = std::make_shared <volkov::Circle> (circ_n);
    volkov::CompositeShape composite_shape(circ);
    composite_shape.addShape(rect);
    composite_shape.deleteShapes();
    BOOST_CHECK_THROW(composite_shape.removeShape(1), std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
