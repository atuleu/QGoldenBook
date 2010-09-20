/**
 * \file DrawerToolDockWidget.cpp
 *
 *  \date 20 sept. 2010
 *  \author akay
 */

#include "DrawerToolDockWidget.h"

DrawerToolDockWidget::DrawerToolDockWidget(QWidget *parent)
: QDockWidget(parent){
  this->setupUi(this);

  colorPicker->setStandardColors();
}

DrawerToolDockWidget::~DrawerToolDockWidget() {
}
