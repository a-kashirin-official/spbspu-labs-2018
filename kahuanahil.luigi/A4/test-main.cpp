#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(FrameRectangle)
  {
    kahuanahil::Rectangle rec(20.0, 30.0, {10.0, 15.0});
    BOOST_CHECK_CLOSE(rec.getFrameRect().width, 20.0 , EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().height, 30.0 , EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.x, 10.0 , EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.y, 15.0 , EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaTestRectangle)
  {
    kahuanahil::Rectangle rec(10.0, 15.0, {5.0, 8.0});
    BOOST_CHECK_CLOSE(rec.getArea(), 10.0 * 15.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MovetoPointRectangleTest)
  {
    kahuanahil::Rectangle rec(20.0, 15.0, {10.0, 15.0});
    rec.move({2.0, 2.0});
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.x, 2.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.y, 2.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().width, 20.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().height, 15.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getArea(), 20.0 * 15.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveCoorRectangle)
  {
    kahuanahil::Rectangle rec(20.0, 15.0, {5.0, 8.0});
    rec.move(3.0, 2.0);
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.x, 8.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.y, 10.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().width, 20.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getFrameRect().height, 15.0, EPSILON);
    BOOST_CHECK_CLOSE(rec.getArea(), 20.0 * 15.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    kahuanahil::Rectangle rec(20.0, 10.0, {10.0, 15.0});
    rec.scale(3.0);
    BOOST_CHECK_CLOSE(rec.getArea(), 20.0*10.0*pow(3.0,2), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidFrame)
  {
    BOOST_CHECK_THROW(kahuanahil::Rectangle(-20.0, 10.0, {5.0, 8.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScale)
  {
    kahuanahil::Rectangle rec(10.0, 15.0, {5.0, 10.0});
    BOOST_CHECK_THROW(rec.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(FrameCircle)
  {
    kahuanahil::Circle cir(5.0, {10.0, 15.0});
    BOOST_CHECK_CLOSE(cir.getFrameRect().width, 5.0 * 2.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().height, 5.0 * 2.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.x, 10.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.y, 15.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(AreaTestCircle)
  {
    kahuanahil::Circle cir(10.0, {5.0, 20.0});
    BOOST_CHECK_CLOSE(cir.getArea(), (M_PI * pow(10.0,2)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MovetoPointCircle)
  {
    kahuanahil::Circle cir(5.0, {10.0, 20.0});
    cir.move({5.0, 5.0});
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.x, 5.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.y, 5.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().width, 5.0 * 2.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().height, 5.0 * 2.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getArea(), (M_PI * pow(5.0,2)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MovecoorCircle)
  {
    kahuanahil::Circle cir(10.0, {5.0, 8.0});
    cir.move(5.0, 2.0);
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.x, 10.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().pos.y, 10.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().width, 10.0 * 2.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getFrameRect().height, 10.0 * 2.0, EPSILON);
    BOOST_CHECK_CLOSE(cir.getArea(), (M_PI * pow(10.0,2)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ScaleTestCircle)
  {
    kahuanahil::Circle cir(10.0, {5.0, 5.0});
    cir.scale(3.0);
    BOOST_CHECK_CLOSE(cir.getArea(), (M_PI * pow(10.0, 2) * pow(3.0, 2)), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidRadius)
  {
    BOOST_CHECK_THROW(kahuanahil::Circle(-10.0, {5.0, 8.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleCircle)
  {
    kahuanahil::Circle cir(5.0, {8.0, 10.0});
    BOOST_CHECK_THROW(cir.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

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
    kahuanahil::Rectangle rec({10.0, 15.0, {24.0, 48.0}});
    std::shared_ptr< kahuanahil::Shape > rect = std::make_shared< kahuanahil::Rectangle > (rec);
    kahuanahil::CompositeShape composite_shape(rect);
    double AreaBeforeScale = composite_shape.getArea();   
    composite_shape.scale(3.0);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), (AreaBeforeScale * pow(3.0, 2.0)), EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(DeleteAllShape)
  {
    kahuanahil::Circle cir(45.0, {50.0, 70.0});
    kahuanahil::Rectangle rec (30.0, 40., {20.0, 15.0});
    std::shared_ptr < kahuanahil::Shape > pCircle = std::make_shared < kahuanahil::Circle > (cir);
    std::shared_ptr < kahuanahil::Shape > pRectangle = std::make_shared < kahuanahil::Rectangle > (rec);
    kahuanahil::CompositeShape compositeShape(pCircle);
    compositeShape.addShape(pRectangle);
    compositeShape.deleteAllShape();
    BOOST_CHECK_CLOSE(compositeShape.getArea(), 0.0, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, 0.0, EPSILON);
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
    BOOST_CHECK_THROW(composite_shape.deleteShape(3), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTest)

  BOOST_AUTO_TEST_CASE(Matrix)
  {
    kahuanahil::Circle cir{2.0,{ 0.0, 0.0 }};
    kahuanahil::Rectangle rec{2.0, 2.0, { 1.0, 0.0 }};
    kahuanahil::Rectangle rec2{4.0, 4.0, { -3.0, 0.0 }};
    kahuanahil::Circle cir2{5.0, { 3.0, 2.0 }};

    std::shared_ptr< kahuanahil::Shape > pCircle = std::make_shared< kahuanahil::Circle >(cir);
    std::shared_ptr< kahuanahil::Shape > pRectangle = std::make_shared< kahuanahil::Rectangle >(rec);
    std::shared_ptr< kahuanahil::Shape > pRectangle2 = std::make_shared< kahuanahil::Rectangle >(rec2);
    std::shared_ptr< kahuanahil::Shape > pCircle2 = std::make_shared< kahuanahil::Circle >(cir2);

    kahuanahil::Matrix matrix(pCircle);
    matrix.addShape(pRectangle);
    matrix.addShape(pRectangle2);
    matrix.addShape(pCircle2);

    std::unique_ptr< std::shared_ptr< kahuanahil::Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< kahuanahil::Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< kahuanahil::Shape >[] > layer3 = matrix[2];

    BOOST_CHECK_CLOSE(layer1[0]->getFrameRect().pos.x, pCircle->getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(layer2[0]->getFrameRect().pos.x, pRectangle->getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(layer2[1]->getFrameRect().pos.x, pRectangle2->getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(layer3[0]->getFrameRect().pos.x, pCircle2->getFrameRect().pos.x, EPSILON);

    BOOST_CHECK_CLOSE(layer1[0]->getFrameRect().pos.y, pCircle->getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(layer2[0]->getFrameRect().pos.y, pRectangle->getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(layer2[1]->getFrameRect().pos.y, pRectangle2->getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(layer3[0]->getFrameRect().pos.y, pCircle2->getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Matrixnullptr)
  {
    kahuanahil::Circle cir{5.0, { 1.0, 1.0 }};
    std::shared_ptr< kahuanahil::Shape > pCircle = std::make_shared< kahuanahil::Circle >(cir);
    pCircle = nullptr;

    BOOST_CHECK_THROW(kahuanahil::Matrix matrix(pCircle), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
