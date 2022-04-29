#include "sqlite3.h"
#include "sqlite3QT.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlRecord>

//消费模式
#define MONEY_CONSUME_MODE 0//计算模式
#define AUTO_CONSUME_MODE 1//自动模式
#define PLAN_CONSUME_MODE 2//价格方案
//配置数据库路径
char *configDbFile = "/root/ykt_config.db";
//char *configDbFile = "/home/meican/ykt_config.db";
//消费记录数据库
//char *recordDbFile = "/home/meican/record.db";
char *recordDbFile = "/root/record.db";
//黑名单数据库
char *blknumDbFile = "/root/blknum.db";

static char *zErrMsg =NULL;
static char **azResult=NULL; //二维数组存放结果
static int nrow=0;
static int ncolumn = 0;
/*=======================================================================================
* 函 数 名： Sqlite_read_msg_from_configdb
* 参    数： 
* 功能描述:  从配置数据库读取配置信息
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26
==========================================================================================*/
configMsgSt Sqlite3QT::Sqlite_read_msg_from_configdb(void)
{
    configMsgSt pDevMsg;
    int err =-1,dev_status = -1,i,hardNum;
    int nrow,ncolumn;
    char * errmsg = NULL;
    char **azResult; //是 char ** 类型，两个*号
    char gloalVersion[50];
    sqlite3 *config_db =NULL;

    /* 创建基础信息数据库 */
    err = sqlite3_open_v2(configDbFile, &config_db, SQLITE_OPEN_READONLY, NULL);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(config_db);
        sqlite3_close_v2(config_db);
        return pDevMsg;
    }
    //配置数据库读取数据
    char *sql = "select * from config_db";
    err = sqlite3_get_table(config_db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(config_db);
        sqlite3_free_table(azResult);
        sqlite3_free(zErrMsg);
        sqlite3_close_v2(config_db);
        return pDevMsg;
    }
    //   for(i=0;i<(nrow+1)*ncolumn;i++)
    //   {
    //     printf("azResult[%d]=%s\n",i,azResult[i]);
    //   }
    hardNum = 18;
    pDevMsg.version = QString::fromUtf8(azResult[hardNum]);
    qDebug() << "版本号 = "<<pDevMsg.version ;
    pDevMsg.devId = atoi(azResult[hardNum+1]);
    qDebug() << "设备号 = "<<pDevMsg.devId ;
    pDevMsg.localIp = QString::fromUtf8(azResult[hardNum+2]);
    qDebug("本机IP = " + pDevMsg.localIp.toLatin1());
    pDevMsg.remoteIp = QString::fromUtf8(azResult[hardNum+3]);
    qDebug("远端IP = " + pDevMsg.remoteIp.toLatin1());
    pDevMsg.port = atoi(azResult[hardNum+4]);
    printf("IP 端口号 = %d \n",pDevMsg.port);
    pDevMsg.consumeMode = atoi(azResult[hardNum+13]);//消费模式
    printf("消费模式 = %d \n",pDevMsg.consumeMode);
    pDevMsg.consumeModeConsumeMoney = atoi(azResult[hardNum+17]);
    printf("自动模式消费金额 = %d \n",pDevMsg.consumeModeConsumeMoney);
    pDevMsg.MatchCode = QString::fromUtf8(azResult[hardNum+5]);
    qDebug("匹配字 = " + pDevMsg.MatchCode.toLatin1());
    pDevMsg.CardKeyCode = QString::fromUtf8(azResult[hardNum+6]);
    qDebug("读卡密钥 = " + pDevMsg.CardKeyCode.toLatin1());
    pDevMsg.CalCardKey = QString::fromUtf8(azResult[hardNum+7]);
    qDebug("写卡密钥 = " + pDevMsg.CalCardKey.toLatin1());

    sqlite3_free_table(azResult);
    sqlite3_free(zErrMsg);
    //关闭数据库
    sqlite3_close_v2(config_db);
    return pDevMsg;
}

/*=======================================================================================
* 函 数 名： Sqlite_update_ip_msg_result
* 参    数： 
* 功能描述:  修改配置数据库ip地址信息
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26 
==========================================================================================*/
void Sqlite3QT::Sqlite_update_ip_msg_result(configMsgSt pDevMsg)
{
    int err =-1;
    char * errmsg = NULL;
    sqlite3 *config_db =NULL;

    //打开配置数据库
    err = sqlite3_open_v2(configDbFile, &config_db, SQLITE_OPEN_READWRITE, NULL);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(config_db);
        sqlite3_close_v2(config_db);
        return ;
    }

    //修改ip信息
    QString str = "update config_db set localipaddr='";
    str.append(pDevMsg.localIp);
    str.append("',");
    str.append("remoteipaddr='");
    str.append(pDevMsg.remoteIp);
    str.append("',");
    str.append("port=");
    str.append(QString::number(pDevMsg.port, 10));
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
    qDebug() << str;
    printf("更改ip指令 = %s \n", sql);
    err = sqlite3_exec(config_db, sql, NULL, NULL, &zErrMsg);
    //关闭数据库
    sqlite3_close_v2(config_db);
}

