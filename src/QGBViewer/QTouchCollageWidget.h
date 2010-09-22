/**
 * \file QTouchCollageWidget.h
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QTOUCHCOLLAGEWIDGET_H_
#define LIBAMARSI_QUAD_QTOUCHCOLLAGEWIDGET_H_


#include <QWidget>
#include "QGBImage.h"
/**
 *
 */

class QTouchEvent;

class QTouchCollageWidget : public QWidget{
  Q_OBJECT
public:
  QTouchCollageWidget(QWidget * parent = NULL);
  virtual ~QTouchCollageWidget();

  void paint(QPainter *p,bool rectangle=false);

  void paintEvent(QPaintEvent *e);
  void resizeEvent(QResizeEvent *e);


  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseDoubleClickEvent(QMouseEvent *e);

  void touchBeginEvent(QTouchEvent *e);
  void touchUpdateEvent(QTouchEvent *e);
  void touchEndEvent(QTouchEvent *e);
  bool event(QEvent *e);
public slots :

  void addNewImage(QPixmap &);

private :
  typedef QList<QGBImage> ListOfImage;
  void renderAnImage(QPainter *p, const QGBImage & image, int color =-1);
  int selectImageAtPosition(const QPoint & position);
  void initSelectionPixmap();
  ListOfImage d_displayedImage;
  QPixmap d_selectionPixmap;


  QGBImage *d_selectedImage;
  QPointF d_lastPosition;

  qreal d_saveScale;
  qreal d_saveAngle;
};

#endif // LIBAMARSI_QUAD_QTOUCHCOLLAGEWIDGET_H_
