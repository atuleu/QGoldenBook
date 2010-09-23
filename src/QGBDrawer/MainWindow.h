/**
 * \file MainWindow.h
 *
 *  \date 20 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_MAINWINDOW_H_
#define LIBAMARSI_QUAD_MAINWINDOW_H_

#include <libQGBBase/server/QMessageSocket.h>
#include <QMainWindow>
#include "ui_MainDrawerWindow.h"
class DrawerToolDockWidget;

/**
 *
 */
class MainWindow : public QMainWindow, public Ui::MainDrawerWindow{
  Q_OBJECT
public:
  MainWindow();
  virtual ~MainWindow();

public :
  void setColor(const QColor & color);

  void debugDraw();

public slots :
  void on_actionOpen_triggered();
  void on_actionClear_triggered();
  void on_actionSend_triggered();

private :
  DrawerToolDockWidget * d_drawerTools;
  QMessageSocket d_socket;

};

#endif // LIBAMARSI_QUAD_MAINWINDOW_H_
