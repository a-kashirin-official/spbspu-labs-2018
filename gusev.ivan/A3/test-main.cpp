#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

using namespace gusev;

const double dx = 0.000001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)

  BOOST_AUTO_TEST_CASE(CompositeShapeMove1Test)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0 });
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.move({ 1, 1 });
    BOOST_CHECK_CLOSE_FRACTION(comp.getArea(),circ.getArea() + rect.getArea() + trian.getArea(), dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.x, 1, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.y, 1, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().width, 5, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().height, 4, dx);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeMove2Test)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0});
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.move(5.5, 3.0);
    BOOST_CHECK_CLOSE_FRACTION(comp.getArea(),circ.getArea() + rect.getArea() + trian.getArea(), dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.x, 7, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.y, 4, dx);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeScaleTest)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0});
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    point_t center = comp.getFrameRect().pos;
    comp.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(comp.getArea(),(circ.getArea() + rect.getArea() + trian.getArea()) * 4, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.x, center.x, dx);
    BOOST_CHECK_CLOSE_FRACTION(comp.getFrameRect().pos.y, center.y, dx);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemoveFigureTest)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0});
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.removeFigure(2);
    BOOST_CHECK_EQUAL(comp.getCount(), 2);
    BOOST_CHECK_EQUAL(comp.getArea(), rect.getArea() + trian.getArea());
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.x, 2);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.y, 1);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemoveAllTest)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0});
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    comp.removeAll();
    BOOST_CHECK_EQUAL(comp.getCount(), 0);
    BOOST_CHECK_EQUAL(comp.getArea(), 0);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeScaleInvalidTest)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0});
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    BOOST_CHECK_THROW(comp.scale(-2), std::invalid_argument);
    BOOST_CHECK_THROW(comp.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemoveInvalidTest)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0});
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    BOOST_CHECK_THROW(comp.removeFigure(11), std::out_of_range);
    BOOST_CHECK_THROW(comp.removeFigure(-1), std::out_of_range);
    comp.removeAll();
    BOOST_CHECK_THROW(comp.removeFigure(1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeAddShapeInvalidTest)
  {
    Triangle trian({ 0, 0 }, { 4, 0 }, { 0, 2 });
    Circle circ(1, { 0, 0});
    Rectangle rect(2, 4, { 1, 1 });
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);
    CompositeShape comp(rectPtr);
    comp.addShape(circPtr);
    comp.addShape(trianPtr);
    BOOST_CHECK_THROW(comp.addShape(rectPtr), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
