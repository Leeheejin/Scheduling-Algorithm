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
            if (i >= arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) { // 레디 큐에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디 큐에 데이터 삽입
                    break;
                }
            }
        }

        if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
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
            if (i >=arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) { // 레디 큐에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디 큐에 데이터 삽입
                }
                else if (arr[j][1] < arr[ready][1]) {
                    ready = j;
                }
            }
        }

        if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
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
            if (i >= arr[k][0] && k != ready)
                q[k]++;
            else if (i >= arr[k][0] && k == ready)
                q[k] = 0;
        }

        ready = 0;

        for (j = 1; j < 6; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) {
                if (ready == 0) {
                    ready = j;
                }
                else if (q[ready] < q[j]) {
                    ready = j;
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