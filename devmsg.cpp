#include "devmsg.h"
#include "ui_devmsg.h"
#include "setup.h"
#include "sqlite3QT.h"
/****************************************************************************************
 设备信息界面; 由设置界面按键选择跳入
 ****************************************************************************************/

//第一个label的位移
#define FIRST_LABEL_X  20
#define FIRST_LABEL_Y  40
//label的形状大小
#define LABEL_SHAPE_L  80
#define LABEL_SHAPE_H  80
//label横向间隔
#define LABEL_TRANSVERSE_SPACE    150
//label纵向间隔
#define LABEL_VERICAL_SPACE    40
//edit形状大小
#define EDIT_SHAPE_L  200
#define EDIT_SHAPE_H  50
//字体大小
#define FONT_SIZE 24

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息

devMsg::devMsg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::devMsg)
{
    ui->setupUi(this);
    //设置标题栏
    setWindowTitle("设备信息");
    this->resize(QSize(800, 480));//设置窗口大小

     //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    QFont ft;
    ft.setPointSize(FONT_SIZE);
    //设备ID
    QLabel *devIdLabel = new QLabel(this);
    devIdLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y);//位置
    devIdLabel->setText("设备号:");
    devIdLabel->setPalette(pa);//设置颜色
    devIdLabel->setFont(ft);//设置字体大小
    devIdEdit = new QLineEdit(this);
    devIdEdit->setObjectName(("devIdEdit"));
    devIdEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y);
    devIdEdit->resize(EDIT_SHAPE_L, EDIT_SHAPE_H-10);
    devIdEdit->setText(QString::number(mDevMsg.devId, 10));
    devIdEdit->setPalette(pa);//设置颜色
    devIdEdit->setFont(ft);//设置字体大小

    //版本号
    QLabel *versionLabel = new QLabel(this);
    versionLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y+EDIT_SHAPE_H);//位置
    versionLabel->setText("版本号:");
    versionLabel->setPalette(pa);
    versionLabel->setPalette(pa);//设置颜色
    versionLabel->setFont(ft);//设置字体大小
    versionEdit = new QLineEdit(this);
    versionEdit->setObjectName(("versionEdit"));
    versionEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+EDIT_SHAPE_H);
    versionEdit->resize(EDIT_SHAPE_L, EDIT_SHAPE_H-10);
    versionEdit->setText(mDevMsg.version);
    versionEdit->setPalette(pa);//设置颜色
    versionEdit->setFont(ft);//设置字体大小
    versionEdit->setEnabled(false);

    //匹配字
    QLabel  *matchCodeLabel = new QLabel(this);
    matchCodeLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y+EDIT_SHAPE_H*2);//位置
    matchCodeLabel->setText("匹配字:");
    matchCodeLabel->setPalette(pa);
    matchCodeLabel->setPalette(pa);//设置颜色
    matchCodeLabel->setFont(ft);//设置字体大小
    matchCodeEdit = new QLineEdit(this);
    matchCodeEdit->setObjectName(("matchCodeEdit"));
    matchCodeEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+EDIT_SHAPE_H*2);
    matchCodeEdit->resize(EDIT_SHAPE_L, EDIT_SHAPE_H-10);
    matchCodeEdit->setText(mDevMsg.MatchCode);
    matchCodeEdit->setPalette(pa);//设置颜色
    matchCodeEdit->setFont(ft);//设置字体大小
    matchCodeEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color:transparent}");
    matchCodeEdit->setEnabled(false);

    //读卡密钥
    QLabel  *cardKeyCodeLabel = new QLabel(this);
    cardKeyCodeLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y+EDIT_SHAPE_H*3);//位置
    cardKeyCodeLabel->setText("读KEY:");
    cardKeyCodeLabel->setPalette(pa);
    cardKeyCodeLabel->setPalette(pa);//设置颜色
    cardKeyCodeLabel->setFont(ft);//设置字体大小
    cardKeyCodeEdit = new QLineEdit(this);
    cardKeyCodeEdit->setObjectName(("cardKeyCodeEdit"));
    cardKeyCodeEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+EDIT_SHAPE_H*3);
    cardKeyCodeEdit->resize(EDIT_SHAPE_L, EDIT_SHAPE_H-10);
    cardKeyCodeEdit->setText(mDevMsg.CardKeyCode);
    cardKeyCodeEdit->setPalette(pa);//设置颜色
    cardKeyCodeEdit->setFont(ft);//设置字体大小
    cardKeyCodeEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color:transparent}");
    cardKeyCodeEdit->setEnabled(false);

    //写卡密钥
    QLabel  *calCardKeyLabel = new QLabel(this);
    calCardKeyLabel->move(FIRST_LABEL_X, FIRST_LABEL_Y+EDIT_SHAPE_H*4);//位置
    calCardKeyLabel->setText("写KEY:");
    calCardKeyLabel->setPalette(pa);
    calCardKeyLabel->setPalette(pa);//设置颜色
    calCardKeyLabel->setFont(ft);//设置字体大小
    calCardKeyEdit = new QLineEdit(this);
    calCardKeyEdit->setObjectName(("calCardKeyEdit"));
    calCardKeyEdit->move(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+EDIT_SHAPE_H*4);
    calCardKeyEdit->resize(EDIT_SHAPE_L+50, EDIT_SHAPE_H-10);
    calCardKeyEdit->setText(mDevMsg.CalCardKey);//pDevMsg.CalCardKey
    calCardKeyEdit->setPalette(pa);//设置颜色
    calCardKeyEdit->setFont(ft);//设置字体大小
    calCardKeyEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color:transparent}");
    calCardKeyEdit->setEnabled(false);
}

devMsg::~devMsg()
{
    delete ui;
}

/*==================================================================================
* 函 数 名： save_devMsg_to_config_db
* 参    数：
* 功能描述:  保存设备信息到配置数据库
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void devMsg::save_devMsg_to_config_db(void)
{
    QString str = devIdEdit->text();

    mSqliteClass.Sqlite_update_dev_id(str.toInt());//保存设备ID
}

/*================================================================================
* 函 数 名： keyPressEvent
* 参    数：
* 功能描述:  获取按键值
* 返 回 值： 
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
void devMsg::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter)  //按键触发保存设备信息到配置数据库
    {
        qDebug() << "press key enter";
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Show Qt", "是否保存设备信息?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes); 
        if(rb == QMessageBox::Yes) 
        { 
            save_devMsg_to_config_db();
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
