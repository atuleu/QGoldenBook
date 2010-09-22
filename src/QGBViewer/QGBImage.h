/**
 * \file QGBImage.h
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QGBIMAGE_H_
#define LIBAMARSI_QUAD_QGBIMAGE_H_

#include <QPoint>

class QPixmap;

/**
 *
 */
class QGBImage{
public:
  QGBImage(const QPixmap & pixmap);

  virtual ~QGBImage();

  const QPixmap & pixmap() const;

  double scale() const;

  double angle() const;

  const QPointF & const_position() const;

  QPointF & position();

  void setAngle(double angle);

  void setScale(double scale);

private :
  const QPixmap * d_pixmap;
  double d_scale;
  double d_angle;
  QPointF d_position;
};

#endif // LIBAMARSI_QUAD_QGBIMAGE_H_
