/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* 用例编号：TTMS_UC_02
* File name: Seat_UI.c			  
* Description : 设置座位用例界面层	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015年4月22日	
*/

#include "Seat_UI.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Common/List.h"
#include <stdio.h>
#include "../Service/Account.h"

/*
表识符：TTMS_SCU_Seat_UI_S2C 
函数功能：根据座位状态获取界面显示符号。
参数说明：status为seat_status_t类型，表示座位状态。
返 回 值：字符型，表示座位的界面显示符号。
*/
inline char Seat_UI_Status2Char(seat_status_t status)
{
	char statusChar;
	switch (status) {
        case SEAT_GOOD:		//有座位
            statusChar = '#';
            break;
        case SEAT_BROKEN:	//损坏的座位
            statusChar = 'X';
            break;
        case SEAT_NONE:
        default:
		statusChar = '|';
            break;
	}
	return statusChar;
}





/*
标识符：TTMS_SCU_Seat_UI_C2S
函数功能：根据输入符号获取座位状态。
参数说明：statusChar为字符型，表示设置座位的输入符号。
返 回 值：seat_status_t类型，表示座位的状态。
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar)
{
	seat_status_t status;
	switch (statusChar) {
	case '#':		//有座位
		status = SEAT_GOOD;
		break;
	case 'X':	//损坏的座位
		status = SEAT_BROKEN;
		break;
	default:
		status = SEAT_NONE;
		break;
	}
	return status;
}

/*
标识符：TTMS_SCU_Seat_UI_MgtEnt
函数功能：界面层管理座位的入口函数，显示当前的座位数据，并提供座位数据添加、修改、删除功能操作的入口。
参数说明：roomID为整型，是需要设置座位的演出厅ID。
返 回 值：无。
*/ 
void Seat_UI_MgtEntry(int roomID)
{
	int seatCount = 0;
	int changedCount = 0;
	studio_t studioRec;

    if (!Studio_Srv_FetchByID(roomID, &studioRec))//studioRec中会存放找到的演播厅信息
    {
		printf("\nNo studio!\nReturned to the superior interface for you\n");
		return;
	}
	seat_list_t list;//演出厅座位链表的头指针
	//seat_node_t *p;//该演播厅座位的节点
	List_Init(list, seat_node_t);//为list初始化为双向链表节点
    if(studioRec.seatsCount == 0)
    {
        seatCount = Seat_Srv_RoomInit(list, roomID, studioRec.rowsCount,studioRec.colsCount);
		studioRec.seatsCount = seatCount;
		Studio_Srv_Modify(&studioRec);
    }
    else
    {

        seatCount = Seat_Srv_FetchByRoomID(list,roomID);
    }
    printf("Mistakes");
    char choice;
    do
    {
        system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
        printf("\n==================================================================================================\n");
        printf("************************************** Information of seats in the concert hall ************************************\n");
        printf("--------------------------------------------------------------------------------------------------\n\n\n");
        seat_node_t *seatdata;
        int i,j;
        printf("               ");
        for(j = 1; j <= studioRec.colsCount; j++ )
            printf("%2d Row ",j);
        printf("\n");
        for (i = 1; i <= studioRec.rowsCount; i++)
        {
            j=1;
            printf("  \t%2d Row: ", i);
            List_ForEach(list,seatdata)
            {
                if (seatdata->data.row == i)
                {
                    while (seatdata->data.column != j && j <= studioRec.colsCount) {
                        printf("%3c", ' ');
                        j++;
                    }
                    printf("%3c", Seat_UI_Status2Char(seatdata->data.status));
                    j++;
                }
            }
            printf("\n");
        }
        printf("---------------------------------------------------------------------------------------------------\n");
        printf(
            "      [A]    Add new seat   |    [U]    Change seats    |    [D]    Delete seat    |    [R]    Back to the top");
        printf(
            "\n==================================================================================================\n");

        printf("Please enter the action you want to select:");
        fflush(stdin);
        scanf("%c", &choice);
        fflush(stdin);
        switch (choice) {
            case 'a':
            case 'A':
                {
                    changedCount=Seat_UI_Add(list, roomID, studioRec.rowsCount, studioRec.colsCount);
                    if(changedCount!=0)
                    {
                        seatCount += changedCount;
                        studioRec.seatsCount = seatCount;
                        Studio_Srv_Modify(&studioRec);
                    }
                }
                break;
            case 'u':
            case 'U':
                 {
                    changedCount=Seat_UI_Modify(list, studioRec.rowsCount, studioRec.colsCount);
                    if(changedCount!=0)
                    {
                        seatCount += changedCount;
                        studioRec.seatsCount = seatCount;
                        Studio_Srv_Modify(&studioRec);
                    }
                }
                break;
            case 'd':
            case 'D':
                {
                    changedCount = Seat_UI_Delete(list, studioRec.rowsCount,
					studioRec.colsCount);
                    if (changedCount > 0)
                    {
                        seatCount -= changedCount;
                        studioRec.seatsCount = seatCount;
                        Studio_Srv_Modify(&studioRec);
                    }
                }
                break;
            }

        }while (choice != 'r' && choice != 'R');
        List_Destroy(list, seat_node_t);
}

