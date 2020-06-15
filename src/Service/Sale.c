#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Query_Persist.h"
#include "../Service/Sale.h"

//根据票的信息插入到订单的信息
int Sale_Srv_Add(const sale_t *data) {
	return Sale_Perst_Insert(data);
}

//删除订单的信息
int Sale_Srv_DeleteByID(int saleID) {
	return Sale_Perst_DeleteByID(saleID);
}

int Ticket_Srv_Modify(const ticket_t*data){
    assert(NULL!=data);
	FILE *fp=fopen(SALE_SELL,"ab");
	int rtn=0;
	if (NULL==fp)
	{
		printf("无法打开文件 %s!\n", SALE_SELL);
		return 0;
	}
	rtn=fwrite(data,sizeof(sale_t),1,fp);
	fclose(fp);
	return rtn;
}
int Ticket_Srv_Mod(const ticket_t*data){
    assert(NULL!=data);
	FILE *fp=fopen(SALE_SELL,"ab");
	int rtn=0;
	if (NULL==fp)
	{
		printf("无法打开文件 %s!\n", SALE_SELL);
		return 0;
	}
	rtn=fwrite(data,sizeof(sale_t),1,fp);
	fclose(fp);
	return rtn;
}
int Ticket_Srv_FetchBySchID(int ID,ticket_list_t list){
    assert(NULL!=list);
    int sum;
    if(list->data.id==ID){
        sum+=1;
    }
    return sum;

}
int Ticket_Srv_SelBySchID(int id, ticket_list_t list,const sale_t *data){
int count;
typedef struct list{
	int value;
	struct list *next;
}list;
FILE *fd;

fd = fopen("ticket.dat", "r");
if(NULL == fd)
{
perror("open error.\n");
fclose(fd);
return -1;
}
fclose(fd);
while((feof(fd))!=0){
    fclose(fd);
fscanf(fd,"%d",data);
count+=(int)data;
if(data->schedule_h==id){
struct node *newNode;
newNode=(struct node *)malloc(sizeof(list));  
scanf("%d",data);  
newNode=data;
}
fclose(fd);
return count;
}
return 0;
}

ticket_node_t* Ticket_Srv_FetchBySeatID(ticket_list_t list,int seat_id)
{
    assert(NULL!=list);
	ticket_node_t *p;

	if (p->data.id==seat_id)
		return p;
    else
	return NULL ;
}
