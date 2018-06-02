#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <math.h>
#include <memory>
#include <stdexcept>

#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

const double ACCURACY = 10e-4;

using namespace styagov;

/* Start of Rectangle test suite section */
BOOST_AUTO_TEST_SUITE(rectangle_tests)

  // method under test - styagov::Rectangle::setWidth(const double)
  BOOST_AUTO_TEST_CASE(rectangle_set_width_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    rectangle.setWidth(20.0);

    BOOST_REQUIRE_EQUAL(rectangle.getWidth(), 20.0);
  }

  // method under test - styagov::Rectangle::getWidth()
  BOOST_AUTO_TEST_CASE(rectangle_get_width_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);

    BOOST_REQUIRE_EQUAL(rectangle.getWidth(), 10.0);
  }

  // method under test - styagov::Rectangle::setHeight(const double)
  BOOST_AUTO_TEST_CASE(rectangle_set_height_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    rectangle.setHeight(15.0);

    BOOST_REQUIRE_EQUAL(rectangle.getHeight(), 15.0);
  }

  // method under test - styagov::Rectangle::getHeight()
  BOOST_AUTO_TEST_CASE(rectangle_get_height_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);

    BOOST_REQUIRE_EQUAL(rectangle.getHeight(), 5.0);
  }

  // method under test - styagov::Rectangle::getPos()
  BOOST_AUTO_TEST_CASE(rectangle_get_center_position_test)
  {
    Rectangle rectangle({ -4.0, 8.0 }, 10.0, 5.0);

    BOOST_REQUIRE_EQUAL(rectangle.getPos().x, -4.0);
    BOOST_REQUIRE_EQUAL(rectangle.getPos().y, 8.0);
  }

  // method under test - styagov::Rectangle::getArea()
  BOOST_AUTO_TEST_CASE(rectangle_area_calculation_test)
  {
    Rectangle rectangle({ 5.0, 0.0 }, 10.0, 5.0);

    BOOST_REQUIRE_EQUAL(rectangle.getArea(), 50.0);
  }

  // method under test - styagov::Rectangle::getFrameRect()
  BOOST_AUTO_TEST_CASE(rectangle_frame_rect_calculation_test)
  {
    Rectangle rectangle({ 12.0, -1.0 }, 10.0, 5.0);

    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.x, 12.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.y, -1.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 10.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 5.0);
  }

  // method under test - styagov::Rectangle::move(const point_t &)
  BOOST_AUTO_TEST_CASE(rectangle_move_in_new_position_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    rectangle.move({ 10.0, -10.0 });

    BOOST_REQUIRE_EQUAL(rectangle.getPos().x, 10.0);
    BOOST_REQUIRE_EQUAL(rectangle.getPos().y, -10.0);
  }

  // method under test - styagov::Rectangle::move(const double, const double)
  BOOST_AUTO_TEST_CASE(rectangle_move_by_offset_test)
  {
    Rectangle rectangle({ 5.0, 0.0 }, 10.0, 5.0);
    rectangle.move(-5.0, 5.0);

    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().x, 0.0, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getPos().y, 5.0, ACCURACY);
  }

  // method under test - styagov::Rectangle::scale(const double)
  BOOST_AUTO_TEST_CASE(rectangle_scale_test)
  {
    Rectangle rectangle({ 5.0, 0.0 }, 10.0, 5.0);
    rectangle.scale(2.0);

    BOOST_REQUIRE_CLOSE_FRACTION(rectangle.getArea(), 200.0, ACCURACY);
  }

  // method under test - styagov::Rectangle::move(const point_t &)
  BOOST_AUTO_TEST_CASE(rectangle_sizes_and_area_immutability_after_move_in_new_position_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    double rectangleWidthBeforeMove = rectangle.getWidth();
    double rectangleHeightBeforeMove = rectangle.getHeight();
    double rectangleAreaBeforeMove = rectangle.getArea();

    rectangle.move({ 10.0, -10.0 });

    BOOST_REQUIRE_EQUAL(rectangleWidthBeforeMove, rectangle.getWidth());
    BOOST_REQUIRE_EQUAL(rectangleHeightBeforeMove, rectangle.getHeight());
    BOOST_REQUIRE_EQUAL(rectangleAreaBeforeMove, rectangle.getArea());
  }

  // method under test - styagov::Rectangle::move(const double, const double)
  BOOST_AUTO_TEST_CASE(rectangle_sizes_and_area_immutability_after_move_by_offset_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    double rectangleWidthBeforeMove = rectangle.getWidth();
    double rectangleHeightBeforeMove = rectangle.getHeight();
    double rectangleAreaBeforeMove = rectangle.getArea();

    rectangle.move(-5.0, 5.0);

    BOOST_REQUIRE_EQUAL(rectangleWidthBeforeMove, rectangle.getWidth());
    BOOST_REQUIRE_EQUAL(rectangleHeightBeforeMove, rectangle.getHeight());
    BOOST_REQUIRE_EQUAL(rectangleAreaBeforeMove, rectangle.getArea());
  }

  // method under test - styagov::Rectangle::scale(const double)
  BOOST_AUTO_TEST_CASE(rectangle_quadratic_area_change_after_scale_test)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 10.0, 5.0);
    double rectangleAreaBeforeScale = rectangle.getArea();
    double ratio = 2.0;

    rectangle.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * rectangleAreaBeforeScale, rectangle.getArea(), ACCURACY);
  }

  // method under test - styagov::Rectangle::Rectangle(const rectangle_t &)
  BOOST_AUTO_TEST_CASE(rectangle_constructor_invalid_argument_test)
  {
    BOOST_REQUIRE_THROW(Rectangle({ 5.0, 0.0 }, -10.0, 5.0), std::invalid_argument);
    BOOST_REQUIRE_THROW(Rectangle({ 5.0, 0.0 }, 10.0, -5.0), std::invalid_argument);
  }

  // method under test - styagov::Rectangle::setWidth(const double)
  BOOST_AUTO_TEST_CASE(rectangle_set_width_invalid_argument_test)
  {
    Rectangle rectangle({ 5.0, 0.0 }, 10.0, 5.0);

    BOOST_REQUIRE_THROW(rectangle.setWidth(-1.0), std::invalid_argument);
  }

  // method under test - styagov::Rectangle::setHeight(const double)
  BOOST_AUTO_TEST_CASE(rectangle_set_height_invalid_argument_test)
  {
    Rectangle rectangle({ 5.0, 0.0 }, 10.0, 5.0);

    BOOST_REQUIRE_THROW(rectangle.setHeight(-2.0), std::invalid_argument);
  }

  // method under test - styagov::Rectangle::scale(const double)
  BOOST_AUTO_TEST_CASE(rectangle_scale_invalid_argument_test)
  {
    Rectangle rectangle({ 5.0, 0.0 }, 10.0, 5.0);

    BOOST_REQUIRE_THROW(rectangle.scale(-3.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_frame_rect_after_rotate)
  {
    Rectangle rectangle({ 0.0, 0.0 }, 4.0, 6.0);
    rectangle.rotate(45.0);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.07106, ACCURACY); 
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.07106, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()
/* End of Rectangle test suite section */


/* Start of Circle test suite section */
BOOST_AUTO_TEST_SUITE(circle_tests)

  // method under test - styagov::Circle::getRadius()
  BOOST_AUTO_TEST_CASE(circle_get_radius_test)
  {
    Circle circle({ -5.0, -5.0 }, 2.0);

    BOOST_REQUIRE_EQUAL(circle.getRadius(), 2.0);
  }

  // method under test - styagov::Circle::getPos()
  BOOST_AUTO_TEST_CASE(circle_get_center_position_test)
  {
    Circle circle({ -5.0, -5.0 }, 2.0);

    BOOST_REQUIRE_EQUAL(circle.getPos().x, -5.0);
    BOOST_REQUIRE_EQUAL(circle.getPos().y, -5.0);
  }

  // method under test - styagov::Circle::getArea()
  BOOST_AUTO_TEST_CASE(circle_area_calculation_test)
  {
    Circle circle({ -5.0, -5.0 }, 2.0);

    BOOST_REQUIRE_EQUAL(circle.getArea(), M_PI * 4.0);
  }

  // method under test - styagov::Circle::getFrameRect()
  BOOST_AUTO_TEST_CASE(circle_frame_rect_calculation_test)
  {
    Circle circle({ 0.0, 0.0 }, 7.0);

    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 0.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 0.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 14.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 14.0);
  }

  // method under test - styagov::Circle::move(const point_t &)
  BOOST_AUTO_TEST_CASE(circle_move_in_new_position_test)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    circle.move({ 10.0, 10.0 });

    BOOST_REQUIRE_EQUAL(circle.getPos().x, 10.0);
    BOOST_REQUIRE_EQUAL(circle.getPos().y, 10.0);
  }

  // method under test - styagov::Circle::move( const double, const double )
  BOOST_AUTO_TEST_CASE(circle_move_by_offset_test)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    circle.move(-5.0, 5.0);

    BOOST_CHECK_CLOSE_FRACTION(circle.getPos().x, -6.0, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(circle.getPos().y, 18.0, ACCURACY);
  }

  // method under test - styagov::Circle::scale(const double)
  BOOST_AUTO_TEST_CASE(circle_scale_test)
  {
    Circle circle({ 0.0, 2.0 }, 4.0);
    circle.scale(2.0);

    BOOST_REQUIRE_CLOSE_FRACTION(circle.getArea(), M_PI * 16.0 * 4.0, ACCURACY);
  }

  // method under test - styagov::Circle::move(const point_t &)
  BOOST_AUTO_TEST_CASE(circle_sizes_and_area_immutability_after_move_in_new_position_test)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    double circleWidthBeforeMove = circle.getFrameRect().width;
    double circleHeightBeforeMove = circle.getFrameRect().height;
    double circleAreaBeforeMove = circle.getArea();

    circle.move({ 10.0, 10.0 });

    BOOST_REQUIRE_EQUAL(circleWidthBeforeMove, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(circleHeightBeforeMove, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(circleAreaBeforeMove, circle.getArea());
  }

  // method under test - styagov::Circle::move(const double, const double)
  BOOST_AUTO_TEST_CASE(circle_sizes_and_area_immutability_after_move_by_offset_test)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    double circleWidthBeforeMove = circle.getFrameRect().width;
    double circleHeightBeforeMove = circle.getFrameRect().height;
    double circleAreaBeforeMove = circle.getArea();

    circle.move(-5.0, 5.0);

    BOOST_REQUIRE_EQUAL(circleWidthBeforeMove, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(circleHeightBeforeMove, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(circleAreaBeforeMove, circle.getArea());
  }

  // method under test - styagov::Circle::scale(const double)
  BOOST_AUTO_TEST_CASE(circle_quadratic_area_change_after_scale_test)
  {
    Circle circle({ -1.0, 13.0 }, 5.0);
    double circleAreaBeforeScale = circle.getArea();
    double ratio = 2.0;

    circle.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * circleAreaBeforeScale, circle.getArea(), ACCURACY);
  }

  // method under test - styagov::Circle::Circle(const point_t &, const double)
  BOOST_AUTO_TEST_CASE(circle_constructor_invalid_argument_test)
  {
    BOOST_CHECK_THROW(Circle({ -5.0, 5.0 }, -2.0), std::invalid_argument);
  }

  // method under test - styagov::Circle::scale(const double)
  BOOST_AUTO_TEST_CASE(circle_scale_invalid_argument_test)
  {
    Circle circle({ -5.0, -5.0 }, 2.0);

    BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
/* End of Circle test suite section */


/* Start of Triangle test suite section */
BOOST_AUTO_TEST_SUITE(triangle_tests)

  // method under test - styagov::Triangle::setVertexAtIndex(const int, const point_t &)
  BOOST_AUTO_TEST_CASE(triangle_set_vertex_at_index_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    triangle.setVertexAtIndex(0, { 0.0, 1.0 });
    triangle.setVertexAtIndex(1, { 3.0, 7.0 });
    triangle.setVertexAtIndex(2, { 6.0, 1.0 });

    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(0).x, 0.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(0).y, 1.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(1).x, 3.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(1).y, 7.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(2).x, 6.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(2).y, 1.0);
  }

  // method under test - styagov::Triangle::getVertexAtIndex(const int)
  BOOST_AUTO_TEST_CASE(triangle_get_vertex_at_index_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });

    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(0).x, 0.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(0).y, 0.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(1).x, 3.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(1).y, 6.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(2).x, 6.0);
    BOOST_REQUIRE_EQUAL(triangle.getVertexAtIndex(2).y, 0.0);
  }

  // method under test - styagov::Triangle::getPos()
  BOOST_AUTO_TEST_CASE(triangle_get_center_position_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });

    BOOST_REQUIRE_EQUAL(triangle.getPos().x, 3.0);
    BOOST_REQUIRE_EQUAL(triangle.getPos().y, 2.0);
  }

  // method under test - styagov::Triangle::getArea()
  BOOST_AUTO_TEST_CASE(triangle_area_calculation_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });

    BOOST_REQUIRE_EQUAL(triangle.getArea(), 2.0 * 0.5 * 2.0 * 4.0);
  }

  // method under test - styagov::Triangle::getFrameRect()
  BOOST_AUTO_TEST_CASE(triangle_get_frame_rect_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });

    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().pos.x, 2.0);
    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().pos.y, 2.0);
    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().width, 4.0);
    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().height, 4.0);
  }

  // method under test - styagov::Triangle::move(const point_t &)
  BOOST_AUTO_TEST_CASE(triangle_move_in_new_position_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    triangle.move({ 5.0, 5.0 });

    BOOST_REQUIRE_EQUAL(triangle.getPos().x, 5.0);
    BOOST_REQUIRE_EQUAL(triangle.getPos().y, 5.0);
    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().pos.x, 5.0);
    BOOST_REQUIRE_EQUAL(triangle.getFrameRect().pos.y, 6.0);
  }

  // method under test - styagov::Triangle::move( const double, const double )
  BOOST_AUTO_TEST_CASE(triangle_move_by_offset_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    triangle.move(-5.0, 5.0);

    BOOST_CHECK_CLOSE_FRACTION(triangle.getPos().x, -2.0, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(triangle.getPos().y, 7.0, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(triangle.getFrameRect().pos.x, -2.0, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(triangle.getFrameRect().pos.y, 8.0, ACCURACY);
  }

  // method under test - styagov::Triangle::scale(const double)
  BOOST_AUTO_TEST_CASE(triangle_scale_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
    triangle.scale(4.0);

    BOOST_REQUIRE_CLOSE_FRACTION(triangle.getArea(), 8.0 * 16.0, ACCURACY);
  }

  // method under test - styagov::Triangle::move(const point_t &)
  BOOST_AUTO_TEST_CASE(triangle_sizes_and_area_immutability_after_move_in_new_position_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    double triangleWidthBeforeMove = triangle.getFrameRect().width;
    double triangleHeightBeforeMove = triangle.getFrameRect().height;
    double triangleAreaBeforeMove = triangle.getArea();

    triangle.move({ 10.0, 10.0 });

    BOOST_REQUIRE_EQUAL(triangleWidthBeforeMove, triangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(triangleHeightBeforeMove, triangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(triangleAreaBeforeMove, triangle.getArea());
  }

  // method under test - styagov::Triangle::move(const double, const double)
  BOOST_AUTO_TEST_CASE(triangle_sizes_and_area_immutability_after_move_by_offset_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    double triangleWidthBeforeMove = triangle.getFrameRect().width;
    double triangleHeightBeforeMove = triangle.getFrameRect().height;
    double triangleAreaBeforeMove = triangle.getArea();

    triangle.move(-5.0, 5.0);

    BOOST_REQUIRE_EQUAL(triangleWidthBeforeMove, triangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(triangleHeightBeforeMove, triangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(triangleAreaBeforeMove, triangle.getArea());
  }

  // method under test - styagov::Triangle::scale(const double)
  BOOST_AUTO_TEST_CASE(triangle_quadratic_area_change_after_scale_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
    double triangleAreaBeforeScale = triangle.getArea();
    double ratio = 4.0;

    triangle.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * triangleAreaBeforeScale, triangle.getArea(), ACCURACY);
  }

  // method under test - styagov::Triangle::scale(const double)
  BOOST_AUTO_TEST_CASE(triangle_center_immutability_after_scale_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    point_t oldPos = triangle.getPos();
    double ratio = 4.0;

    triangle.scale(ratio);

    BOOST_REQUIRE_EQUAL(oldPos.x, triangle.getPos().x);
    BOOST_REQUIRE_EQUAL(oldPos.y, triangle.getPos().y);
  }

  // method under test - styagov::Triangle::setVertexAtIndex(const int, const point_t &)
  BOOST_AUTO_TEST_CASE(triangle_set_vertex_at_index_invalid_argument_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });

    BOOST_CHECK_THROW(triangle.setVertexAtIndex(-5, { 0.0, 0.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(triangle.setVertexAtIndex(5, { 0.0, 0.0 }), std::invalid_argument);
  }

  // method under test - styagov::Triangle::getVertexAtIndex(const int)
  BOOST_AUTO_TEST_CASE(triangle_get_vertex_at_index_invalid_argument_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });

    BOOST_CHECK_THROW(triangle.getVertexAtIndex(-5), std::invalid_argument);
    BOOST_CHECK_THROW(triangle.getVertexAtIndex(5), std::invalid_argument);
  }

  // method under test - styagov::Triangle::scale(const double)
  BOOST_AUTO_TEST_CASE(triangle_scale_invalid_argument_test)
  {
    Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });

    BOOST_CHECK_THROW(triangle.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
/* End of Triangle test suite section */

/* Start of Composite Shape test suite section */
BOOST_AUTO_TEST_SUITE(composite_shape_tests)

  // method under test - styagov::CompositeShape::getPos()
  BOOST_AUTO_TEST_CASE(composite_shape_get_center_position_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared< styagov::Circle >(Circle({ 7.0, 2.0 }, 5.0));
    CompositeShape compositeShape(shape);

    BOOST_REQUIRE_EQUAL(compositeShape.getPos().x, 7.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getPos().y, 2.0);
  }

  // method under test - styagov::CompositeShape::getArea()
  BOOST_AUTO_TEST_CASE(composite_shape_area_calculation_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared<styagov::Rectangle>(Rectangle({ 2.0, 2.0 }, 5.0, 5.0));
    CompositeShape compositeShape(shape);

    BOOST_REQUIRE_EQUAL(compositeShape.getArea(), 5.0 * 5.0);
  }

  // method under test - styagov::CompositeShape::getFrameRect()
  BOOST_AUTO_TEST_CASE(composite_shape_get_frame_rect_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared<styagov::Rectangle>(Rectangle({ 2.0, 2.0 }, 5.0, 5.0));
    CompositeShape compositeShape(shape);

    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, 2.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, 2.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().width, 5.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().height, 5.0);
  }

  // method under test - styagov::CompositeShape::move(const point_t &)
  BOOST_AUTO_TEST_CASE(composite_shape_move_in_new_position_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared<styagov::Rectangle>(Rectangle({ 2.0, 2.0 }, 5.0, 5.0));
    CompositeShape compositeShape(shape);
    shape = std::make_shared<styagov::Rectangle>(Rectangle({ 2.0, 2.0 }, 10.0, 10.0));
    compositeShape.add(shape);

    compositeShape.move({ 5.0, 5.0 });

    BOOST_REQUIRE_EQUAL(compositeShape.getPos().x, 5.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getPos().y, 5.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, 5.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, 5.0);
  }

  // method under test - styagov::CompositeShape::move(const double, const double)
  BOOST_AUTO_TEST_CASE(composite_shape_move_by_offset_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared<styagov::Rectangle>(Rectangle({ 5.0, 0.0 }, 10.0, 5.0));
    CompositeShape compositeShape(shape);
    compositeShape.move(-5.0, 5.0);

    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getPos().x, 0.0, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getPos().y, 5.0, ACCURACY);
  }

  // method under test - styagov::CompositeShape::scale(const double)
  BOOST_AUTO_TEST_CASE(composite_shape_scale_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared<styagov::Rectangle>(Rectangle({ 2.0, 2.0 }, 5.0, 5.0));
    CompositeShape compositeShape(shape);

    compositeShape.scale(4.0);

    BOOST_REQUIRE_CLOSE_FRACTION(compositeShape.getArea(), 5.0 * 5.0 * 16.0, ACCURACY);
  }

  // method under test - styagov::CompositeShape::move(const point_t &)
  BOOST_AUTO_TEST_CASE(composite_shape_sizes_and_area_immutability_after_move_in_new_position_test)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    styagov::Rectangle rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    std::shared_ptr< styagov::Shape > rectanglePtr = std::make_shared< styagov::Rectangle >(rectangle);
    styagov::CompositeShape compositeShape(circlePtr);
    compositeShape.add(rectanglePtr);

    double compositeShapeWidthBeforeMove = compositeShape.getFrameRect().width;
    double compositeShapeHeightBeforeMove = compositeShape.getFrameRect().height;
    double compositeShapeAreaBeforeMove = compositeShape.getArea();

    compositeShape.move({ 10.0, 10.0 });

    BOOST_REQUIRE_EQUAL(compositeShapeWidthBeforeMove, compositeShape.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(compositeShapeHeightBeforeMove, compositeShape.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(compositeShapeAreaBeforeMove, compositeShape.getArea());
  }

  // method under test - styagov::CompositeShape::move(const double, const double)
  BOOST_AUTO_TEST_CASE(composite_shape_sizes_and_area_immutability_after_move_by_offset_test)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    styagov::Rectangle rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    std::shared_ptr< styagov::Shape > rectanglePtr = std::make_shared< styagov::Rectangle >(rectangle);
    styagov::CompositeShape compositeShape(circlePtr);
    compositeShape.add(rectanglePtr);

    double compositeShapeWidthBeforeMove = compositeShape.getFrameRect().width;
    double compositeShapeHeightBeforeMove = compositeShape.getFrameRect().height;
    double compositeShapeAreaBeforeMove = compositeShape.getArea();

    compositeShape.move(-5.0, 5.0);

    BOOST_REQUIRE_EQUAL(compositeShapeWidthBeforeMove, compositeShape.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(compositeShapeHeightBeforeMove, compositeShape.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(compositeShapeAreaBeforeMove, compositeShape.getArea());
  }

  // method under test - styagov::CompositeShape::scale(const double)
  BOOST_AUTO_TEST_CASE(composite_shape_quadratic_area_change_after_scale_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared<styagov::Rectangle>(Rectangle({ 2.0, 2.0 }, 5.0, 5.0));
    CompositeShape compositeShape(shape);
    double compositeShapeAreaBeforeScale = compositeShape.getArea();
    double ratio = 4.0;

    compositeShape.scale(ratio);

    BOOST_CHECK_CLOSE(ratio * ratio * compositeShapeAreaBeforeScale, compositeShape.getArea(), ACCURACY);
  }

  // method under test - styagov::CompositeShape::scale(const double)
  BOOST_AUTO_TEST_CASE(composite_shape_center_immutability_after_scale_test)
  {
    std::shared_ptr< styagov::Shape > shape = std::make_shared<styagov::Rectangle>(Rectangle({ 2.0, 2.0 }, 5.0, 5.0));
    CompositeShape compositeShape(shape);
    point_t oldPos = compositeShape.getPos();
    double ratio = 4.0;

    compositeShape.scale(ratio);

    BOOST_REQUIRE_EQUAL(oldPos.x, compositeShape.getPos().x);
    BOOST_REQUIRE_EQUAL(oldPos.y, compositeShape.getPos().y);
  }

  // method under test - styagov::CompositeShape::scale(const double)
  BOOST_AUTO_TEST_CASE(composite_shape_remove_test)
  {
    styagov::Rectangle rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    std::shared_ptr< styagov::Shape > rectanglePtr = std::make_shared< styagov::Rectangle >(rectangle);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    styagov::CompositeShape compositeShape(rectanglePtr);
    compositeShape.add(circlePtr);

    compositeShape.remove(1);

    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
    BOOST_REQUIRE_EQUAL(compositeShape.getArea(), rectangle.getArea());
    BOOST_REQUIRE_EQUAL(compositeShape.getSize(), 1);
  }

  // method under test - styagov::CompositeShape::scale(const double)
  BOOST_AUTO_TEST_CASE(composite_shape_clear_shapes_test)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    styagov::Rectangle rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    std::shared_ptr< styagov::Shape > rectanglePtr = std::make_shared< styagov::Rectangle >(rectangle);
    styagov::CompositeShape compositeShape(circlePtr);
    compositeShape.add(rectanglePtr);

    compositeShape.clearShapes();
    BOOST_REQUIRE_EQUAL(compositeShape.getSize(), 0);
  }

  // method under test - styagov::CompositeShape::scale(const double)
  BOOST_AUTO_TEST_CASE(composite_shape_scale_invalid_argument_test)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    styagov::CompositeShape compositeShape(circlePtr);

    BOOST_CHECK_THROW(compositeShape.scale(-3.0), std::invalid_argument);
  }

  // method under test - styagov::CompositeShape::add(const std::shared_ptr< styagov::Shape >)
  BOOST_AUTO_TEST_CASE(composite_shape_add_duplicate_shape_exception_test)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    styagov::CompositeShape compositeShape(circlePtr);

    BOOST_CHECK_THROW(compositeShape.add(circlePtr), std::invalid_argument);
  }

  // method under test - styagov::CompositeShape::remove(const int)
  BOOST_AUTO_TEST_CASE(composite_shape_remove_invalid_argument_exception_test)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    styagov::CompositeShape compositeShape(circlePtr);

    BOOST_CHECK_THROW(compositeShape.remove(2), std::out_of_range);
    BOOST_CHECK_THROW(compositeShape.remove(-1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(composite_shape_copy_constructor_test)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    styagov::Rectangle rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    std::shared_ptr< styagov::Shape > rectanglePtr = std::make_shared< styagov::Rectangle >(rectangle);
    styagov::CompositeShape compositeShape(circlePtr);
    compositeShape.add(rectanglePtr);

    styagov::CompositeShape compShape(compositeShape);

    BOOST_CHECK(compositeShape.getSize() == compShape.getSize());
  }

  BOOST_AUTO_TEST_CASE(composite_shape_copy_assignment_operator)
  {
    styagov::Circle circle({ 7.0, 0.0 }, 5.0);
    styagov::Rectangle rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    std::shared_ptr< styagov::Shape > circlePtr = std::make_shared< styagov::Circle >(circle);
    std::shared_ptr< styagov::Shape > rectanglePtr = std::make_shared< styagov::Rectangle >(rectangle);
    
    styagov::CompositeShape compositeShape(circlePtr);
    compositeShape.add(rectanglePtr);
    size_t size = compositeShape.getSize();
    styagov::CompositeShape compShape(std::move(compositeShape));

    BOOST_CHECK(size == compShape.getSize());
  }

  BOOST_AUTO_TEST_CASE(composite_shape_rotate)
  {
    styagov::Rectangle rectangle({ 0.0, 0.0 }, 4.0, 6.0);
    std::shared_ptr <styagov::Shape> rectanglePtr = std::make_shared <styagov::Rectangle>(rectangle);
    styagov::CompositeShape compositeShape(rectanglePtr);

    compositeShape.rotate(45);

    BOOST_CHECK_CLOSE(compositeShape.getShapes()[0]->getFrameRect().width, 7.07106, ACCURACY); 
    BOOST_CHECK_CLOSE(compositeShape.getShapes()[0]->getFrameRect().height, 7.07106, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()
/* End of Composite Shape test suite section */

/* Start of Composite Shape test suite section */
BOOST_AUTO_TEST_SUITE(matrix_tests)

  BOOST_AUTO_TEST_CASE(matrix_main_test)
  {
    styagov::Circle matrixCircle { { 7.0, 0.0 }, 5.0 };
    styagov::Rectangle matrixRectangleA { { -5.0, 10.0 }, 15.0, 10.0 };
    styagov::Rectangle matrixRectangleB { { 0.0, 7.0 }, 10.0, 2.0 };
    styagov::Rectangle matrixRectangleC { { 12.0, -1.0 }, 13.0, 12.0 };
    styagov::Rectangle matrixRectangleD { { 2.5, 3.5 }, 5.0, 5.0 };

    std::shared_ptr <styagov::Shape> matrixCirclePtr = std::make_shared <styagov::Circle>(matrixCircle);
    std::shared_ptr <styagov::Shape> matrixRectangleAPtr = std::make_shared <styagov::Rectangle>(matrixRectangleA);
    std::shared_ptr <styagov::Shape> matrixRectangleBPtr = std::make_shared <styagov::Rectangle>(matrixRectangleB);
    std::shared_ptr <styagov::Shape> matrixRectangleCPtr = std::make_shared <styagov::Rectangle>(matrixRectangleC);
    std::shared_ptr <styagov::Shape> matrixRectangleDPtr = std::make_shared <styagov::Rectangle>(matrixRectangleD);

    styagov::Matrix matrix(matrixCirclePtr);
    matrix.add(matrixRectangleAPtr);
    matrix.add(matrixRectangleBPtr);
    matrix.add(matrixRectangleCPtr);
    matrix.add(matrixRectangleDPtr);

    std::unique_ptr <std::shared_ptr<styagov::Shape>[]> matrixLayerA = matrix[0];
    std::unique_ptr <std::shared_ptr<styagov::Shape>[]> matrixLayerB = matrix[1];
    std::unique_ptr <std::shared_ptr<styagov::Shape>[]> matrixLayerC = matrix[2];

    BOOST_CHECK(matrixLayerA[0] == matrixCirclePtr);
    BOOST_CHECK(matrixLayerA[1] == matrixRectangleBPtr);
    BOOST_CHECK(matrixLayerB[0] == matrixRectangleAPtr);
    BOOST_CHECK(matrixLayerB[1] == matrixRectangleCPtr);
    BOOST_CHECK(matrixLayerC[0] == matrixRectangleDPtr);
    BOOST_CHECK(matrixLayerC[1] == nullptr);
  }

  BOOST_AUTO_TEST_CASE(matrix_add_null_pointer_as_a_shape_test)
  {
    BOOST_CHECK_THROW(styagov::Matrix matrix(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(matrix_copy_constructor_test)
  {
    std::shared_ptr <styagov::Shape> rectanglePtr = std::make_shared <styagov::Rectangle>(styagov::Rectangle({ { 1.0, 2.0 }, 5.0, 2.0 }));

    styagov::Matrix matrixA(rectanglePtr);
    styagov::Matrix matrixB(matrixA);

    BOOST_CHECK(matrixA[0][0] == matrixB[0][0]);
  }

  BOOST_AUTO_TEST_CASE(matrix_copy_assignment_operator)
  {
    std::shared_ptr <styagov::Shape> rectanglePtr = std::make_shared <styagov::Rectangle>(styagov::Rectangle({ { 7.0, 5.0 }, 2.0, 4.0 }));
    std::shared_ptr <styagov::Shape> rectanglePtr2 = std::make_shared <styagov::Rectangle>(styagov::Rectangle({ { -1.0, 2.0 }, 2.0, 1.0 }));
    
    styagov::Matrix matrixA(rectanglePtr);
    styagov::Matrix matrixB(rectanglePtr2);
    matrixB = matrixA;
    
    BOOST_CHECK(matrixA[0][0] == matrixB[0][0]);
  }

  BOOST_AUTO_TEST_CASE(matrix_overlapping_check_test)
  {
    std::shared_ptr <styagov::Shape> rectangleA = std::make_shared <styagov::Rectangle>(styagov::Rectangle({ { 0.0, 0.0 }, 11.0, 1.0 }));
    std::shared_ptr <styagov::Shape> rectangleB = std::make_shared <styagov::Rectangle>(styagov::Rectangle({ { 1.0, 13.0 }, 10.0, 1.0 }));
    std::shared_ptr <styagov::Shape> rectangleC = std::make_shared <styagov::Rectangle>(styagov::Rectangle({ { 1.0, 0.0 }, 10.0, 1.0 }));

    styagov::Matrix matrix(rectangleA);

    BOOST_CHECK(!matrix.doesOverlap(0, rectangleB));
    BOOST_CHECK(matrix.doesOverlap(0, rectangleC));
  }

  BOOST_AUTO_TEST_CASE(matrix_creation_from_composite_shape)
  {
    styagov::Circle newCircle = Circle({ 3.0, 3.0 }, 4.0);
    std::shared_ptr <styagov::Shape> shapePtr = std::make_shared <styagov::Circle>(newCircle);
    styagov::CompositeShape compositeShape(shapePtr);
    styagov::Rectangle newRectangle = Rectangle({ -5.0, -5.0 }, 2.0, 8.0);
    shapePtr = std::make_shared <styagov::Rectangle>(newRectangle);
    compositeShape.add(shapePtr);
    styagov::Triangle newTriangle = Triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
    shapePtr = std::make_shared <styagov::Triangle>(newTriangle);
    compositeShape.add(shapePtr);

    styagov::Matrix matrixFromCompositeShape(compositeShape);

    BOOST_REQUIRE_EQUAL(matrixFromCompositeShape.getLayers(), 2);
    BOOST_REQUIRE_EQUAL(matrixFromCompositeShape.getLayerSize(), 2);
  }
BOOST_AUTO_TEST_SUITE_END()
/* End of Composite Shape test suite section */
