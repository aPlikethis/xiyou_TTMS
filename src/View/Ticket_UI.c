#include "../View/Ticket_UI.h"

#include "../Common/List.h"
#include "../Common/common.h"

#include "../Service/Ticket.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"


#include <stdio.h>
#include <stdlib.h>

//��ʶ����TTMS_SCU_Ticket_UI_MgtEnt
//���ܣ���ʾ�������Ӧ���ݳ��ƻ���Ϣ
void Ticket_UI_MgtEntry(int schedule_id)
{
    char choice;

    //�����ݳ��ƻ�ID��ȡ�ݳ��ƻ���Ϣ
    //�ӻ�ȡ����Ϣ�У�ʹ�þ�ĿID��ȡ�þ�Ŀ��Ϣ
    schedule_t *need_schedule;
    play_t *need_play;

    need_schedule = (schedule_t *)malloc(sizeof(schedule_t));
    need_play = (play_t *)malloc(sizeof(play_t));
    
    Schedule_Srv_SelectByID(schedule_id, need_schedule);
    Play_Srv_FetchByID( need_schedule->play_id, need_play);
    
    
    
    
    do{
        	printf("\n==================================================================================================\n");
    printf("********************************************THE TICKET********************************************\n");
	printf("   Repertoire name          Performance ID              Performance date            Show time             \n\n");
	printf("      %-6s                    %.2d                       %d/%.2d/%.2d               %.2d:%.2d:%.2d\n\n\n",
                need_play->name,need_schedule->studio_id,
                need_schedule->date.year,need_schedule->date.month,need_schedule->date.day,
                need_schedule->time.hour,need_schedule->time.minute,need_schedule->time.second);


	printf("**************************************************************************************************\n");
	printf("  |    [A]dd show ticket   |    [D]elete and generate show tickets    |       [R]eturn         |\n");
	printf("\n==================================================================================================\n");
	printf("Please enter your choice:");
	fflush(stdin);
	scanf("%c",&choice);
	getchar();
        if( choice=='a' || choice == 'A' || choice == 'd' || choice == 'D' || choice == 'R' || choice == 'r')
        { 
		    switch(choice)
            {
		        case 'a':
	        	case 'A':
		         	if (Ticket_Srv_GenBatch(schedule_id))
			        	printf("Generated successfully!\n");
			     else
				        printf("Generation failed!\n");
			        break;
		        case 'd':
		        case 'D':
			        if(Ticket_Srv_DeleteBatch(schedule_id) && Ticket_Srv_GenBatch(schedule_id))
				        printf("Rebuilt successfully");
			        else
				        printf("Rebuild failed");
			        break;
            }   
        }
        else
        {
           printf("Unknown operation, please re-enter"); 
        }
	}while (choice != 'r' && choice != 'R');
	system("cls");

}
//��ʶ����TTMS_SCU_Ticket_UI_Qry
//���ܣ���ѯ�ݳ�Ʊ����
void Ticket_UI_Query(void) {
	int id;
	printf("\n\t\t\t\t\tTicket_ID:");
	scanf("%d",&id);
	Ticket_UI_ShowTicket(id);
}


//��ʶ����TTMS_SCU_Ticket_UI_ShowTickeet
//���ܣ���ѯ�ݳ�Ʊ����
int Ticket_UI_ShowTicket(int ticket_id) {
	ticket_t *buf;
	system("cls");
	printf("\n\n\n\n\n") ;
	if (Ticket_Srv_FetchByID(ticket_id, buf)) {
        printf(
                "\n==================================================================================================\n");
        printf(
                "*********************************************THE TICKET********************************************\n");
        printf("           Ticket_ID          	 schedule_ID               Seat_ID                 Price                  \n\n");
        printf("               %d                    %d                         %d                      %d\n\n\n",
               buf->id, buf->schedule_id, buf->seat_id, buf->price);
        printf("**************************************************************************************************\n");
    }
	else
	{
		printf("Not Found����");
	}
    return 0;
}
