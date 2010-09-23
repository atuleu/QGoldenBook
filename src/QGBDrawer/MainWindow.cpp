/**
 * \file MainWindow.cpp
 *
 *  \date 20 sept. 2010
 *  \author akay
 */

#include "DrawerToolDockWidget.h"
#include "MainWindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>
#include <libQGBBase/message.pb.h>

MainWindow::MainWindow() {
  this->setupUi(this);

  d_drawerTools = new DrawerToolDockWidget(this);

  this->addDockWidget(Qt::RightDockWidgetArea,d_drawerTools);
  centralwidget->setColor(Qt::black);
  showFullScreen();
  QDir dir(":/ressources");

  connect(d_drawerTools,SIGNAL(sizeChanged(qreal)),
          centralwidget,SLOT(setFactor(qreal)));

  foreach(const QFileInfo & file , dir.entryInfoList()){
    qDebug()<<file.absoluteFilePath()<<" "<<file.size();
  }
  on_actionClear_triggered();
}

MainWindow::~MainWindow() {
}

void MainWindow::setColor(const QColor & color){
  centralwidget->setColor(color);
}


void MainWindow::debugDraw(){

}


void MainWindow::on_actionClear_triggered(){

  centralwidget->loadImage(":/ressources/paperGround.png");
}


void MainWindow::on_actionOpen_triggered(){
  QString file=QFileDialog::getOpenFileName(this,tr("Open an image"),
                                                 "./",
                                                 tr("Images (*.jpg *.jpeg)"));

  if(file.isEmpty())
    file=":/ressources/paperGround.jpg";

  centralwidget->loadImage(file);
}


void MainWindow::on_actionSend_triggered(){
  qDebug()<<"Start to send";
  BaseMessage m;
  Image * im =m.mutable_image();
  qDebug()<<"Start to parse image";
  QByteArray bytes;
  QBuffer buffer(&bytes);
  buffer.open(QIODevice::WriteOnly);
  centralwidget->const_pixmap().save(&buffer,"JPG");
  im->set_data(bytes,bytes.size());
  m.set_type(BaseMessage_Type_NEW_IMAGE);
  qDebug()<<"Start to send m "<<m.ByteSize();
  d_socket.sendNewMessage(&m);
  qDebug()<<"Sended";
}
