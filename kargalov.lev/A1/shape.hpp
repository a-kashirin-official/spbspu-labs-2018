#ifndef Shape_hpp
#define Shape_hpp

#include "base-types.hpp"

class Shape {
public:
    virtual ~Shape() = default;
    virtual void move(const point_t& point) = 0;
    virtual void move(double dx , double dy) = 0;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
};
#endif /* Shape_hpp */
