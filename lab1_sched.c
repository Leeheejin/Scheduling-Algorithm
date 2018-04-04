/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 
*	    Student name : 
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/



#include "../lab1_sched/include/lab1_sched_types.h"

/*
 * you need to implement FCFS, RR, SPN, SRT, HRRN, MLFQ scheduler. 
 */
void FCFS(int arr[][2])
{
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    int qn = 0;
    char output[5][20];

    for (i = 0; i < 5; i++) {
        loop += arr[i][1];
    }
    // 총 걸리는 시간 계산
    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 0; j < 5; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) { // 레디 큐에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디 큐에 데이터 삽입
                    break;
                }
            }
        }

        for (k = 0; k < 5; k++) { // 레디 큐에 들어온 프로세스 처리
            if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
                arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
                output[ready][loop] = 1; // 아웃풋 데이터에 입력
            }
        }
    }

    for (i = 0; i< 5; i++) {
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf("■");
            }
            else
                printf("□\n");
        }
        printf("\n");
    }
    

}

void SJF(int arr[][2])
{
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    int qn = 0;
    char output[5][20];

    for (i = 0; i < 5; i++) {
        loop += arr[i][1];
    }
    // 총 걸리는 시간 계산
    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 0; j < 5; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) { // 레디 큐에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디 큐에 데이터 삽입
                }
                else if (arr[j][1] > arr[ready][1]) {
                    ready = j;
                }
            }
        }

        for (k = 0; k < 5; k++) { // 레디 큐에 들어온 프로세스 처리
            if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
                arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
                output[ready][loop] = 1; // 아웃풋 데이터에 입력
            }
        }
    }

    for (i = 0; i< 5; i++) {
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf("■");
            }
            else
                printf("□\n");
        }
        printf("\n");
    }

}
void RR(int arr[][2])
{

}
void MLFQ(int arr[][2])
{

}
void Lottery(int arr[][2])
{
    
}