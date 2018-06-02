#ifndef BASETYPES
#define BASETYPES
namespace shapiev{
struct point_t {
  double x,y;
};
struct rectangle_t {
  double width, height;
  point_t pos;
};
}
#endif // BASETYPES