/*=======================================================================================
* 函 数 名： Sqlite_update_dev_id
* 参    数： 
* 功能描述:  修改配置数据库设备地址
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26 
==========================================================================================*/
void Sqlite3QT::Sqlite_update_dev_id(int devid)
{
    int err =-1;
    char * errmsg = NULL;
    sqlite3 *config_db =NULL;

    //打开配置数据库
    err = sqlite3_open_v2(configDbFile, &config_db, SQLITE_OPEN_READWRITE, NULL);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(config_db);
        sqlite3_close_v2(config_db);
        return ;
    }
    //修改设备ID
    QString str = "update config_db set maincode=";
    str.append(QString::number(devid, 10));
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
    qDebug() << str;
    printf("更改设备号指令 = %s \n",sql);
    err = sqlite3_exec(config_db, sql, NULL, NULL, &zErrMsg);
    //关闭数据库
    sqlite3_close_v2(config_db);
}

/*=======================================================================================
* 函 数 名： Sqlite_update_consumne_mode
* 参    数： 
* 功能描述:  修改配置数据库消费模式
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26 
==========================================================================================*/
void Sqlite3QT::Sqlite_update_consumne_mode(int mode,int money)
{
    int err =-1;
    char * errmsg = NULL;
    sqlite3 *config_db =NULL;

    //打开配置数据库
    err = sqlite3_open_v2(configDbFile, &config_db, SQLITE_OPEN_READWRITE, NULL);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(config_db);
        sqlite3_close_v2(config_db);
        return ;
    }
    //修改消费模式
    QString str = "update config_db set consumeMode=";
    str.append(QString::number(mode, 10));
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
    qDebug() << str;
    printf("更改消费模式指令 = %s \n", sql);
    err = sqlite3_exec(config_db, sql, NULL, NULL, &zErrMsg);

    if(mode == AUTO_CONSUME_MODE)//自动模式修改消费金额
    {
        str = "update config_db set AutoModeMoney=";
        str.append(QString::number(money, 10));
        QByteArray ba=str.toLatin1();
        char *sql=ba.data();
        qDebug() << str;
        printf("更改自动模式消费金额 = %s \n", sql);
        err = sqlite3_exec(config_db, sql, NULL, NULL, &zErrMsg);
    }
    //关闭数据库
    sqlite3_close_v2(config_db);
}

/*=======================================================================================
* 函 数 名： Sqlite_update_consumne_mode
* 参    数： 
* 功能描述:  查询某日--某日的消费记录总额跟笔数
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26
==========================================================================================*/
struct	dayConsumeRecordSt Sqlite3QT::sqlite3_consume_query_daymoney_db(QString daytime1, QString daytime2)
{
    int err =-1;
    char * errmsg = NULL;
    sqlite3 *recod_db =NULL;
    sqlite3_stmt *stmt = NULL; // 用来取数据的
	struct	dayConsumeRecordSt RecordStr;

	/* 打开数据库 */
	err = sqlite3_open_v2(recordDbFile, &recod_db, SQLITE_OPEN_READWRITE, NULL);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(recod_db);
        sqlite3_close_v2(recod_db);
        return RecordStr;
    }
    
    RecordStr.toalMoney  = 0;
    RecordStr.toalNumber = 0;
	// -1代表系统会自动计算SQL语句的长度
    QString str = "select *from consume where time between  ";
    str.append(daytime1);
    str.append(" and ");
    str.append(daytime2);
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
    qDebug() << str;
    printf("查询日采集记录指令 = %s \n", sql);

    if (sqlite3_prepare_v2(recod_db, sql, -1, &stmt, NULL) == SQLITE_OK) 
	{   
		while(sqlite3_step(stmt) == SQLITE_ROW ) 
		{	
			RecordStr.toalNumber++;
			// 取出第2列字段的值
			RecordStr.toalMoney += sqlite3_column_int(stmt, 2);
		}
		printf("RecordStr.toalNumber = %d, RecordStr.toalMoney = %d\n",RecordStr.toalNumber,RecordStr.toalMoney);
	}
	sqlite3_finalize(stmt);
    //关闭数据库
    sqlite3_close_v2(recod_db);
    return RecordStr;
}

/*=======================================================================================
* 函 数 名： sqlite3_collection_consumemoney_db
* 参    数： flag ==0查询未采记录；flag ==1查询已采记录
* 功能描述:  查询消费记录
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26 
==========================================================================================*/
struct	consumeRecordSt Sqlite3QT::sqlite3_collection_consumemoney_db(int flag)
{
    int err =-1;
    char * errmsg = NULL;
    sqlite3 *recod_db =NULL;
    sqlite3_stmt *stmt = NULL; // 用来取数据的
	struct	consumeRecordSt RecordStr;

