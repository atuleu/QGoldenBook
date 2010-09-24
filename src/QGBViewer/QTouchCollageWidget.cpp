/**
 * \file QTouchCollageWidget.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */
#include <cmath>
#include "QTouchCollageWidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTouchEvent>
#include <iostream>

QTouchCollageWidget::QTouchCollageWidget(QWidget * parent)
: QWidget(parent)
, d_selectedImage(0){
  initSelectionPixmap();
  this->setAttribute(Qt::WA_AcceptTouchEvents);
}

QTouchCollageWidget::~QTouchCollageWidget() {

}

void QTouchCollageWidget::paint(QPainter *p, bool rectanle) {
  p->save();
  p->setRenderHint(QPainter::Antialiasing);
  p->setRenderHint(QPainter::SmoothPixmapTransform);
  for (unsigned int i=0;i<d_displayedImage.length();++i){
    renderAnImage(p,d_displayedImage.at(i),rectanle?i+1:-1);
  }

  p->restore();
}

void QTouchCollageWidget::renderAnImage(QPainter *p,
                                        const QGBImage & image,
                                        int color){
  p->save();


  QPointF center(image.pixmap().width()/2.0,image.pixmap().height()/2.0);
  p->translate(image.const_position());
  p->scale(image.scale(),image.scale());
  p->rotate(image.angle());
  p->translate(-center);

  if(color>=0){
    p->setPen(Qt::NoPen);
    p->setBrush(QColor(color,color,color,255));
    p->setRenderHint(QPainter::Antialiasing,false);
    p->setRenderHint(QPainter::SmoothPixmapTransform,false);
    p->drawRect(0,0,image.pixmap().width(),image.pixmap().height());
  }
  else{
    p->drawPixmap(QPointF(0.0,0.0),image.pixmap());
  }

  p->restore();
}

void QTouchCollageWidget::addNewImage(QPixmap & pixmap){

  //first sets the image to 33% of the screen size
  qreal maxWH = std::max(pixmap.width(),pixmap.height());

  qreal scale = width()/(qreal(3) * maxWH );

  qreal angle = (qrand() / qreal(RAND_MAX) -0.5) * 1.6;

  qreal x = ((qrand() / qreal(RAND_MAX))*0.66+0.16)*width();
  qreal y = ((qrand() / qreal(RAND_MAX))*0.66+0.16)*height();

  QGBImage image(pixmap);
  image.position()=QPointF(x,y);
  image.setAngle(angle);
  image.setScale(scale);

  d_displayedImage.push_back(image);

  update();

}

void QTouchCollageWidget::paintEvent(QPaintEvent *){
  QPainter p(this);
  this->paint(&p);

  d_selectionPixmap.fill(Qt::black);
  QPainter selecP(&d_selectionPixmap);
  this->paint(&selecP,true);


}


void QTouchCollageWidget::resizeEvent(QResizeEvent *e){
  initSelectionPixmap();
}

void QTouchCollageWidget::initSelectionPixmap(){
  QPixmap newPixmap = QPixmap(width(), height());
  newPixmap.fill(Qt::black);
  QPainter painter(&newPixmap);
  if (!d_selectionPixmap.isNull())
      painter.drawPixmap(0, 0, d_selectionPixmap);
  painter.end();
  d_selectionPixmap = newPixmap;
}

int QTouchCollageWidget::selectImageAtPosition(const QPoint & position){
  int index = qGray(d_selectionPixmap.toImage().pixel(position));
  if(index == 0)
    return index-1;
  for(ListOfImage::iterator it= d_displayedImage.begin();
      it - d_displayedImage.begin() <= index-1;
      ++it){
    d_selectedImage = &(*it);
  }
  return index-1;
}

void QTouchCollageWidget::mousePressEvent(QMouseEvent *e){
  if(e->button() == Qt::LeftButton){
    selectImageAtPosition(e->pos());
    d_lastPosition = e->posF();
  }
  if(e->button() == Qt::RightButton){
    mouseDoubleClickEvent(e);
  }
}

