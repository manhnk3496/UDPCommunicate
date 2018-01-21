#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 6789);
    connect(ui->lineEditChat,SIGNAL(returnPressed()),this,SLOT(sendMessage()));
    connect(ui->pushButtonSend,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    ui->textEditCentent->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage(){
    socket->writeDatagram(ui->lineEditChat->text().toUtf8(), QHostAddress::LocalHost, 3456);
    ui->lineEditChat->clear();
}

void MainWindow::receiveMessage(){
    while(socket->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        socket->readDatagram(buffer.data(),buffer.size(), &sender, &senderPort);
        ui->textEditCentent->append(buffer.data());
    }
}

