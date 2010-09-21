/**
 * \file MainWindow.cpp
 *
 *  \date 20 sept. 2010
 *  \author akay
 */

#include "DrawerToolDockWidget.h"
#include "MainWindow.h"

MainWindow::MainWindow() {
  this->setupUi(this);

  d_drawerTools = new DrawerToolDockWidget(this);

  this->addDockWidget(Qt::RightDockWidgetArea,d_drawerTools);
  centralwidget->setColor(Qt::black);
  showFullScreen();
}

MainWindow::~MainWindow() {
}

void MainWindow::setColor(const QColor & color){
  centralwidget->setColor(color);
}


void MainWindow::debugDraw(){

}
