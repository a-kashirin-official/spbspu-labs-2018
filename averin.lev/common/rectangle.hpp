#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
#include "base-types.hpp"

namespace averin
{
class Rectangle : public Shape 
{
public:       

  //Height, width, x y cords of center
  Rectangle(double h, double w, double x, double y);
    
  double getArea() const override;
       
  rectangle_t getFrameRect() const override;  
    
  void printInfo() const override;
  
  void move(point_t c) override;
  
  void move(double dx, double dy) override; 
  
  void scale(double ratio) override;
  
  double getHeight();
  
  double getWidth();
  
  void rotate(double deg) override;

  void printAngle() const override;
  
  void setAngle(double deg) override;
  
  void printName() const override;
    
private:
    
  double height_;
    
  double width_;
  
  point_t center_;
  
  double angle_;
  
  point_t topLeft_;
 
};
}
#endif
