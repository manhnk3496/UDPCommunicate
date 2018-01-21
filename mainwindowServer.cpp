#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    ui->textEditCentent->setEnabled(false);
    socket->bind(QHostAddress::LocalHost,3456);
    //when event click "Send" and enter(lineEditChat) will send Message
    connect(ui->pushButtonSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(ui->lineEditChat,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));

    //when event have signal from socket(not complete)
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*..................................................
  handle functions send and receive message
  ..................................................*/

void MainWindow::sendMessage(){
    socket->writeDatagram(ui->lineEditChat->text().toUtf8(), QHostAddress::LocalHost, 6789);
    ui->lineEditChat->clear();
}
void MainWindow::receiveMessage(){
    while(socket->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(buffer.data(),buffer.size(),&sender, &senderPort);
        ui->textEditCentent->append("Server: ");
        ui->textEditCentent->append(buffer.data());
    }
}
