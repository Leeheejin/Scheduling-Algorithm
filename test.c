#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

void FCFS(int arr[][2]);
void SJF(int arr[][2]);
void RR(int arr[][2]);
void MLFQ(int arr[][2]);
void Lottery(int arr[][2]);

int main(int argc, char *argv[]){

     // 배열 인자전달로 값이 손상됨

    int choice = 0;
    
    while (1) {
        int arr[6][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};

        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. RR\n");
        printf("4. MLFQ\n");
        printf("5. Lottery\n");
        printf (">>>");
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
            case 6:
                break;
        }
    }
}


void FCFS(int arr[][2])
{
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    char output[6][20];


    for (i = 1; i < 6; i++) {
        loop += arr[i][1];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }
    //printf("%d",loop);

    // 총 걸리는 시간 계산
    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 1; j < 6; j++) {
            if (i >= arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 레디에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디에 데이터 삽입
                    break;
                }
            }
        }

        if (ready > 0) { // 레디에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
        }
    }fflush(stdout);

    for (i = 1; i < 6; i++) {
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf(" ■ ");
            }
            else
                printf(" □ ");
        }
        printf("\n");
    }
}


void SJF(int arr[][2])
{
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    char output[6][20];

    for (i = 1; i < 6; i++) {
        loop += arr[i][1];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }
    //printf("%d",loop);

    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 1; j < 6; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 레디에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디에 데이터 삽입
                }
                else if (arr[j][1] < arr[ready][1]) {
                    ready = j;
                }
            }
        }

        if (ready > 0) { // 레디에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
        }
    }

    for (i = 1; i < 6; i++) {
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf(" ■ ");
            }
            else
                printf(" □ ");
        }
        printf("\n");
    }
}

void RR(int arr[][2])
{
    int i,j,l,k,past;
    int loop = 0; 
    int ready = 0;
    char output[6][20];
    int q[6] = {0};

    for (i = 1; i < 6; i++) {
        loop += arr[i][1];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }
    //printf("%d",loop);

    for (i = 0; i < loop; i++) {
        
        for (k = 1; k < 6; k++) {
            if (i >= arr[k][0] && k != ready) // 현재 진행 시간에 프로세스가 도착했는지 판단하고 k 값이 직전에 스케쥴링되었는지 확인
                q[k]++; // 스케쥴링이 직전에 되지 않았다면 배고픔을 증가시킴
            else if (i >= arr[k][0] && k == ready) // 스케쥴링이 직전에 되었다면
                q[k] = 0; // 배고픔은 사라짐
        }

        ready = 0; // 실행할 프로세스를 고르기 전에 초기화

        for (j = 1; j < 6; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 실행할 프로세스를 아직 고르지 못했다면
                    ready = j; // 프로세스를 고름
                }
                else if (q[ready] < q[j]) { // 프로세스를 이미 골랐음에도 지금 스케쥴링할 다른 프로세스가 존재한다면 배고픔 정도를 비교
                    ready = j; // 더 배고프다면 스케쥴링할 프로세스를 교체
                }
            }
        }

        if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
            past = ready;
        }
    }

    for (i = 1; i < 6; i++) {
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf(" ■ ");
            }
            else
                printf(" □ ");
        }
        printf("\n");
    }
}

void MLFQ(int arr[][2])
{

}
void Lottery(int arr[][2])
{
    
}