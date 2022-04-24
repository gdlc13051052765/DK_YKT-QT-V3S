

#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include <QDebug>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <QMutex>
#include <QQueue>
#include <QTime>
#include <QTimer>
#include <QProcess>
#include "cJSON.h"
#include "sqlite3QT.h"
#include "rfal_thread.h"
extern "C"
{
    #include "readWriteCard.h"
    #include "MFRC522.h"
}

int ConsumCase = 0;//消费状态机
int CurrentConsumMoney=0;   //消费额
static Sqlite3QT mSqliteClass;//sqlite类
static configMsgSt mDevMsg;//设备信息

RFAL_THREAD::RFAL_THREAD(QObject *parent)
{
    //配置数据库读取信息
    mDevMsg = mSqliteClass.Sqlite_read_msg_from_configdb();
}

RFAL_THREAD::~RFAL_THREAD()
{

}

void RFAL_THREAD::MainWindow_Receive_Handler()
{
    printf("接收主窗口发过来的数据\n");
}

void RFAL_THREAD::run()
{
    int fd;
    uint8_t status;
    cardMsgInfo pMsg;

    // //打开rc522设备
    // fd = open("/dev/rfid_rc522_dev", O_RDWR);
    
    // if (fd < 0)
    // {
    //     printf("[%s]:[%d] open rfid_rc522_dev file error\r\n", __FUNCTION__, __LINE__);
    //     //return -1;
    // }

    InitRc522Driver();
   // MFRC522_Initializtion() ;//RC522初始化
    //emit myslot("afsalkfnaklsfnkalsf");//发送测试数据到主消费界面
    while(1)
    {
        switch(ConsumCase)
        {
            case 0: //
                ConsumCase = 1;//消费状态机
                CurrentConsumMoney=0;   //消费额
            break ;

            case 1: //寻卡
                pMsg=RequestCard();//卡复位信息	
                if(!pMsg.status)//有卡
                {
                    qDebug() << "寻卡成功";
                    //选择一卡通文件，读公共信息和累计文件     
                    pMsg= ReadCardCommonDatas_M1(mDevMsg.cardSector, pMsg);
                    if(!pMsg.status)//读取卡信息成功
                    {

                    }
                }
            break ;
        }
    }
}
