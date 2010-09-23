/**
 * \file QMessageSocketListener.cpp
 *
 *  \date 22 sept. 2010
 *  \author akay
 */
#include "QMessageSocketListener.h"
#include <QPixmap>
QMessageSocketListener::QMessageSocketListener(QTcpSocket *socket,
                                               QObject *parent)
: QObject(parent)
, d_socket(socket)
, d_gettedMessage(false)
, d_size(0)
, d_stream(d_socket){
  d_stream.setVersion(QDataStream::Qt_4_6);
  connect(d_socket,SIGNAL(disconnected()),
          this,SLOT(deleteLater()));
  connect(d_socket,SIGNAL(disconnected()),
          this,SLOT(deleteLater()));
  connect(d_socket,SIGNAL(readyRead()),
          this,SLOT(readDataFromSocket()));
}

QMessageSocketListener::~QMessageSocketListener(){
  d_socket->abort();
}

void QMessageSocketListener::cleanUpForNextMessage(){
  d_data.clear();
  d_size = 0;
  d_gettedMessage= false;
}

void QMessageSocketListener::readDataFromSocket(){
  if(d_gettedMessage)
    return;//we are waiting that the user read a message, so we wait

  if(d_size == 0 ){
    if(d_socket->bytesAvailable() < (qint64) sizeof(qint64)){
      return;
    }
    d_stream >> d_size;
  }

  if(d_socket->bytesAvailable()< d_size)
    return;

  d_stream>> d_data;
  emit gettedNewData(d_data,this);
}

void QMessageSocketListener::writeImageToSocket(QPixmap & image){
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_6);
  out<<(qint64) 0;
  image.save(out.device(),"jpg");
  out.device()->seek(0);
  out<<(qint64)(block.size() -  sizeof(qint64));
  d_socket->write(block);

}
