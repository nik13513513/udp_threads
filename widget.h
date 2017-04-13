#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSettings>

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

private slots: //form slots
    void on_receiverPortSetButton_clicked();
    void on_setDataButton_clicked();
    void on_senderPortSetButton_clicked();

private slots://receive data
    void receiver_dataReceived(const QByteArray& _data);

private:
	Ui::udpWidget *ui;

	QThread* p_senderThread;
	QThread* p_receiverThread;

	UdpSender* p_sender;
	UdpReceiver* p_receiver;

    QSettings m_settings;
};

#endif // WIDGET_H
