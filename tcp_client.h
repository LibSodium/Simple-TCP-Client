#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QTimer>
#include <QThread>
#include <QTcpSocket>

class MyTcpClient : public QThread
{
    Q_OBJECT
public:
    MyTcpClient(QString ip, qint16 port);
    
public slots:
    void tryToConnect();
    void onReadyRead();
    void onStateChanged(QAbstractSocket::SocketState);
    
private:
    QString ip_;
    qint16 port_;
    QTcpSocket *socket_;
    QTimer *connection_restorer_;
};



#endif // MYTCPCLIENT_H
