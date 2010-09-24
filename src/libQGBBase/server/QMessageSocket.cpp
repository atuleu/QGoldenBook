/**
 * \file QMessageSocket.cpp
 *
 *  \date 23 sept. 2010
 *  \author akay
 */

#include "../message.pb.h"

#include "QMessageSocket.h"

QMessageSocket::QMessageSocket(QObject * parent)
 : QObject(parent)
 , d_socket(0){
  QTcpSocket * socket = new QTcpSocket();
  d_socket = new QMessageSocketListener(socket,this);

  connect(d_socket,SIGNAL(gettedNewData(const QString & ,
                          QMessageSocketListener * )),
          this, SLOT(newDataToRead(const QString &,
                                   QMessageSocketListener *)));
}

QMessageSocket::~QMessageSocket() {
  for(MessageQueue::iterator m = d_queue.begin();
      m != d_queue.end();
      ++m){
    delete *m;
  }
}

google::protobuf::Message* QMessageSocket::nextPendingMessage(){
  if(!d_queue.empty())
    return d_queue.front();
  return NULL;
}

void QMessageSocket::nextMessage(){
  if(d_queue.empty())
    return;
  delete d_queue.front();
  d_queue.pop_front();
}

void QMessageSocket::newDataToRead(const QString & data, QMessageSocketListener *socket){

  BaseMessage * m = new BaseMessage;

  m->ParseFromString(data.toStdString());


  d_queue.push_back(m);
  socket->cleanUpForNextMessage();
  emit receivedNewMessage();
}

void QMessageSocket::sendNewMessage(google::protobuf::Message *m){
  d_socket->writeMessageToSocket(m);
}
