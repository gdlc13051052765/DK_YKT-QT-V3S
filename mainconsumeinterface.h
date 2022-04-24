#ifndef MAINCONSUMEINTERFACE_H
#define MAINCONSUMEINTERFACE_H

#include <QDialog>
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
#include <QTimer>
#include <QGroupBox>
#include "sqlite3.h"
#include "setconsumemode.h"
#include <sys/msg.h>
#include <sys/ipc.h>

namespace Ui {
class mainConsumeInterface;
}

struct mymesg
{
    long int mtype;
    char mtext[512];
};

class mainConsumeInterface : public QDialog
{
    Q_OBJECT

public:
    explicit mainConsumeInterface(QWidget *parent = 0);
    ~mainConsumeInterface();
    void getConsumeModeFromDialog(int, QString str);

private:
    Ui::mainConsumeInterface *ui;
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
    QTimer *Communicate_Msg_QT_Go_Timer;//消息队列定时器
    void hideConsumeShowConsumeResult(bool);
    void analyzeConsumptionResults(char *jsonData);

private slots:
    void updateSysTimeHandle();
    void twinkleTimerTimeHandle();
    void keyPressEvent(QKeyEvent *ev);
    void Communicate_Msg_QT_Go_Handle();
signals:
    void Touch_Allow_Send_Handler(void);
public slots:
    void getConsumeModeHandle(QString );
    void Handle_Rfal_Value_Event(QString str);
};

#endif // MAINCONSUMEINTERFACE_H
