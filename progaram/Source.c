#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // 키 입력
#include <windows.h> // Sleep() 함수 사용을 위함

// 색깔 0== 검정 ,1== 파랑 , 2== 초록 ,3== 옥색 , 4== 빨강, 6==노랑 , 7== 흰색
// 보드크기 가로,세로,블록 크기
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20 
#define BLOCK_SIZE 4

char board[BOARD_HEIGHT][BOARD_WIDTH + 1]; // 보드 배열
int currentX = 4; // 블록의 X 좌표
int currentY = 0; // 블록의 Y 좌표

// 도형 구조체
typedef struct {
    char shape[BLOCK_SIZE][BLOCK_SIZE];
    int width;
    int height;
} Tetromino;

// 도형 정의
Tetromino I = { {{' ', ' ', ' ', ' '}, {'#', '#', '#', '#'}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}}, 4, 1 };
Tetromino O = { {{' ', ' ', ' ', ' '}, {' ', '#', '#', ' '}, {' ', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 2, 2 };
Tetromino T = { {{' ', ' ', ' ', ' '}, {'#', '#', '#', ' '}, {' ', '#', ' ', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino J = { {{' ', ' ', ' ', ' '}, {'#', ' ', ' ', ' '}, {'#', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino L = { {{' ', ' ', ' ', ' '}, {' ', ' ', '#', ' '}, {'#', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino S = { {{' ', ' ', ' ', ' '}, {' ', '#', '#', ' '}, {'#', '#', ' ', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino Z = { {{' ', ' ', ' ', ' '}, {'#', '#', ' ', ' '}, {' ', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };

// 보드 초기화
void initBoard() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[y][x] = ' '; // 블럭이 없는 빈 공간
        }
        board[y][BOARD_WIDTH] = '\0'; // 문자열 종료
    }
}

// 보드 그리기
void drawBoard() {
    system("cls"); // 화면 지우기
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        printf("%s\n", board[y]); // 현재 보드 상태 출력
    }
}

// 블록 배치
void placeBlock(int x, int y, char blockChar) {
    if (y >= 0 && y < BOARD_HEIGHT && x >= 0 && x < BOARD_WIDTH) {
        board[y][x] = blockChar; // 블록 문자 배치
    }
}

// 블록 비우기
void clearBlock() {
    if (currentY >= 0 && currentY < BOARD_HEIGHT && currentX >= 0 && currentX < BOARD_WIDTH) {
        board[currentY][currentX] = ' '; // 이전 위치 비우기
    }
}

// 도형 배치
void placeTetromino(int startX, int startY, Tetromino tetromino) {
    for (int y = 0; y < tetromino.height; y++) {
        for (int x = 0; x < tetromino.width; x++) {
            if (tetromino.shape[y][x] != ' ') {
                placeBlock(startX + x, startY + y, tetromino.shape[y][x]);
            }
        }
    }
}

// 줄 삭제 함수
void clearFullLines() {
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        int full = 1; // 줄이 꽉 차 있는지 확인하는 변수
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[y][x] == ' ') {
                full = 0; // 빈 공간이 있으면 false
                break;
            }
        }
        if (full) {
            // 줄 삭제
            for (int i = y; i > 0; i--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    board[i][x] = board[i - 1][x];
                }
            }
            // 맨 위 줄 비우기
            for (int x = 0; x < BOARD_WIDTH; x++) {
                board[0][x] = ' ';
            }
            y++; // 다시 검사하기 위해 y를 증가
        }
    }
}

// 블록 이동
void moveBlock(int dx, int dy) {
    clearBlock();   // 이전 위치 비우기
    currentX += dx; // X 좌표 이동
    currentY += dy; // Y 좌표 이동
    placeTetromino(currentX, currentY, T); // 새로운 위치에 블록 배치 (현재 블록을 T로 설정)
    clearFullLines(); // 줄 삭제 체크
}

int main() {
    initBoard(); // 보드 초기화
    placeTetromino(currentX, currentY, T); // 초기 블록 배치
    drawBoard(); // 보드 그리기

    // 게임 루프
    while (1) {
        if (_kbhit()) // 키 입력 확인
        {
            char ch = _getch();
            if (ch == 'q') break; // 'q' 를 누르면 종료
            else if (ch == 'a') moveBlock(-1, 0); // 왼쪽 이동
            else if (ch == 'd') moveBlock(1, 0);  // 오른쪽 이동
            else if (ch == 's') moveBlock(0, 1);  // 아래 이동
        }
        drawBoard();
        Sleep(100);
    }
    return 0;
}
