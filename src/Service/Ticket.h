#ifndef TICKET_UI_H_
#define TICKET_UI_H_

<<<<<<< HEAD
#include "../Service/Ticket.h"

//ç¥¨çŠ¶æ€ç±»å‹å®šä¹‰
=======

//Æ±×´Ì¬ÀàĞÍ¶¨Òå
>>>>>>> 8438a436b212b5c7e5eb2c6523afd67f261d82be
typedef enum{
    TICKET_AVL=0,     //´úÊÛ
    TICKET_SOLD=1,    //ÒÑÊÛ
    TICKET_RESV=9     //Ô¤Áô
}ticket_status_t;


//Æ±ÊµÌåÊı¾İÀàĞÍµÄ¶¨ÒåÈçÏÂ
typedef struct{
    int id;                   //Æ±ID
    int schedule_id;          //Ñİ³ö¼Æ»®ID
    int seat_id;              //×ùÎ»ID
    int price;                //Æ±¼Û
    ticket_status_t status;   //Æ±×´Ì¬
}ticket_t;


typedef struct ticket_node{
    ticket_t data;
    struct ticket_node *next,*prev;
}ticket_node_t,*ticket_list_t;

<<<<<<< HEAD

//æ ‡è¯†ç¬¦ï¼šTTMS_SCU_Ticket_Srv_GenBatch
//åŠŸèƒ½ï¼šç”Ÿæˆæ¼”å‡ºç¥¨
void Ticket_Srv_GenBatch(int schedule_id);


//æ ‡è¯†ç¬¦ï¼šTTMS_SCU_Ticket_Sry_DeleteBatch
//åŠŸèƒ½ï¼šæ ¹æ®æ¼”å‡ºè®¡åˆ’IDåˆ é™¤æ¼”å‡ºç¥¨
void Ticket_Srv_DeleteBatch(int schedule_id);


//æ ‡è¯†ç¬¦ï¼šTTMS_SCU_Ticket_Srv_FetchByID
//åŠŸèƒ½ï¼šæ ¹æ®IDè·å–æ¼”å‡ºç¥¨
int Ticket_Srv_FetchByID(int id, ticket_t *buf);


//æ ‡è¯†ç¬¦ï¼šTTMS_SCU_Schedule_Srv_FetchByID
//åŠŸèƒ½: æ ¹æ®IDè·å–æ¼”å‡ºè®¡åˆ’
int Schedule_Srv_FetchByID(int id,schedule_t *buf );



//æŸ¥è¯¢æ‰€æœ‰ç¥¨ä¿¡æ¯
=======
//²éÑ¯ËùÓĞÆ±ĞÅÏ¢
>>>>>>> 8438a436b212b5c7e5eb2c6523afd67f261d82be
int Ticket_Srv_FetchAll(ticket_list_t list);

//±êÊ¶·û£ºTTMS_SCU_Ticket_Srv_GenBatch
//¹¦ÄÜ£ºÉú³ÉÑİ³öÆ±
int Ticket_Srv_GenBatch(int schedule_id);


//±êÊ¶·û£ºTTMS_SCU_Ticket_Sry_DeleteBatch
//¹¦ÄÜ£º¸ù¾İÑİ³ö¼Æ»®IDÉ¾³ıÑİ³öÆ±
void Ticket_Srv_DeleteBatch(int schedule_id);


//±êÊ¶·û£ºTTMS_SCU_Ticket_Srv_FetchByID
//¹¦ÄÜ£º¸ù¾İID»ñÈ¡Ñİ³öÆ±
int Ticket_Srv_FetchByID(int id, ticket_t *buf);


//±êÊ¶·û£ºTTMS_SCU_Schedule_Srv_FetchByID
//¹¦ÄÜ: ¸ù¾İID»ñÈ¡Ñİ³ö¼Æ»®
int Schedule_Srv_FetchByID(int id,schedule_t *buf );

#endif
