/**
 * \file QGBViewerMainWindow.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#include "QGBViewerMainWindow.h"
#include <QFileDialog>

#include <QDebug>

QGBViewerMainWindow::QGBViewerMainWindow() {

  QString directory = QFileDialog::getExistingDirectory(0,"Open a directory containing photos","~/Pictures");
  qDebug()<< "User want to open "<< directory;

  this->setupUi(this);

  selectionWidget->populateWithDirectory(directory);

  connect(selectionWidget,SIGNAL(openedImage(QPixmap &)),
          collageWidget,SLOT(addNewImage(QPixmap &)));


}

QGBViewerMainWindow::~QGBViewerMainWindow() {
}
