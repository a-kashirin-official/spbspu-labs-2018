#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include "shape.hpp"
#include <memory>

namespace shapiev
{
    class CompositeShape : public Shape
    {
    public:
        CompositeShape();
        CompositeShape(const CompositeShape & rhs);
        CompositeShape(CompositeShape && rhs);
        using ptr_type = std::shared_ptr < Shape >;

        CompositeShape & operator =(const CompositeShape & rhs);
        CompositeShape & operator =(CompositeShape && rhs);

        size_t size() const;
        ptr_type operator [](size_t index) const;
        void addShape(const ptr_type & shape);
        void removeShape(const size_t index);
        void rotate(const double angle);


        double getArea() const ;
        rectangle_t getFrameRect() const ;
        void move(const point_t & resPoint);
        void move(const double dx, const double dy);
        void scale(const double value);
        point_t getPos() const ;

    private:
        size_t size_;
        std::unique_ptr<ptr_type[]> shapes_;
        double angle_;
    };
}

#endif
