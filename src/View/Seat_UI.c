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
		printf("\n没有该演播厅！\n已为您返回上级界面\n");
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
    printf("错误处");
    char choice;
    do
    {
        printf("\n==================================================================================================\n");
        printf("**************************************  演 出 厅 座 位 信 息  ************************************\n");
        printf("--------------------------------------------------------------------------------------------------\n\n\n");
        seat_node_t *seatdata;
        int i,j;
        printf("               ");
        for(j = 1; j <= studioRec.colsCount; j++ )
            printf("%2d ",j);
        printf("\n");
        for (i = 1; i <= studioRec.rowsCount; i++)
        {
            j=1;
            printf("  \t%2d排: ", i);
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
            "      [A]    添加新座位    |    [U]    修改座位    |    [D]    删除座位    |    [R]    返回上层");
        printf(
            "\n==================================================================================================\n");

        printf("请输入您要选择的操作:");
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
		printf("\n==================================================================================================\n");
		printf("*************************************** 添 加 新 的 座 位 ****************************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
        do
        {
            printf("待添加座位行号: ");
            fflush(stdin);
            scanf("%d", &(seatRec.row));
            printf("待添加座位列号: ");
            scanf("%d", &(seatRec.column));
            printf("\n\n\n");
            printf("==================================================================================================\n");
        }while(seatRec.row>row||seatRec.column>column);

        seatdata = Seat_Srv_FindByRowCol(list,seatRec.row,seatRec.column);
		if (seatdata != NULL)
        {
			printf("该座位已存在\n");
            continue;
		}
		seatRec.roomID = roomID;
		seatRec.status = SEAT_GOOD;

		if(Seat_Srv_Add(&seatRec))
        {
            newRecCount++;
            printf("新座位添加成功\n");
            seatdata = (seat_node_t*) malloc(sizeof(seat_node_t));
			seatdata->data = seatRec;
			Seat_Srv_AddToSoftedList(list,seatdata);
        }
        else
        {
             printf("新的座位添加失败!\n");
        }
		printf("---------------------------------------------------------------------------------------------------\n");
		printf("[A] 继续添加, [R] 返回:");
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
		printf("\n==================================================================================================\n");
		printf("******************************************  修 改 座 位 ******************************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
        do
		{
            printf("待修改座位行号:");
            fflush(stdin);
            scanf("%d", &(seatrec.row));
            printf("待修改座位列号:");
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
		printf("当前状态[%c]\n要修改为的状态 [X]损坏的座位 [#]完好的座位 [|]过道 : ",Seat_UI_Status2Char(seatnode->data.status));
		getchar();
		seatnode->data.status = seatrec.status = Seat_UI_Char2Status(getchar());
		if(Seat_Srv_Modify(&seatrec))
        {
            if(seatrec.status == SEAT_GOOD)
                newRecCount++;
            else
                newRecCount--;
            printf("座位修改成功\n");
        }
        else
        {
             printf("座位修改失败!\n");
        }
        printf("\n\n\n");
		printf("--------------------------------------------------------------------------------------------------\n");
		printf("A 继续修改, R 返回:");
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
		printf("******************************************  删 除 座 位 ******************************************\n");
		printf("--------------------------------------------------------------------------------------------------\n\n\n");
		do
		{
			fflush(stdin);
			printf("待删除座位行号:");
			scanf("%d", &(newrow));
			printf("待删除座位列号:");
			scanf("%d", &(newcolumn));
			fflush(stdin);
		} while (newrow > row || newcolumn > column);
        seatnode = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
        if(NULL == seatnode)
        {
            printf("该座位不存在！请输入存在的座位！\n");
            continue;
        }
		if (Seat_Srv_DeleteByID(seatnode->data.id)) {
				printf("座位删除成功\n");
				delSeatCount++;
				List_FreeNode(seatnode);	//释放结点座位结点p

		}
        printf("\n\n\n");
		printf("--------------------------------------------------------------------------------------------------\n");
		printf("[A]继续删除, [R]返回");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
	} while ('a' == choice || 'A' == choice);
	return delSeatCount;
}

