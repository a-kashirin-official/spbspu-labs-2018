#define BOOST_TEST_MODULE main
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

using namespace kargalov;

const double EPSILON = 0.0000001;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

const point_t center = {1, 34};
const double width = 245;
const double height = 12;
Rectangle testrect({width, height, center});
const double areaBefore = testrect.getArea();


BOOST_AUTO_TEST_CASE(testMoving)
{
    testrect.move({100, 23});
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore, EPSILON);
    
    testrect.move(45, 11);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().width, width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getFrameRect().height, height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    testrect.scale(102);
    BOOST_CHECK_CLOSE_FRACTION(testrect.getArea(), areaBefore * 102 * 102, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    BOOST_CHECK_THROW( testrect.scale(-1.0), std::invalid_argument );
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

const point_t center = {1, 34};
const double radius = 245;
Circle testcirc(center, radius);
const double areaBefore = testcirc.getArea();


BOOST_AUTO_TEST_CASE(testMoving)
{
    testcirc.move({100, 23});
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getFrameRect().width, radius * 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore, EPSILON);
    
    testcirc.move(45, 11);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getFrameRect().width, radius * 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    testcirc.scale(102);
    BOOST_CHECK_CLOSE_FRACTION(testcirc.getArea(), areaBefore * 102 * 102, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    BOOST_CHECK_THROW( testcirc.scale(-1.0), std::invalid_argument );
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)
BOOST_AUTO_TEST_CASE(testMoving)
{
    Rectangle compRect({12, 23, {11, 45}});
    Circle compCirc({16, 4}, 7);
    auto ptrRect = std::make_shared<Rectangle>(compRect);
    auto ptrCirc = std::make_shared<Circle>(compCirc);
    CompositeShape testCompSh(ptrRect);
    testCompSh.addShape(ptrCirc);
    const double areaBefore = testCompSh.getArea();
    const rectangle_t paramBefore = testCompSh.getFrameRect();

    testCompSh.move({100, 23});
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getArea(), areaBefore, EPSILON);
    
    testCompSh.move(45, 11);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
    Rectangle compRect({12, 23, {11, 45}});
    Circle compCirc({16, 4}, 7);
    auto ptrRect = std::make_shared<Rectangle>(compRect);
    auto ptrCirc = std::make_shared<Circle>(compCirc);
    CompositeShape testCompSh(ptrRect);
    testCompSh.addShape(ptrCirc);
    const double areaBefore = testCompSh.getArea();

    testCompSh.scale(102);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getArea(), areaBefore * 102 * 102, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    Rectangle compRect({12, 23, {11, 45}});
    Circle compCirc({16, 4}, 7);
    auto ptrRect = std::make_shared<Rectangle>(compRect);
    auto ptrCirc = std::make_shared<Circle>(compCirc);
    CompositeShape testCompSh(ptrRect);
    testCompSh.addShape(ptrCirc);

    BOOST_CHECK_THROW(testCompSh.scale(-1.0), std::invalid_argument);
    BOOST_CHECK_THROW(testCompSh.addShape(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(testCompSh.removeShape(23), std::invalid_argument);
    BOOST_CHECK_THROW(testCompSh.removeShape(-1), std::invalid_argument);
    BOOST_CHECK_THROW(CompositeShape testComposite(nullptr), std::invalid_argument);
    
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(EmptyCompositeShapeSuite)
BOOST_AUTO_TEST_CASE(testMoving)
{
    
    CompositeShape testCompSh;
    const double areaBefore = testCompSh.getArea();
    const rectangle_t paramBefore = testCompSh.getFrameRect();
    
    testCompSh.move({100, 23});
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getArea(), areaBefore, EPSILON);
    
    testCompSh.move(45, 11);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().width, paramBefore.width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getFrameRect().height, paramBefore.height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getArea(), areaBefore, EPSILON);
}

BOOST_AUTO_TEST_CASE(testArea){
   
    CompositeShape testCompSh;
    const double areaBefore = testCompSh.getArea();
    
    testCompSh.scale(102);
    BOOST_CHECK_CLOSE_FRACTION(testCompSh.getArea(), areaBefore * 102 * 102, EPSILON);
}

BOOST_AUTO_TEST_CASE(testIncorrectParametrs){
    
    CompositeShape testCompSh;
    
    BOOST_CHECK_THROW(testCompSh.scale(-1.0), std::invalid_argument);
    BOOST_CHECK_THROW(testCompSh.addShape(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(testCompSh.removeShape(23), std::invalid_argument);
    BOOST_CHECK_THROW(testCompSh.removeShape(-1), std::invalid_argument);
  
}
BOOST_AUTO_TEST_SUITE_END()


