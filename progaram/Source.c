#include <stdio.h>   // printf(), scanf()
#include <stdlib.h>   // rand()
#include <time.h>   // time()
#include <conio.h>   // _getch()
#include <windows.h>// wincon.h


#define true 1
#define false 0
#define bool int

#define BOARD_WIDTH 10   // 게임 가로 영역(열) >=10 :-
#define BOARD_HEIGHT 20   // 게임 세로 영역(행) >=20 :|

#define BOARD_X 4   // 보드 열 x좌표
#define BOARD_Y 2   // 보드 행 y좌표

#define DELAY 100   // 지연

// 키보드 방향키로 움직이고 스페이스로 떨어트림
enum ControlKeys
{
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    SPACE = 32
};

static int score = 0;   // 게임 점수
static int level = 1;   // 게임 레벨
static int speed = 180;
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };

// 테르리스 블록 모양
int blocks[28][4][4] =
{
    // ####
    {
       { 0, 1, 0, 0},
       { 0, 1, 0, 0},
       { 0, 1, 0, 0},
       { 0, 1, 0, 0}

    },
    {
       { 0, 0, 0, 0},
       { 0, 0, 0, 0},
       { 1, 1, 1, 1},
       { 0, 0, 0, 0}
    },
    {
       { 0, 1, 0, 0},
       { 0, 1, 0, 0},
       { 0, 1, 0, 0},
       { 0, 1, 0, 0}
    },
    {
       { 0, 0, 0, 0},
       { 0, 0, 0, 0},
       { 1, 1, 1, 1},
       { 0, 0, 0, 0}
    },

    // ##
    // ##
    {
       { 1, 1, 0, 0},
       { 1, 1, 0, 0},
       { 0, 0, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 1, 1, 0, 0},
       { 1, 1, 0, 0},
       { 0, 0, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 1, 1, 0, 0},
       { 1, 1, 0, 0},
       { 0, 0, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 1, 1, 0, 0},
       { 1, 1, 0, 0},
       { 0, 0, 0, 0},
       { 0, 0, 0, 0}
    },

    //  #
    // ###
    {
       { 0, 1, 0, 0},
       { 1, 1, 1, 0},
       { 0, 0, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 0, 0, 0, 0},
       { 0, 1, 0, 0},
       { 1, 1, 0, 0},
       { 0, 1, 0, 0}
    },
    {
       { 0, 0, 0, 0},
       { 0, 0, 0, 0},
       { 1, 1, 1, 0},
       { 0, 1, 0, 0}
    },
    {
       { 0, 0, 0, 0},
       { 0, 1, 0, 0},
       { 0, 1, 1, 0},
       { 0, 1, 0, 0}
    },

    //   #
    // ###
    {
       { 0, 0, 0, 0},
       { 0, 0, 1, 0},
       { 1, 1, 1, 0},
       { 0, 0, 0, 0}
    },
    {
       { 0, 1, 1, 0},
       { 0, 0, 1, 0},
       { 0, 0, 1, 0},
       { 0, 0, 0, 0}
    },
    {
       { 1, 1, 1, 0},
       { 1, 0, 0, 0},
       { 0, 0, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 1, 0, 0, 0},
       { 1, 0, 0, 0},
       { 1, 1, 0, 0},
       { 0, 0, 0, 0}
    },

    // #
    // ###
    {
       { 0, 0, 0, 0},
       { 1, 0, 0, 0},
       { 1, 1, 1, 0},
       { 0, 0, 0, 0}
    },
    {
       { 0, 0, 1, 0},
       { 0, 0, 1, 0},
       { 0, 1, 1, 0},
       { 0, 0, 0, 0}
    },
    {
       { 1, 1, 1, 0},
       { 0, 0, 1, 0},
       { 0, 0, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 1, 1, 0, 0},
       { 1, 0, 0, 0},
       { 1, 0, 0, 0},
       { 0, 0, 0, 0}
    },

    //  ##
    // ##
    {
       { 0, 0, 0, 0},
       { 0, 1, 1, 0},
       { 1, 1, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 0, 1, 0, 0},
       { 0, 1, 1, 0},
       { 0, 0, 1, 0},
       { 0, 0, 0, 0}
    },
    {
       { 0, 0, 0, 0},
       { 0, 1, 1, 0},
       { 1, 1, 0, 0},
       { 0, 0, 0, 0}
    },
    {
       { 0, 1, 0, 0},
       { 0, 1, 1, 0},
       { 0, 0, 1, 0},
       { 0, 0, 0, 0}
    },

    // ##
    //  ##
 {
    { 0, 0, 0, 0},
    { 1, 1, 0, 0},
    { 0, 1, 1, 0},
    { 0, 0, 0, 0}
 },
 {
    { 0, 0, 1, 0},
    { 0, 1, 1, 0},
    { 0, 1, 0, 0},
    { 0, 0, 0, 0}
 },
 {
    { 0, 0, 0, 0},
    { 1, 1, 0, 0},
    { 0, 1, 1, 0},
    { 0, 0, 0, 0}
 },
 {
    { 0, 0, 1, 0},
    { 0, 1, 1, 0},
    { 0, 1, 0, 0},
    { 0, 0, 0, 0}
 },
}; // end block[][][]