	/* 打开数据库 */
	err = sqlite3_open_v2(recordDbFile, &recod_db, SQLITE_OPEN_READWRITE, NULL);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(recod_db);
        sqlite3_close_v2(recod_db);
        return RecordStr;
    }
	
    RecordStr.toalMoney  = 0;
    RecordStr.toalNumber = 0;
    //-1代表系统会自动计算SQL语句的长度
    QString str = "select *from consume where tag = ";
    if(flag == 0)
        str.append("0");
    else
        str.append("1");
    qDebug() << str;

    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
    qDebug() << str;
    printf("查询采集记录指令 = %s \n", sql);

    if (sqlite3_prepare_v2(recod_db, sql, -1, &stmt, NULL) == SQLITE_OK) 
	{   
		while(sqlite3_step(stmt) == SQLITE_ROW ) 
		{	
			RecordStr.toalNumber++;
			// 取出第2列字段的值
			RecordStr.toalMoney += sqlite3_column_int(stmt, 2);
		}
		printf("RecordStr.toalNumber = %d, RecordStr.toalMoney = %d\n",RecordStr.toalNumber,RecordStr.toalMoney);
	}
	sqlite3_finalize(stmt);

    //关闭数据库
    sqlite3_close_v2(recod_db);
    return RecordStr;
}

/*=======================================================================================
* 函 数 名： sqlite3_consume_insert_db
* 参    数： 
* 功能描述:  插入消费记录搭配记录数据库
* 返 回 值： 
* 备    注： 
* 作    者： lc
* 创建时间： 2022-01-26 
==========================================================================================*/
int Sqlite3QT::sqlite3_consume_insert_db(int consumeMode,int CurrentConsumMoney, QString consumeTime, QString cardNumber, QString name)
{
	char tempdata[200];
	int len,recordId,err;
	char *buf;
    sqlite3 *recod_db =NULL;
	sqlite3_stmt *stmt = NULL; // 用来取数据的

    recordId = 0;
	/* 打开数据库 */
	err = sqlite3_open_v2(recordDbFile, &recod_db, SQLITE_OPEN_READWRITE, NULL);
    if( err ) {
        qDebug()<< "Can't open database: "<< sqlite3_errmsg(recod_db);
        sqlite3_close_v2(recod_db);
        return err;
    }
	else 
		qDebug()<< "You have opened a sqlite3 database named user successfully";
    
    //查找最后一条交易记录的id号
    QString idSql = "select * from consume order by id desc limit 1";//查找最后一条交易记录的ID号
    QByteArray ba=idSql.toLatin1();
    char *sql0=ba.data();

	if (sqlite3_prepare_v2(recod_db, sql0, -1, &stmt, NULL) == SQLITE_OK) 
	{   
		while(sqlite3_step(stmt) == SQLITE_ROW ) 
		{	
			// 取出第1列字段的值
			recordId= sqlite3_column_int(stmt, 1);
		}
        qDebug()<< "最后一条交易记录 ID = " << recordId;
	}
	sqlite3_finalize(stmt);

	/*插入数据	*/
    recordId++;
    QString str = "insert into consume values(";
    str.append(QString::number(0));//采集标识
    str.append(",");
    str.append(QString::number(recordId));//交易记录ID
    str.append(",");
    str.append(QString::number(consumeMode));//消费模式
    str.append(",");
    str.append(QString::number(CurrentConsumMoney));//消费金额
    str.append(",'");
    str.append(consumeTime);//消费时间
    str.append("','");
    str.append(cardNumber);//消费卡号
    str.append("','");
    str.append(name);//用户姓名
    str.append("')");
    qDebug() << str;
    ba=str.toLatin1();
    char *sql=ba.data();

	sqlite3_exec(recod_db,sql,NULL,NULL,&zErrMsg);
	sqlite3_close(recod_db);
}

