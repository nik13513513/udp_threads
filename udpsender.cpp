#include "udpsender.h"

UdpSender::UdpSender(QObject *parent) :
    QObject(parent),
    m_socket(this),
    m_timer(this)
{
    m_timer.setInterval(1000);
    connect(&m_timer,SIGNAL(timeout()),SLOT(on_timerTimeout()));
    m_timer.start();
}

UdpSender::~UdpSender()
{

}

void UdpSender::setAddress(const QString &_address, int _port)
{
    m_address = _address;
    m_port = _port;
}

void UdpSender::setDataForSend(const QByteArray &_data)
{
    m_data = _data;
}

void UdpSender::stopTimer()
{
    m_timer.stop();
}

void UdpSender::on_timerTimeout()
{
    m_socket.writeDatagram(m_data,QHostAddress(m_address),m_port);
}

