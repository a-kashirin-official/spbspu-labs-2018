#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <memory>
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/composite-shape.hpp"

#include <boost/test/included/unit_test.hpp>

const double EPS = 0.000001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(ConstructorTest)
  {
    std::shared_ptr <belonogova::Shape> emptyShape = nullptr;
    BOOST_CHECK_THROW(belonogova::CompositeShape comp(emptyShape), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared <belonogova::Rectangle> (belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::CompositeShape otherComp(rect);
    otherComp.addComponent(circ);

    belonogova::CompositeShape comp1{otherComp};

    BOOST_CHECK_EQUAL(comp1.getSize(), otherComp.getSize());
    BOOST_CHECK_CLOSE(comp1.getArea(), otherComp.getArea(), EPS);
    BOOST_CHECK_EQUAL(comp1.getFrameRect().pos.x, otherComp.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(comp1.getFrameRect().pos.y, otherComp.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared <belonogova::Rectangle> (belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::CompositeShape otherComp(rect);
    otherComp.addComponent(circ);

    double otherSize = otherComp.getSize();
    double otherArea = otherComp.getArea();
    belonogova::rectangle_t otherFrame = otherComp.getFrameRect();

    belonogova::CompositeShape comp2{std::move(otherComp)};

    BOOST_CHECK_EQUAL(otherComp.getSize(), 0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().width, 0.0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().height, 0.0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().pos.x, 0.0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().pos.y, 0.0);

    BOOST_CHECK_EQUAL(comp2.getSize(), otherSize);
    BOOST_CHECK_CLOSE(comp2.getArea(), otherArea, EPS);
    BOOST_CHECK_EQUAL(comp2.getFrameRect().pos.x, otherFrame.pos.x);
    BOOST_CHECK_EQUAL(comp2.getFrameRect().pos.y, otherFrame.pos.y);
  }

  BOOST_AUTO_TEST_CASE(CopyAssigmentOperatorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared <belonogova::Rectangle> (belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::CompositeShape otherComp(rect);
    otherComp.addComponent(circ);
    belonogova::CompositeShape comp1(rect);

    comp1 = otherComp;

    BOOST_CHECK_EQUAL(comp1.getSize(), otherComp.getSize());
    BOOST_CHECK_CLOSE(comp1.getArea(), otherComp.getArea(), EPS);
    BOOST_CHECK_EQUAL(comp1.getFrameRect().pos.x, otherComp.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(comp1.getFrameRect().pos.y, otherComp.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(MoveAssigmentOperatorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared <belonogova::Rectangle> (belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::CompositeShape otherComp(rect);
    otherComp.addComponent(circ);

    double otherSize = otherComp.getSize();
    double otherArea = otherComp.getArea();
    belonogova::rectangle_t otherFrame = otherComp.getFrameRect();

    belonogova::CompositeShape comp2(rect);
    comp2 = std::move(otherComp);

    BOOST_CHECK_EQUAL(otherComp.getSize(), 0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().width, 0.0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().height, 0.0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().pos.x, 0.0);
    BOOST_CHECK_EQUAL(otherComp.getFrameRect().pos.y, 0.0);

    BOOST_CHECK_EQUAL(comp2.getSize(), otherSize);
    BOOST_CHECK_CLOSE(comp2.getArea(), otherArea, EPS);
    BOOST_CHECK_EQUAL(comp2.getFrameRect().pos.x, otherFrame.pos.x);
    BOOST_CHECK_EQUAL(comp2.getFrameRect().pos.y, otherFrame.pos.y);
  }

  BOOST_AUTO_TEST_CASE (IndexOperatorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    belonogova::CompositeShape comp(rect);
    BOOST_CHECK_THROW(comp[7], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE (MovesTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::CompositeShape comp(rect);
    comp.addComponent(circ);

    belonogova::rectangle_t originalFrame = comp.getFrameRect();
    double originalArea = comp.getArea();
    double dx = 2.0;
    double dy = 5.0;
    comp.move(dx, dy);

    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, originalFrame.pos.x + dx, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, originalFrame.pos.y + dy, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, originalFrame.width, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, originalFrame.height, EPS);
    BOOST_CHECK_CLOSE(comp.getArea(), originalArea, EPS);

    belonogova::point_t newPos = {5.0, 0.0};
    comp.move(newPos);

    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.x, newPos.x);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.y, newPos.y);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::CompositeShape comp(rect);
    comp.addComponent(circ);

    double originalArea = comp.getArea();
    double originalWidth = comp.getFrameRect().width;
    double originalHeight = comp.getFrameRect().height;
    belonogova::point_t originalPos = comp.getFrameRect().pos;
    double coef = 3.0;
    comp.scale(coef);

    BOOST_CHECK_CLOSE(comp.getFrameRect().width, originalWidth*coef, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, originalHeight*coef, EPS);
    BOOST_CHECK_CLOSE(comp.getArea(), originalArea*coef*coef, EPS);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.x, originalPos.x);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.y, originalPos.y);
  }

  BOOST_AUTO_TEST_CASE(AddComponentTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    belonogova::CompositeShape comp(rect);
    std::shared_ptr <belonogova::Shape> emptyShape = nullptr;
    BOOST_CHECK_THROW(comp.addComponent(emptyShape), std::invalid_argument);
    BOOST_CHECK_THROW(comp.addComponent(rect), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RemoveComponentTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    belonogova::CompositeShape comp(rect);
    BOOST_CHECK_THROW(comp.removeComponent(5), std::invalid_argument);
    BOOST_CHECK_THROW(comp.removeComponent(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