/*
识符：TTMS_SCU_Seat_UI_Add
函数功能：用于添加一个新的座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，
         第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功添加了座位的标志。
*/
int Seat_UI_Add(seat_list_t list, int roomID, int row, int column)
{  
 //输入一个座位
    seat_t seatRec;//座位的临时信息
    seat_node_t *seatdata;//链表的结点
	int newRecCount = 0;

	char choice;
	do {
	    system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
		printf("\n==================================================================================================\n");
		printf("*************************************** Add a new seat ****************************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
        do
        {
            printf("Seat line number to be added:");
            fflush(stdin);
            scanf("%d", &(seatRec.row));
            printf("Row number of seat to be added: ");
            scanf("%d", &(seatRec.column));
            printf("\n\n\n");
            printf("==================================================================================================\n");
        }while(seatRec.row>row||seatRec.column>column);

        seatdata = Seat_Srv_FindByRowCol(list,seatRec.row,seatRec.column);
		if (seatdata != NULL)
        {
			printf("The seat already exists\n");
            continue;
		}
		seatRec.roomID = roomID;
		seatRec.status = SEAT_GOOD;

		if(Seat_Srv_Add(&seatRec))
        {
            newRecCount++;
            printf("New seat added successfully\n");
            seatdata = (seat_node_t*) malloc(sizeof(seat_node_t));
			seatdata->data = seatRec;
			Seat_Srv_AddToSoftedList(list,seatdata);
        }
        else
        {
             printf("Failed to add new seat!\n");
        }
		printf("---------------------------------------------------------------------------------------------------\n");
		printf("[A]Continue to add , [R] return:");
		fflush(stdin);
		scanf("%c", &choice);
	}while ('a' == choice || 'A' == choice);

	return newRecCount;
}


/*
标识符：TTMS_SCU_Seat_UI_Mod 
函数功能：用于修改一个座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功修改了座位的标志。
*/
int Seat_UI_Modify(seat_list_t list, int row, int column)
{
    seat_t seatrec;
    seat_node_t *seatnode;
	int newRecCount = 0;
	char choice;

	do {
        system("cls");
        printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
		printf("\n==================================================================================================\n");
		printf("******************************************  Change seats ******************************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
        do
		{
            printf("Seat line number to be modified:");
            fflush(stdin);
            scanf("%d", &(seatrec.row));
            printf("Row no. of seats to be modified:");
            scanf("%d", &(seatrec.column));
            printf("\n\n\n");
            printf("==================================================================================================\n");
        }while(seatrec.row>row||seatrec.column>column);

        seatnode = Seat_Srv_FindByRowCol(list,seatrec.row,seatrec.column);
		if (NULL == seatnode)
        {
			printf("该座位不存在\n");
            continue;
		}

		seatrec.roomID = seatnode->data.roomID;
		seatrec.id = seatnode->data.id;
		printf("current state[%c]\nStatus to modify to [X]Damaged seat [#]Good seats [|]aisle : ",Seat_UI_Status2Char(seatnode->data.status));
		getchar();
		seatnode->data.status = seatrec.status = Seat_UI_Char2Status(getchar());
		if(Seat_Srv_Modify(&seatrec))
        {
            if(seatrec.status == SEAT_GOOD)
                newRecCount++;
            else
                newRecCount--;
            printf("Seat modified successfully\n");
        }
        else
        {
             printf("Seat modification failed!\n");
        }
        printf("\n\n\n");
		printf("--------------------------------------------------------------------------------------------------\n");
		printf("A Continue to modify, R return:");
		fflush(stdin);
		scanf("%c", &choice);
	}while ('a' == choice || 'A' == choice);
	return newRecCount;
}

/*
标识符：TTMS_SCU_Seat_UI_Del
函数功能：用于删除一个座位的数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功删除了座位的标志。
*/
int Seat_UI_Delete(seat_list_t list, int row, int column)
{
	int delSeatCount = 0;
	int newrow, newcolumn;
	seat_node_t *seatnode;
	char choice;
	do {
		printf("\n==================================================================================================\n");
		printf("******************************************  Delete seat ******************************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
		do
		{
			fflush(stdin);
			printf("Seat line number to be deleted:");
			scanf("%d", &(newrow));
			printf("Row number of seat to be deleted:");
			scanf("%d", &(newcolumn));
			fflush(stdin);
		} while (newrow > row || newcolumn > column);
        seatnode = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
        if(NULL == seatnode)
        {
            printf("The seat does not exist! Please enter the existing seats!\n");
            continue;
        }
		if (Seat_Srv_DeleteByID(seatnode->data.id)) {
				printf("Seat deleted successfully\n");
				delSeatCount++;
				List_FreeNode(seatnode);	//释放结点座位结点p

		}
        printf("\n\n\n");
		printf("--------------------------------------------------------------------------------------------------\n");
		printf("[A]Continue to delete, [R]return");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
	} while ('a' == choice || 'A' == choice);
	return delSeatCount;
}

