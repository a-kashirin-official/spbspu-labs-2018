#define BOOST_TEST_MODULE main
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace vlasov;

const double EPSILON = 0.0000001;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

const point_t center = {1.0, 34.0};
const double width = 245.0;
const double height = 12.0;
vlasov::Rectangle testrect({width, height, center});
const double areaBefore = testrect.getArea();


BOOST_AUTO_TEST_CASE(testMoving)
{
    testrect.move({100.0, 23.0});
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore, EPSILON);
    
    testrect.move(45.0, 11.0);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    testrect.scale(102.0);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore * 102.0 * 102.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    BOOST_CHECK_THROW( testrect.scale(-1.0), std::invalid_argument );
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

const point_t center = {1.0, 34.0};
const double radius = 245.0;
Circle testcirc(radius, center);
const double areaBefore = testcirc.getArea();


BOOST_AUTO_TEST_CASE(testMoving)
{
    testcirc.move({100.0, 23});
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getFrameRect().width, radius * 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore, EPSILON);
    
    testcirc.move(45.0, 11.0);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getFrameRect().width, radius * 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    testcirc.scale(102.0);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore * 102.0 * 102.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    BOOST_CHECK_THROW( testcirc.scale(-1.0), std::invalid_argument );
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)
BOOST_AUTO_TEST_CASE(testMoving)
{
    vlasov::Rectangle compRect({12.0, 23.0, {11.0, 45.0}});
    Circle compCirc(7.0, {16.0, 4.0});
    auto ptrRect = std::make_shared<vlasov::Rectangle>(compRect);
    auto ptrCirc = std::make_shared<Circle>(compCirc);
    CompositeShape composition(ptrRect);
    composition.add(ptrCirc);
    const double areaBefore = composition.getArea();
    const rectangle_t paramBefore = composition.getFrameRect();

    composition.move({100.0, 23});
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getArea(), areaBefore, EPSILON);
    
    composition.move(45.0, 11.0);
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    vlasov::Rectangle compRect({12.0, 23.0, {11.0, 45.0}});
    Circle compCirc(7.0, {16.0, 4.0});
    auto ptrRect = std::make_shared<vlasov::Rectangle>(compRect);
    auto ptrCirc = std::make_shared<Circle>(compCirc);
    CompositeShape composition(ptrRect);
    composition.add(ptrCirc);
    const double areaBefore = composition.getArea();

    composition.scale(102.0);
    BOOST_CHECK_CLOSE_FRACTION(composition.getArea(), areaBefore * 102.0 * 102.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    vlasov::Rectangle compRect({12.0, 23.0, {11.0, 45.0}});
    Circle compCirc(7.0, {16.0, 4.0});
    auto ptrRect = std::make_shared<vlasov::Rectangle>(compRect);
    auto ptrCirc = std::make_shared<Circle>(compCirc);
    CompositeShape composition(ptrRect);
    composition.add(ptrCirc);

    BOOST_CHECK_THROW(composition.scale(-1.0), std::invalid_argument);
    BOOST_CHECK_THROW(composition.add(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(composition.remove(23), std::invalid_argument);
    BOOST_CHECK_THROW(composition.remove(-1), std::invalid_argument);
    BOOST_CHECK_THROW(CompositeShape testComposite(nullptr), std::invalid_argument);
    
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(EmptyCompositeShapeSuite)
BOOST_AUTO_TEST_CASE(testMoving)
{
    
    CompositeShape composition;
    const double areaBefore = composition.getArea();
    const rectangle_t paramBefore = composition.getFrameRect();
    
    composition.move({100.0, 23.0});
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getArea(), areaBefore, EPSILON);
    
    composition.move(45.0, 11.0);
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(composition.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
   
    CompositeShape composition;
    const double areaBefore = composition.getArea();
    
    composition.scale(102.0);
    BOOST_CHECK_CLOSE_FRACTION(composition.getArea(), areaBefore * 102.0 * 102.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    
    CompositeShape composition;
    
    BOOST_CHECK_THROW(composition.scale(-1.0), std::invalid_argument);
    BOOST_CHECK_THROW(composition.add(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(composition.remove(23), std::invalid_argument);
    BOOST_CHECK_THROW(composition.remove(-1), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()


