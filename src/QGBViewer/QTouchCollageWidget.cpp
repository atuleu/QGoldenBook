/**
 * \file QTouchCollageWidget.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#include "QTouchCollageWidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
QTouchCollageWidget::QTouchCollageWidget(QWidget * parent)
: QWidget(parent)
, d_selectedImage(0){
  initSelectionPixmap();
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
  p->translate(center);
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


