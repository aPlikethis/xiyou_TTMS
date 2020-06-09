/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* File name: common.h			 
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015年4月22日		 
*/

#ifndef COMMON_H_
#define COMMON_H_

//日期结构体 
typedef struct {
	int year;
	int month;
	int day;
}user_date_t;

//时间结构体 
typedef struct {
	int hour;
	int minute;
	int second;
}user_time_t;

//8号修改开始
/* 剧目类型定义 */
typedef enum {
    PLAY_TYPE_FILM = 1,
    PLAY_TYPE_OPEAR = 2,
    PLAY_TYPE_CONCERT = 3,
}play_type_t;

/* 剧目分级类型定义 */
typedef enum {
    PLAY_TYPE_CHILD = 1,
    PLAY_RATE_TEENAGE = 2,
    PLAY_RATE_ADULT = 3
}play_rating_t;

/* 日期类型的定义如下 */
typedef struct {
    int year;
    int month;
    int day;
}ttms_date_t;
/* 剧目实体数据类型定义 */
typedef struct {
    int id;                 //剧目id
    char name[31];          //剧目名称
    play_type_t type;       //剧目类型
    char area[9];           //剧目出品地区
    play_rating_t rating;   //剧目等级
    int duration;           //时长，以分钟为单位
    ttms_date_t start_date; //开始放映日期
    ttms_date_t end_date;   //放映结束日期
    int price;              //建议票价

}play_t;

/* 剧目链表节点定义 */
typedef struct play_node {
	play_t date;             //实体数据
	struct play_node *next;  //后继指针
	struct play_node *prev;  //前驱指针
}play_node_t, *play_list_t;

//8号修改结束

//直接读取键盘输入值
//int ScanKeyboard();

//将字符串str就地转换为大写字符串，并返回字符串头指针
char *Str2Upper(char *str);

//将字符串str就地转换为小写字符串，并返回字符串头指针
char *Str2Lower(char *str);

//比较日期dt1, dt2的大小。相等返回0，dt1<dt2返回-1，否则1
int DateCmp(user_date_t dt1, user_date_t dt2);

//获取系统当前日期
user_date_t DateNow();

//获取系统当前时间
user_time_t TimeNow();

#endif /* COMMON_H_ */
