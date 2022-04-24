
#include "ipinformation.h"
#include <QApplication>
#include <QFontDatabase>
#include <QTextCodec>
#include <QFont>
#include "setup.h"
#include "devmsg.h"
#include "setconsumemode.h"
#include "queryconsumerecord.h"
#include "querydayconsumemoney.h"
//#include "mainconsumeinterface.h"
#include "modifysystimeui.h"
#include "rfal_thread.h"

QFontDatabase fontbase;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOverrideCursor(Qt::BlankCursor);//隐藏鼠标
    //UBUNTU
    // QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    // QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    //V3S
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); 
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    // //IMX6
    // int index = QFontDatabase::addApplicationFont("/opt/qt-4.8.-arm/lib/fonts/DroidSansFallback.ttf");
    // // int index = QFontDatabase::addApplicationFont("/opt/Fonts/DroidSansFallback.ttf");
    // // int index = QFontDatabase::addApplicationFont("/opt/qt-4.8.-arm/lib/fonts/HYQiHei-65S.ttf");
    // if(index != -1)
    // {
    //     QStringList fontList(QFontDatabase::applicationFontFamilies(index));
    //     if(fontList.count() > 0)
    //     {
    //         qDebug() << "open ttf ok";
    //         QFont font_zh(fontList.at(0));
    //         font_zh.setBold(false);
    //         a.setFont(font_zh);
    //     }
    // } else {
    //    qDebug() << "open ttf err";
    // }

    a.setFont(QFont("Droid Sans Fallback", 9));
    //遍历本地字库
    foreach (const QString &fontfamily, fontbase.families()) {
        qDebug()<<fontfamily;
    }
    //MainConsumeWindow w;
    //setUp w;
    //ipInformation w;
    //devMsg w;
    //setConsumeMode w;
    //queryConsumeRecord w;
    //QueryDayConsumeMoney w;
    mainConsumeInterface w;
    //modifySysTimeUi w;
    w.show();

    RFAL_THREAD * p_rfal_thread  = new  RFAL_THREAD();
    p_rfal_thread->start();
    QObject::connect(p_rfal_thread,SIGNAL(myslot(QString)), &w,SLOT(Handle_Rfal_Value_Event(QString)));
    QObject::connect(&w, SIGNAL(Touch_Allow_Send_Handler()), p_rfal_thread,SLOT(MainWindow_Receive_Handler()));

    return a.exec();
}
