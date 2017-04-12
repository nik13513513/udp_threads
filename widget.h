#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class UdpSender;
class UdpReceiver;

namespace Ui {
class udpWidget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private:
	Ui::udpWidget *ui;

	QThread* p_senderThread;
	QThread* p_receiverThread;

	UdpSender* p_sender;
	UdpReceiver* p_receiver;
};

#endif // WIDGET_H
