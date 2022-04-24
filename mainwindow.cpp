#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlite3.h"
#include "sqlite3QT.h"
#include "setup.h"

#include "rfal_thread.h"
#include "readWriteCard.h"
#include "MFRC522.h"

//消费模式
#define MONEY_CONSUME_MODE 0//计算模式
#define AUTO_CONSUME_MODE 1//自动模式
#define PLAN_CONSUME_MODE 2//价格方案

//第一个label的位移
#define FIRST_LABEL_X  20
#define FIRST_LABEL_Y  60
//label的形状大小
#define LABEL_SHAPE_L  80
#define LABEL_SHAPE_H  80
//label横向间隔
#define LABEL_TRANSVERSE_SPACE    150
//label纵向间隔
#define LABEL_VERICAL_SPACE    40
//edit形状大小
#define EDIT_SHAPE_L  250
#define EDIT_SHAPE_H  60
//字体大小
#define FONT_SIZE 40
#define BIG_FONT_SIZE 55
#define SIM_FONT_SIZE 24

//系统时间坐标
#define CONSUME_MODE_X   200
#define CONSUME_MODE_Y   150
//系统时间坐标
#define SYSTIME_X   520
#define SYSTIME_Y   450
//设备号坐标
#define DEV_NUMBER_X   20
#define DEV_NUMBER_Y   450
//版本号坐标
#define VERSION_X   200
#define VERSION_Y   450

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息
/****************************************************************************************
 设置主界面
 ****************************************************************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCursor(Qt::BlankCursor);   //隐藏鼠标
    this->setWindowFlags(Qt::FramelessWindowHint);//不显示标题栏
    this->resize(QSize(800, 480));
    this->setGeometry(0, 0, 800, 480);//设置窗口大小
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    //创建一个权限为0666（所有用户可读可写，具体查询linux权限相关内容）的消息队列，并返回一个消息队列ID，
    //如果key值已经存在有消息队列了，则直接返回一个消息队列ID。
    //创建消息队列用于接收消费后台信息
    key_Rcv = ftok("/tmp", 88);
    id_Rcv = msgget(key_Rcv, IPC_CREAT|0666);
    if(id_Rcv == -1) {
        printf("create Rcv_msg error ");
    }
    key_Snd = ftok("/tmp", 66);
    id_Snd = msgget(key_Snd, 0666|IPC_CREAT);
    if(id_Snd == -1) {
        printf("create Snd_msg error ");
    }
    Snd_msg.mtype = 66;
    //创建消息队列接收定时器
    Communicate_Msg_QT_Go_Timer = new QTimer(this);          //  MSG消息队列定时器任务     
    connect(Communicate_Msg_QT_Go_Timer, SIGNAL(timeout()), this, SLOT(Communicate_Msg_QT_Go_Handle()));
    Communicate_Msg_QT_Go_Timer->start(100);

     //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    QFont ft;
    ft.setPointSize(FONT_SIZE);

    //跟设置界面创建信息互联
    mainDialog = new setConsumeMode(this);
    connect(mainDialog,SIGNAL(sendConsumeModeSingnals(QString)),this,SLOT(getConsumeModeHandle(QString)));

    //创建闪烁定时器
    twinkleTimer = new QTimer(this);          //  MSG消息队列定时器任务     
    connect(twinkleTimer, SIGNAL(timeout()), this, SLOT(twinkleTimerTimeHandle()));
    //twinkleTimer->start(1000);

    //消费输入GroupBox ，消费控件放入此GroupBox
    //行列布局layout
    inputMoneyGoupBox = new QGroupBox(this);
    inputMoneyGoupBox->move(150,100);
    inputMoneyGoupBox->resize(450, 180);
    inputMoneyGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(255,255,255);");

    //消费金额 label
    QLabel *consumeMoneyLabel = new QLabel(this);
    QString currentMoneyStr = "";
    if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )
    {
        currentMoneyStr = "计算模式";
    }
    else if (mDevMsg.consumeMode == AUTO_CONSUME_MODE )
    {
        currentMoneyStr = "自动模式";
        twinkleTimer->start(1000);
    }
    else if (mDevMsg.consumeMode == PLAN_CONSUME_MODE )
    {
        currentMoneyStr = "方案方案";
    }
    else {
        currentMoneyStr = "计算模式";
    }
    consumeMoneyLabel->setText(currentMoneyStr);
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    consumeMoneyLabel->setPalette(pa);//设置颜色
    QFont modeft;
    modeft.setPointSize(BIG_FONT_SIZE);
    consumeMoneyLabel->setFont(modeft);//设置字体大小

    consumeMoneyEdit = new QLineEdit(this);
    consumeMoneyEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    consumeMoneyEdit->setObjectName("consumeMoneyEdit");
    consumeMoneyEdit->setPalette(pa);//设置颜色
    ft.setPointSize(BIG_FONT_SIZE);
    consumeMoneyEdit->setFont(ft);//设置字体大小
    consumeMoneyEdit->setCursorPosition(consumeMoneyEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
    if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )
    {
        consumeMoneyEdit->setText("");
        consumeMoneyEdit->setEnabled(true);
    } else {
        QString money = QString::number(mDevMsg.consumeModeConsumeMoney);
        QString str1 = money.right(2);  
        QString str = money.mid(0,money.length()-2);  
        str.append(".");   
        str.append(str1);
        str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
        consumeMoneyEdit->setText(str);
        consumeMoneyEdit->setEnabled(false);
    }
    
    QLabel  *moneyLabel = new QLabel(this);
    moneyLabel->setText("金额:");
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    moneyLabel->setFont(ft);//设置字体大小
    moneyLabel->setPalette(pa);//设置颜色
    QLabel  *moneyFlagLabel = new QLabel(this);
    moneyFlagLabel->setText("元");
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    moneyFlagLabel->setFont(ft);//设置字体大小
    moneyFlagLabel->setPalette(pa);//设置颜色

    //行列布局layout
    QGridLayout *inputMoneyLayout = new QGridLayout();
    //设置布局内部四边的空隙 左-上-右-下
    inputMoneyLayout->setRowStretch(2, 2);    //创建5行
    inputMoneyLayout->addWidget(consumeMoneyLabel,0,1,Qt::AlignVCenter);//第0行，第0列开始，占1行3列 居中显示
    inputMoneyLayout->addWidget(moneyLabel,1,0);
    inputMoneyLayout->addWidget(consumeMoneyEdit,1,1);
    inputMoneyLayout->addWidget(moneyFlagLabel,1,2);
    inputMoneyGoupBox->setLayout(inputMoneyLayout);
    
    //消费输入GroupBox ，消费控件放入此GroupBox
    //行列布局layout
    consumeResultGoupBox = new QGroupBox(this);
    consumeResultGoupBox->move(200,50);
    consumeResultGoupBox->resize(500, 300);
    consumeResultGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(255,255,255);");

    cardNumberLabel = new QLabel(this);
    cardNumberLabel->setText("卡号：");
    ft.setPointSize(BIG_FONT_SIZE);
    cardNumberLabel->setFont(ft);//设置字体大小
    userNameLabel = new QLabel(this);
    userNameLabel->setText("姓名：");
    userNameLabel->setFont(ft);//设置字体大小
    currentMoneyLabel = new QLabel(this);
    currentMoneyLabel->setText("金额：");
    currentMoneyLabel->setFont(ft);//设置字体大小
    balanceLabel = new QLabel(this);
    balanceLabel->setText("余额：");
    balanceLabel->setFont(ft);//设置字体大小
    //行列布局layout
    QGridLayout *consumeResuleLayout = new QGridLayout();
    //设置布局内部四边的空隙 左-上-右-下
    consumeResuleLayout->setRowStretch(4, 2);    //创建4行
    consumeResuleLayout->addWidget(cardNumberLabel,0,0);//第0行，第0列开始，占1行3列 居中显示
    consumeResuleLayout->addWidget(userNameLabel,1,0);
    consumeResuleLayout->addWidget(currentMoneyLabel,2,0);
    consumeResuleLayout->addWidget(balanceLabel,3,0);
    consumeResultGoupBox->setLayout(consumeResuleLayout);
    consumeResultGoupBox->hide();//默认隐藏。消费成功后显示
    //刷卡提示 label
    pushCardLabel = new QLabel(this);
    pushCardLabel->move(CONSUME_MODE_X+130, CONSUME_MODE_Y+150);//位置
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    pushCardLabel->setText("请刷卡");
    pushCardLabel->setPalette(pa);//设置颜色
    pushCardLabel->setFont(ft);//设置字体大小
    pushCardLabel->hide();//默认隐藏。等待刷卡时闪烁显示

    //系统时间 label
    //获取当前时间
    QDateTime dateTime(QDateTime::currentDateTime());
	QString qStr = dateTime.toString("yyyy.MM.dd hh:mm:ss");
    sysTimeLabel = new QLabel(this);
    sysTimeLabel->move(SYSTIME_X, SYSTIME_Y);//位置
    sysTimeLabel->setText(qStr);
    sysTimeLabel->setPalette(pa);//设置颜色
    QFont sysTimeft;
    sysTimeft.setPointSize(SIM_FONT_SIZE);
    sysTimeLabel->setFont(sysTimeft);//设置字体大小
  
    //设备号 label
    devNumberLabel = new QLabel(this);
    devNumberLabel->move(DEV_NUMBER_X, DEV_NUMBER_Y);//位置
    qStr = "设备号: ";
    qStr.append(QString::number(mDevMsg.devId));
    devNumberLabel->setText(qStr);
    devNumberLabel->setPalette(pa);//设置颜色
    QFont devNumberLabelft;
    devNumberLabelft.setPointSize(SIM_FONT_SIZE);
    devNumberLabel->setFont(devNumberLabelft);//设置字体大小

    //版本号 label
    versionLabel = new QLabel(this);
    versionLabel->move(VERSION_X, VERSION_Y);//位置
    qStr = "版本号: ";
    qStr.append(mDevMsg.version);
    versionLabel->setText(qStr);
    versionLabel->setPalette(pa);//设置颜色
    versionLabel->setFont(devNumberLabelft);//设置字体大小

    //创建定时更新系统时间定时器
    updateSysTimeTimer = new QTimer(this);          //  MSG消息队列定时器任务     
    connect(updateSysTimeTimer, SIGNAL(timeout()), this, SLOT(updateSysTimeHandle()));
    updateSysTimeTimer->start(1000);

    //QT创建卡消费线程任务
}

/*==================================================================================
* 函 数 名： getConsumeModeHandle
* 参    数：
* 功能描述: 接收设置消费界面传递过来的数据
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void MainWindow::getConsumeModeHandle(QString str)
{
    qDebug() << "接收到设置消费模式消息 = " << str;
}

/*==================================================================================
* 函 数 名： Handle_Rfal_Value_Event
* 参    数：
* 功能描述: 接收读卡线程发过来的数据
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void MainWindow::Handle_Rfal_Value_Event(QString str)
{
    qDebug() << "接收读卡线程发过来的数据 = " << str;
}

/*==================================================================================
* 函 数 名： hideConsumeShowConsumeResult
* 参    数：flag == false显示消费输入隐藏消费结果
* 功能描述: 隐藏消费输入，显示消费结果
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void MainWindow::hideConsumeShowConsumeResult(bool flag)
{
    if(flag == false)
    {
        consumeResultGoupBox->show();
        inputMoneyGoupBox->hide();

    } else {
        consumeResultGoupBox->hide();
        inputMoneyGoupBox->show();
    }

}

/*==================================================================================
* 函 数 名： updateSysTimeHandle
* 参    数：
* 功能描述: 定时更新系统时间
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void MainWindow::updateSysTimeHandle()
{
    //获取当前时间
    QDateTime dateTime(QDateTime::currentDateTime());
	QString qStr = dateTime.toString("yyyy.MM.dd hh:mm:ss ddd");
    sysTimeLabel->setText(qStr);
}

/*==================================================================================
* 函 数 名： twinkleTimerTimeHandle
* 参    数：
* 功能描述: 闪烁定时器
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void MainWindow::twinkleTimerTimeHandle()
{
    if(pushCardLabel->isVisible() == true)
        pushCardLabel->hide();
    else
        pushCardLabel->show();
}

/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter) 
    {
        qDebug() << "press key enter";
        QString str = consumeMoneyEdit->text();
        str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
        consumeMoneyEdit->setText(str);
        twinkleTimer->start(1000);
        qDebug() <<"consumeMoneyEdit->text() " << consumeMoneyEdit->text();
        //hideConsumeShowConsumeResult(false);//显示消费结果界面
        return;
    }
    if (ev->key() == Qt::Key_Up)
    {
        qDebug() << "press key up";
        this->focusNextPrevChild(false);//按A时焦点切换至上一部件 
        return;
    }
    if (ev->key() == Qt::Key_Down)
    {
        qDebug() << "press key down";
        this->focusNextPrevChild(false);//按D时焦点切换至下一部件 
        return;
    }
    if (ev->key() == Qt::Key_F1)
    {
        qDebug() << "press key f1";
        //跳回设置主界面
        setUp d;
        d.exec();
        return;
    }
    if (ev->key() == Qt::Key_Escape)
    {
        qDebug() << "press key Esc";
        if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )
        {
            twinkleTimer->stop();
            pushCardLabel->hide();
            consumeMoneyEdit->setText("");
        }
        hideConsumeShowConsumeResult(true);//显示消费输入界面
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*==================================================================================
* 函 数 名： Communicate_Msg_QT_Go_Handle
* 参    数：
* 功能描述:  处理消息队列信息
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void MainWindow::Communicate_Msg_QT_Go_Handle()
{
    //读取队列信息
    if(msgrcv(id_Rcv, (void *)&Rcv_msg, 10, 88, IPC_NOWAIT) == -1) {
 
    } else {
        qDebug() << "消息队列接收信息 = "<< Rcv_msg.mtext;
    }
}

/*==================================================================================
* 函 数 名： Msg_QT_Send_Handle
* 参    数：
* 功能描述:  消息队列发送数据到消费后台
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void MainWindow::Msg_QT_Send_Handle(mymesg Snd_msg)
{
    if(msgsnd(id_Snd, (void *)&Snd_msg, 10, IPC_NOWAIT) == -1) {
        qDebug()<<"send msg error ";  
    }
}

void MainWindow::on_OpenDialog_clicked()
{
    dialog->setModal(false);   //模态
    dialog->show();
}

void MainWindow::on_emitBtn_clicked()
{
    connect(this,SIGNAL(mainWidgetStr(QString &)),dialog,SLOT(mainWidgetStr(QString &)));
    //QString str = ui->EmitLineEdit->text();
    //emit mainWidgetStr(str);
}

void MainWindow::setStr(QString &str)
{
    //ui->ReceiveLineEdit->setText(str);
}

/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 显示网络状态
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
// void mousePressEvent(QMouseEvent *event);        //单击
// void mouseReleaseEvent(QMouseEvent *event);      //释放
// void mouseDoubleClickEvent(QMouseEvent *event);  //双击
// void mouseMoveEvent(QMouseEvent *event);         //移动
// void wheelEvent(QWheelEvent *event);             //滑轮

