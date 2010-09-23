/**
 * \file QTouchSelectionWidget.h
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QTOUCHSELECTIONWIDGET_H_
#define LIBAMARSI_QUAD_QTOUCHSELECTIONWIDGET_H_

#include <QWidget>
/**
 *
 */
class ThumbImage {
public:
  ThumbImage(const QString & file);
  ThumbImage(const QPixmap & pix);

  const QPixmap & const_pixmap() const;

  QPixmap & pixmap();

  qreal width() const;
  qreal height() const;

  qreal scale() const;

  static qreal maxWidthHeightSize();
private:

  void setSize();
  static qreal s_maxWidthHeight;

  QPixmap d_pixmap;
  qreal d_thumbWidth;
  qreal d_thumbHeight;
  qreal d_factor;
};

class QTouchSelectionWidget : public QWidget {
Q_OBJECT
public:
  typedef QList<ThumbImage> ListOfQPixmap;

  QTouchSelectionWidget(QWidget * parent = NULL);
  virtual ~QTouchSelectionWidget();

  void populateWithDirectory(const QString & dir);

  const ListOfQPixmap & openedImage() const;

  void paintEvent(QPaintEvent *);

  void mouseReleaseEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void mouseDoubleClickEvent(QMouseEvent *e);
  void paint(QPainter *p);

  void addPixmap(QPixmap &p);

signals :
  void openedImage(QPixmap &);
  void reloadedImages();

private:
  qreal posOfImage(unsigned int i);

  qreal maxSeed();
  void updateSeed(const QPointF & pos);
  static qreal s_margin;

  ListOfQPixmap d_openedImage;
  qreal d_seed;

  bool d_moving;
  QPointF d_lastPos;
};

inline qreal QTouchSelectionWidget::maxSeed(){

  return ((s_margin+ThumbImage::maxWidthHeightSize())* d_openedImage.length())-width();

}

inline qreal QTouchSelectionWidget::posOfImage(unsigned int i){
  return s_margin + i*(ThumbImage::maxWidthHeightSize()+s_margin) - d_seed;
}

#endif // LIBAMARSI_QUAD_QTOUCHSELECTIONWIDGET_H_
