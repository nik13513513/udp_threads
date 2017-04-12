#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>

class UdpSender : public QObject
{
	Q_OBJECT
public:
	explicit UdpSender(QObject *parent = 0);
	~UdpSender();

};

#endif // UDPSENDER_H
