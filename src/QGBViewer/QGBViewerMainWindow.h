/**
 * \file QGBViewerMainWindow.h
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QGBVIEWERMAINWINDOW_H_
#define LIBAMARSI_QUAD_QGBVIEWERMAINWINDOW_H_

#include <QDir>
#include "ui_QGBViewerMainWindow.h"

#include <libQGBBase/server/QMessageServer.h>
/**
 *
 */
class QGBViewerMainWindow : public QMainWindow, public Ui::QGBViewerMainWindow{
  Q_OBJECT
public:
  QGBViewerMainWindow();
  virtual ~QGBViewerMainWindow();

  void keyPressEvent(QKeyEvent *e);

public slots :
  void openAFolder();
  void on_resetButton_clicked();
  void on_reloadButton_clicked();
  void receiveAnImage();
private :
  QDir d_dir;
  QMessageServer d_server;
};

#endif // LIBAMARSI_QUAD_QGBVIEWERMAINWINDOW_H_
