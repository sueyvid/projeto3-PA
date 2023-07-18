#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void tcpConnect();
  void timerEvent(QTimerEvent *event);
public slots:
  void putData();
  void conectar();
  void desconectar();
  void setMin();
  void setMax();
  void comecar();
  void parar();
  void alteratempo();
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int temporizador;
  int estado = 0;
};

#endif // MAINWINDOW_H
