/**
 * \file DrawerToolDockWidget.h
 *
 *  \date 20 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_DRAWERTOOLDOCKWIDGET_H_
#define LIBAMARSI_QUAD_DRAWERTOOLDOCKWIDGET_H_

#include <QDockWidget>
#include "ui_DrawerToolDockWidget.h"
/**
 *
 */
class MainWindow;
class DrawerToolDockWidget : public QDockWidget,
public Ui::DrawerToolDockWidget{
  Q_OBJECT
public:
  DrawerToolDockWidget(MainWindow *parent);
  virtual ~DrawerToolDockWidget();


  public slots :
  void on_colorPicker_colorChanged(const QColor & color);
  void on_sizeSlider_valueChanged(int value);
  signals :
  void sizeChanged(qreal);

  private :
  MainWindow *d_mainWindow;
};

#endif // LIBAMARSI_QUAD_DRAWERTOOLDOCKWIDGET_H_