/*=======================================================================================
* 函 数 名： sqlite3_blaknumber_query_db
* 参    数： 卡号
* 功能描述:  查询是否再黑名单数据库中
* 返 回 值： 0==正常卡；1==黑名单卡
* 备    注： 
* 作    者： lc
* 创建时间： 2022-04-26 
==========================================================================================*/
int Sqlite3QT::sqlite3_blaknumber_query_db(QString number)
{
	char tempdata[100],bufer[10];
	int len;
	char *buf;
    const unsigned char *numberbak;
	sqlite3_stmt *stmt = NULL; // 用来取数据的
    sqlite3 *blknumber_db=NULL;//黑名单数据库句柄
	memset(bufer,10,0);
	memset(tempdata,100,0);

	int ret =-1;
	/* 打开数据库 */
	len = sqlite3_open(blknumDbFile,&blknumber_db);
	if( len )
	{
	   /*  fprintf函数格式化输出错误信息到指定的stderr文件流中  */
	   qDebug() <<"Can't open database:"<<sqlite3_errmsg(blknumber_db);//sqlite3_errmsg(db)用以获得数据库打开错误码的英文描述。
	   sqlite3_close(blknumber_db);
	   return len;
	  // exit(1);
	}
	else 
		qDebug() <<"You have opened a sqlite3 database named user successfully!";

    QString str = "select *from blknumber where number =";
    str.append(number);
    qDebug() <<str;
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
	ret = -1;
	if (sqlite3_prepare(blknumber_db, sql, -1, &stmt, NULL) == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			numberbak = sqlite3_column_text(stmt, 1);
            char *str1 = (char *)numberbak;
	        QString str =  QString(QLatin1String(str1));
            if(str.compare(number, Qt::CaseInsensitive))//不区分大小写
            {
                qDebug() <<"黑名单卡";
                sqlite3_finalize(stmt);
                sqlite3_close(blknumber_db);
                return 1;
            }
		}
	}
    qDebug() <<"正常卡卡";
    sqlite3_finalize(stmt);
    sqlite3_close(blknumber_db);
    return 0;
}

//插入黑名单数据库
int Sqlite3QT::sqlite3_blaknumber_insert_db(QString number)
{
	char tempdata[200];
	int len;
	char *buf;
	sqlite3_stmt *stmt = NULL; // 用来取数据的
    sqlite3 *blknumber_db=NULL;//黑名单数据库句柄

	if(sqlite3_blaknumber_query_db(number))//数据库中已经存在
		return 0;

	/* 打开数据库 */
	len = sqlite3_open(blknumDbFile,&blknumber_db);
	if( len )
	{
	  /*  fprintf函数格式化输出错误信息到指定的stderr文件流中  */
	   qDebug() <<"Can't open database:"<<sqlite3_errmsg(blknumber_db);//sqlite3_errmsg(db)用以获得数据库打开错误码的英文描述。
	   sqlite3_close(blknumber_db);
	   return len;
	  // exit(1);
	}
	else 
		printf("You have opened a sqlite3 database named user successfully!\n");

    QString str = "insert into blknumber values(";
    str.append(number);
    str.append(")");
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
    qDebug() <<str;
	sqlite3_exec(blknumber_db,sql,NULL,NULL,&zErrMsg);
	sqlite3_close(blknumber_db);
    return 0;
}
//删除黑名单从数据库
int Sqlite3QT::sqlite3_blaknumber_del_db(QString number)
{
	char tempdata[200];
	int len;
	char *buf;
	sqlite3_stmt *stmt = NULL; // 用来取数据的
    sqlite3 *blknumber_db=NULL;//黑名单数据库句柄

	/* 打开数据库 */
	len = sqlite3_open(blknumDbFile,&blknumber_db);
	if( len )
	{
	 /*  fprintf函数格式化输出错误信息到指定的stderr文件流中  */
	   qDebug() <<"Can't open database:"<<sqlite3_errmsg(blknumber_db);//sqlite3_errmsg(db)用以获得数据库打开错误码的英文描述。
	   sqlite3_close(blknumber_db);
	   return len;
	}
	else 
		printf("You have opened a sqlite3 database named user successfully!\n");

    QString str = "delete from blknumber where number = ";
    str.append(number);
    str.append(")");
    qDebug() <<str;
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();

	sqlite3_exec(blknumber_db,sql,NULL,NULL,&zErrMsg);
	sqlite3_close(blknumber_db);
}

//清空黑名单数据库
int Sqlite3QT::sqlite3_blaknumber_clr_db(void)
{
	char tempdata[200];
	int len;
	char *buf;
	sqlite3_stmt *stmt = NULL; // 用来取数据的
    sqlite3 *blknumber_db=NULL;//黑名单数据库句柄

	/* 打开数据库 */
	len = sqlite3_open("blknum.db",&blknumber_db);
	if( len )
	{
	   /*  fprintf函数格式化输出错误信息到指定的stderr文件流中  */
	   qDebug() <<"Can't open database:"<<sqlite3_errmsg(blknumber_db);//sqlite3_errmsg(db)用以获得数据库打开错误码的英文描述。
	   sqlite3_close(blknumber_db);
	   return len;
	}
	else 
		printf("You have opened a sqlite3 database named user successfully!\n");

    QString str = "delete from blknumber;";
    qDebug() <<str;
    QByteArray ba=str.toLatin1();
    char *sql=ba.data();
	sqlite3_exec(blknumber_db,sql,NULL,NULL,&zErrMsg);
	sqlite3_close(blknumber_db);
}
