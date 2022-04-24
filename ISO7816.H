

#include "string.h"
#include <stdint.h>
#include <unistd.h>

#define     MATCHCODE_ERR           19//PSAM閸掓繂顫愰崠鏍晩鐠囷拷(1.婢跺秳缍�2.PPS婢惰精瑙�3.娑撯偓閸楋繝鈧氨娲拌ぐ锟�4.鐟欙妇鍋ｉ幒銉ㄐ曟稉宥堝)
#define     CPU_SELFILE_FAIL        20//闁鏋冩禒璺恒亼鐠愶拷(1.娑撹崵娲拌ぐ锟�2.娑撯偓閸楋繝鈧艾绨查悽锟�3.闁藉崬瀵橀弬鍥︽)
#define     CPU_READFILE_FAIL       21//鐠囩粯鏋冩禒璺恒亼鐠愶拷(1.閸忣剙鍙℃穱鈩冧紖2.缁鳖垵顓搁弬鍥︽3.鐠佹澘缍�)
#define     CPU_REDABALANCE_FAIL    22//鐠囪缍戞０婵嗐亼鐠愶拷
#define		Uncert_State						23//閸愭瑥宕遍妴浣锋唉閺勬挸銇戠拹锟�
#define     CARD_SAME_ERROR	        24//闂堢偛鎮撴稉鈧鐘插幢闁挎瑨顕�(1.鎼村繐鍨崣锟�2.閸椻€冲祪閸掑嘲褰�)
#define 	GET_PROVE_FAIL		    25//閸欐牔姘﹂弰鎾诡吇鐠囦礁銇戠拹锟�
#define     PSAM_MAC1_FAIL		    26//MAC1
#define     PSAM_CHECK_MAC2		    27//MAC2
#define	    PSAM_RESET_ERROR        28//閸栧綊鍘ょ€涙鏁�
#define	    PSAM_FILEPARA_ERR       29//PSAM闁挎瑨顕�(1.娑撯偓閸楋繝鈧氨娲拌ぐ锟�2.閸欏倹鏆熺拠璇插絿3.缁旀瑧鍋ｆ稉锟�0)
#define		NO_PURSE_ERROR			30 //闁藉崬瀵樺▽陇顔曠純锟�
#define		SYS_CONSUM_ESC			31 //闁藉崬瀵樺▽陇顔曠純锟�
#define		No_Use					32 //娑撳秴鍘戠拋鍛婎劃闊偂鍞ゅ☉鍫ｅ瀭
#define		No_ip					33 //IP娑撱垹銇�#define		CARD_NOCARD				0xff
  
#define     PSAM_COM_ERROR          0xf1//PSAM闁俺顔嗛柨娆掝嚖(1.闂€鍨2.閺冪姴鎼锋惔锟�3.閸濆秴绨查柨娆掝嚖) 
#define     CPU_WRITEPURSE_FAIL     0xf2//閸愭瑧鐤拋鈥炽亼鐠愶拷
#define     CONSUM_PROCE_FAIL	    0xf3//娴溿倖妲楁径杈Е



char ISO7816_PSAM(unsigned char SendLen, unsigned char * SendBuf, unsigned char * RcvLen, unsigned char * Rcvdata);

uint8_t ReadCardCommonDatas_CPU(void);//閺嶈宓侀崡陇顫夐崚鎺曨嚢閸欐渿PU閸椻剝鏆熼幑锟�

