#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "dialog.h"
#include <QDebug>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QTime>
#include <QTextCodec>
#include <QFontDatabase>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QGroupBox>
#include "sqlite3.h"
#include "setconsumemode.h"

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OpenDialog_clicked();
    void on_emitBtn_clicked();
    void setStr(QString&);
    void keyPressEvent(QKeyEvent *ev);
    void Communicate_Msg_QT_Go_Handle();//休息队列信息接收处理函数
    void Msg_QT_Send_Handle(mymesg Snd_msg);//消息队列发送数据到消费后台
    void updateSysTimeHandle();
    void twinkleTimerTimeHandle();
private:
    Ui::MainWindow *ui;
    Dialog *dialog;
    key_t key_Rcv;
    int id_Rcv;
    struct mymesg Rcv_msg;
    key_t key_Snd;
    int id_Snd;
    struct mymesg Snd_msg;
    QLineEdit *consumeMoneyEdit;
    QLineEdit *newBalanceMoneyEdit;
    QLabel  *sysTimeLabel;
    QLabel  *devNumberLabel;
    QLabel  *consumeMoneyLabel;
    QLabel  *moneyLabel;
    QLabel  *moneyFlagLabel;
    QLabel *cardNumberLabel;
    QLabel *userNameLabel;
    QLabel *currentMoneyLabel;
    QLabel *balanceLabel;
    QLabel *versionLabel;
    QTimer *updateSysTimeTimer;
    QTimer *twinkleTimer;
    QLabel  *pushCardLabel;
    QGroupBox *inputMoneyGoupBox;
    QGroupBox *consumeResultGoupBox;
    void hideConsumeShowConsumeResult(bool);
    setConsumeMode *mainDialog;
    QTimer *Communicate_Msg_QT_Go_Timer;//消息队列定时器

signals:
    void mainWidgetStr(QString &);

public slots:
    void getConsumeModeHandle(QString );
    void Handle_Rfal_Value_Event(QString str);

};

#endif // MAINWINDOW_H
