#include "Play_UI.h"
#include "StaSales_UI.h"
#include "Ticket_UI.h"
#include "Schedule_UI.h"
#include "../Service/Account.h"

void Queries_Menu(void) {
    system("cls");
    printf("user: %s | id: %d \n", gl_CurUser.username, gl_CurUser.id);
    char choice;
    printf("=======================================================\n");
    printf("[P]Query Play schedule                [S]Query stasales\n");
    printf("[R]eturn                                               \n");
    printf("=======================================================\n");

    scanf("%c", &choice);
    getchar();
    if(choice == 'P' || choice == 'p') {
        Schedule_UI_Query();
    }
    if(choice == 's' || choice == 'S') {
        StaSales_UI_MgtEntry();
    }
    if(choice != 'r' && choice != 'R')  {
        Queries_Menu();
    }

}
