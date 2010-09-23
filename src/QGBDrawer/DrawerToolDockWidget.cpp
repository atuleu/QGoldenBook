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

void DrawerToolDockWidget::on_sizeSlider_valueChanged(int value){
  qreal nV= value * 2.7 / qreal(sizeSlider->maximum()- sizeSlider->minimum()) +0.3;
  emit sizeChanged(nV);
}
