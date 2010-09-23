/**
 * \file QGBViewerMainWindow.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */
#include <ctime>

#include "QGBViewerMainWindow.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QSettings>
#include <QDebug>

#include<libQGBBase/settings/QGBSettings.h>

QGBViewerMainWindow::QGBViewerMainWindow() {

  QSettings settings;



  if(!settings.contains("viewer/directory")){
    openAFolder();
  }else{
    d_dir = QDir(settings.value("viewer/directory").toString());
  }
  this->setupUi(this);

  selectionWidget->populateWithDirectory(d_dir.absolutePath());

  connect(selectionWidget,SIGNAL(openedImage(QPixmap &)),
          collageWidget,SLOT(addNewImage(QPixmap &)));

  connect(selectionWidget,SIGNAL(reloadedImages()),
          collageWidget,SLOT(cleanAll()));

  connect(&d_server,SIGNAL(receivedNewMessage()),
          this,SLOT(receiveAnImage()));
}

QGBViewerMainWindow::~QGBViewerMainWindow() {
}


void QGBViewerMainWindow::openAFolder(){
  QString directory = QFileDialog::getExistingDirectory(0,"Open a directory containing photos","~/Pictures");
  qDebug()<< "User want to open "<< directory;

  d_dir = QDir(directory);
  QSettings settings;

  settings.setValue("viewer/directory",d_dir.absolutePath());

  selectionWidget->populateWithDirectory(d_dir.absolutePath());
}

void QGBViewerMainWindow::keyPressEvent(QKeyEvent *e){
  if(e->key() == Qt::Key_O && e->modifiers() & Qt::ControlModifier){
    openAFolder();
  }

  if(e->key() == Qt::Key_S && e->modifiers() & Qt::ControlModifier){
    QGBSettings::instance()->show();
  }
}

 void QGBViewerMainWindow::on_resetButton_clicked(){
   collageWidget->cleanAll();
 }

 void QGBViewerMainWindow::on_reloadButton_clicked(){
   selectionWidget->populateWithDirectory(d_dir.absolutePath());
 }


 void QGBViewerMainWindow::receiveAnImage(){

   QPixmap *p= d_server.nextPendingImage();

   time_t second = time(NULL);
   p->save(d_dir.absoluteFilePath(QString("img-")
                                  +QString::number(second)+".jpg"));

   selectionWidget->addPixmap(*p);

   d_server.nextImage();
 }
