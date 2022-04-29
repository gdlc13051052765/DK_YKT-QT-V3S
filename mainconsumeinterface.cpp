#include "mainconsumeinterface.h"
#include "ui_mainconsumeinterface.h"
#include <QHBoxLayout>
#include "cJSON.h"
#include "sqlite3QT.h"
#include "setup.h"

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

mainConsumeInterface::mainConsumeInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainConsumeInterface)
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
    this->setCursor(Qt::BlankCursor); //隐藏鼠标

 
    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    QFont ft;
    ft.setPointSize(FONT_SIZE);

    //跟设置界面创建信息互联
    setConsumeMode *mainDialog = new setConsumeMode(this);
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
    consumeMoneyLabel = new QLabel(this);
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
        currentMoneyStr = "价格方案";
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
    
    QLabel *moneyLabel = new QLabel(this);
    QString str = QString::fromLocal8Bit("金额:");
    moneyLabel->setText(str);
    pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
    moneyLabel->setFont(ft);//设置字体大小
    moneyLabel->setPalette(pa);//设置颜色
    QLabel *moneyFlagLabel = new QLabel(this);
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
    pushCardLabel->move(CONSUME_MODE_X+100, CONSUME_MODE_Y+150);//位置
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
    //发送消费模式到golang
    Snd_msg.mtext[0] = 3;
    Snd_msg.mtext[1] = 3;//消费模式命令
    Snd_msg.mtext[2] = mDevMsg.consumeMode;
    Snd_msg.mtext[3] = 0;
    if(msgsnd(id_Snd, (void *)&Snd_msg, 10, 0) == -1) 
    {
        qDebug()<<"Send_Status Response \n";  
    }
    //插入交易记录测试
    QString nameStr = "张三";
    mSqliteClass.sqlite3_consume_insert_db(1,100,"2022-04-29","11223344",nameStr);
}

