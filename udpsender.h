#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

class UdpSender : public QObject
{
	Q_OBJECT
public:
	explicit UdpSender(QObject *parent = 0);
	~UdpSender();

public slots:
    void setAddress(const QString& _address,int _port);
    void setDataForSend(const QByteArray& _data);
    void stopTimer();

private slots:
    void on_timerTimeout();

private:
    QUdpSocket    m_socket;
    QTimer              m_timer;
    QByteArray     m_data;

    QString             m_address;
    int                       m_port;
};

#endif // UDPSENDER_H

