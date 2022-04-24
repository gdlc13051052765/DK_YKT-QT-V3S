#include "setconsumemode.h"
#include "ui_setconsumemode.h"
#include <qinputdialog.h>
#include "setup.h"
#include "sqlite3QT.h"
/****************************************************************************************
 设备信息界面; 由设置界面按键选择跳入
 ****************************************************************************************/

//消费模式
#define MONEY_CONSUME_MODE 0//计算模式
#define AUTO_CONSUME_MODE 1//自动模式
#define PLAN_CONSUME_MODE 2//价格方案
//消费模式总数
#define MAX_CONSUME_NUMBER 3

//第一个label的位移
#define FIRST_LABEL_X  150
#define FIRST_LABEL_Y  150
//label的形状大小
#define LABEL_SHAPE_L  80
#define LABEL_SHAPE_H  80
//label横向间隔
#define LABEL_TRANSVERSE_SPACE    50
//label纵向间隔
#define LABEL_VERICAL_SPACE    80
//edit形状大小
#define EDIT_SHAPE_L  200
#define EDIT_SHAPE_H  50
//字体大小
#define FONT_SIZE 24

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息
static QStringList consumeModeList;   //消费模式
static QFont itemFont;         //字体样式
static int Current_FontSize;//
static int autoMoney = 0;//自动模式金额

//消费模式
extern int consumeMode ;  
//消费金额
extern QString autoConsumeMoney ;