/*==================================================================================
* 函 数 名： analyzeConsumptionResults
* 参    数：
* 功能描述:  解析消费结果json数据
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/01/24
==================================================================================*/
void mainConsumeInterface::analyzeConsumptionResults(char *jsonData)
{
    QStringList consumeCmdList; 
    consumeCmdList << "getBalance" << "consumeResult" << "removeCard";

    cJSON *root ,*parse;
    root = cJSON_Parse(jsonData);
    if(!root)
    {
        qDebug() << "JSON格式错误";
    } else { // JSON格式正确
        qDebug() << "JSON格式ok：" << root;
        parse = cJSON_GetObjectItem(root, "cmd");
        QString cmd = QString::fromUtf8(parse->valuestring);//char *转 QString
        qDebug() << "cmd = " << cmd ;
        switch(consumeCmdList.indexOf(cmd))
        {
            case 2: //卡片移开
            hideConsumeShowConsumeResult(true);
            if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )//计算模式消费金额清零
            {
                consumeMoneyEdit->setText("");
            }
            break;
            case 0: //查询余额
            case 1: //解析消费结果
                parse = cJSON_GetObjectItem(root, "result");
                QString result = QString::fromUtf8(parse->valuestring);//char *转 QString
                qDebug() << "result = " << parse->valuestring;
                if(result == "ok")//消费成功
                {
                    parse = cJSON_GetObjectItem(root, "name");
                    QString name = "";
                    if(parse != NULL)
                    {
                        name = QString::fromUtf8(parse->valuestring);//char *转 QString
                        qDebug() << "name = " << name;
                    }
                    
                    parse = cJSON_GetObjectItem(root, "cardNum");
                    QString cardNum = "";
                    if(parse != NULL)
                    {
                        cardNum = QString::fromUtf8(parse->valuestring);//char *转 QString
                        qDebug() << "cardNum = " << cardNum;
                    }
                    
                    parse = cJSON_GetObjectItem(root, "balance");
                    int balance = 0;
                    if(parse != NULL)
                    {
                        qDebug() << "balance = " << parse->valueint;
                        balance = parse->valueint;
                    }
                    
                    parse = cJSON_GetObjectItem(root, "currentMoney");
                     int currentMoney  = 0;
                    if(parse != NULL)
                    {
                        qDebug() << "currentMoney = " << parse->valueint;
                        currentMoney = parse->valueint;
                    }
                    

                    QString str = "卡号：";
                    str.append(cardNum);
                    cardNumberLabel->setText(str);
                    str = "姓名：";
                    str.append(name);
                    userNameLabel->setText(str);
                    if(currentMoney == 0)
                    {
                        str = "金额：0.00 元";
                        currentMoneyLabel->setText(str);//设置消费金额
                    } else {
                        str = "金额：";
                        // QString money = QString::number(currentMoney);
                        // money.insert(money.length()-2,".");
                        // qDebug() << "money = " << money;
                        // str.append(money);  

                        QString money = QString::number(currentMoney);
                        QString str1 = money.right(2);  
                        str = money.mid(0,money.length()-2);  
                        str.append(".");   
                        str.append(str1);
                        str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
                        str.append(" 元"); 
                        currentMoneyLabel->setText("金额："+str);//设置消费金额
                    }
                   
                    if(balance == 0 )
                    {
                        str = "余额：0.00";
                    } else {
                        str = "余额：";
                        QString money = QString::number(balance);
                        money.insert(money.length()-2,".");
                        qDebug() << "money = " << money;
                        str.append(money);   
                       
                    }
                    pushCardLabel->hide();
                    twinkleTimer->stop();//停止闪烁
                    balanceLabel->setText(str+" 元");//设置余额显示内容
                    hideConsumeShowConsumeResult(false);//显示消费结果界面
                } else {//消费失败
                    parse = cJSON_GetObjectItem(root, "consumeStatus");
                    QString consumeStatus = QString::fromUtf8(parse->valuestring);//char *转 QString
                    qDebug() << "consumeStatus = " << consumeStatus;
                    QPalette pa;
                    pa.setColor(QPalette::WindowText,Qt::red);
                    pushCardLabel->setPalette(pa);//设置颜色红
                    pushCardLabel->setText(consumeStatus);
                    pushCardLabel->show();
                    twinkleTimer->stop();//停止闪烁
                }
            break;
        } 
    }
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
void mainConsumeInterface::Communicate_Msg_QT_Go_Handle()
{
    //读取队列信息
    memset(Rcv_msg.mtext, 0, 512);
    if(msgrcv(id_Rcv, (void *)&Rcv_msg, 512, 88, IPC_NOWAIT) == -1) {
 
    } else {
        qDebug() << "消息队列接收信息 = "<< Rcv_msg.mtext;
        analyzeConsumptionResults(Rcv_msg.mtext);
    }    
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
void mainConsumeInterface::getConsumeModeFromDialog(int mode, QString str)
{
    qDebug() << "getConsumeModeFromDialog = " << str << mode << mDevMsg.consumeMode;
    QString currentMoneyStr = "";
    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();
    
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
        currentMoneyStr = "价格方案";
    }
    else {
        currentMoneyStr = "计算模式";
    }
    consumeMoneyLabel->setText(currentMoneyStr);
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
void mainConsumeInterface::getConsumeModeHandle(QString str)
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
void mainConsumeInterface::Handle_Rfal_Value_Event(QString str)
{
    qDebug() << "receive read cad thread data = " << str;
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
void mainConsumeInterface::hideConsumeShowConsumeResult(bool flag)
{
    if(flag == false)
    {
        consumeResultGoupBox->show();//显示消费结果界面
        inputMoneyGoupBox->hide();//隐藏消费输入界面
        pushCardLabel->setText("");
    } else {
        consumeResultGoupBox->hide();//隐藏消费结果界面
        inputMoneyGoupBox->show();//显示消费输入界面
        if (mDevMsg.consumeMode == AUTO_CONSUME_MODE )
        {
            twinkleTimer->start(1000);
            QPalette pa;
            pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
            pushCardLabel->setPalette(pa);//设置颜色
            pushCardLabel->setText("请刷卡");
        }
        if (mDevMsg.consumeMode == MONEY_CONSUME_MODE )
        {
            twinkleTimer->stop();
            QPalette pa;
            pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
            pushCardLabel->setPalette(pa);//设置颜色
            pushCardLabel->setText("");
        }
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
void mainConsumeInterface::updateSysTimeHandle()
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
void mainConsumeInterface::twinkleTimerTimeHandle()
{
    if(pushCardLabel->isVisible() == true)
        pushCardLabel->hide();
    else {
        pushCardLabel->show();
        QPalette pa;
        pa.setColor(QPalette::WindowText, QColor(205,205,0));//浅黄色
        pushCardLabel->setPalette(pa);//设置颜色
        pushCardLabel->setText("请刷卡");
    }  
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
void mainConsumeInterface::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter) 
    {
        qDebug() << "press key enter";
        QString str = consumeMoneyEdit->text();
        str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
        consumeMoneyEdit->setText(str);
        twinkleTimer->start(500);
        pushCardLabel->setText("请刷卡");
        qDebug() <<"consumeMoneyEdit->text() " << consumeMoneyEdit->text();

        if(mDevMsg.consumeMode == MONEY_CONSUME_MODE)//计算模式
        {
            Snd_msg.mtext[0] = 6;
            Snd_msg.mtext[1] = 1;
            str.replace(QString("."), QString(""));
            int money = str.toInt();
            qDebug() << "money = "<< money;
            Snd_msg.mtext[5] = money>>24;
            Snd_msg.mtext[4] = money>>16;
            Snd_msg.mtext[3] = money>>8;
            Snd_msg.mtext[2] = money;
            if(msgsnd(id_Snd, (void *)&Snd_msg, 10, IPC_NOWAIT) == -1) 
            {
                qDebug()<<"Send_Status Response \n";  
            }
        }
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
        Snd_msg.mtext[0] = 2;
        Snd_msg.mtext[1] = 2;//消费取消命令
        Snd_msg.mtext[2] = 0;
        if(msgsnd(id_Snd, (void *)&Snd_msg, 10, IPC_NOWAIT) == -1) 
        {
            qDebug()<<"Send_Status Response \n";  
        }
        hideConsumeShowConsumeResult(true);//显示消费输入界面
        return;
    }
}

mainConsumeInterface::~mainConsumeInterface()
{
    delete ui;
}
