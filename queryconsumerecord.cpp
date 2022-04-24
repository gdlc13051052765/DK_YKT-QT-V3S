#include "queryconsumerecord.h"
#include "ui_queryconsumerecord.h"
#include "sqlite3.h"
#include "setup.h"
#include "sqlite3QT.h"
//第一个label的位移
#define FIRST_LABEL_X  20
#define FIRST_LABEL_Y  200
//label的形状大小
#define LABEL_SHAPE_L  80
#define LABEL_SHAPE_H  80
//label横向间隔
#define LABEL_TRANSVERSE_SPACE    10
//label纵向间隔
#define LABEL_VERICAL_SPACE    80
//edit形状大小
#define EDIT_SHAPE_L  200
#define EDIT_SHAPE_H  50
//字体大小
#define FONT_SIZE 40

static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息
static QFont itemFont;         //字体样式
static int Current_FontSize;//
static int noCllectConsumeNumber = 0;//未采消费记录笔数
static int noCollectConsumeMoney = 0;//未采消费记录总额


queryConsumeRecord::queryConsumeRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryConsumeRecord)
{
    ui->setupUi(this);
    //设置标题栏
    setWindowTitle("查询采集记录");
    this->resize(QSize(800, 480));
    this->setGeometry(0, 40, 800, 440);//设置窗口大小
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::black); //设置背景黑色
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    consumeRecordSt st =  mSqliteClass.sqlite3_collection_consumemoney_db(0);
    noCllectConsumeNumber = st.toalNumber;//消费笔数
    noCollectConsumeMoney = st.toalMoney;//未采消费记录总额
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
void queryConsumeRecord::paintEvent(QPaintEvent *)
{   
    QPainter p(this);
    QPen pen;
    pen.setColor(QColor(255, 255, 255));
    p.setPen(pen);
    Current_FontSize = FONT_SIZE;
    itemFont.setPixelSize(Current_FontSize);
    p.setFont(itemFont);

    p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y, "未采记录笔数：");
    QString num = QString::number(noCllectConsumeNumber,10);
    num.append(" 笔");
    p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE*28, FIRST_LABEL_Y, num);

    p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE, FIRST_LABEL_Y+(1*LABEL_VERICAL_SPACE), "未采记录总额：");
    
    QString money = QString::number(noCollectConsumeMoney);
    QString str1 = money.right(2);  
    QString str = money.mid(0,money.length()-2);  
    str.append(".");   
    str.append(str1);
    str = QString::number(str.toFloat(), 'f', 2);//字符串转float并保留后面两位小数
    str.append(" 元");
    p.drawText(FIRST_LABEL_X+LABEL_TRANSVERSE_SPACE*28, FIRST_LABEL_Y+(1*LABEL_VERICAL_SPACE), str);
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
void queryConsumeRecord::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter)  //enter按键触发保存消费模式到数据库
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
        //跳回设置主界面
        this->close();
        setUp d;
        d.exec();
        return;
    }
}

queryConsumeRecord::~queryConsumeRecord()
{
    delete ui;
}
