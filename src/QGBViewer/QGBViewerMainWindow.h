/**
 * \file QGBViewerMainWindow.h
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QGBVIEWERMAINWINDOW_H_
#define LIBAMARSI_QUAD_QGBVIEWERMAINWINDOW_H_

#include "ui_QGBViewerMainWindow.h"
/**
 *
 */
class QGBViewerMainWindow : public QMainWindow, public Ui::QGBViewerMainWindow{
public:
  QGBViewerMainWindow();
  virtual ~QGBViewerMainWindow();
};

#endif // LIBAMARSI_QUAD_QGBVIEWERMAINWINDOW_H_
