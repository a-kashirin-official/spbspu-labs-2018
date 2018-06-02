#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

using namespace kahuanahil;

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(AreaTest)
  {
    kahuanahil::Rectangle rec({10.0, 15.0, {24.0, 48.0}});
    std::shared_ptr < kahuanahil::Shape > rect = std::make_shared < kahuanahil::Rectangle > (rec);
    kahuanahil::Circle cir(3.0, {5.0, 5.0});
    std::shared_ptr< kahuanahil::Shape > circ = std::make_shared < kahuanahil::Circle > (cir);
    kahuanahil::CompositeShape composite_shape(rect);
    composite_shape.addShape(circ);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), (10.0 * 15.0 + M_PI * pow(3.0, 2)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(GetPosition)
  {
    kahuanahil::Rectangle rec({10.0, 15.0, {24.0, 48.0}});
    std::shared_ptr< kahuanahil::Shape > rect = std::make_shared < kahuanahil::Rectangle > (rec);
    kahuanahil::CompositeShape composite_shape(rect);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 24.0, EPSILON);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 48.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MovetoNewPos)
  {
    kahuanahil::Rectangle rec({10.0, 15.0, {24.0, 48.0}});
    std::shared_ptr< kahuanahil::Shape > rect = std::make_shared < kahuanahil::Rectangle > (rec);
    kahuanahil::CompositeShape composite_shape(rect);
    composite_shape.move({2.0, 2.0});
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.x, 2.0, EPSILON);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().pos.y, 2.0, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(Scale)
  {
    kahuanahil::Circle cir(4.3, { 10.32, 1.23 });
    kahuanahil::Rectangle rec(7.0, 10.79, { 15.64, 8.35 });
    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(cir);
    std::shared_ptr<Shape> rectanglePtr = std::make_shared<Rectangle>(rec);
    CompositeShape composite_Shape(circlePtr);
    composite_Shape.addShape(rectanglePtr);
    kahuanahil::rectangle_t frameRect = composite_Shape.getFrameRect();
    composite_Shape.scale(2.0);
    BOOST_CHECK_CLOSE_FRACTION(composite_Shape.getFrameRect().pos.x, frameRect.pos.x, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composite_Shape.getFrameRect().pos.y, frameRect.pos.y, EPSILON);

  }
  
  BOOST_AUTO_TEST_CASE(Invalid_Scale)
  {
    kahuanahil::Rectangle rec({10.0, 15.0, {24.0, 48.0}});
    std::shared_ptr< kahuanahil::Shape > rect = std::make_shared < kahuanahil::Rectangle > (rec);
    kahuanahil::CompositeShape composite_shape(rect);
    BOOST_CHECK_THROW(composite_shape.scale(-2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Constructor)
  {
    BOOST_CHECK_THROW(kahuanahil::CompositeShape composite_shape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_AddShape)
  {
    kahuanahil::Rectangle rec({10.0, 15.0, {24.0, 48.0}});
    std::shared_ptr< kahuanahil::Shape > rect = std::make_shared < kahuanahil::Rectangle > (rec);
    kahuanahil::CompositeShape composite_shape(rect);
    BOOST_CHECK_THROW(composite_shape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_DeleteShape)
  {
    kahuanahil::Rectangle rec({10.0, 15.0, {24.0, 48.0}});
    std::shared_ptr< kahuanahil::Shape > rect = std::make_shared< kahuanahil::Rectangle > (rec);
    kahuanahil::CompositeShape composite_shape(rect);
    BOOST_CHECK_THROW(composite_shape.deleteShape(1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
