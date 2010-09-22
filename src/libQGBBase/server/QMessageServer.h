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

#include <QObject>


namespace google{
  namespace protobuf{
    class Message;
  }
}
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

  google::protobuf::Message * getNextPendingMessage();
  void nextMessage();

  void broadcastMessageToClient(google::protobuf::Message * message );

public slots :
  void appendNewClient();
  void newDataToRead(const QString & data, QMessageSocketListener *socket);

signals :
 void receivedNewMessage();
 void wantToSendMessage(google::protobuf::Message *m);
private :
  QTcpServer * d_server;

  typedef int ClientId;
  typedef std::list<google::protobuf::Message *> MessageQueue;

  MessageQueue d_queue;

};

#endif // LIBAMARSI_QUAD_QMESSAGESERVER_H_
