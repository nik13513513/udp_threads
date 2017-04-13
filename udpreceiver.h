#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

class UdpReceiver : public QObject
{
	Q_OBJECT
public:
	explicit UdpReceiver(QObject *parent = 0);
	~UdpReceiver();

public slots:
     void startListen (int _port);

signals:
    void dataReceived(const QByteArray& data);

private slots:
    void on_readyRead();

private:
       QUdpSocket m_socket;
};

#endif // UDPRECEIVER_H
