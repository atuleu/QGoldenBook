/**
 * \file QMessageServer.cpp
 *
 *  \date 21 sept. 2010
 *  \author akay
 */

#include <google/protobuf/Message.h>

#include <QTcpServer>
#include <QDebug>
#include <QSettings>
#include <QObject>
#include "QMessageServer.h"
#include "../message.pb.h"
#include "QMessageSocketListener.h"

QMessageServer::QMessageServer()
: d_server(new QTcpServer(NULL)){

  QSettings settings;

  unsigned int port = settings.value("port",6666).toInt();


  if(!d_server->listen(QHostAddress::Any,port)){
    qDebug()<<tr("Unable to start the server: %1.")
                               .arg(d_server->errorString());
    return;
  }


}

QMessageServer::~QMessageServer() {
  delete d_server;
}

google::protobuf::Message * QMessageServer::getNextPendingMessage(){
  return d_queue.front();
}
void QMessageServer::nextMessage(){
  delete d_queue.front();
  d_queue.pop_front();
}

void QMessageServer::broadcastMessageToClient(google::protobuf::Message * m ){
  emit wantToSendMessage(m);
}

void QMessageServer::appendNewClient(){
  QTcpSocket *newClient = d_server->nextPendingConnection();
  QMessageSocketListener * listener = new QMessageSocketListener(newClient);
  connect(listener,SIGNAL(gettedNewData(const QString &, QMessageSocketListener *)),
          this, SLOT(newDataToRead(const QString &, QMessageSocketListener *)));
  connect(this,SIGNAL(wantToSendMessage(google::protobuf::Message *m)),
          listener,SLOT(writeMessageToSocket(google::protobuf::Message *)));
}
void QMessageServer::newDataToRead(const QString & data, QMessageSocketListener *socket){

  BaseMessage * m = new BaseMessage;

  m->ParseFromString(data.toStdString());


  d_queue.push_back(m);
  socket->cleanUpForNextMessage();
  emit receivedNewMessage();
}
