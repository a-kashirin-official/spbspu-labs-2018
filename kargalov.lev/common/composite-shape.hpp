#ifndef composite_shape_hpp
#define composite_shape_hpp

#include <memory>
#include "shape.hpp"

namespace kargalov {
    
    class CompositeShape : public Shape
    {
    public:
        CompositeShape(std::shared_ptr<Shape> newShape);
        CompositeShape();
        void move(const point_t& point) override;
        void move(const double dx, const double dy) override;
        void scale(const double increment) override;
        double getArea() const override;
        rectangle_t getFrameRect() const override;
        
        void addShape(const std::shared_ptr<Shape> newShape);
        void removeShape(const int index);
        
    private:
        int size_;
        std::unique_ptr<std::shared_ptr<Shape> []> list_;
        
        
        
    };
}
#endif /* composite_shape_hpp */
