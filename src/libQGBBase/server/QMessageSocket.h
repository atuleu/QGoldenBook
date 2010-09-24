/**
 * \file QMessageSocket.h
 *
 *  \date 23 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QMESSAGESOCKET_H_
#define LIBAMARSI_QUAD_QMESSAGESOCKET_H_

#include <QObject>

#include "QMessageSocketListener.h"
/**
 *
 */
class QMessageSocket : public QObject{
  Q_OBJECT
public:
  QMessageSocket(QObject * parent=NULL);
  virtual ~QMessageSocket();

  google::protobuf::Message * nextPendingMessage();
  void nextMessage();

public slots :
  void sendNewMessage(google::protobuf::Message *m);
  void newDataToRead(const QString & data, QMessageSocketListener *socket);
signals :
  void receivedNewMessage();

private :
  typedef std::list<google::protobuf::Message *> MessageQueue;
  QMessageSocketListener * d_socket;

  MessageQueue d_queue;

};

#endif // LIBAMARSI_QUAD_QMESSAGESOCKET_H_
