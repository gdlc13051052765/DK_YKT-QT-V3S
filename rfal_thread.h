#ifndef RFAL_THREAD_H
#define RFAL_THREAD_H

#include <QObject>
#include <QThread>
#include <QTime>
#include <QTimer>

class RFAL_THREAD: public QThread
{
    Q_OBJECT
public:
    explicit RFAL_THREAD(QObject *parent = 0);
    ~RFAL_THREAD();

protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();
private slots:
    void MainWindow_Receive_Handler();
signals:
    void myslot(QString);     //声明一个信号，不需要实现
};

#endif // PUGIJSON_H