#ifndef SQLITE3_H__
#define SQLITE3_H__

#include <stdlib.h>
#include <qdebug.h>
// #include <QSqlDatabase>
// #include <QSqlError>
// #include <QSqlQuery>
// #include <QtSql/QSqlRecord>

//配置信息结构体
struct configMsgSt
{
    QString version;//版本号
    int devId;//设备ID
    QString localIp;//本机IP
    QString remoteIp;//远端IP
    int port;//端口号
    QString MatchCode;//匹配字
    QString CardKeyCode;//读卡密钥
    QString CalCardKey;//写卡密钥
    int CardMinBalance;//卡底金
    int DayLimetMoney;//限额
    int cardSector;//公共扇区号
    int CardRebate;//卡折扣
    int consumeMode;//消费模式 
    int consumeModeConsumeMoney;//自动模式消费金额
};
//菜单信息结构体
struct menuSt
{
    int id;//菜品序号
    QString premenu;//上级菜单
    QString nextmenu;//下级菜单
    int grade;//菜单等级
    QString context;//菜品名称
    int dish_id;//菜品id
};

//日消费记录
struct dayConsumeRecordSt
{
    int toalNumber;//日消费笔数
    int toalMoney;//日消费总额
};

//消费记录
struct consumeRecordSt
{
    int toalNumber;//消费笔数
    int toalMoney;//消费总额
};

// //菜品 list
// struct menuList
// {
//     QStringList name;//菜品名称
//     QStringList spell;//菜品首字母

// }
//写盘器数据库读取接口函数
class Sqlite3QT
{
    public:
        configMsgSt Sqlite_read_msg_from_configdb(void);//配置数据库读取信息
        void Sqlite_update_ip_msg_result(configMsgSt pDevMsg);//修改配置数据库ip地址信息
        void Sqlite_update_dev_id(int devid);//修改配置数据库设备号
        void Sqlite_update_consumne_mode(int mode,int money);//修改配置数据库消费模式
        struct	dayConsumeRecordSt sqlite3_consume_query_daymoney_db(QString daytime1, QString daytime2);//日消费记录查询
        struct	consumeRecordSt sqlite3_collection_consumemoney_db(int flag);//查询采集记录
};

#endif // SQLITE3_H__