// [1] 커서 숨기기 : ture(보이기), false(숨기기)
void CursorVisible(bool blnCursorVisible) // 커서 보이기,숨기기
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = blnCursorVisible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// [2]커서 위치 설정
void SetCursorPosition(int cursorLeft, int cursorTop)
{
    int posX = cursorLeft;
    int posY = cursorTop;

    COORD pos = { posX, posY };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// [3]커서 위치 가져오기
COORD GetCursorPosition(void)
{
    COORD cursor;
    CONSOLE_SCREEN_BUFFER_INFO cursorInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursor.X = cursorInfo.dwCursorPosition.X;
    cursor.Y = cursorInfo.dwCursorPosition.Y;
    return cursor;
}

// [4] 시작 화면, 콘솔 초기화
void ConsoleInit()
{
    // 콘솔 초기화 시작화면
    printf("테트리스\n\n");
    printf(""
        "====================      \n"
        "조작법:                  \n"
        "→     오른쪽 이동         \n"
        "←     왼  쪽 이동         \n"
        "↓     아래쪽 이동         \n"
        "↑     블  록 회전         \n"
        "space  블록 드랍            \n"
        "====================      \n");
    _getch();
    system("cls");
    CursorVisible(false);      // 커서 숨기기
    SetCursorPosition(0, 0);   // 보드 시작위치
}

// [5] 게임판 그리기
void DrawField(void)
{
    int x, y;

    // 중앙 라인
    for (x = 1; x <= BOARD_WIDTH + 1; x++)
    {
        board[BOARD_HEIGHT][x] = 1;
        SetCursorPosition((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT); // 콘솔 좌표
        printf("━━");
    }

    // 왼쪽 라인
    for (y = 0; y < BOARD_HEIGHT + 1; y++)
    {
        board[y][0] = 1;
        SetCursorPosition(BOARD_X, BOARD_Y + y);
        if (y == BOARD_HEIGHT)
            printf("┗");
        else
            printf("┃");
    }

    // 오른쪽 라인
    for (y = 0; y < BOARD_HEIGHT + 1; y++)
    {
        board[y][BOARD_WIDTH + 1] = 1;
        SetCursorPosition(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
        if (y == BOARD_HEIGHT)
            printf("┛");
        else
            printf("┃");
    }

    // 모서리 값 변경
    board[20][0] = 1;
    board[20][11] = 1;

    puts(" ");
}

// [6] 점수판 출력
void ShowPoint(void)
{
    SetCursorPosition(40, 3);
    printf("테트리스");
    SetCursorPosition(40, 5);
    printf("레벨: %d\n", level);
    SetCursorPosition(40, 7);
    printf("점수: %d\n", score);
}

// [7] 블럭 위치
// 들어간다 ture, 못들어간다 false

bool CanPositionedAt(int rotation, int move1, int move2)
{
    int x, y;
    int arrX, arrY; // 좌표 저장
    COORD pos = GetCursorPosition();

    arrX = pos.X + move1;
    arrY = pos.Y + move2;

    arrX = (arrX / 2) - 2;
    arrY = arrY - BOARD_Y;

    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            if ((blocks[rotation][y][x] == 1) && board[arrY + y][arrX + x] == 1)
                return false; // 보드와 벽돌 겹침
        }
    }
    return true; // 겹치지 않음
}

// [8] 현재 위치에 블록 출력
void WriteBlock(int rotation)
{
    int i, j;
    COORD cursor = GetCursorPosition();

    if (CanPositionedAt(rotation, 0, 0) == true)
    {
        for (i = 0; i < 4; i++)      // 행 반복
        {
            for (j = 0; j < 4; j++)   // 열 반복
            {
                SetCursorPosition(cursor.X + (j * 2), cursor.Y + i);
                if (blocks[rotation][i][j] == 1)
                {
                    printf("■");
                }
            }
        }
        SetCursorPosition(cursor.X, cursor.Y);
    }
}


// [9] 블록 보드판
void BoardInit(int n, int move1, int move2)
{
    COORD pos = GetCursorPosition();

    int arrX = pos.X + move1;   // 콘솔 열 좌표
    int arrY = pos.Y + move2;   // 콘솔 행 좌표
    int x, y;

    arrX = arrX / 2 - 2;
    arrY = arrY - 2;

    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            if (blocks[n][y][x] == 1)
            {
                board[arrY + y][arrX + x] = 1;
            }
        }
    }
}

//[10] 배열,블록 옮기기
void Stepper(int column)
{
    int y, x;

    for (y = column; y >= 0; y--)
    {
        for (x = 1; x <= 10; x++)
        {
            board[y][x] = board[y - 1][x];
        }
    }
    for (x = 1; x <= 10; x++)
        board[0][x] = 0;

    for (y = 1; y <= 19; y++)
    {
        for (x = 1; x <= 10; x++)
        {
            SetCursorPosition((BOARD_X)+x * 2 + 1, y + BOARD_Y);
            if (board[y][x] == 1)
                printf("■");
        }
    }
}

// [11] level 스코어 계산
void CountScore(void)
{
    score += 10;
    if (score % 30 == 0)
    {
        level += 1;
        speed -= 30;   // 레빌 1증가할때 스피드 30밀리초 빨라짐
    }
    ShowPoint();
}

// [12] 블록 한줄 사라짐
void RemoveLine(void)
{
    int x, y;

    // 아래에서 위로 확인
    for (y = 19; y >= 1; y--)
    {
        int lineCleared = 1; // 이 줄이 꽉 찼는지 확인

        // 해당 줄이 꽉 차 있는지 확인
        for (x = 1; x < 11; x++)
        {
            if (board[y][x] == 0) // 비어있는 부분이 있으면
            {
                lineCleared = 0; // 꽉 차지 않음
                break; // 이 줄을 더 이상 확인할 필요 없음
            }
        }

        // 줄이 꽉 차면 처리
        if (lineCleared)
        {
            // 해당 줄을 지운 후, 위의 블록을 아래로 이동
            for (int row = y; row > 1; row--) // 줄을 위에서 아래로 이동
            {
                for (x = 1; x < 11; x++)
                {
                    board[row][x] = board[row - 1][x]; // 위의 블록을 아래로 이동
                }
            }

            // 가장 위 줄은 비워줌
            for (x = 1; x < 11; x++)
            {
                board[1][x] = 0; // 최상단 줄 비우기
            }

            // 시각적으로 업데이트
            for (x = 1; x < 11; x++)
            {
                SetCursorPosition((x + 2) * 2, y + 2);
                printf("  "); // 해당 줄 지우기
            }

            CountScore(); // 점수 계산
            // 블록을 제거한 후, 한 줄 아래로 이동한 경우 추가 검사 필요
            y++; // 한 줄 삭제했으므로 다시 위에서 확인
        }
    }
}


// [13] 현재 블록 클리어
void ClearBlock(int rotation, int move1, int move2)
{
    int x, y;

    COORD cursor = GetCursorPosition();

    if (CanPositionedAt(rotation, move1, move2) == true)
    {
        for (y = 0; y < 4; y++)
        {
            for (x = 0; x < 4; x++)
            {
                SetCursorPosition(cursor.X + (x * 2), cursor.Y + y);
                if (blocks[rotation][y][x] == 1)
                    printf("  ");
            }
        }
        SetCursorPosition(cursor.X + move1, cursor.Y + move2);
    }
}

// [14] 게임 시작
void StartGame(void)
{
    int n;
    int kb;
    int c = 2;

    srand((unsigned)time(0));   // rnad() 함수 랜덤값

    while (1)
    {
        // 블록 생성 좌표 (13,2)
        SetCursorPosition(13, 2);

        n = rand() % 7;

        n = n * 4;

        if (level == 10) // 레벨 10되면 게임 승리
        {
            SetCursorPosition(40, 15);
            printf("게임 클리어");
            getchar();
            exit(1);
        }

        if (CanPositionedAt(n, 0, 0) == false)
            break; // 게임 끝

        while (1)
        {
            int ww = 0;
            int k = 0;

            while (!_kbhit())
            {
                WriteBlock(n);
                Sleep(DELAY + speed);
                if (CanPositionedAt(n, 0, 1) == false)
                {
                    ww = 1;
                    BoardInit(n, 0, 0); //보드 벽돌 배열 1추가
                    RemoveLine();
                    break;
                }
                ClearBlock(n, 0, 1);
            }
            if (ww == 1)
                break;

            kb = _getch();

            // 방향키
            switch (kb)
            {
            case LEFT:
                ClearBlock(n, -2, 0);
                WriteBlock(n);
                break;
            case RIGHT:
                ClearBlock(n, 2, 0);
                WriteBlock(n);
                break;
            case UP:
                k = n / 4;
                k *= 4;

                if ((n + 1) <= (k + 3))
                {
                    k = n + 1;
                }

                if (CanPositionedAt(k, 0, 0) == true)
                {
                    ClearBlock(n, 0, 0);
                    n = k;
                    WriteBlock(n);
                    break;
                }
                break;
            case DOWN:
                ClearBlock(n, 0, 2);
                break;
            case SPACE: // 아래로 떨어지는 로직
                while (1)
                {
                    ClearBlock(n, 0, 1);
                    if (CanPositionedAt(n, 0, 1) == false)
                    {
                        WriteBlock(n);
                        BoardInit(n, 0, 0);
                        break;
                    }
                }
            default: break;
            }
        }
    }
}

//[15] 게임 종료 화면
void EndGame()
{
    SetCursorPosition(40, 15);
    printf("게임 종료");
    getchar();
    system("cls");
}
int main()
{
    ConsoleInit();   // 시작 화면

    DrawField();   // 게임 영역

    ShowPoint();   // 점수판

    StartGame();   // 게임 시작

    EndGame();      // 게임 종료

    return 0;
}