setConsumeMode::setConsumeMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setConsumeMode)
{
    ui->setupUi(this);
    QFont ft;
    ft.setPointSize(FONT_SIZE);
    //设置标题栏
    setWindowTitle("设置消费模式");
    this->resize(QSize(800, 480));
    this->setGeometry(0, 40, 800, 440);//设置窗口大小
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    consumeModeList<<"计算模式"<<"自动模式"<<"价格方案";
    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();
    autoMoney = mDevMsg.consumeModeConsumeMoney;
    if(mDevMsg.consumeMode>=MAX_CONSUME_NUMBER)
        mDevMsg.consumeMode = 0;

    //自动模式金额
    autoMoneyEdit = new QLineEdit(this);
    autoMoneyEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    autoMoneyEdit->setObjectName("consumeMoneyEdit");
    autoMoneyEdit->move(500,FIRST_LABEL_Y+30);
    autoMoneyEdit->resize(160, 50);
    autoMoneyEdit->setPalette(pal);//设置颜色
    ft.setPointSize(40);
    autoMoneyEdit->setFont(ft);//设置字体大小
    autoMoneyEdit->setCursorPosition(autoMoneyEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
    this->focusNextPrevChild(false);//按D时焦点切换至下一部件 
    QString money = QString::number(mDevMsg.consumeModeConsumeMoney);
    QString str1 = money.right(2);  
    QString str = money.mid(0,money.length()-2);  
    str.append(".");   
    str.append(str1);
    autoMoneyEdit->setText(str);
    if(mDevMsg.consumeMode != AUTO_CONSUME_MODE)
        autoMoneyEdit->hide();
    
    // //设置修改系统时间按键
    // setConsumeModeButton = new QPushButton(this);
    // setConsumeModeButton->move(500,300);
    // setConsumeModeButton->resize(160, 50);
    // setConsumeModeButton->setFont(ft);//设置字体大小
    // setConsumeModeButton->setText("设置");
    // setConsumeModeButton->setStyleSheet("QPushButton::focus {background-color: rgb(64, 224, 208); }");//焦点状态时控件颜色
    // connect(setConsumeModeButton, SIGNAL(clicked()), this, SLOT(setConsumeModeButtonClicked()));
    // setConsumeModeButton->hide();
}

/*==================================================================================
* 函 数 名： setConsumeModeButtonClicked
* 参    数：
* 功能描述:  
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void setConsumeMode::setConsumeModeButtonClicked()
{
    // QString str = "设置消费模式";
    // qDebug() << "set consumemode button clicked";
    // emit sendConsumeModeSingnals(str);//发送消模式到主消费界面
   
}

/*==================================================================================
* 函 数 名： 弹窗输入自动模式消费金额
* 参    数：
* 功能描述:  
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void setConsumeMode::input_auto_mode_consume_money_clicked()
{
    bool ok;
    QString money = QString::number(mDevMsg.consumeModeConsumeMoney);
    QString str1 = money.right(2);  
    QString str = money.mid(0,money.length()-2);  
    str.append(".");   
    str.append(str1);
    QString text = str;
    text = QInputDialog::getText(this, tr("自动模式消费金额"),tr("请输入消费金额XX.XX元"), QLineEdit::Normal,str, &ok);
    
    if (ok && !text.isEmpty())
    {
        if (text.indexOf(".") != -1 )//查找是否存在 "."
        {
            for(int i = text.indexOf("."); i<text.length()-2; i++)
            {
                text.append("0");
            }   
        }
        else {
            text.append(".00");
        }
        text.replace(QString("."), QString(""));
        autoMoney =  text.toInt();
        qDebug() << "输入== " << autoMoney;
        mSqliteClass.Sqlite_update_consumne_mode(mDevMsg.consumeMode, autoMoney);//修改消费模式信息到数据库
    } else {
      
    }
}
/*==================================================================================
* 函 数 名： paintEvent绘图函数
* 参    数：
* 功能描述:  
* 返 回 值： 设备id
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void setConsumeMode::paintEvent(QPaintEvent *)
{   
    QPainter p(this);
    QPen pen;

    for(int i=0; i<MAX_CONSUME_NUMBER; i++)
    {
        if(i == mDevMsg.consumeMode)
            pen.setColor(QColor(0, 255, 0));//绿色
        else
            pen.setColor(QColor(255, 255, 255));
        p.setPen(pen);
        Current_FontSize = 70;
        itemFont.setPixelSize(Current_FontSize);
        p.setFont(itemFont);
        if(mDevMsg.consumeMode > MAX_CONSUME_NUMBER)
            mDevMsg.consumeMode = 0;

        p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+(i*LABEL_VERICAL_SPACE), consumeModeList.at(i));
    }
}

/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void setConsumeMode::reboot()
{
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QApplication::exit();
}
/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void setConsumeMode::Delay_MSec( int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/*==================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void setConsumeMode::keyPressEvent(QKeyEvent *ev)
//void setConsumeMode::keyReleaseEvent(QKeyEvent *ev)//按键松开
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter)  //enter按键触发保存消费模式到数据库
    {
        qDebug() << "press key enter "<< mDevMsg.consumeMode;
        if(mDevMsg.consumeMode == AUTO_CONSUME_MODE)//自动模式输入消费金额
        {
            QString text = autoMoneyEdit->text();
          
            text = QString::number(text.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
           
            autoMoneyEdit->setText(text);
            text.replace(QString("."), QString(""));
            autoMoney =  text.toInt();
            mSqliteClass.Sqlite_update_consumne_mode(mDevMsg.consumeMode, autoMoney);//修改消费模式信息到数据库
            //input_auto_mode_consume_money_clicked();
        } else {
            mSqliteClass.Sqlite_update_consumne_mode(mDevMsg.consumeMode, autoMoney);//修改消费模式信息到数据库
        }
        QString str = autoMoneyEdit->text();
        //跟设置界面创建信息互联
        mainConsumeInterface *mainDialog = new mainConsumeInterface;
        //connect(this,&setConsumeMode::sendConsumeModeSingnals,mainDialog,&mainConsumeInterface::getConsumeModeHandle);
        emit sendConsumeModeSingnals(str);//发送消模式到主消费界面
        mainDialog->getConsumeModeFromDialog(mDevMsg.consumeMode,str);
        Delay_MSec(1000);
        reboot();//QT进程重启
        //return;
    }
    if (ev->key() == Qt::Key_Up)
    {
        qDebug() << "press key up";
        if(mDevMsg.consumeMode > 0)
            mDevMsg.consumeMode -= 1;
        if(mDevMsg.consumeMode == AUTO_CONSUME_MODE)
            autoMoneyEdit->show();
        else
            autoMoneyEdit->hide();
        update();
        return;
    }
    if (ev->key() == Qt::Key_Down)
    {
        qDebug() << "press key down";
        this->focusNextPrevChild(false);//按D时焦点切换至下一部件 
        mDevMsg.consumeMode += 1;
        if(mDevMsg.consumeMode >= MAX_CONSUME_NUMBER)
        {
            mDevMsg.consumeMode = 0;
        }
        if(mDevMsg.consumeMode == AUTO_CONSUME_MODE)
            autoMoneyEdit->show();
        else
            autoMoneyEdit->hide();
        update();
        return;
    }
    if (ev->key() == Qt::Key_Escape)
    {
        qDebug() << "press key Esc";
        //跳回设置主界面
        this->hide();
        setUp d;
        d.exec();
        return;
    }
}

setConsumeMode::~setConsumeMode()
{
    delete ui;
}
