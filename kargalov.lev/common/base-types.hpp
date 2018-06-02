#ifndef base_types_hpp
#define base_types_hpp

namespace kargalov {
struct point_t {
    double x;
    double y;
};

struct rectangle_t {
    double width;
    double height;
    point_t pos;
};
}
#endif /* base_types_hpp */