void QTouchCollageWidget::mouseDoubleClickEvent(QMouseEvent *e){
  int index = selectImageAtPosition(e->pos());

  if(!d_selectedImage)
    return;

  d_selectedImage = NULL ; //unselect the image right now !!!

  d_displayedImage.move(index,d_displayedImage.length()-1);

  update();
}


void QTouchCollageWidget::mouseMoveEvent(QMouseEvent *e){
  if(e->buttons() & Qt::LeftButton && d_selectedImage != NULL){
    d_selectedImage->position() += e->posF() - d_lastPosition;
    d_lastPosition = e->posF();
    update();
  }
}

void QTouchCollageWidget::mouseReleaseEvent(QMouseEvent *e){
  if(e->buttons() & Qt::LeftButton && d_selectedImage != NULL){
    d_selectedImage->position() += e->posF() - d_lastPosition;
    d_lastPosition = e->posF();
    update();
  }
  d_selectedImage = NULL;
}

bool QTouchCollageWidget::event(QEvent *e){
  if(e->type() == QEvent::TouchBegin ||
     e->type() == QEvent::TouchEnd ||
     e->type() == QEvent::TouchUpdate){
    QTouchEvent *event = static_cast<QTouchEvent *>(e);
    switch(e->type()){
    case QEvent::TouchBegin :
      touchBeginEvent(event);
      break;
    case QEvent::TouchUpdate :
      touchUpdateEvent(event);
      break;
    case QEvent::TouchEnd :
      touchEndEvent(event);
      break;
    }
	return true;
  }
  return QWidget::event(e);
}


void QTouchCollageWidget::touchBeginEvent(QTouchEvent *e){
  if(e->touchPoints().count() != 1){
    e->ignore();
    return;
  }
  e->accept();
  const QTouchEvent::TouchPoint & first = e->touchPoints().first();
 

  int indexFirst = selectImageAtPosition(QPoint(first.pos().x(),first.pos().y()));


  if(indexFirst == -1){
    d_selectedImage =NULL; //deselect image;
    return;
  }

  d_saveAngle = d_selectedImage->angle();
  d_saveScale = d_selectedImage->scale();

}


void QTouchCollageWidget::updateScaleAngle(QTouchEvent *e){
  if(e->touchPoints().count() != 2){
      return;
  }

  e->accept();
  const QTouchEvent::TouchPoint & first = e->touchPoints().first();
  const QTouchEvent::TouchPoint & last = e->touchPoints().last();

  int indexFirst = selectImageAtPosition(QPoint(first.pos().x(),first.pos().y()));
  int indexLast = selectImageAtPosition(QPoint(first.pos().x(),first.pos().y()));

  qreal scaleFactor = 0.2*QLineF(first.pos(), last.pos()).length()
                               / QLineF(first.startPos(), last.startPos()).length() + 0.8;


  QPointF vecNow(first.pos()-last.pos());
  QPointF vecStart(first.startPos()-last.startPos());


  qreal normNow = std::sqrt(vecNow.x()*vecNow.x()+vecNow.y()* vecNow.y());
  qreal normStart = std::sqrt(vecStart.x()*vecStart.x()+vecStart.y()* vecStart.y());


  qreal angle = std::acos((vecNow.x()*vecStart.x()+vecNow.y()* vecStart.y())/(normNow * normStart))*180/3.14159265;

  qreal discr = vecNow.x() * vecStart.y() - vecNow.y() * vecStart.x();
  angle *= discr < 0? 1.0 : -1.0; 
  
  std::cerr<< " angle "<<angle<<" "<<scaleFactor<<std::endl;
  d_selectedImage->setAngle(d_saveAngle+angle);
  d_selectedImage->setScale(d_saveScale*scaleFactor);


}

void QTouchCollageWidget::touchUpdateEvent(QTouchEvent *e){

  if(!d_selectedImage)
    return;
  updateScaleAngle(e);

  update();
}


void QTouchCollageWidget::touchEndEvent(QTouchEvent *e){
  if(!d_selectedImage)
    return;

  updateScaleAngle(e);
  d_selectedImage = NULL;//unselect the image

  update();

}


void QTouchCollageWidget::cleanAll(){
  d_displayedImage.clear();
  update();
}


