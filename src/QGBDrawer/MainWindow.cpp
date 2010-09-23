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
#include <QSettings>
#include <QKeyEvent>

#include<libQGBBase/settings/QGBSettings.h>

MainWindow::MainWindow()
: d_connected(false){
  this->setupUi(this);

  d_drawerTools = new DrawerToolDockWidget(this);

  this->addDockWidget(Qt::RightDockWidgetArea,d_drawerTools);
  centralwidget->setColor(Qt::black);
  showFullScreen();

  connect(d_drawerTools,SIGNAL(sizeChanged(qreal)),
          centralwidget,SLOT(setFactor(qreal)));

  connect(&d_socket,SIGNAL(connected()),
          this,SLOT(onConnection()));

  QSettings settings;
  d_socket.connectToHost(settings.value("server").toString(),
                         settings.value("port").toInt(),
                         QIODevice::WriteOnly);



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
  if(d_connected){
    sendPixmap(centralwidget->const_pixmap());
    return;
  }
  d_waitingImages.push_back(centralwidget->const_pixmap());
}

void MainWindow::onConnection(){
  d_connected = true;

  foreach(const QPixmap & pix, d_waitingImages){
    sendPixmap(pix);
  }
}

void MainWindow::sendPixmap(const QPixmap & pix){
  QByteArray block;
  QDataStream out(&block,QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_6);
  out<<(qint64) 0;
  pix.save(out.device(),"jpg");
  out.device()->seek(0);
  out<<(qint64)(block.size()-sizeof(qint64));
  d_socket.write(block);
}


void MainWindow::keyPressEvent(QKeyEvent *e){
  if(e->key()== Qt::Key_S && e->modifiers() & Qt::ControlModifier){
    QGBSettings::instance()->show();
  }
}
