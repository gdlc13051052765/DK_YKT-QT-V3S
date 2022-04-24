#include "querydayconsumemoney.h"
#include "ui_querydayconsumemoney.h"
#include "sqlite3.h"
#include "setup.h"
#include "sqlite3QT.h"
#include <QGridLayout>
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
#define EDIT_SHAPE_L  250
#define EDIT_SHAPE_H  50
//字体大小
#define FONT_SIZE 24

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息
static dayConsumeRecordSt mDayConsumeRecord;//
static QFont itemFont;      //字体样式
static int Current_FontSize;//
int dayConsumeMoney = 0;//日消费金额
int dayConsumeNum = 0;  //日消费笔数
int startDate, endDate;//起始，截至日期

QueryDayConsumeMoney::QueryDayConsumeMoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryDayConsumeMoney)
{
    ui->setupUi(this);
    //设置标题栏
    setWindowTitle("查询消费额");
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
	QString qStr = dateTime.toString("yyyy.MM.dd");

    //起始日期 label
    QLabel  *startDateLabel = new QLabel(this);
    startDateLabel->setText("起始日期:");
    startDateLabel->setPalette(pa);//设置颜色
    startDateLabel->setFont(ft);//设置字体大小

    startDateEdit = new QLineEdit(this);
    startDateEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    startDateEdit->setObjectName(("startDateEdit"));
    startDateEdit->setPalette(pa);//设置颜色
    startDateEdit->setFont(ft);//设置字体大小
    startDateEdit->setCursorPosition(startDateEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
    startDateEdit->setText(qStr);

    //截至日期 label  
    QLabel  *endDateLabel = new QLabel(this);
    endDateLabel->setText("截至日期:");
    endDateLabel->setPalette(pa);
    endDateLabel->setPalette(pa);//设置颜色
    endDateLabel->setFont(ft);//设置字体大小

    endDateEdit = new QLineEdit(this);
    endDateEdit->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    endDateEdit->setObjectName(("remoteIpEdit"));
    endDateEdit->setText(qStr);
    endDateEdit->setPalette(pa);//设置颜色
    endDateEdit->setFont(ft);//设置字体大小
    endDateEdit->setCursorPosition(endDateEdit->text().size()); //设置焦点（光标） 位置，设置在末尾

    //消费笔数 label  
    dayConsumeNumberLabel = new QLabel(this);
    dayConsumeNumberLabel->setText("消费笔数:");
    dayConsumeNumberLabel->setPalette(pa);
    dayConsumeNumberLabel->setFont(ft);//设置字体大小
    dayConsumeNumberLabel->hide();

    dayConsumeNumberEdit = new QLineEdit(this);
    dayConsumeNumberEdit->setObjectName(("dayConsumeNumberEdit"));
    dayConsumeNumberEdit->setText("");
    dayConsumeNumberEdit->setPalette(pa);//设置颜色
    dayConsumeNumberEdit->setFont(ft);//设置字体大小
    dayConsumeNumberEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color:transparent}");
    dayConsumeNumberEdit->setEnabled(false);
    dayConsumeNumberEdit->hide();

    //消费总额 label  
    dayConsumeMoneyLabel = new QLabel(this);

    dayConsumeMoneyLabel->setText("消费总额:");
    dayConsumeMoneyLabel->setPalette(pa);//设置颜色
    dayConsumeMoneyLabel->setFont(ft);//设置字体大小
    dayConsumeMoneyLabel->hide();

    dayConsumeMoneyEdit = new QLineEdit(this);
    dayConsumeMoneyEdit->setObjectName(("dayConsumeMoneyEdit"));
    dayConsumeMoneyEdit->setText("");
    dayConsumeMoneyEdit->setPalette(pa);//设置颜色
    dayConsumeMoneyEdit->setFont(ft);//设置字体大小
    dayConsumeMoneyEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color:transparent}");
    dayConsumeMoneyEdit->setEnabled(false);
    dayConsumeMoneyEdit->hide();

    //行列布局layout
    QGridLayout  *dayConsuneLayout = new QGridLayout();
    //设置布局内部四边的空隙 左-上-右-下
    dayConsuneLayout->setContentsMargins(200, 100, 200, 200);
    dayConsuneLayout->setRowStretch(5, 2);    //创建5行
    dayConsuneLayout->addWidget(startDateLabel,0,1);
    dayConsuneLayout->addWidget(startDateEdit,0,2);
    dayConsuneLayout->addWidget(endDateLabel,1,1);
    dayConsuneLayout->addWidget(endDateEdit,1,2);
    dayConsuneLayout->addWidget(dayConsumeNumberLabel,3,1);
    dayConsuneLayout->addWidget(dayConsumeNumberEdit,3,2);
    dayConsuneLayout->addWidget(dayConsumeMoneyLabel,4,1);
    dayConsuneLayout->addWidget(dayConsumeMoneyEdit,4,2);
    this->setLayout(dayConsuneLayout);
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
bool  QueryDayConsumeMoney::judgeDateValidity(QString str)  
{
    QDateTime date = QDateTime::fromString(str, "yyyy.MM.dd");
    bool res = date.isValid();
    if(res)
        qDebug()<<"res is true:"<<res;
    else
        qDebug()<<"res is false:"<<res;
    return res;
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
void QueryDayConsumeMoney::select_consume_date()
{
    bool ok;

    //获取当前时间
    QDateTime dateTime(QDateTime::currentDateTime());
	QString qStr = dateTime.toString("yyyy.MM.dd");

    input_dialog = new QInputDialog(this);
    input_dialog->installEventFilter(this);//在窗体上为lineEdit1安装过滤器
    QString text = input_dialog->getText(this, tr("查询日期输入"), tr("请输入起始日期XXXX(年).XX(月).XX(日)"), QLineEdit::Normal, qStr, &ok);
  
    qDebug() << "输入 = " << text;
    if (ok && !text.isEmpty())
    {
        QDateTime stDTime = QDateTime::fromString(qStr, "yyyy.MM.dd");
        if(judgeDateValidity(text) == false)//日期不合法
        {
            //警告弹窗
            QMessageBox::critical(this, tr("警告"), tr("日期不合法"), QMessageBox::Yes);
            select_consume_date();//递归重新选择输入
        } else {
            //将时间转为时间戳
            startDate = stDTime.toTime_t() - 8*3600;
            qDebug() << "起始日期时间戳 = " << startDate;
        }
    }

    text = QInputDialog::getText(this, tr("查询日期输入"), tr("请输入截至日期XXXX(年).XX(月).XX(日)"), QLineEdit::Normal, qStr, &ok);
    qDebug() << "输入 = " << text;
    if (ok && !text.isEmpty())
    {   
        QDateTime stDTime = QDateTime::fromString(qStr, "yyyy.MM.dd");
        if(judgeDateValidity(text) == false)//日期不合法
        {
            //警告弹窗
            QMessageBox::critical(this, tr("警告"), tr("日期不合法"), QMessageBox::Yes);
            select_consume_date();//递归重新选择输入
        } else {
            //将时间转为时间戳
            endDate = stDTime.toTime_t() - 8*3600;
            qDebug() << "截至日期时间戳 = " << endDate;
        }
    }
    //数据库查询消费记录
   // mDayConsumeRecord = mSqliteClass.sqlite3_consume_query_daymoney_db(QString::number(startDate), QString::number(endDate));
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
bool QueryDayConsumeMoney::eventFilter(QObject *watched, QEvent *event)
{ 
    if(watched == startDateEdit)
    {   
        if(event->type() == QEvent::FocusIn)
        {
            qDebug() << "localIpEdit焦点FocusIn";
            startDateEdit->setCursorPosition(startDateEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
            startDateEdit->cursorBackward(true,1);//向后2位移动光标并选中内容
        }
    }
    else if(watched == endDateEdit)
    {
        if(event->type() == QEvent::FocusIn)
        {
            qDebug() << "endDateEdit焦点FocusIn";
            endDateEdit->setCursorPosition(endDateEdit->text().size()); //设置焦点（光标） 位置，设置在末尾
            endDateEdit->cursorBackward(true,1);//向后2位移动光标并选中内容
        }
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
void QueryDayConsumeMoney::paintEvent(QPaintEvent *)
{   
    // QPainter p(this);
    // QPen pen;
    // pen.setColor(QColor(255, 255, 255));
    // p.setPen(pen);
    // Current_FontSize = FONT_SIZE;
    // itemFont.setPixelSize(Current_FontSize);
    // p.setFont(itemFont);

    // p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y, "消费笔数：");
    // p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE*20, FIRST_LABEL_Y, QString::number(mDayConsumeRecord.toalNumber,10));

    // p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+(1*LABEL_VERICAL_SPACE), "消费总额：");
    // p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE*20, FIRST_LABEL_Y+(1*LABEL_VERICAL_SPACE), QString::number(mDayConsumeRecord.toalMoney,10));
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
void QueryDayConsumeMoney::keyPressEvent(QKeyEvent *ev)
{
    QString startTimeStr, endTimeStr;

    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter) //enter按键触发保存消费模式到数据库
    {
        qDebug() << "press key enter";
        
        if(judgeDateValidity(startDateEdit->text()) == false)//日期不合法
        {
            //警告弹窗
            QMessageBox::critical(this, tr("警告"), tr("日期不合法"), QMessageBox::Yes);
        } else {
            qDebug() << "startDateEdit->text() = " <<startDateEdit->text();
            QDateTime stDTime = QDateTime::fromString(startDateEdit->text(), "yy.MM.dd");
            //将时间转为时间戳
            // startDate = stDTime.toTime_t() - 8*3600;
            startTimeStr = startDateEdit->text().mid(2);
            startTimeStr.replace(".","");
            qDebug() << "起始日期时间戳 = " << startTimeStr;
        }
        if(judgeDateValidity(endDateEdit->text()) == false)//日期不合法
        {
            //警告弹窗
            QMessageBox::critical(this, tr("警告"), tr("日期不合法"), QMessageBox::Yes);
        } else {
            QDateTime stDTime = QDateTime::fromString(endDateEdit->text(), "yy.MM.dd");
            //将时间转为时间戳
            endTimeStr = endDateEdit->text().mid(2);
            endTimeStr.replace(".","");
            // startDate = stDTime.toTime_t() - 8*3600;
            qDebug() << "截至日期时间戳 = " << endTimeStr;
        }
        //数据库查询消费记录
        mDayConsumeRecord = mSqliteClass.sqlite3_consume_query_daymoney_db(startTimeStr, endTimeStr);
        QString money = QString::number(mDayConsumeRecord.toalMoney,10);
        QString str1 = money.right(2);  
        QString str = money.mid(0,money.length()-2);  
        str.append(".");   
        str.append(str1);
        str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
        str.append(" 元");
        dayConsumeNumberEdit->setText(QString::number(mDayConsumeRecord.toalNumber,10).append(" 笔"));
        dayConsumeMoneyEdit->setText(str);
        dayConsumeNumberLabel->show();
        dayConsumeMoneyLabel->show();
        dayConsumeNumberEdit->show();
        dayConsumeMoneyEdit->show();
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
        dayConsumeNumberLabel->hide();
        dayConsumeMoneyLabel->hide();
        dayConsumeNumberEdit->hide();
        dayConsumeMoneyEdit->hide();
        //跳回设置主界面
        this->close();
        setUp d;
        d.exec();
        return;
    }
}

QueryDayConsumeMoney::~QueryDayConsumeMoney()
{
    delete ui;
}
