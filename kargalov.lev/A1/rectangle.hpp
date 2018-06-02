
#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "shape.hpp"

class Rectangle:
    public Shape
{
public:
    Rectangle(const rectangle_t& parametrs);
    void move(const point_t& point) override;
    void move(const double dx, const double dy) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
private:
    rectangle_t parametrs_;
};

#endif /* Rectangle_hpp */
