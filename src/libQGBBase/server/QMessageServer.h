/**
 * \file QMessageServer.h
 *
 *  \date 21 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QMESSAGESERVER_H_
#define LIBAMARSI_QUAD_QMESSAGESERVER_H_

#include <list>
#include <map>
#include <QPixmap>
#include <QObject>


class QTcpServer;
class QMessageSocketListener;
/**
 *
 */
class QMessageServer :  public QObject{
  Q_OBJECT
public:
  QMessageServer();
  virtual ~QMessageServer();

  QPixmap* nextPendingImage();
  void nextImage();

  void broadcastMessageToClient(QPixmap & pixmap);

public slots :
  void appendNewClient();
  void newDataToRead(const QByteArray & data, QMessageSocketListener *socket);

signals :
 void receivedNewMessage();
 void wantToSendMessage(QPixmap & pixmap);
private :
  QTcpServer * d_server;

  typedef int ClientId;
  typedef std::list<QPixmap *> MessageQueue;

  MessageQueue d_queue;

};

#endif // LIBAMARSI_QUAD_QMESSAGESERVER_H_
