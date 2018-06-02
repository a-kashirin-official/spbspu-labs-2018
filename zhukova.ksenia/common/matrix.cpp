
#include "matrix.hpp"
#include <iostream>
#include <sstream>

zhukova::Matrix::Matrix(const CompositeShape & arg):
  countLayer_(0),
  layersLength_(0),
  shapeMatrix_()
{
  rectangle_t rec = { 0, 0, { 0, 0 } };

  boost::shared_array < int > layerIndex{ new int [arg.getCount()] };
  for (int i = 0; i < arg.getCount(); i++) {
    layerIndex[i] = -1;
  }

  bool addInCurLayer = true;
  bool addInNewLayer = true;

  for (int i = 0; i < arg.getCount(); i++) {
    rec = arg[i]->getFrameRect();

    addInNewLayer = true;
    for (int j = 0; j < countLayer_; j++) {
      
      addInCurLayer = true;
      for (int k = 0; k < i; k++) {
        if (layerIndex[k] == j) {
          if ( checkCross(rec, arg[k]->getFrameRect()) ) {
            addInCurLayer = false;
            break;
          }
        }
      }

      if (addInCurLayer) {
        layerIndex[i] = j;
        addInNewLayer = false;
        break;
      }

    }

    if (addInNewLayer) {
      layerIndex[i] = countLayer_++;
    }
  }

  int count = 0;
  for (int i = 0; i < countLayer_; i++) {
    count = 0;
    for (int j = 0; j < arg.getCount(); j++) {
      if (layerIndex[j] == i) {
        count++;
      }
    }
    layersLength_ = (count > layersLength_ ? count : layersLength_);
  }

  shapeMatrix_ = boost::shared_array< std::shared_ptr <Shape> >{ new std::shared_ptr <Shape> [countLayer_ * layersLength_] };
  for (int i = 0; i < countLayer_ * layersLength_; i++) {
    shapeMatrix_[i] = nullptr;
  }

  for (int i = 0; i < countLayer_; i++) {
    count = 0;
    for (int j = 0; j < arg.getCount(); j++) {
      if (layerIndex[j] == i) {
        shapeMatrix_[i * layersLength_ + count] = arg[j];
        count++;
      }
    }
  }

}

zhukova::Matrix::Matrix(const zhukova::Matrix & arg):
  countLayer_(0),
  layersLength_(0),
  shapeMatrix_()
{
  if (this != & arg) {
    shapeMatrix_ = boost::shared_array< std::shared_ptr <Shape> >
        { new std::shared_ptr <Shape> [arg.countLayer_ * arg.layersLength_] };

    countLayer_ = arg.countLayer_;
    layersLength_ = arg.layersLength_;
    
    for (int i = 0; i < countLayer_ * layersLength_; i++) {
      shapeMatrix_[i] = arg.shapeMatrix_ [i];
    }
  } else {
    throw std::invalid_argument("Matrix: initialization by itself");
  }
}

std::shared_ptr <zhukova::Shape> zhukova::Matrix::operator [] (matrixIndex i)
{
  if ( (i.layer >= countLayer_) || (i.layer < 0) ) {
    throw std::invalid_argument("Matrix: index out of range");
  }
  if ((i.shape >= layersLength_) || (i.shape < 0)) {
    throw std::invalid_argument("Matrix: index out of range");
  } 

  return shapeMatrix_[i.layer * layersLength_ + i.shape];
}

std::shared_ptr <zhukova::Shape> * zhukova::Matrix::operator [] (int i)
{
  if ((i >= countLayer_) || (i < 0)) {
    throw std::invalid_argument("Matrix: index out of range");
  }

  return & shapeMatrix_[i * layersLength_];
}

std::string zhukova::Matrix::getInfo() const
{
  std::ostringstream outStr;
  rectangle_t rect = { 0, 0, { 0, 0 } };

  outStr << std::fixed;
  outStr.precision(2);

  for (int i = 0; i < countLayer_; i++) {

    outStr << std::to_string(i + 1);
    outStr << " LAYER" << std::endl;

    for (int j = 0; j < layersLength_; j++) {
      if (shapeMatrix_[i*layersLength_ + j] != nullptr) {
        rect = shapeMatrix_[i*layersLength_ + j]->getFrameRect();

        outStr << "\tCenter { " << rect.pos.x << ", " << rect.pos.y
          << " }, width = " << rect.width << ", height = " << rect.height << std::endl;
      } else {
        outStr << "\tnullptr" << std::endl;
      }
    }
  }
  return outStr.str();
}

zhukova::Matrix & zhukova::Matrix::operator = (const zhukova::Matrix & rhs)
{
  if (this !=  & rhs) {
    shapeMatrix_ = boost::shared_array< std::shared_ptr <Shape> >
        { new std::shared_ptr <Shape>[countLayer_ * layersLength_] };

    countLayer_ = rhs.countLayer_;
    layersLength_ = rhs.layersLength_;

    for (int i = 0; i < countLayer_ * layersLength_; i++) {
      shapeMatrix_[i] = rhs.shapeMatrix_[i];
    }
  } else {
    throw std::invalid_argument("Matrix: assignment by itself");
  }
  return *this;
}

bool zhukova::Matrix::checkCross(const rectangle_t & r1, const rectangle_t & r2) const
{
  double left1 = r1.pos.x - (r1.width / 2);
  double left2 = r2.pos.x - (r2.width / 2);
  double right1 = r1.pos.x + (r1.width / 2);
  double right2 = r2.pos.x + (r2.width / 2);

  double top1 = r1.pos.y + (r1.height / 2);
  double top2 = r2.pos.y + (r2.height / 2);
  double bottom1 = r1.pos.y - (r1.height / 2);
  double bottom2 = r2.pos.y - (r2.height / 2);

  return !(left1 > right2 || right1 < left2 || top1 < bottom2 || bottom1 > top2);

  //if(r1.left > r2.right || r1.right < r2.left || r1.top < r2.bottom || r1.bottom > r2.top) return false;
  //return true;
}
