#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  //tcpConnect();
  ui->pushButton_parar->setEnabled(false);
  ui->pushButton_comecar->setEnabled(false);
  ui->pushButton_desconectar->setEnabled(false);
}

void MainWindow::tcpConnect(){
  if(ui->textEditIPServer->toPlainText()==""){
    socket->connectToHost("127.0.0.1",1234);
      ui->textEditIPServer->setText("127.0.0.1");
  }
  else{
    socket->connectToHost(ui->textEditIPServer->toPlainText(),1234);
  }

  if(socket->waitForConnected(3000)){
    ui->labelConectado->setText("Conectado");
    ui->pushButton_comecar->setEnabled(true);
    ui->pushButton_desconectar->setEnabled(true);
    ui->pushButton_conectar->setEnabled(false);
  }
  else{
    ui->labelConectado->setText("Conexão Falhou");
  }
}

void MainWindow::timerEvent(QTimerEvent *event){
    putData();
}

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;

  if(socket->state()== QAbstractSocket::ConnectedState){
    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " +
        QString::number(ui->sliderMin->value()+rand()%(ui->sliderMax->value()-ui->sliderMin->value()+1))+"\r\n";

    /*
      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str())
               << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
    */
    socket->write(str.toStdString().c_str());
    ui->listWidget->addItem(str);
  }
}

void MainWindow::conectar(){
  tcpConnect();
}

void MainWindow::desconectar(){
  socket->disconnectFromHost();
  ui->labelConectado->setText("Desconectado");
  if(estado == 1){
    parar();
  }
  ui->pushButton_conectar->setEnabled(true);
  ui->pushButton_desconectar->setEnabled(false);
  ui->pushButton_comecar->setEnabled(false);
  ui->pushButton_parar->setEnabled(false);
}

void MainWindow::setMin(){
  ui->sliderMax->setMinimum(ui->sliderMin->value());
}

void MainWindow::setMax(){
  ui->sliderMin->setMaximum(ui->sliderMax->value());
}

void MainWindow::comecar(){
  temporizador = startTimer(ui->sliderTempo->value()*1000);
  estado = 1;
  ui->pushButton_parar->setEnabled(true);
  ui->pushButton_comecar->setEnabled(false);
}

void MainWindow::parar(){
  killTimer(temporizador);
  estado = 0;
  ui->pushButton_parar->setEnabled(false);
  ui->pushButton_comecar->setEnabled(true);
}

void MainWindow::alteratempo()
{
    if(estado == 1){
      killTimer(temporizador);
      temporizador = startTimer(ui->sliderTempo->value()*1000);
    }
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
