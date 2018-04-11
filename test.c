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

#define M 6 //데이터개수

void FCFS();
void SJF();
void RR();
void MLFQ();
void Lottery();

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

void FCFS()
{
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    int i,j,k,l;
    int loop = 0;
    int ready = 0;
    int output[M][100] = {0};

    for (i = 1; i < M; i++) {
        loop += arr[i][1];
        //printf("%d %d\n", arr[i][0], arr[i][1]);
    }

    //printf("%d",loop);

    // 총 걸리는 시간 계산
    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 1; j < M; j++) {
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

    printf("    ");
    for (l = 0; l < loop; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < loop; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}

void SJF()
{
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    int output[M][100] = {0};

    for (i = 1; i < M; i++) {
        loop += arr[i][1];
    }

    

    for (i = 0; i < loop; i++) {
        ready = 0;
        for (j = 1; j < M; j++) {
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


    printf("    ");
    for (l = 0; l < loop; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < loop; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}

void RR()
{
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    int i,j,l,k;
    int loop = 0; // 전체 시간
    int ready = 0; //다음에 스케쥴링할 데이터
    int output[M][100] = {0}; //아웃풋 데이터 저장
    int q[M] = {0}; // 배고픔 측정용
    int scpr[M] = {0}; // 프로세스가 타임퀀텀을 다 사용했는지 체크
    int timequantom = 4; // 타임퀀텀

    for (i = 1; i < M; i++) {
        loop += arr[i][1];
    }

    for (i = 0; i < loop; i++) {

        if (scpr[ready] % timequantom == 0 || arr[ready][1] < 1) {
            scpr[ready] = 0;
            q[ready] = 0; // 스케쥴링이 되어 배고픔이 사라짐
            for (k = 1; k < M; k++) {
                if (i >= arr[k][0] && k != ready) // 현재 진행 시간에 프로세스가 도착했는지 판단하고 k 값이 직전에 스케쥴링되었는지 확인
                    q[k]++; // 스케쥴링이 직전에 되지 않았다면 배고픔을 증가시킴
            }
        }

        ready = 0; // 실행할 프로세스를 고르기 전에 초기화

        for (j = 1; j < M; j++) {
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
            scpr[ready]++;
        }
    }

    printf("    ");
    for (l = 0; l < loop; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < loop; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}

void MLFQ()
{
    //int arr[8][2] = {{0,0},{0,7},{2,6},{4,4},{6,5},{8,2},{8,6},{9,1}}; // M을 8로 만들고 실행할 것
    int arr[6][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    int i,j,l,k;
    int loop = 0;  // 전체 시간
    int ready = 0; //다음에 스케쥴링할 데이터
    int q[M] = {0}; // 배고픔을 저장
    int pr[M] = {0}; // 처리된 회수를 저장
    int output[M][100] = {0}; //아웃풋 데이터 저장
    int timequantom = 2; // 타임퀀텀
    int scpr[M] = {0}; // 프로세스가 타임퀀텀을 다 사용했는지 체크

    for (i = 1; i < M; i++) {
        loop += arr[i][1];
    }

    for (i = 0; i < loop; i++) {
        
        if (scpr[ready] % timequantom == 0 || arr[ready][1] < 1) {
            scpr[ready] = 0;
            q[ready] = 0; // 스케쥴링이 되어 배고픔이 사라짐
            for (k = 1; k < M; k++) {
                if (i >= arr[k][0] && k != ready) // 현재 진행 시간에 프로세스가 도착했는지 판단하고 k 값이 직전에 스케쥴링되었는지 확인
                    q[k]++; // 스케쥴링이 직전에 되지 않았다면 배고픔을 증가시킴
            }
        }
        
        ready = 0; // 실행할 프로세스를 고르기 전에 초기화

        for (j = 1; j < M; j++) {
            if (i == arr[j][0] && arr[j][1] >= 1) { q[j] = 9999; if (ready == 0) ready = j;} // 새로 들어온 프로세스는 무조건 우선순위를 가져서 먼저 처리됨
            if (i >= arr[j][0] && arr[j][1] >= 1) { // 현재 진행 시간에 프로세스가 도착했는지 판단하고 스케쥴링 할 프로세스의 처리시간이 남았는지 확인
                if (ready == 0) { // 실행할 프로세스를 아직 고르지 못했다면
                    ready = j; // 프로세스를 고름
                }
                else if (pr[ready] > pr[j] && q[j] != 0) { // 실행될 프로세스가 새 로 발견한 프로세스보다 더 낮은 우선순위의 큐에 있는지 확인하고 배고픔을 체크 (배고픔을 체크 안할경우 더 낮은 상태의 큐가 무조건 먼저 돌아감) 
                    ready = j;
                }
            }
        }

        if (ready > 0) { // 레디 큐에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
            scpr[ready]++; // 프로세스가 타임퀀텀 사용
            if (scpr[ready] % timequantom == 0)
                pr[ready]++; // 프로세스의 우선순위를 낮춤
            if (q[ready] == 9999)
                q[ready] = 0;
        }
    }

    printf("    ");
    for (l = 0; l < loop; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < loop; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}

void Lottery()
{
    int arr[M][2] = {{0,0},{0,3},{2,6},{4,4},{6,5},{8,2}};
    //int arr[M][2] = {{0,0},{0,3},{0,6},{0,4},{0,5},{0,2}};
    int i,j,k,l;
    int loop = 0; 
    int ready = 0;
    int take_tic[M] = {0,10,40,30,20,50}; // 각 프로세스가 가진 스케쥴링 우선도 티켓 case 1 : 프로세스가 가진 티켓이 사용자가 가진 티켓 미만인 경우
    //int take_tic[M] = {0,500,600,200,10,400}; // 각 프로세스가 가진 스케쥴링 우선도 티켓 case 2 : 프로세스가 가진 티켓이 사용자가 가진 티켓 미만인 경우
    int sumtake = 0;
    int scpr[M] = {0};
    int gacha = -1;
    int output[M][100] = {0};

    srand((unsigned int)time(NULL));

    for (i = 1; i < M; i++) {
        sumtake += take_tic[i];
    }
    //printf("%d\n",sumtake);

    for (i = 1; i < M; i++) {
        scpr[i] = scpr[i-1] + ((float)take_tic[i] / sumtake + 0.005) * 100;
        //printf("%d ",scpr[i]);
    }
    scpr[5] += 1;
    //printf("\n");
    //printf(" %d",scpr[5]);

    for (i = 1; i < M; i++) {
        loop += arr[i][1];
    }// 총 걸리는 시간 계산

    for (i = 0; i < loop; i++) {
        for (j = 1; j < M; j++) {
            if (gacha == -1) {
                gacha = rand() % scpr[5]; // 랜덤 티켓을 생성함
                //printf("%d = 새로뽑았어!\n",gacha);
                // 프로세스 비율 :   7 27 20 13 33
                //                0 7 34 54 67 100(+1)
            }
            if (gacha >= scpr[j-1] && gacha < scpr[j]) { // 티켓이 어느 값 사이에 위치하는지 확인함
                //printf("%d 는 %d와 %d 사이에 존재\n",gacha, scpr[j-1], scpr[j]);
                if (i >= arr[j][0] && arr[j][1] >= 1) // 정한 값이 프로세스가 도착하고 실행할 시간이 남아있다면
                {
                    //printf("그리고 실행가능함\n");
                    ready = j; //다음 실행시킬 프로세스로 정함
                    break;
                }
                if (i < arr[j][0] || arr[j][1] < 1) { // 아무때나 값 교체하는게 아니라 다 돌았는데도 티켓 사이값에 해당하는 프로세스를 못 찾았을 경우엔
                    if (ready == 0) {
                        //printf("근데 실행가능하지는 않아 남은실행 %d\n", arr[j][1]);
                        //printf("그러니까 초기화시켜\n");
                        gacha = -1; // 다시 뽑음
                        i--; //뽑았으니 다시 비교에 들어감
                        break;
                    }
                }
            }
        }

        if (ready > 0) { // 레디에 처리할 프로세스가 존재한다면
            arr[ready][1]--; // 프로세스의 실행시간을 1 줄이고
            output[ready][i] = 1; // 아웃풋 데이터에 입력
            ready = 0;
            //printf("그래서 %d 는 정상처리\n",gacha);
            gacha = -1;
        }
    }

    printf("\n");

    printf("    ");
    for (l = 0; l < loop; l++)  {
            printf("%2d   ",l);
        }
        printf("\n    ");
        
        for (l = 0; l < loop; l++)  {
            printf("-----");
        }
        printf("\n");

    for (i = 1; i < M; i++) {
        printf("%c ",i+64);
        for (l = 0; l < loop; l++)  {
            if (output[i][l] == 1) {
                printf("  ■  ");
            }
            else
                printf("  □  ");
        }
        printf("\n");
    }
}
