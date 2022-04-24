#ifndef SETCONSUMEMODE_H
#define SETCONSUMEMODE_H

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
#include "sqlite3.h"
#include "mainconsumeinterface.h"

namespace Ui {
class setConsumeMode;
}

class setConsumeMode : public QDialog
{
    Q_OBJECT

public:
    explicit setConsumeMode(QWidget *parent = 0);
    ~setConsumeMode();

private:
    Ui::setConsumeMode *ui;
    QLineEdit *consumeModeEdit;
    QLineEdit *autoMoneyEdit;
    QPushButton *setConsumeModeButton;
    void Delay_MSec( int msec);
    void reboot();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *ev);
    //void keyReleaseEvent(QKeyEvent *ev);//按键松开
    void input_auto_mode_consume_money_clicked();

signals:
    void sendConsumeModeSingnals(QString);

public slots:
    void setConsumeModeButtonClicked();
};

#endif // SETCONSUMEMODE_H
