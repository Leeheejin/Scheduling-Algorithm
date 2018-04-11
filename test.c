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

    int choice = 0;
    //int arr[6][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    int arr[6][2] = {{0,0},{0,3},{0,6},{0,4},{0,5},{0,2}};
    
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

void SJF(int arr[][2])
{
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    char output[6][20];

    for (i = 1; i < 6; i++) {
        loop += arr[i][1];
    }

    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 1; j < 6; j++) {
            if (i >=arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 레디에 데이터가 들어갈 수 있는지 판단
                    ready = j; // 레디에 데이터 삽입
                }
                else if (arr[j][1] < arr[ready][1]) { // 새로 발견한 프로세스가 더 짧은 실행시간을 가지고 있다면 교체하여 실행
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
    }

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
    int i,j,l,k;
    int loop = 0;  // 전체 시간
    int ready = 0; //다음에 스케쥴링할 데이터
    char output[6][20]; //아웃풋 데이터 저장
    int q[6] = {0}; // 배고픔을 저장
    int pr[6] = {0}; // 처리된 회수를 저장

    for (i = 1; i < 6; i++) {
        loop += arr[i][1];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }
    //printf("%d",loop);

    for (i = 0; i < loop; i++) {
        
        for (k = 1; k < 6; k++) {
            if (i >= arr[k][0] && k != ready) {// 현재 진행 시간에 프로세스가 도착했는지 판단하고 k 값이 직전에 스케쥴링되었는지 확인
                // 스케쥴링이 직전에 되지 않았다면 배고픔을 증가시킴
                q[k]++;
            }
            else if (i >= arr[k][0] && k == ready) // 스케쥴링이 직전에 되었다면
                // 배고픔은 사라짐
                q[k] = 0;
        }
        
        ready = 0; // 실행할 프로세스를 고르기 전에 초기화

        for (j = 1; j < 6; j++) {
            if (i == arr[j][0] && arr[j][1] >= 1) { ready = j; break;} // 새로 들어온 프로세스는 무조건 우선순위를 가져서 먼저 처리됨
            if (i >=arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 실행할 프로세스를 아직 고르지 못했다면
                    ready = j; // 프로세스를 고름
                }
                else if (pr[ready] > pr[j] && q[j] != 0) { // 실행될 프로세스가 새로 발견한 프로세스보다 더 낮은 우선순위의 큐에 있는지 확인하고 배고픔을 체크 (배고픔을 체크 안할경우 더 낮은 상태의 큐가 무조건 먼저 돌아감) 
                    ready = j;
                }
            }
        }

        if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
            pr[ready]++; // 프로세스의 우선순위를 낮춤
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
void Lottery(int arr[][2])
{
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    char output[6][20];
    int ticket = 500; // 현재 사용자가 가진 티켓 수
    int take_tic[6] = {0,10,40,30,20,50}; // 각 프로세스가 가진 스케쥴링 우선도 티켓 case 1 : 프로세스가 가진 티켓이 사용자가 가진 티켓 미만인 경우
    int sumtake = 0;
    //int take_tic2[6] = {0,500,600,200,10,700,400}; // 각 프로세스가 가진 스케쥴링 우선도 티켓 case 1 : 프로세스가 가진 티켓이 사용자가 가진 티켓 미만인 경우
    int scpr[6] = {0};
    int gacha = 0;
    // {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}} 프로세스 목록

    srand((unsigned int)time(NULL));

    for (i = 1; i < 6; i++) {
        sumtake += take_tic[i];
    }
    //printf("%d\n",sumtake);

    for (i = 1; i < 6; i++) {
        scpr[i] = scpr[i-1] + ((float)take_tic[i] / sumtake + 0.005) * 100;
        //printf("%d ",scpr[i]);
    }
    scpr[5] += 1;
    //printf("\n");
    //printf(" %d",scpr[5]);

    for (i = 1; i < 6; i++) {
        loop += arr[i][1];
    }// 총 걸리는 시간 계산

    for (i = 0; i < loop; i++) {
        for (j = 1; j < 6; j++) {
            if (gacha == 0) {
                gacha = rand() % scpr[5];
                //printf("%d\n",gacha);
            }
            if (gacha >= scpr[j-1] && gacha < scpr[j]) {
                if (i >=arr[j][0] && arr[j][1] >= 1) {
                    ready = j;
                }
                else if (i >=arr[j][0] && arr[j][1] < 1) {
                    gacha = rand() % scpr[5];
                    j = 1;
                    ready = 0;
                }
            }
        }

        if (ready > 0) { // 레디에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
            printf("%d ",gacha);
            gacha = 0;
        }

    }
    printf("\n");
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
