/**
 * \file QMessageServer.cpp
 *
 *  \date 21 sept. 2010
 *  \author akay
 */


#include <QTcpServer>
#include <QDebug>
#include <QSettings>
#include <QPixmap>
#include <QObject>
#include "QMessageServer.h"
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
  for(MessageQueue::iterator m = d_queue.begin();
      m!= d_queue.end();
      ++m)
    delete *m;
  d_queue.clear();
}

QPixmap * QMessageServer::nextPendingImage(){
  if(!d_queue.empty())
    return d_queue.front();
  return NULL;
}
void QMessageServer::nextImage(){
  if(d_queue.empty())
    return;
  delete d_queue.front();
  d_queue.pop_front();
}

void QMessageServer::broadcastMessageToClient(QPixmap &p){
  emit wantToSendMessage(p);
}

void QMessageServer::appendNewClient(){
  QTcpSocket *newClient = d_server->nextPendingConnection();
  QMessageSocketListener * listener = new QMessageSocketListener(newClient);
  connect(listener,SIGNAL(gettedNewData(const QString &, QMessageSocketListener *)),
          this, SLOT(newDataToRead(const QString &, QMessageSocketListener *)));
  connect(this,SIGNAL(wantToSendMessage(google::protobuf::Message *m)),
          listener,SLOT(writeMessageToSocket(google::protobuf::Message *)));
}
void QMessageServer::newDataToRead(const QByteArray & data, QMessageSocketListener *socket){

  QPixmap *pix=new QPixmap();
  pix->loadFromData(data,"JPG");
  d_queue.push_back(pix);
  socket->cleanUpForNextMessage();
  emit receivedNewMessage();
}
