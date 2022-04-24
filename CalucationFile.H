#include "string.h"
#include <stdint.h>
#include <unistd.h>

		 
uint8_t   	BytesCheckSum(uint8_t *,uint8_t);//校验和比较
uint8_t     BytesComp( uint8_t * ,uint8_t *,uint8_t);//字符串比较，正确返回0
uint8_t	    BCD_String_Diag(uint8_t * ,uint8_t);//BCD码字符串诊断
uint8_t     BCDToHex(uint8_t  );
uint8_t     HexToBCD(uint8_t  );
uint32_t	ChgBCDStringToUlong(uint8_t * ,uint8_t);//BCD码字符串转换为整型数
uint8_t	    CalCheckSum(uint8_t * ,uint8_t);//计算校验和�
void	    ChgUlongToBCDString( uint32_t ,uint8_t * ,uint8_t );
void	    ChgIntToStrings(uint16_t	ii,uint8_t * ptr);
uint32_t	ChgInputToUlong(uint8_t * ,uint8_t);//输入的数字转换为长整形
uint32_t 	GetU32_HiLo(uint8_t *);
uint16_t 	GetU16_HiLo(uint8_t *);
void 	    PutU32_HiLo(uint8_t *,uint32_t);
void 	    PutU16_HiLo(uint8_t *,uint16_t);
void	    FormatBuffer(uint8_t,uint8_t * ,uint8_t *);
uint32_t	ChgKeyStringToUlong(uint8_t * ptr ,uint8_t Len);
uint32_t	ChgStringsToInt(uint8_t * ptr);
uint16_t    DoubleBigToSmall(uint16_t a);
void        HexGroupToHexString(uint8_t *data,uint8_t *dst,uint8_t len);
uint16_t    HexStringToHexGroup(uint8_t *,uint8_t *,uint16_t);
uint8_t     AddQuFan(uint8_t *str,uint8_t len);//累加和取反
 