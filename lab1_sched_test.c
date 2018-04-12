/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32142863  
*	    Student name : 이희진
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
*
*/



#include "/home/heejinlee/Scheduling-Algorithm/include/lab1_sched_types.h"

void FCFS();
void SJF();
void RR();
void MLFQ();
void Lottery();
int int_pow(int base, int exp);

int main(int argc, char *argv[]){

    int choice = 0;
    
    while (1) {
        printf("------------------- NOTICE ------------------\n");
        printf("이 프로그램은 예제 데이터 셋을 사용합니다.\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. RR\n");
        printf("4. MLFQ\n");
        printf("5. Lottery\n");
        printf("6. Exit\n");
        printf (">>>");
        scanf("%1d",&choice);

        while(1) {
            if (choice < 7) break;
            else {
                    printf("Wrong Input!!!!!!!!\n\n\n");
                    printf("1. FCFS\n");
                    printf("2. SJF\n");
                    printf("3. RR\n");
                    printf("4. MLFQ\n");
                    printf("5. Lottery\n");
                    printf("6. Exit\n");
                    printf (">>>");
                    scanf("%1d",&choice);
            }
        }
        switch(choice) {
            case 1:
                FCFS();
                break;
            case 2:
                SJF();
                break;
            case 3:
                RR();
                break;
            case 4:
                MLFQ();
                break;
            case 5:
                Lottery();
                break;
            case 6:
                return 0;
        }
    }
}