#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{

  try
  {

    lyachko::Circle circle( { 0, 0 }, 5 );
    lyachko::Rectangle rectangle1( { { 10, 10 }, 4, 4 } );
    lyachko::Rectangle rectangle2( { { 4, 4 }, 3, 3 });

    lyachko::Shape * pShape;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    pShape = &circle;

    std::cout<<" Circle's ("<<pShape->getFrameRect().pos.x<<","<<pShape->getFrameRect().pos.y
             <<")"<<std::endl<<" Radius : "<<pShape->getFrameRect().width/2<<std::endl
             <<" Area : "<<pShape->getArea()<<std::endl;

    lyachko::CompositeShape compositeshape_cc ( pShape );
    lyachko::CompositeShape compositeshape = compositeshape_cc;

    std::cout<<" Cmp Width: "<<compositeshape.getFrameRect().width<<std::endl;
    std::cout<<" Cmp Height "<<compositeshape.getFrameRect().height<<std::endl;
    std::cout<<" Cmp Area: "<<compositeshape.getArea()<<std::endl;

    std::cout << "---------------------------------------------" << std::endl;

    pShape = &rectangle1;

    std::cout<<" Rectangle's ("<<pShape->getFrameRect().pos.x<<", "<<pShape->getFrameRect().pos.y<<")"<<std::endl 
             <<" Height : "<<pShape->getFrameRect().height<<std::endl
             <<" Width : "<<pShape->getFrameRect().width<<std::endl
             <<" Area : "<<pShape->getArea()<<std::endl;

    compositeshape.add( pShape );

    std::cout<<" Cmp Width: "<<compositeshape.getFrameRect().width<<std::endl;
    std::cout<<" Cmp Height: "<<compositeshape.getFrameRect().height<<std::endl;
    std::cout<<" Cmp Area: "<<compositeshape.getArea()<<std::endl;

    std::cout << "---------------------------------------------" << std::endl;

    pShape = &rectangle2;

    std::cout<<" Rectangle's ("<<pShape->getFrameRect().pos.x<<", "<<pShape->getFrameRect().pos.y<<")"<<std::endl 
             <<" Height : "<<pShape->getFrameRect().height<<std::endl
             <<" Width : "<<pShape->getFrameRect().width<<std::endl
             <<" Area : "<<pShape->getArea()<<std::endl;

    compositeshape.add( pShape );

    std::cout<<" Cmp Width: "<<compositeshape.getFrameRect().width<<std::endl;
    std::cout<<" Cmp Height: "<<compositeshape.getFrameRect().height<<std::endl;
    std::cout<<" Cmp Area: "<<compositeshape.getArea()<<std::endl;

    std::cout << "---------------------------------------------" << std::endl;

    std::cout<<" Scaling by 2 "<<std::endl;
    compositeshape.scale( 2.0 );

    std::cout<<" Cmp Width: "<<compositeshape.getFrameRect().width<<std::endl;
    std::cout<<" Cmp Height "<<compositeshape.getFrameRect().height<<std::endl;
    std::cout<<" Cmp Area: "<<compositeshape.getArea()<<std::endl;

    std::cout << "---------------------------------------------" << std::endl;

    std::cout<<" Removing 1nd Shape "<<std::endl;
    compositeshape.remove( 1 );

    std::cout<<" Cmp Width: "<<compositeshape.getFrameRect().width<<std::endl;
    std::cout<<" Cmp Height "<<compositeshape.getFrameRect().height<<std::endl;
    std::cout<<" Cmp Area: "<<compositeshape.getArea()<<std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
  
  } catch ( std::invalid_argument & smth ) 
  {
    std::cerr << smth.what() << std::endl;
    return 1; 
  }
  return 0;
}
