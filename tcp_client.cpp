#include "tcp_client.h"

MyTcpClient::MyTcpClient(QString ip, qint16 port) : QThread(NULL)
{
    this->ip_ = ip;
    this->port_ = port;
    
    socket_ = new QTcpSocket;
    connection_restorer_ = new QTimer();
    connection_restorer_->setInterval(1500);
    
    QObject::connect(connection_restorer_, SIGNAL(timeout()), this, SLOT(tryToConnect()));  
    QObject::connect(socket_, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    QObject::connect(socket_, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                     this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    QObject::connect(socket_, SIGNAL(disconnected()), this, SLOT(quit()));
    QObject::connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    
    tryToConnect();
}

void MyTcpClient::tryToConnect()
{
    if(socket_->state() == QAbstractSocket::ConnectedState)
        return;
    socket_->disconnectFromHost();
    socket_->connectToHost(ip_, port_);
    if(socket_->waitForConnected(3000)) {
        qDebug() << "client -> connected";
    } else {
        connection_restorer_->start();
    }  
}

void MyTcpClient::onStateChanged(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::UnconnectedState)
        connection_restorer_->start();
}

void MyTcpClient::onReadyRead()
{
    
}
