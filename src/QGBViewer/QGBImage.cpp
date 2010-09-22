/**
 * \file QGBImage.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#include "QGBImage.h"


QGBImage::QGBImage(const QPixmap & pixmap)
 : d_pixmap(&pixmap)
 , d_scale(1.0)
 , d_angle(0.0)
 , d_position(0.0,0.0){
}

QGBImage::~QGBImage(){

}

void QGBImage::setAngle(double angle){
  d_angle=angle;
}

void QGBImage::setScale(double scale){
  d_scale = scale;
}

const QPixmap & QGBImage::pixmap() const{
  return *d_pixmap;
}

double QGBImage::scale() const{
  return d_scale;
}

double QGBImage::angle() const{
  return d_angle;
}

const QPointF & QGBImage::const_position() const{
  return d_position;
}

QPointF & QGBImage::position(){
  return d_position;
}



