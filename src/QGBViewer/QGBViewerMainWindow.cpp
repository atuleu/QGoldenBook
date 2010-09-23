/**
 * \file QGBViewerMainWindow.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#include "QGBViewerMainWindow.h"
#include <QFileDialog>
#include <libQGBBase/message.pb.h>
#include <QKeyEvent>
#include <QSettings>
#include <QDebug>

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
}

 void QGBViewerMainWindow::on_resetButton_clicked(){
   collageWidget->cleanAll();
 }

 void QGBViewerMainWindow::on_reloadButton_clicked(){
   selectionWidget->populateWithDirectory(d_dir.absolutePath());
 }


 void QGBViewerMainWindow::receiveAnImage(){
   BaseMessage *m = static_cast<BaseMessage *>(d_server.nextPendingMessage());
   if(m->has_image()){

     const std::string & data=m->image().data();
     QPixmap pix;
     pix.loadFromData((uchar*)data.c_str(),data.length(),"JPG");


     time_t seconds;
     pix.save(d_dir.absoluteFilePath("img"+QString::number(seconds)+".jpg"));

     selectionWidget->addPixmap(pix);
   }

   d_server.nextMessage();
 }
