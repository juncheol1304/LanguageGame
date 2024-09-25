#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BOARD_WIDTH 17
#define BOARD_HEIGHT 20

// 블록 모양 정의
char blocks[7][4][4] = {
    // I 블록
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', '#'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // O 블록
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // T 블록
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // J 블록
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    // L 블록
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {'#', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // S 블록
    {
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // Z 블록
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    }
};

int currentX = 4; // 블록의 X 좌표
int currentY = 0; // 블록의 Y 좌표
int currentBlock = 0; // 현재 블록 인덱스
char board[BOARD_HEIGHT][BOARD_WIDTH + 1]; // 보드 배열
int score = 0; // 점수

// 보드 초기화
void initBoard() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[y][x] = ' '; // 빈 공간
        }
        board[y][BOARD_WIDTH] = '\0'; // 문자열 종료
    }
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        board[y][0] = '|'; // 왼쪽 벽
        board[y][BOARD_WIDTH - 1] = '|'; // 오른쪽 벽
    }
    for (int x = 0; x < BOARD_WIDTH; x++) {
        board[0][x] = '-'; // 상단 벽
        board[BOARD_HEIGHT - 1][x] = '-'; // 바닥
    }
}

// 랜덤 블록 생성
void generateNewBlock() {
    currentBlock = rand() % 7; // 랜덤 블록 선택
    currentX = 4; // 초기 X 좌표
    currentY = 0; // 초기 Y 좌표
}

// 블록 회전 함수
void rotateBlock() {
    if (currentBlock == 1) return; // O 블록은 회전하지 않음

    char temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = blocks[currentBlock][i][j]; // 회전된 형태 저장
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            blocks[currentBlock][i][j] = temp[i][j];
        }
    }
}

// 보드 그리기
void drawBoard() {
    system("cls"); // 화면 지우기
    printf("Score: %d\n", score); // 점수 출력
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        printf("%s\n", board[y]); // 현재 보드 상태 출력
    }
}

// 블록 배치
void placeBlock(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[currentBlock][i][j] == '#') {
                board[y + i][x + j] = '#'; // 블록 문자 배치
            }
        }
    }
}

// 블록 비우기
void clearBlock() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[currentBlock][i][j] == '#') {
                board[currentY + i][currentX + j] = ' '; // 이전 위치 비우기
            }
        }
    }
}

// 바닥 및 다른 블록 체크
int isAtBottom() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[currentBlock][i][j] == '#') {
                if (currentY + i + 1 >= BOARD_HEIGHT - 1 ||
                    (currentY + i + 1 < BOARD_HEIGHT &&
                        currentX + j >= 1 &&
                        currentX + j < BOARD_WIDTH - 1 &&
                        board[currentY + i + 1][currentX + j] != ' ')) {
                    return 1; // 다른 블록에 닿음
                }
            }
        }
    }
    return 0; // 바닥에 닿지 않음
}

// 줄 삭제 함수
void clearLines() {
    for (int y = BOARD_HEIGHT - 2; y > 0; y--) {
        int complete = 1;
        for (int x = 1; x < BOARD_WIDTH - 1; x++) {
            if (board[y][x] == ' ') {
                complete = 0; // 줄이 완전하지 않으면
                break;
            }
        }
        if (complete) {
            // 줄 삭제 및 점수 증가
            score += 100;
            for (int i = y; i > 1; i--) {
                for (int x = 1; x < BOARD_WIDTH - 1; x++) {
                    board[i][x] = board[i - 1][x]; // 위 줄을 아래로 이동
                }
            }
            // 삭제된 줄의 맨 위를 비우기
            for (int x = 1; x < BOARD_WIDTH - 1; x++) {
                board[1][x] = ' ';
            }
        }
    }
}

// 블록 이동 함수
void moveBlock(int dx, int dy) {
    clearBlock(); // 이전 위치 비우기
    currentX += dx; // X 좌표 이동
    currentY += dy; // Y 좌표 이동

    // 경계 체크
    if (currentX < 1) currentX = 1; // 왼쪽 벽에 닿지 않도록
    if (currentX >= BOARD_WIDTH - 5) currentX = BOARD_WIDTH - 5; // 오른쪽 벽에 닿지 않도록

    // 아래로 이동
    if (isAtBottom()) {
        currentY--; // 블록을 바닥에 고정
        placeBlock(currentX, currentY); // 현재 블록 배치
        clearLines(); // 줄 삭제
        generateNewBlock(); // 새로운 블록 생성
    }
    else {
        placeBlock(currentX, currentY); // 새로운 위치에 블록 배치
    }
}

int main() {
    srand(time(NULL)); // 랜덤 시드 초기화
    initBoard(); // 보드 초기화
    generateNewBlock(); // 초기 블록 생성
    placeBlock(currentX, currentY); // 초기 블록 배치
    drawBoard(); // 보드 그리기

    // 게임 루프
    while (1) {
        if (_kbhit()) { // 키 입력 확인
            char ch = _getch();
            if (ch == 'q') break; // 'q'를 누르면 종료
            else if (ch == 'a') moveBlock(-1, 0); // 왼쪽 이동
            else if (ch == 'd') moveBlock(1, 0); // 오른쪽 이동
            else if (ch == 's') moveBlock(0, 1); // 아래 이동
            else if (ch == 'w') { // 블록 회전
                clearBlock(); // 이전 위치 비우기
                rotateBlock(); // 블록 회전
                placeBlock(currentX, currentY); // 새로운 위치에 블록 배치
            }
        }
        drawBoard();
        Sleep(100);
    }
    return 0;
}
