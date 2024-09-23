#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // 키 입력
#include <windows.h> // Sleep() 함수 사용을 위함

// 색깔 0== 검정 ,1== 파랑 , 2== 초록 ,3== 옥색 , 4== 빨강, 6==노랑 , 7== 흰색

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20 
// 보드크기 가로,세로

char board[BOARD_HEIGHT][BOARD_WIDTH+1]; // 보드 배열

// 보드 초기화 시키는 방법
void initBoard()
{
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            board[y][x] = ' '; // 블럭이 없는 빈 공간
        }
        board[y][BOARD_WIDTH] = '\0'; // 문자열 종료
    }
}

// 보드 그리는 방법
void drawBoard()
{
    system("cls"); // 화면 지우는 코드
    
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        printf("%s\n", board[y]); // 현재 보드 상태 출력
    }
}

void placeBlock(int x, int y)
{
    if (y >= 0 && y < BOARD_HEIGHT && x >= 0 && x < BOARD_WIDTH)
    {
        board[y][x] = currentBlock;
    }
}

int main()
{

    return 0;
}