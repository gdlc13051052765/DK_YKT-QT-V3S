#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QtGui>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QStringList>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>
#include <QTime>
#include <QTextCodec>
#include <QFontDatabase>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGridLayout>

namespace Ui {
class setUp;
}

class setUp : public QDialog
{
    Q_OBJECT

public:
    explicit setUp(QWidget *parent = 0);
    ~setUp();

private:
    Ui::setUp *ui;
    QPushButton *setIpButton;   //设置IP按键
    QPushButton *setDeviceNumberButton;//设置设备号
    QPushButton *queryConsumeNumberButton;//为采集记录
    QPushButton *queryCollectRecordButton;//日消费记录
    QPushButton *setConsumeModeButton;//设置消费模式
    QPushButton *sysTimeButton;//修改系统时间
    QGridLayout *setButtonLayout;

private slots:
    void keyPressEvent(QKeyEvent *ev);
    void focusInEvent(QFocusEvent *);
    void setIpButtonClicked();
    void setDeviceNumberButtonClicked();
    void queryDayConsumeRecordButtonClicked();
    void queryCollectRecordButtonClicked();
    void setConsumeModeButtonClicked();
    void modifySysTimeButtonClicked();

};

#endif // SETUP_H
