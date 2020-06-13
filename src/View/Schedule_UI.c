#include<stdio.h>
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Service/Ticket.h"
#include "../View/Ticket_UI.h"

/* �����ݳ��ƻ����� */
void Schedule_UI_MgtEntry(int play_id) {
    Pagination_t paging;
    schedule_list_t list;
    schedule_node_t *p;
    int i;
    char choice;
    List_Init(list, schedule_node_t);
    paging.offset = 0;
    paging.pageSize = 5;
    paging.totalRecords = Schedule_Srv_SelectByPlayID(play_id, list);
    do {
        system("clear");
        printf("============�ݳ��ƻ�===========\n");
        Paging_ViewPage_ForEach(list, paging, schedule_node_t, p, i) {
            
            printf("==========================\n");
            /*  */
            
        }
        printf("==============�����˵�===========\n");
        printf("                                   \n");
        printf("[a]������ݳ��ƻ�\n");
        printf("[m]�޸��ݳ��ƻ�\n");
        printf("[d]ɾ���ݳ��ƻ�\n");
        printf("[r]�˳�");
        scanf("%d", &choice);

    }while(choice != 'r' && choice != 'R');
}
/* add */
int Schedule_UI_Add(void) {
    schedule_t data;
    int rtn = 0;
    printf("�������Ŀid��");
    scanf("%d", &data.play_id);
    /*  */
    do {
        printf("�������ݳ���ID:");
        scanf("%d", &data.id);
        /*  */
    }while(data.id != -1);
    if(data.id != -1) {
        printf("=============�������ݳ��ƻ�����=================\n");
        printf("\n");
        /*  */
        data.id = EntKey_Perst_GetNewKeys(&data, 1);
    }
    Schedule_Srv_Add(&data);
    Ticket_UI_MgtEntry(data.id);
}

/* ɾ�� */
int Schedule_UI_Del(int id) {
    int rtn = 0;
    if(Schedule_Srv_Delete(id)) {
        printf("ɾ���ɹ���\n");
        rtn = 1;
        return rtn;
    }
    else {
        printf("ɾ��ʧ�ܣ�\n");
        return rtn;
    }
}
/* mod */
int Schedule_UI_Mod(int id) {
    int rtn = 0;
    schedule_t data;
    if(Schedule_Srv_SelectByID(id, &data)) {
        printf("=========�ݳ��ƻ���Ϣ=========\n");
        printf("                             \n");
        printf("�ݳ��ƻ�ID��                %d\n",data.id);
        printf("��ĿID��                    %d\n",data.play_id);
        printf("�ݳ���ID��                  %d\n",data.studio_id);
        printf("��ӳ���ڣ�            %d-%d-%d\n",data.date.year, data.date.month, data.date.day);
        printf("��ӳʱ�䣺            %d-%d-%d\n",data.time.hour, data.time.minute, data.time.second);
        printf("��λ����                    %d\n",data.seat_count);
        printf("==============================\n");
        printf("������Ҫ�޸ĵ���Ϣ��\n");
        printf("�������ĿID:");
        scanf("%d", &data.play_id);
        /*  */
        printf("");
        scanf("%d", &data.studio_id);
        printf("");
        scanf("%d-%d-%d", &data.date.year, &data.date.month, &data.date.day);

        if(Schedule_Srv_Mod(&data)) {
            printf("�޸ĳɹ�\n");
            rtn = 1;
            return rtn;
        }
        else {
            printf("�޸�ʧ��\n");
            return rtn;
        }
    }
    else {
        printf("û���ҵ�\n");
        return rtn;
    }
}

int Schedule_UI_Query(void) {
    char name[40];
    printf("please input play name:");
    scanf("%s", name);
    Schedule_Srv_SelectByName(name);
}