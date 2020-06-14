#include "../View/Ticket_UI.h"
#include "../View/Sale_UI.h"

#include "../Common/List.h"
#include "../Common/common.h"

#include "../Service/Ticket.h"
#include "../Service/Play.h"
#include "../Service/studio.h"
#include "../Service/Schedule.h"
#include "../Service/seat.h"


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
    
    Schedule_Srv_FetchByID(schedule_id, need_schedule);
    Play_Srv_FetchByID( need_schedule->play_id, need_play);
    
    
    
    
    do{
        printf(
                "\n==================================================================================================\n");
        printf(
                "*********************************************Ʊ �� Ϣ*********************************************\n");
	printf("             ��Ŀ����             �ݳ������             �ݳ�����             �ݳ�ʱ��             \n\n");
		

	printf("           %-6s                 %.2d                %d/%.2d/%.2d            %.2d:%.2d:%.2d\n\n\n",
                need_play->name,need_schedule->studio_id,
                need_schedule->date.year,need_schedule->date.month,need_schedule->date.day,
                need_schedule->time.hour,need_schedule->time.minute,need_schedule->time.second);


	printf("**************************************************************************************************\n");
	printf("          |    [A]     ���ɸ��ݳ�Ʊ    |    [D]    ���������ݳ�Ʊ    |     [R]     �����ϲ�       |\n");
	printf("\n==================================================================================================\n");
	printf("����������ѡ��");
	fflush(stdin);
	scanf("%c",&choice);
	getchar();
        if( choice=='a' || choice == 'A' || choice == 'd' || choice == 'D' || choice == 'R' || choice == 'r')
        { 
		    switch(choice)
            {
		        case 'a':
	        	case 'A':
		         	if (Ticke_Srv_GenBatch(schedule_id))
			        	printf("���ɳɹ�!\n");
			     else
				        printf("����ʧ��!\n");
			        break;
		        case 'd':
		        case 'D':
			        if(Ticket_Sry_DeleteBatch(schedule_id) && Ticker_Srv_GenBatch(schedule_id))
				        printf("�������ɳɹ�");
			        else
				        printf("��������ʧ��");
			        break;
            }   
        }
        else
        {
           printf("δ֪����������������"); 
        }
	}while (choice != 'r' && choice != 'R');
	system("cls");

}
//��ʶ����TTMS_SCU_Ticket_UI_Qry
//���ܣ���ѯ�ݳ�Ʊ����
void Ticket_UI_Query(void) {
	int id;
	printf("\n\t\t\t\t\tƱ��ID:");
	scanf("%d",&id);
	Ticket_UI_ShowTicket(id);
}


//��ʶ����TTMS_SCU_Ticket_UI_ShowTickeet
//���ܣ���ѯ�ݳ�Ʊ����
int Ticket_UI_ShowTicket(int ticket_id) {
	ticket_t buf, data;
	sale_t sale;
	system("cls");
	gettime();
	printf("\n\n\n\n\n") ;
	if (Ticket_Srv_FetchByID(ticket_id, &buf))
	{
		if (buf.status == 1)
		{
			data.id = buf.id;
			data.schedule_id = buf.schedule_id;
			data.seat_id = buf.seat_id;
			data.status = 1;

			Ticket_Info(&data);
			printf("\t\t\t\t    ״̬:����\n");
			printf("\n\t\t\t\t    ���������");
			getch();

		}
		else
		{
			data.id = buf.id;
			data.schedule_id = buf.schedule_id;
			data.seat_id = buf.seat_id;
			data.status = 1;

			Ticket_Info(&data);
			printf("\t\t\t\t    ״̬:δ��\n");
			printf("\n\t\t\t\t    ���������");
			getch();


		}
	}
	else
	{
		printf("\t\t\t\t        �޴�Ʊ,���������");
		getch();
	}
    return 0;
}
