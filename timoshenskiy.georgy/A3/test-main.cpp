//
//  test-main.cpp
//  A3
//
//  Created by Георгий Тимошенский on 10.05.2018.
//  Copyright © 2018 Георгий Тимошенский. All rights reserved.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <math.h>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPS_REL = 0.0001;

const timoshenskiy::point_t kRectangleCentre1 = {1.0, 1.0};
const timoshenskiy::point_t kCircleCentre1 = {3.0, 3.0};
const timoshenskiy::point_t kMoveto = {4.0, 5.0};

const double kDx = 2.0;
const double kDy = 2.0;

const double kRectangleWidth1 = 4.0;
const double kRectangleHeight1 = 4.0;
const double kCircleRadius1 = 3.0;

const double kMultiplier = 2.0;

const double kInvalidRectangleHeight = -5.0;
const double kInvalidRectangleWidth = -5.0;
const double kInvalidCircleRadius = -1.0;
const double kInvalidMultiplier = -1.0;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Rect_ParametersDuringMovingInTest)
  {
    timoshenskiy::Rectangle r({kRectangleCentre1, kRectangleWidth1, kRectangleHeight1});
    double area = r.getArea();
    r.move({1.0, 2.0});
    BOOST_REQUIRE_EQUAL(r.getFrameRect().width, kRectangleWidth1);
    BOOST_REQUIRE_EQUAL(r.getFrameRect().height, kRectangleHeight1);
    BOOST_REQUIRE_EQUAL(r.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Rect_ParametersDuringMovingOnTest)
  {
    timoshenskiy::Rectangle r({kRectangleCentre1, kRectangleWidth1, kRectangleHeight1});
    double area = r.getArea();
    r.move(1.0,2.0);
    BOOST_REQUIRE_EQUAL(r.getFrameRect().width, kRectangleWidth1);
    BOOST_REQUIRE_EQUAL(r.getFrameRect().height, kRectangleHeight1);
    BOOST_REQUIRE_EQUAL(r.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Rect_ScaleTest)
  {
    timoshenskiy::Rectangle r({kRectangleCentre1, kRectangleWidth1, kRectangleHeight1});
    double area = r.getArea();
    r.scale(kMultiplier);
    BOOST_REQUIRE_CLOSE_FRACTION(r.getArea(), area * std::pow(kMultiplier, 2), EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Rect_InvalidArgumentsConstructorTest)
  {
    BOOST_CHECK_THROW(timoshenskiy::Rectangle r({kRectangleCentre1, kInvalidRectangleWidth, kInvalidRectangleHeight}),std::invalid_argument);
  
    BOOST_CHECK_THROW(timoshenskiy::Rectangle r({kRectangleCentre1, kRectangleWidth1, kInvalidRectangleHeight}),std::invalid_argument);
  
    BOOST_CHECK_THROW(timoshenskiy::Rectangle r({kRectangleCentre1, kInvalidRectangleWidth, kInvalidRectangleHeight}),std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rect_InvalidArgumentScaleTest)
  {
    timoshenskiy::Rectangle r({kRectangleCentre1, kRectangleWidth1, kRectangleHeight1});
    BOOST_CHECK_THROW(r.scale(kInvalidMultiplier), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Circle_Tests)

  BOOST_AUTO_TEST_CASE(Circle_ParametersDuringMovingInTest)
  {
    timoshenskiy::Circle c({kCircleCentre1, kCircleRadius1});
    double area = c.getArea();
    c.move(kMoveto);
    BOOST_REQUIRE_EQUAL(c.getFrameRect().width, 2 * kCircleRadius1);
    BOOST_REQUIRE_EQUAL(c.getFrameRect().height, 2 * kCircleRadius1);
    BOOST_REQUIRE_EQUAL(c.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Circle_ParametersDuringMovingOnTest)
  {
    timoshenskiy::Circle c({kCircleCentre1, kCircleRadius1});
    double area = c.getArea();
    c.move(kDx, kDy);
    BOOST_REQUIRE_EQUAL(c.getFrameRect().width, 2 * kCircleRadius1);
    BOOST_REQUIRE_EQUAL(c.getFrameRect().height, 2 * kCircleRadius1);
    BOOST_REQUIRE_EQUAL(c.getArea(), area);
  }

  BOOST_AUTO_TEST_CASE(Circle_ScaleTest)
  {
    timoshenskiy::Circle c({kCircleCentre1, kCircleRadius1});
    double area = c.getArea();
    c.scale(kMultiplier);
    BOOST_REQUIRE_CLOSE_FRACTION(c.getArea(), area * std::pow(kMultiplier, 2), EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Circle_InvalidArgumentsConstructorTest)
  {
    BOOST_CHECK_THROW(timoshenskiy::Circle c({kCircleCentre1, kInvalidCircleRadius}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_InvalidArgumentScaleTest)
  {
    timoshenskiy::Circle c({kCircleCentre1, kCircleRadius1});
    BOOST_CHECK_THROW(c.scale(kInvalidMultiplier), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Composite_Tests)

  BOOST_AUTO_TEST_CASE(Composite_MoveTo_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    timoshenskiy::rectangle_t frameBefore = compositeShape.getFrameRect();
    compositeShape.move(kMoveto);
  
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.x, kMoveto.x, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.y, kMoveto.y, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), circle.getArea() + rectangle.getArea(), EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().width, frameBefore.width, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().height, frameBefore.height, EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Composite_MoveOn_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    timoshenskiy::point_t posBefore = compositeShape.getFrameRect().pos;
    timoshenskiy::rectangle_t frameBefore = compositeShape.getFrameRect();
    compositeShape.move(kDx, kDy);
  
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().width, frameBefore.width, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().height, frameBefore.width, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.x, posBefore.x + kDx, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.y, posBefore.y + kDy, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), circle.getArea() + rectangle.getArea(), EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Composite_GetArea_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
  
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), circle.getArea() + rectangle.getArea(), EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Composite_FrameRect_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
  
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().width, 7.0, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().height, 7.0, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.x, 2.5, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.y, 2.5, EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Composite_Scale_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    double xBeforeScalling = compositeShape.getFrameRect().pos.x;
    double yBeforeScalling = compositeShape.getFrameRect().pos.y;
    compositeShape.scale(kMultiplier);
  
    BOOST_CHECK(compositeShape.getFrameRect().pos.x == xBeforeScalling);
    BOOST_CHECK(compositeShape.getFrameRect().pos.y == yBeforeScalling);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), ((circle.getArea() + rectangle.getArea())
                               * pow(kMultiplier, 2)), EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Composite_Delete_shape_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.deleteShape(1);
  
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getArea(), rectangle.getArea(), EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.x, rectangle.getFrameRect().pos.x, EPS_REL);
    BOOST_CHECK_CLOSE_FRACTION(compositeShape.getFrameRect().pos.y, rectangle.getFrameRect().pos.y, EPS_REL);
  }

  BOOST_AUTO_TEST_CASE(Composite_Delete_all_shape_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.deleteAllShapes();
  
    BOOST_REQUIRE_EQUAL(compositeShape.getArea(), 0.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.x, 0.0);
    BOOST_REQUIRE_EQUAL(compositeShape.getFrameRect().pos.y, 0.0);
  }

  BOOST_AUTO_TEST_CASE(Composite_Invalid_scale_coefficient_test)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
  
    BOOST_CHECK_THROW(compositeShape.scale(kInvalidMultiplier), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Composite_Invalid_shape_number_when_deleting)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
  
    BOOST_CHECK_THROW(compositeShape.deleteShape(7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Composite_Empty_composite_shape_when_deleting)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.deleteAllShapes();
  
    BOOST_CHECK_THROW(compositeShape.deleteShape(1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Composite_Null_pointer_error)
  {
    BOOST_CHECK_THROW(timoshenskiy::CompositeShape compositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Composite_Null_pointer_when_adding_shape)
  {
    timoshenskiy::Circle circle ({kCircleCentre1, kCircleRadius1});
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pCircle = std::make_shared < timoshenskiy::Circle > (circle);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pRectangle);
    pCircle = nullptr;
  
    BOOST_CHECK_THROW(compositeShape.addShape(pCircle), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Composite_Adding_already_existed_shape)
  {
    timoshenskiy::Rectangle rectangle (kRectangleCentre1, kRectangleWidth1, kRectangleHeight1);
    std::shared_ptr < timoshenskiy::Shape > pRectangle = std::make_shared < timoshenskiy::Rectangle > (rectangle);
    timoshenskiy::CompositeShape compositeShape(pRectangle);
  
    BOOST_CHECK_THROW(compositeShape.addShape(pRectangle), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

