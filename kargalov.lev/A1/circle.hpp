#ifndef Circle_hpp
#define Circle_hpp

#include "shape.hpp"

class Circle:
public Shape
{
public:
    Circle(const point_t& center, const double radius);
    void move(const point_t& point) override;
    void move(const double dx, const double dy) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
private:
    point_t center_;
    double radius_;
};
#endif /* Circle_hpp */
