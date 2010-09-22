/**
 * \file QMessageSocketListener.h
 *
 *  \date 22 sept. 2010
 *  \author akay
 */

#ifndef LIBAMARSI_QUAD_QMESSAGESOCKETLISTENER_H_
#define LIBAMARSI_QUAD_QMESSAGESOCKETLISTENER_H_


#include <QTcpSocket>


namespace google{
  namespace protobuf {
    class Message;
  }
}

/**
 *
 */

class QMessageSocketListener : public QObject{
  Q_OBJECT
public:
  QMessageSocketListener(QTcpSocket *d_socket);
  virtual ~QMessageSocketListener();

  void cleanUpForNextMessage();

public slots :

  void writeMessageToSocket(google::protobuf::Message *m);
  void readDataFromSocket();

signals :
  void gettedNewData(const QString & data,
                     QMessageSocketListener * me);

private :
  QTcpSocket *d_socket;
  bool d_gettedMessage;
  qint64 d_size;
  QString d_data;
  QDataStream d_stream;
};

#endif // LIBAMARSI_QUAD_QMESSAGESOCKETLISTENER_H_
