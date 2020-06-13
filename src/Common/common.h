/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* File name: common.h			 
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015Äê4ÔÂ22ÈÕ		 
*/

#ifndef COMMON_H_
#define COMMON_H_

<<<<<<< HEAD
#include "../Common/common.h"

//æ—¥æœŸç»“æ„ä½“ 
=======
//ÈÕÆÚ½á¹¹Ìå 
>>>>>>> 8438a436b212b5c7e5eb2c6523afd67f261d82be
typedef struct {
	int year;
	int month;
	int day;
}user_date_t;

//Ê±¼ä½á¹¹Ìå 
typedef struct {
	int hour;
	int minute;
	int second;
}user_time_t;

//Ö±½Ó¶ÁÈ¡¼üÅÌÊäÈëÖµ
//int ScanKeyboard();

//½«×Ö·û´®str¾ÍµØ×ª»»Îª´óĞ´×Ö·û´®£¬²¢·µ»Ø×Ö·û´®Í·Ö¸Õë
char *Str2Upper(char *str);

//½«×Ö·û´®str¾ÍµØ×ª»»ÎªĞ¡Ğ´×Ö·û´®£¬²¢·µ»Ø×Ö·û´®Í·Ö¸Õë
char *Str2Lower(char *str);

//±È½ÏÈÕÆÚdt1, dt2µÄ´óĞ¡¡£ÏàµÈ·µ»Ø0£¬dt1<dt2·µ»Ø-1£¬·ñÔò1
int DateCmp(user_date_t dt1, user_date_t dt2);

//»ñÈ¡ÏµÍ³µ±Ç°ÈÕÆÚ
user_date_t DateNow();

//»ñÈ¡ÏµÍ³µ±Ç°Ê±¼ä
user_time_t TimeNow();

#endif /* COMMON_H_ */
