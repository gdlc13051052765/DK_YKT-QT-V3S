#include "modifysystimeui.h"
#include "ui_modifysystimeui.h"
#include <QDebug>
#include "setup.h"

#define FONT_SIZE 40

modifySysTimeUi::modifySysTimeUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifySysTimeUi)
{
    ui->setupUi(this);
     //设置标题栏
    setWindowTitle("系统时间");
    this->resize(QSize(800, 480));
    this->setGeometry(0, 40, 800, 440);//设置窗口大小
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    QFont ft;
    ft.setPointSize(FONT_SIZE);

    //获取当前时间
    QDateTime dateTime(QDateTime::currentDateTime());
	QString qStr = dateTime.toString("yyyy.MM.dd.HH.mm.ss");

    QLabel  *timeFormatLabel = new QLabel(this);
    timeFormatLabel->setText("时间格式: XXXX(年).XX(月).XX(日).XX(时).XX(分).XX(秒)");
    timeFormatLabel->setPalette(pa);//设置颜色
    ft.setPointSize(20);
    timeFormatLabel->setFont(ft);//设置字体大小

    //起始日期 label
    QLabel  *sysTimeLabel = new QLabel(this);
    sysTimeLabel->setText("系统时间:");
    sysTimeLabel->setPalette(pa);//设置颜色
    ft.setPointSize(FONT_SIZE);
    sysTimeLabel->setFont(ft);//设置字体大小

    sysTimeEdit = new QLineEdit(this);
    sysTimeEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    sysTimeEdit->setObjectName(("sysTimeEdit"));
    sysTimeEdit->setPalette(pa);//设置颜色
    sysTimeEdit->setFont(ft);//设置字体大小
    sysTimeEdit->setCursorPosition(sysTimeEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
    sysTimeEdit->setText(qStr);

    //行列布局layout
    QGridLayout *sysTimeLayout = new QGridLayout();
    //设置布局内部四边的空隙 左-上-右-下
    sysTimeLayout->setRowStretch(2, 2);    //创建2行
    sysTimeLayout->addWidget(timeFormatLabel,0,1);//第0行，第0列开始，占1行3列 居中显示
    sysTimeLayout->addWidget(sysTimeLabel,1,0);//第1行，第0列开始，占1行3列 居中显示
    sysTimeLayout->addWidget(sysTimeEdit,1,1);//第1行，第1列开始，占1行3列 居中显示
    // 设置水平间距
    sysTimeLayout->setHorizontalSpacing(10);
    // 设置垂直间距
    sysTimeLayout->setVerticalSpacing(1);
    // 设置外间距
    sysTimeLayout->setContentsMargins(10, 10, 10, 10);

    //消费输入GroupBox ，设置控件放入此GroupBox
    //行列布局layout
    QGroupBox *sysTimeGoupBox = new QGroupBox(this);
    sysTimeGoupBox->move(0,100);
    sysTimeGoupBox->resize(800, 400);
    sysTimeGoupBox->setStyleSheet("background-color:rgba(0,0,0);  color:rgb(255,255,255);");
    sysTimeGoupBox->setLayout(sysTimeLayout);

    //创建定时更新系统时间定时器
    // updateSysTimeTimer = new QTimer(this);          //  MSG消息队列定时器任务     
    // connect(updateSysTimeTimer, SIGNAL(timeout()), this, SLOT(updateSysTimeHandle()));
    // updateSysTimeTimer->start(1000);
}

/*==================================================================================
* 函 数 名： 判断字符串是否符合日期格式
* 参    数：
* 功能描述:  
* 返 回 值： 成功返回true
* 备    注： None
* 作    者： lc
* 创建时间： 2021/8/2
==================================================================================*/
bool  modifySysTimeUi::judgeDateValidity(QString str)  
{
    QDateTime date = QDateTime::fromString(str, "yyyy.MM.dd.HH.mm.ss");
    bool res = date.isValid();
 
    return res;
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
void modifySysTimeUi::updateSysTimeHandle()
{
    //获取当前时间
    // QDateTime dateTime(QDateTime::currentDateTime());
	// QString qStr = dateTime.toString("yyyy.MM.dd hh:mm:ss");
    // sysTimeEdit->setText(qStr);
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
void modifySysTimeUi::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter) 
    {
        if(judgeDateValidity(sysTimeEdit->text()) == false)
        {
            QMessageBox::warning(this, "Error", "时间格式不合法");
            return;
        }
        QDateTime dt = QDateTime::fromString(sysTimeEdit->text(), "yyyy.MM.dd.HH.mm.ss");
        QString str = "date -s \"";
        sysTimeEdit->text().indexOf(".");//查找第一个 "."
        //截取字第1段"yyyy";
        qDebug()<<"年: "<< sysTimeEdit->text().mid(0, 4);
        str.append(sysTimeEdit->text().mid(0, 4));
        str.append("-");
        //截取字第2段"MM";
        qDebug()<<"月: "<< sysTimeEdit->text().mid(5, 2);
        str.append(sysTimeEdit->text().mid(5, 2));
        str.append("-");
        //截取字第3段"dd";
        qDebug()<<"日: "<< sysTimeEdit->text().mid(8, 2);
        str.append(sysTimeEdit->text().mid(8, 2));
        str.append(" ");
        //截取字第4段"HH";
        qDebug()<<"时: "<< sysTimeEdit->text().mid(11, 2);
        str.append(sysTimeEdit->text().mid(11, 2));
        str.append(":");
        //截取字第5段"mm";
        qDebug()<<"分: "<< sysTimeEdit->text().mid(14, 2);
        str.append(sysTimeEdit->text().mid(14, 2));
        str.append(":");
        //截取字第6段"ss";
        qDebug()<<"秒: "<< sysTimeEdit->text().mid(17, 2);
        str.append(sysTimeEdit->text().mid(14, 2));
        str.append("\"");

        char *a;
        QByteArray ba=str.toLatin1();
        a=ba.data();
        printf("修改系统时间 = %s \n", a);
        system(a);
        system("hwclock -w");
        //跳回设置主界面
        QMessageBox::warning(this, "ok", "修改成功");
        this->close();
        setUp d;
        d.exec();
    }
    if (ev->key() == Qt::Key_Up)
    {
        return;
    }
    if (ev->key() == Qt::Key_Down)
    {
        return;
    }
    if (ev->key() == Qt::Key_Escape)
    {
        //跳回设置主界面
        this->close();
        setUp d;
        d.exec();
        return;
    }
}

modifySysTimeUi::~modifySysTimeUi()
{
    delete ui;
}
