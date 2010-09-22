/**
 * \file QTouchSelectionWidget.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#include "QTouchSelectionWidget.h"

#include <QDebug>

#include <QDir>
#include <QFileInfo>
#include <QPainter>
#include <QMouseEvent>
QTouchSelectionWidget::QTouchSelectionWidget(QWidget *parent)
 : QWidget(parent)
 , d_seed(0.0)
 , d_moving(false){

}

QTouchSelectionWidget::~QTouchSelectionWidget() {

}

void QTouchSelectionWidget::populateWithDirectory(const QString & dir){
  d_openedImage.clear();
  qDebug()<<"Inspecting "<<dir;
  QDir directory(dir);
  foreach(const QFileInfo & file, directory.entryInfoList()){
    if(file.isDir())
      continue;
    if(file.isFile()){
      QString suffix=file.suffix();
      qDebug() << "File "<< file.filePath() <<" has suffix "<< suffix;
      if(suffix == "jpg" || suffix == "jpeg"){
        ThumbImage pix(file.filePath());
        d_openedImage.push_back(pix);
        qDebug()<<"Added an image";
      }
    }
  }
}


ThumbImage::ThumbImage(const QString & file)
 : d_pixmap(file){
  setSize();
}

ThumbImage::ThumbImage(const QPixmap & pixmap)
 : d_pixmap(pixmap){
  setSize();
}

void ThumbImage::setSize(){
  if(d_pixmap.width()>d_pixmap.height()){
      d_thumbWidth = s_maxWidthHeight;
      d_factor = s_maxWidthHeight / qreal(d_pixmap.width());
      d_thumbHeight = qreal(d_pixmap.height())* d_factor;
  }else{
      d_thumbHeight = 100;
      d_factor = s_maxWidthHeight / qreal(d_pixmap.height());
      d_thumbWidth = qreal(d_pixmap.width())* d_factor;
  }
}

void QTouchSelectionWidget::paint(QPainter * p){
  p->save();
//  p->setPen(Qt::NoPen);
//  p->setBrush(QColor(0,0,255));
//  p->drawRect(QRect(0,0,width(),height()));
  p->translate(0.0,height()/qreal(2));

  qreal myWidth(width());

  unsigned int index=0;
  while(index < d_openedImage.length()
        && posOfImage(index)+ThumbImage::maxWidthHeightSize() < 0 ){
    ++index;
  }
  while(index < d_openedImage.length() &&
        posOfImage(index) < myWidth){
    const ThumbImage & thumb = d_openedImage.at(index);
    QRectF imageRect(posOfImage(index),-thumb.height()/2.0,
                     thumb.width(),
                     thumb.height());
    p->drawPixmap(imageRect,thumb.const_pixmap(),
                  QRectF(0.0,0.0,
                  thumb.const_pixmap().width(),
                  thumb.const_pixmap().height()));
//    p->setPen(QPen(QColor(255, 0, 0), 0.25, Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin));
//    p->setBrush(Qt::NoBrush);
//    p->drawRect(imageRect.adjusted(-2,-2,2,2));
    ++index;
  }
  p->restore();
}

void QTouchSelectionWidget::paintEvent(QPaintEvent *e){
  QPainter p(this);
  this->paint(&p);
}


qreal ThumbImage::height() const {
  return d_thumbHeight;
}

qreal ThumbImage::width() const {
  return d_thumbWidth;
}

qreal QTouchSelectionWidget::s_margin (20.0);

const QPixmap & ThumbImage::const_pixmap()const{
  return d_pixmap;
}

QPixmap & ThumbImage::pixmap(){
  return d_pixmap;
}

qreal ThumbImage::s_maxWidthHeight(100.0);

qreal ThumbImage::maxWidthHeightSize(){
  return s_maxWidthHeight;
}

void QTouchSelectionWidget::updateSeed(const QPointF & pos){
  d_seed -= pos.x() - d_lastPos.x();
  d_lastPos = pos;
  d_seed=std::max(-3.0*s_margin,std::min(maxSeed()+4.0*s_margin,d_seed));
  update();
}

void QTouchSelectionWidget::mouseMoveEvent(QMouseEvent *e){
  if(e->buttons() & Qt::LeftButton && d_moving){
    updateSeed(e->posF());
  }
}

void QTouchSelectionWidget::mouseReleaseEvent(QMouseEvent *e){
  if(e->buttons() & Qt::LeftButton && d_moving){
    updateSeed(e->posF());
    d_moving = false;
  }
}

void QTouchSelectionWidget::mousePressEvent(QMouseEvent *e){
  if(e->button() == Qt::LeftButton){
    d_moving = true;
    d_lastPos = e->posF();
  }
  if(e->button() & Qt::RightButton){
    mouseDoubleClickEvent(e);
  }
}

void QTouchSelectionWidget::mouseDoubleClickEvent(QMouseEvent *e){
  for(ListOfQPixmap::iterator image = d_openedImage.begin();
      image != d_openedImage.end();
      ++image){
    qreal posOFThumb(posOfImage(image-d_openedImage.begin()));
    if(posOFThumb >e->posF().x())
      break;
    if(posOFThumb+ThumbImage::maxWidthHeightSize() > e->posF().x()){
      emit openedImage(image->pixmap());
    }
  }
}

