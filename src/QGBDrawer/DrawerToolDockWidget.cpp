/**
 * \file DrawerToolDockWidget.cpp
 *
 *  \date 20 sept. 2010
 *  \author akay
 */

#include "DrawerToolDockWidget.h"

#include "MainWindow.h"

DrawerToolDockWidget::DrawerToolDockWidget(MainWindow *parent)
: QDockWidget(parent)
, d_mainWindow(parent){
  this->setupUi(this);

  colorPicker->setStandardColors();
}

DrawerToolDockWidget::~DrawerToolDockWidget() {
}


void DrawerToolDockWidget::on_colorPicker_colorChanged(const QColor & color){
  d_mainWindow->setColor(color);
}
