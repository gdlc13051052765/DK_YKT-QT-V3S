#include "setup.h"
#include "ui_setup.h"
#include "setconsumemode.h"
#include "ipinformation.h"
#include "querydayconsumemoney.h"
#include "queryconsumerecord.h"
#include "devmsg.h"
//#include "mainwindow.h"
#include <QHBoxLayout>
#include "sqlite3QT.h"
#include "modifysystimeui.h"
#include "mainconsumeinterface.h"


//第一个按键的位移
#define FIRST_BUTTON_X  20
#define FIRST_BUTTON_Y  140
//按键的形状大小
#define BUTTON_SHAPE_L  80
#define BUTTON_SHAPE_H  80
//按键横向间隔
#define BUTTON_TRANSVERSE_SPACE    100
//按键纵向间隔
#define BUTTON_VERICAL_SPACE    100
//字体大小
#define FONT_SIZE 20

setUp::setUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setUp)
{
    ui->setupUi(this);
    //设置标题栏
    setWindowTitle("设置窗口");
    this->resize(QSize(800, 480));
    this->setGeometry(0, 40, 800, 440);//设置窗口大小
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    QFont ft;
    ft.setPointSize(FONT_SIZE);

    //创建设置ip按键
    setIpButton = new QPushButton("设置IP");
    setIpButton->setFont(ft);//设置字体大小
    setIpButton->setStyleSheet("QPushButton::focus {background-color: rgb(64, 224, 208); }");  //焦点状态时控件颜色
    connect(setIpButton, SIGNAL(clicked()), this, SLOT(setIpButtonClicked()));
    //创建设备信息按键
    setDeviceNumberButton = new QPushButton("设备信息");
    setDeviceNumberButton->setFont(ft);//设置字体大小
    setDeviceNumberButton->setStyleSheet("QPushButton::focus {background-color: rgb(64, 224, 208); }");//焦点状态时控件颜色
    connect(setDeviceNumberButton, SIGNAL(clicked()), this, SLOT(setDeviceNumberButtonClicked()));
    //查询日消费数据按键
    queryConsumeNumberButton = new QPushButton("消费数据");
    queryConsumeNumberButton->setFont(ft);//设置字体大小
    queryConsumeNumberButton->setStyleSheet("QPushButton::focus {background-color: rgb(64, 224, 208); }");//焦点状态时控件颜色
    connect(queryConsumeNumberButton, SIGNAL(clicked()), this, SLOT(queryDayConsumeRecordButtonClicked()));
    //查询采集记录按键
    queryCollectRecordButton = new QPushButton("采集记录");
    queryCollectRecordButton->setFont(ft);//设置字体大小
    queryCollectRecordButton->setStyleSheet("QPushButton::focus {background-color: rgb(64, 224, 208); }");//焦点状态时控件颜色
    connect(queryCollectRecordButton, SIGNAL(clicked()), this, SLOT(queryCollectRecordButtonClicked()));
    //设置消费模式按键
    setConsumeModeButton = new QPushButton("消费模式");
    setConsumeModeButton->setFont(ft);//设置字体大小
    setConsumeModeButton->setStyleSheet("QPushButton::focus {background-color: rgb(64, 224, 208); }");//焦点状态时控件颜色
    connect(setConsumeModeButton, SIGNAL(clicked()), this, SLOT(setConsumeModeButtonClicked()));
    //设置修改系统时间按键
    sysTimeButton = new QPushButton("系统时间");
    sysTimeButton->setFont(ft);//设置字体大小
    sysTimeButton->setStyleSheet("QPushButton::focus {background-color: rgb(64, 224, 208); }");//焦点状态时控件颜色
    connect(sysTimeButton, SIGNAL(clicked()), this, SLOT(modifySysTimeButtonClicked()));

    //行列布局layout
    setButtonLayout = new QGridLayout();
    //设置布局内部四边的空隙 左-上-右-下
    setButtonLayout->setRowStretch(2, 2);    //创建2行
    setButtonLayout->addWidget(setIpButton,0,0);//第0行，第0列开始，占1行3列 居中显示
    setButtonLayout->addWidget(setDeviceNumberButton,0,1);
    setButtonLayout->addWidget(queryConsumeNumberButton,0,2);
    setButtonLayout->addWidget(queryCollectRecordButton,0,3);
    setButtonLayout->addWidget(setConsumeModeButton,0,4);
    setButtonLayout->addWidget(sysTimeButton,1,0);//第1行，第0列开始
    // 设置水平间距
    setButtonLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    setButtonLayout->setVerticalSpacing(40);
    // 设置外间距
    setButtonLayout->setContentsMargins(10, 10, 10, 10);

    //消费输入GroupBox ，设置控件放入此GroupBox
    //行列布局layout
    QGroupBox *setupGoupBox = new QGroupBox(this);
    setupGoupBox->move(0,100);
    setupGoupBox->resize(800, 400);
    //setupGoupBox->setStyleSheet("background-color:rgba(105,105,105); ");
    setupGoupBox->setStyleSheet("background-color:rgba(0,0,0); color:rgb(255,255,255);");
    setupGoupBox->setLayout(setButtonLayout);
}

/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  设置ip按键事件
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void setUp::setIpButtonClicked()
{
    qDebug() << "设置IP按键事件触发";
    ipInformation d;
    d.exec();
}

/*==================================================================================
* 函 数 名： setDeviceNumberButtonClicked
* 参    数：
* 功能描述:  设置设备号按键事件
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void setUp::setDeviceNumberButtonClicked()
{
    qDebug() << "设置设备号按键事件触发";
    devMsg d;
    d.exec();
}

/*==================================================================================
* 函 数 名： queryConsumeNumberButtonClicked
* 参    数：
* 功能描述:  获取消费金额按键事件
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void setUp::queryDayConsumeRecordButtonClicked()
{
    qDebug() << "获取消费金额按键事件触发";
    QueryDayConsumeMoney d;
    d.exec();
}

/*==================================================================================
* 函 数 名： queryCollectRecordButtonClicked
* 参    数：
* 功能描述:  获取采集记录按键事件
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void setUp::queryCollectRecordButtonClicked()
{
    qDebug() << "获取采集记录按键事件触发";
    queryConsumeRecord d;
    d.exec();
}

/*==================================================================================
* 函 数 名： setConsumeModeButtonClicked
* 参    数：
* 功能描述:  设置消费模式
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void setUp::setConsumeModeButtonClicked()
{
    qDebug() << "设置消费模式按键事件触发";
    setConsumeMode d;
    d.exec();
}

/*==================================================================================
* 函 数 名： modifySysTimeButtonClicked
* 参    数：
* 功能描述:  修改系统时间
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void setUp::modifySysTimeButtonClicked()
{
    qDebug() << "修改系统时间按键触发";
    modifySysTimeUi d;
    d.exec();
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
void setUp::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter)  
    {
        qDebug() << "press key enter";
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
    if (ev->key() == Qt::Key_Escape)
    {
        qDebug() << "press key Esc";
        //跳回主消费界面
        this->close();
        mainConsumeInterface d ;
        d.show();
        return;
    }
}

/*==================================================================================
* 函 数 名： focusInEvent
* 参    数：
* 功能描述:  控件焦点状态
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2022/2/7
==================================================================================*/
void setUp::focusInEvent(QFocusEvent *)
{
    //setStyleSheet("QPushButton{border:0px solid rgba(34, 139, 34);}");
}

setUp::~setUp()
{
    delete ui;
}
