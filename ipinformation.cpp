#include "ipinformation.h"
#include "ui_ipinformation.h"
#include "setup.h"
#include "sqlite3QT.h"
/****************************************************************************************
 设置ip地址界面; 由设置界面按键选择跳入
 ****************************************************************************************/

//第一个label的位移
#define FIRST_LABEL_X  20
#define FIRST_LABEL_Y  40
//label的形状大小
#define LABEL_SHAPE_L  80
#define LABEL_SHAPE_H  80
//label横向间隔
#define LABEL_TRANSVERSE_SPACE    120
//label纵向间隔
#define LABEL_VERICAL_SPACE    40
//edit形状大小
#define EDIT_SHAPE_L  250
#define EDIT_SHAPE_H  50
//字体大小
#define FONT_SIZE 24

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息



ipInformation::ipInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ipInformation)
{
    ui->setupUi(this);
    this->resize(QSize(800, 480));//设置窗口大小
    //设置标题栏
    setWindowTitle("网络信息");
    this->setStyleSheet("background-color:white;");
    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    QFont ft;
    ft.setPointSize(FONT_SIZE);
    //本机ip label
    QLabel  *localIpLabel = new QLabel(this);
    localIpLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y);//位置
    localIpLabel->setText("本机IP:");
    localIpLabel->setPalette(pa);//设置颜色
    localIpLabel->setFont(ft);//设置字体大小

    localIpEdit = new QLineEdit(this);
    localIpEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    localIpEdit->setObjectName(("localIpEdit"));
    localIpEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y);
    localIpEdit->resize(EDIT_SHAPE_L, EDIT_SHAPE_H-10);
    localIpEdit->setPalette(pa);//设置颜色
    localIpEdit->setFont(ft);//设置字体大小
    localIpEdit->setCursorPosition(localIpEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
    localIpEdit->setText(mDevMsg.localIp);

    //远端ip label  remoteIp
    QLabel  *remoteIpLabel = new QLabel(this);
    remoteIpLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y+EDIT_SHAPE_H);//位置
    remoteIpLabel->setText("远端IP:");
    remoteIpLabel->setPalette(pa);
    remoteIpLabel->setPalette(pa);//设置颜色
    remoteIpLabel->setFont(ft);//设置字体大小

    remoteIpEdit = new QLineEdit(this);
    remoteIpEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    remoteIpEdit->setObjectName(("remoteIpEdit"));
    remoteIpEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+EDIT_SHAPE_H);
    remoteIpEdit->resize(EDIT_SHAPE_L, EDIT_SHAPE_H-10);
    remoteIpEdit->setText(mDevMsg.remoteIp);
    remoteIpEdit->setPalette(pa);//设置颜色
    remoteIpEdit->setFont(ft);//设置字体大小
    remoteIpEdit->setCursorPosition(remoteIpEdit->text().size()); //设置焦点（光标） 位置，设置在末尾

    //端口号
    QLabel  *ipPortLabel = new QLabel(this);
    ipPortLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y+EDIT_SHAPE_H*2);//位置
    ipPortLabel->setText("端口号:");
    ipPortLabel->setPalette(pa);
    ipPortLabel->setPalette(pa);//设置颜色
    ipPortLabel->setFont(ft);//设置字体大小

    ipPortEdit = new QLineEdit(this);
    ipPortEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    ipPortEdit->setObjectName(("ipPortEdit"));
    ipPortEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+EDIT_SHAPE_H*2);
    ipPortEdit->resize(EDIT_SHAPE_L, EDIT_SHAPE_H-10);
    ipPortEdit->setText(QString::number(mDevMsg.port, 10));
    ipPortEdit->setPalette(pa);//设置颜色
    ipPortEdit->setFont(ft);//设置字体大小
    ipPortEdit->setCursorPosition(ipPortEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
}

ipInformation::~ipInformation()
{
    delete ui;
}

/*==================================================================================
* 函 数 名： eventFilter
* 参    数：
* 功能描述:  查询控件焦点状态
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
bool ipInformation::eventFilter(QObject *watched, QEvent *event)
{ 
    if(watched == localIpEdit)
    {   
        if(event->type() == QEvent::FocusIn)
        {
            qDebug() << "localIpEdit焦点FocusIn";
            localIpEdit->setCursorPosition(localIpEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
            localIpEdit->cursorBackward(true,1);//向后2位移动光标并选中内容
        }
        else if(event->type() == QEvent::FocusOut)
        {
            qDebug() << "localIpEdit焦点FocusOut";
        }
    }
    else if(watched == remoteIpEdit)
    {
        if(event->type() == QEvent::FocusIn)
        {
            qDebug() << "remoteIpEdit焦点FocusIn";
            remoteIpEdit->setCursorPosition(remoteIpEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
            remoteIpEdit->cursorBackward(true,1);//向后2位移动光标并选中内容
        }
    }
    else if(watched == ipPortEdit)
    {
        if(event->type() == QEvent::FocusIn)
        {
            qDebug() << "ipPortEdit焦点FocusIn";
            ipPortEdit->setCursorPosition(ipPortEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
            ipPortEdit->cursorBackward(true,1);//向后2位移动光标并选中内容
        }
    }
    return QWidget::eventFilter(watched, event);
}

/*==================================================================================
* 函 数 名： save_ipInformation_to_config_db
* 参    数：
* 功能描述:  保存ip信息到配置数据库
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void ipInformation::save_ipInformation_to_config_db(void)
{
    mDevMsg.remoteIp = remoteIpEdit->text();
    mDevMsg.localIp = localIpEdit->text();
    mDevMsg.port = ipPortEdit->text().toInt();
    mSqliteClass.Sqlite_update_ip_msg_result(mDevMsg);
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
void ipInformation::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter)  //enter按键触发保存ip信息到配置数据库
    {
        qDebug() << "press key enter";
       
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Show Qt", "是否保存新的IP信息?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes); 
        if(rb == QMessageBox::Yes) 
        { 
            save_ipInformation_to_config_db();
            this->close();
            //跳回设置主界面
            setUp d;
            d.exec();
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
    if (ev->key() == Qt::Key_Escape)
    {
        qDebug() << "press key Esc";
        this->close();
        //跳回设置主界面
        setUp d;
        d.exec();
        return;
    }
}
