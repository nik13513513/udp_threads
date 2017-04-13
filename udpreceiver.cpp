#include "udpreceiver.h"

UdpReceiver::UdpReceiver(QObject *parent) :
    QObject(parent),
    m_socket(this)
{
    connect(&m_socket,SIGNAL(readyRead()),SLOT(on_readyRead()));
}

UdpReceiver::~UdpReceiver()
{

}

void UdpReceiver::startListen(int _port)
{
    m_socket.abort();
    m_socket.bind(QHostAddress::AnyIPv4,_port);
}

void UdpReceiver::on_readyRead()
{
    QByteArray datagram;

    datagram.resize(m_socket.pendingDatagramSize());
    m_socket.readDatagram(datagram.data(), datagram.size());

    emit dataReceived(datagram);
}

