#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "iso7816.h"
#include "delay.h"
#include "CalucationFile.h"

////错误信息定义
#define		NO_CARD					-1
#define		SYS_OK					0
#define		CARD_OK					0
#define		SYS_RC500_ERROR			1//读卡模块 
#define		SYS_FLASH_ERROR			2//FLASH
#define		SYS_24C256_ERROR		3//24C256
#define		SYS_24C64_ERROR			4//24C64
#define		CARD_BATCH_ERROR		5//批次
#define		CARD_NUMBER_ERROR		6//卡号不合法(1.BCD 2.超范围)
#define		CARD_LOSTCARDNUM		7//挂失卡
#define		CARD_DATA_ERROR			8//用户数据错误(1.卡数据校验和错2.卡折扣为0)
#define		CARD_LITTLEMONEY		9//金额不足
#define		CARD_OVERDATE			10//1.卡过期2.卡未启用3.黑名单有效月4.钱包有效期5.日期格式
#define		SYS_SAVERECORDFULL		11//记录满
#define   	SYS_PINCHECK_FAIL   	12//系统校验失败
#define		CARD_LIMIT_NUM			13//限次(1.无匹配方案2.限次)
#define		CARD_CONSUM_OVER		14//超出消费限额(1.单笔2.规划范围3.日限4.月限)
#define		SYS_8563_ERROR			15//上电检测时钟模块
#define		NETCARD_ERROR			16//TCP网卡初试化失败
#define		TIME_ERROR				17//消费中检测合法性
#define		CARD_STATUS_ERROR		18 //卡状态错误
#define     CARD_AUTH_FAIL          19//卡片认证失败
#define     MATCHCODE_ERR           20//匹配字失败

//卡片信息
typedef struct 
{       
	int  status;  //读取卡片状态      
	uint8_t  nameBuf[20];//用户名字    
	uint8_t  cardBatch;  //卡片批次
	uint8_t  cardIdentity; //卡身份    
    uint8_t  pursesSector[10];//卡片钱包号索引
	uint8_t  cardPrinterNum[4];//卡片印刷号 
	uint8_t  purseConsumDateTime[4];//钱包最新的消费时间年月日时分
	uint8_t  cardConsumDate[4];//消费日期年月日
	uint8_t  consumCountDateTime[4];//计次消费时间
	uint8_t  pinCode[4];//卡片密码
	uint8_t  daySumMoneyDatasBak[32];//日累计消费额备份
	uint8_t  CardBatchEnable[32];//卡批次索引
	uint8_t  MainWrBufferBak[32];//备份
	uint8_t  PurseWrBufferBak[32];
	uint8_t  PurseDatas_Info[40];
	uint8_t  CardSerialNum[4];//卡片序列号
	uint8_t  matchCode[4];//用户代码
	uint8_t  cardKeyCode[6];//读卡密码
	uint8_t  calCardKey[8];//卡密钥
	uint8_t  cardDayConsumCount;//计次消费次数
	uint8_t  bitUseMoneyBlock;//新余额写入卡余额1，卡余额2
	uint8_t  Limit_MoneySign;//日月限额标识
	uint16_t purseContrlNum;//钱包序列号 
	uint16_t purseBT_Num;//控制序列号
	uint32_t maxConsumMoney;//单笔限额
    uint32_t limit_DayMoney;//日限额  
    uint32_t cardDayConsumMoney;//卡片日累计消费额
    uint32_t cardBalance;//卡片余额
	uint32_t newBalanceMoney;//消费后余额
	uint32_t purseSumConsumMoney;//卡片累计消费额
} cardMsgInfo;


//void MFRC522_Initializtion(void) ;//RC522初始化
//测试是否有卡返回卡序列号
cardMsgInfo RequestCard(void);
/*=======================================================================================
* 函 数 名： ReadCardCommonDatas_M1
* 参    数： cardSector(扇区号), pMsg消费信息结构体;
* 功能描述:  读取卡片信息结构体
* 返 回 值： 成功返回 卡片信息结构体; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
cardMsgInfo ReadCardCommonDatas_M1(uint8_t cardSector, cardMsgInfo pMsg);

/*=======================================================================================
* 函 数 名： ReadCard_DaySumConsumMoney_M1
* 参    数： pMsg消费信息结构体;
* 功能描述:  读出累计日消费额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
cardMsgInfo ReadCard_DaySumConsumMoney_M1(cardMsgInfo pMsg);

/*=======================================================================================
* 函 数 名： ReadCardBalanceDatas_M1
* 参    数： RdSector扇区号；pMsg消费信息结构体;
* 功能描述:  读取卡片余额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
cardMsgInfo ReadCardBalanceDatas_M1(uint8_t RdSector, cardMsgInfo pMsg);

/*=======================================================================================
* 函 数 名： WriteBalanceToCard_M1
* 参    数： bit == 0 消费状态;bit == 1取消消费回写原来金额
			WrSector扇区号; pMsg消费信息结构体;  CurrentConsumMoney消费额; 
* 功能描述:  写入新的卡片余额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
uint8_t WriteBalanceToCard_M1(uint8_t bbit, uint8_t WrSector, uint32_t CurrentConsumMoney, cardMsgInfo pMsg);

/*=======================================================================================
* 函 数 名： ReWriteCardSub_M1
* 参    数： bit == 0 消费状态;bit == 1取消消费回写原来金额 pMsg消费信息结构体;  
* 功能描述:  复写新的卡片余额
* 返 回 值： 成功返回 0; 
* 备    注： 
* 作    者： lc
* 创建时间： 2021-12-02
==================================================================================*/
uint8_t ReWriteCardSub_M1(uint8_t bbit, cardMsgInfo pMsg);
