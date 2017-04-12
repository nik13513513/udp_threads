#include <QThread>

#include "widget.h"
#include "udpsender.h"
#include "udpreceiver.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::udpWidget),
	p_senderThread(new QThread(this)),
	p_receiverThread(new QThread(this)),
	p_sender(new UdpSender(0)),
	p_receiver(new UdpReceiver(0))

{
	ui->setupUi(this);

	p_senderThread->start();
	p_receiverThread->start();


	p_sender->moveToThread(p_senderThread);
	p_receiver->moveToThread(p_receiverThread);

}

Widget::~Widget()
{
	p_senderThread->quit();
	p_senderThread->wait();

	p_receiverThread->quit();
	p_receiverThread->wait();

	delete p_sender;
	delete p_receiver;

	delete ui;
}
