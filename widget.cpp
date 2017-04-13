#include <QThread>
#include <QDateTime>
#include <QApplication>

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
    p_receiver(new UdpReceiver(0)),
    m_settings(qApp->applicationDirPath()+"/udpsettings.ini",QSettings::IniFormat)
{
	ui->setupUi(this);

    //sender
    p_senderThread->start();
    p_sender->moveToThread(p_senderThread);

    //receiver
    p_receiverThread->start();
    p_receiver->moveToThread(p_receiverThread);
    connect(p_receiver,SIGNAL(dataReceived(QByteArray)),SLOT(receiver_dataReceived(QByteArray)));

    //restore settings
    ui->receiverPortSpinBox->setValue(m_settings.value("receiver_port",1190).toInt());

    ui->senderPortSpinBox->setValue(m_settings.value("sender_port",1190).toInt());
    ui->senderAddressLineEdit->setText(m_settings.value("sender_address","127.0.0.1").toString());
    ui->senderDataLineEdit->setText(m_settings.value("sender_data","testString").toString());

    //set params
    on_setDataButton_clicked();
    on_receiverPortSetButton_clicked();
    on_senderPortSetButton_clicked();
}

Widget::~Widget()
{
    //save settings
    m_settings.setValue("receiver_port",ui->receiverPortSpinBox->value());

     m_settings.setValue("sender_port",ui->senderPortSpinBox->value());
     m_settings.setValue("sender_address",ui->senderAddressLineEdit->text());
     m_settings.setValue("sender_data",ui->senderDataLineEdit->text());

    //stop threads
    QMetaObject::invokeMethod(p_sender,"stopTimer",Qt::BlockingQueuedConnection);
	p_senderThread->quit();
	p_senderThread->wait();
    delete p_senderThread;

	p_receiverThread->quit();
	p_receiverThread->wait();
    delete p_receiverThread;

    //
    delete p_sender;
    delete p_receiver;

    //
    delete ui;
}

void Widget::on_receiverPortSetButton_clicked()
{
    int port = ui->receiverPortSpinBox->value();

    QMetaObject::invokeMethod(p_receiver,"startListen",Qt::QueuedConnection,Q_ARG(int,port));
}

void Widget::on_setDataButton_clicked()
{
        QByteArray data = ui->senderDataLineEdit->text().toUtf8();

        QMetaObject::invokeMethod(p_sender,"setDataForSend",Qt::AutoConnection,Q_ARG(QByteArray,data));
}

void Widget::on_senderPortSetButton_clicked()
{
    QString address = ui->senderAddressLineEdit->text();
    int port = ui->senderPortSpinBox->value();

    QMetaObject::invokeMethod(p_sender,"setAddress",Qt::AutoConnection,Q_ARG(QString,address),Q_ARG(int,port));
}

void Widget::receiver_dataReceived(const QByteArray &_data)
{
    QString logString = QString("<font color=\"#3769ba\">%1</font> %2 ")
                                                            .arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"))
                                                            .arg(QString(_data));

    ui->receiverLogEdit->append(logString);
}
