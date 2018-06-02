#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

#define FRACTION_EPS (0.000001)

BOOST_AUTO_TEST_SUITE(Rectangle_tests)
  
  BOOST_AUTO_TEST_CASE(Move_to_point_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move({60.0,80.0});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.x, 60.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.y, 80.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move(15.0, -20.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.x, 35.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.y, 20.0);
  }
  
  BOOST_AUTO_TEST_CASE(GetArea_test)
    {
      suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
      BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100.0*50.0, FRACTION_EPS);
    }

  BOOST_AUTO_TEST_CASE(Frame_rect_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 100.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 50.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.x, 20.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().pos.y, 40.0);
  }

  BOOST_AUTO_TEST_CASE(Scale_area_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.scale(5.0);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100.0*50.0*pow(5.0, 2), FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_area_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move({60.0, 80.0});
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100.0*50.0, FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_area_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move(15.0, -20.0);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 100.0*50.0, FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_width_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move({60.0, 80.0});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 100.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_width_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move(15.0, -20.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 100.0);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_height_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move({60.0, 80.0});
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 50.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_height_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    rectangle.move(15.0, -20.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 50.0);
  }

  BOOST_AUTO_TEST_CASE(Invalid_scale_coefficient_test)
  {
    suslov::Rectangle rectangle({20.0, 40.0}, 100.0, 50.0);
    BOOST_CHECK_THROW(rectangle.scale(-10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_width_or_height_test)
  {
    BOOST_CHECK_THROW(suslov::Rectangle({20.0, 40.0}, -100.0, 50.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_tests)
  
  BOOST_AUTO_TEST_CASE(Move_to_point_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    circle.move({290.0,110.0});
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 290.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 110.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    circle.move(-10.0, 140.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 40.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 210.0);
  }
  
  BOOST_AUTO_TEST_CASE(GetArea_test)
    {
      suslov::Circle circle ({50.0, 70.0}, 80.0);
      BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80.0, 2), FRACTION_EPS);
    }

  BOOST_AUTO_TEST_CASE(Frame_rect_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 80.0 * 2);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 80.0 * 2);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.x, 50.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().pos.y, 70.0);
  }

  BOOST_AUTO_TEST_CASE(Scale_area_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    circle.scale(10.0);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80.0, 2) * pow(10.0, 2), FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_area_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    circle.move({290.0,110.0});
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80.0, 2), FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_area_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    circle.move(-10.0, 140.0);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), M_PI * pow(80.0, 2), FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_radius_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    circle.move({290.0,110.0});
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width / 2.0, 80.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_radius_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    circle.move(-10.0, 140.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width / 2.0, 80.0);
  }

  BOOST_AUTO_TEST_CASE(Invalid_scale_coefficient_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 80.0);
    BOOST_CHECK_THROW(circle.scale(-10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_radius_test)
  {
    BOOST_CHECK_THROW(suslov::Circle({50.0, 70.0}, -80.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Composite_shape_tests)

  BOOST_AUTO_TEST_CASE(Move_to_point_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move({25.0, 40.0});

    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, 25.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, 40.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move(50.0, -40.0);

    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, 100.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, 15.0);
 
  }
  
    BOOST_AUTO_TEST_CASE(GetArea_test)
    {
      suslov::Circle circle ({50.0, 70.0}, 45.0);
      suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
      std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
      std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
      suslov::CompositeShape compositeShape(pCircle);
      compositeShape.addShape(pRectangle);
      BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), M_PI * pow(45.0, 2) + 30.0 * 40.0, FRACTION_EPS);
    }

    BOOST_AUTO_TEST_CASE(Frame_rect_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().width, 90.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().height, 120.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, 50.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, 55.0);
  }

  BOOST_AUTO_TEST_CASE(Scale_area_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), (M_PI * pow(45.0, 2) + (30.0 * 40.0)) * pow(3.0, 2) , FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_area_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move({25.0, 40.0});
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), M_PI * pow(45.0, 2) + 30.0 * 40.0, FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_area_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move(45.0, 80.0);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), M_PI * pow(45.0, 2) + 30.0 * 40.0, FRACTION_EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_width_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move({25.0, 40.0});
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().width, 90.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_width_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move(45.0, 80.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().width, 90.0);
  }

  BOOST_AUTO_TEST_CASE(Move_to_point_height_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move({25.0, 40.0});
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().height, 120.0);
  }

  BOOST_AUTO_TEST_CASE(Move_dx_dy_height_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.move(45.0, 80.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().height, 120.0);
  }

  BOOST_AUTO_TEST_CASE(Delete_shape_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.deleteShape(1);
    BOOST_REQUIRE_EQUAL(compositeShape.getArea(), rectangle.getArea());
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, rectangle.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, rectangle.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(Delete_all_shape_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.deleteAllShapes();
    BOOST_REQUIRE_EQUAL(compositeShape.getArea(), 0.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, 0.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, 0.0);
  }

  BOOST_AUTO_TEST_CASE(Invalid_scale_coefficient_test)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    BOOST_CHECK_THROW(compositeShape.scale(-10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_shape_number_when_deleting)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    BOOST_CHECK_THROW(compositeShape.deleteShape(7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Empty_composite_shape_when_deleting)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.deleteAllShapes();
    BOOST_CHECK_THROW(compositeShape.deleteShape(1), std::invalid_argument);
  }


  BOOST_AUTO_TEST_CASE(Null_pointer_error)
  {
    BOOST_CHECK_THROW(suslov::CompositeShape compositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Null_pointer_when_adding_shape)
  {
    suslov::Circle circle ({50.0, 70.0}, 45.0);
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pCircle = std::make_shared < suslov::Circle > (circle);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pRectangle);
    pCircle = nullptr;

    BOOST_CHECK_THROW(compositeShape.addShape(pCircle), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Adding_already_existed_shape)
  {
    suslov::Rectangle rectangle ({20.0, 15.0}, 30.0, 40.0);
    std::shared_ptr < suslov::Shape > pRectangle = std::make_shared < suslov::Rectangle > (rectangle);
    suslov::CompositeShape compositeShape(pRectangle);

    BOOST_CHECK_THROW(compositeShape.addShape(pRectangle), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()


