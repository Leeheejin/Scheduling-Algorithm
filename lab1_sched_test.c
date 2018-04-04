/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
*
*/



#include "../lab1_sched/include/lab1_sched_types.h"

/*
 * you need to implement scheduler simlator test code.
 *
 */

void FCFS(int arr[][2]);
void SJF(int arr[][2]);
void RR(int arr[][2]);
void MLFQ(int arr[][2]);
void Lottery(int arr[][2]);

int main(int argc, char *argv[]){

    int arr[5][2] = {{0,3},{2,6},{4,4},{6,5},{8,2}};

    int choice = 0;
    printf("1. FCFS");
    printf("2. SJF");
    printf("3. RR");
    printf("4. MLFQ");
    printf("5. Lottery");

    scanf("%1d",&choice);

    switch(choice) {
        case 1:
            FCFS(arr);
        case 2:
            SJF(arr);
        case 3:
            RR(arr);
        case 4:
            MLFQ(arr);
        case 5:
            Lottery(arr);
    }
   
}
