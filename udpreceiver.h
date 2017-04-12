#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>

class UdpReceiver : public QObject
{
	Q_OBJECT
public:
	explicit UdpReceiver(QObject *parent = 0);
	~UdpReceiver();

};

#endif // UDPRECEIVER_H
