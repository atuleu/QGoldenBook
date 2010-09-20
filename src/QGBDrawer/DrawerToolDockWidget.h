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
class DrawerToolDockWidget : public QDockWidget,
public Ui::DrawerToolDockWidget{
  Q_OBJECT
public:
  DrawerToolDockWidget(QWidget *parent);
  virtual ~DrawerToolDockWidget();
};

#endif // LIBAMARSI_QUAD_DRAWERTOOLDOCKWIDGET_H_
