#include <stdio.h>   // printf(), scanf()
#include <stdlib.h>   // rand()
#include <time.h>   // time()
#include <conio.h>   // _getch()
#include <windows.h>// wincon.h


#define true 1
#define false 0
#define bool int

#define BOARD_WIDTH 10   // ���� ���� ����(��) >=10 :-
#define BOARD_HEIGHT 20   // ���� ���� ����(��) >=20 :|

#define BOARD_X 4   // ���� �� x��ǥ
#define BOARD_Y 2   // ���� �� y��ǥ

#define DELAY 100   // ����

// Ű���� ����Ű�� �����̰� �����̽��� ����Ʈ��
enum ControlKeys
{
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    SPACE = 32
};

static int score = 0;   // ���� ����
static int level = 1;   // ���� ����
static int speed = 180;
int board[BOARD_HEIGHT + 1][BOARD_WIDTH + 2] = { 0, };

// �׸����� ��� ���
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


// [1] Ŀ�� ����� : ture(���̱�), false(�����)
void CursorVisible(bool blnCursorVisible) // Ŀ�� ���̱�,�����
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = blnCursorVisible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// [2]Ŀ�� ��ġ ����
void SetCursorPosition(int cursorLeft, int cursorTop)
{
    int posX = cursorLeft;
    int posY = cursorTop;

    COORD pos = { posX, posY };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// [3]Ŀ�� ��ġ ��������
COORD GetCursorPosition(void)
{
    COORD cursor;
    CONSOLE_SCREEN_BUFFER_INFO cursorInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursor.X = cursorInfo.dwCursorPosition.X;
    cursor.Y = cursorInfo.dwCursorPosition.Y;
    return cursor;
}

// [4] ���� ȭ��, �ܼ� �ʱ�ȭ
void ConsoleInit()
{
    // �ܼ� �ʱ�ȭ ����ȭ��
    printf("��Ʈ����\n\n");
    printf(""
        "====================      \n"
        "���۹�:                  \n"
        "��     ������ �̵�         \n"
        "��     ��  �� �̵�         \n"
        "��     �Ʒ��� �̵�         \n"
        "��     ��  �� ȸ��         \n"
        "space  ��� ���            \n"
        "====================      \n");
    _getch();
    system("cls");
    CursorVisible(false);      // Ŀ�� �����
    SetCursorPosition(0, 0);   // ���� ������ġ
}

// [5] ������ �׸���
void DrawField(void)
{
    int x, y;

    // �߾� ����
    for (x = 1; x <= BOARD_WIDTH + 1; x++)
    {
        board[BOARD_HEIGHT][x] = 1;
        SetCursorPosition((BOARD_X)+x * 2, BOARD_Y + BOARD_HEIGHT); // �ܼ� ��ǥ
        printf("����");
    }

    // ���� ����
    for (y = 0; y < BOARD_HEIGHT + 1; y++)
    {
        board[y][0] = 1;
        SetCursorPosition(BOARD_X, BOARD_Y + y);
        if (y == BOARD_HEIGHT)
            printf("��");
        else
            printf("��");
    }

    // ������ ����
    for (y = 0; y < BOARD_HEIGHT + 1; y++)
    {
        board[y][BOARD_WIDTH + 1] = 1;
        SetCursorPosition(BOARD_X + (BOARD_WIDTH + 2) * 2, BOARD_Y + y);
        if (y == BOARD_HEIGHT)
            printf("��");
        else
            printf("��");
    }

    // �𼭸� �� ����
    board[20][0] = 1;
    board[20][11] = 1;

    puts(" ");
}

// [6] ������ ���
void ShowPoint(void)
{
    SetCursorPosition(40, 3);
    printf("��Ʈ����");
    SetCursorPosition(40, 5);
    printf("����: %d\n", level);
    SetCursorPosition(40, 7);
    printf("����: %d\n", score);
}

// [7] �� ��ġ
// ���� ture, ������ false

bool CanPositionedAt(int rotation, int move1, int move2)
{
    int x, y;
    int arrX, arrY; // ��ǥ ����
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
                return false; // ����� ���� ��ħ
        }
    }
    return true; // ��ġ�� ����
}

// [8] ���� ��ġ�� ��� ���
void WriteBlock(int rotation)
{
    int i, j;
    COORD cursor = GetCursorPosition();

    if (CanPositionedAt(rotation, 0, 0) == true)
    {
        for (i = 0; i < 4; i++)      // �� �ݺ�
        {
            for (j = 0; j < 4; j++)   // �� �ݺ�
            {
                SetCursorPosition(cursor.X + (j * 2), cursor.Y + i);
                if (blocks[rotation][i][j] == 1)
                {
                    printf("��");
                }
            }
        }
        SetCursorPosition(cursor.X, cursor.Y);
    }
}


// [9] ��� ������
void BoardInit(int n, int move1, int move2)
{
    COORD pos = GetCursorPosition();

    int arrX = pos.X + move1;   // �ܼ� �� ��ǥ
    int arrY = pos.Y + move2;   // �ܼ� �� ��ǥ
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

//[10] �迭,��� �ű��
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
                printf("��");
        }
    }
}

// [11] level ���ھ� ���
void CountScore(void)
{
    score += 10;
    if (score % 30 == 0)
    {
        level += 1;
        speed -= 30;   // ���� 1�����Ҷ� ���ǵ� 30�и��� ������
    }
    ShowPoint();
}

// [12] ��� ���� �����
void RemoveLine(void)
{
    int x, y;

    // �Ʒ����� ���� Ȯ��
    for (y = 19; y >= 1; y--)
    {
        int lineCleared = 1; // �� ���� �� á���� Ȯ��

        // �ش� ���� �� �� �ִ��� Ȯ��
        for (x = 1; x < 11; x++)
        {
            if (board[y][x] == 0) // ����ִ� �κ��� ������
            {
                lineCleared = 0; // �� ���� ����
                break; // �� ���� �� �̻� Ȯ���� �ʿ� ����
            }
        }

        // ���� �� ���� ó��
        if (lineCleared)
        {
            // �ش� ���� ���� ��, ���� ����� �Ʒ��� �̵�
            for (int row = y; row > 1; row--) // ���� ������ �Ʒ��� �̵�
            {
                for (x = 1; x < 11; x++)
                {
                    board[row][x] = board[row - 1][x]; // ���� ����� �Ʒ��� �̵�
                }
            }

            // ���� �� ���� �����
            for (x = 1; x < 11; x++)
            {
                board[1][x] = 0; // �ֻ�� �� ����
            }

            // �ð������� ������Ʈ
            for (x = 1; x < 11; x++)
            {
                SetCursorPosition((x + 2) * 2, y + 2);
                printf("  "); // �ش� �� �����
            }

            CountScore(); // ���� ���
            // ����� ������ ��, �� �� �Ʒ��� �̵��� ��� �߰� �˻� �ʿ�
            y++; // �� �� ���������Ƿ� �ٽ� ������ Ȯ��
        }
    }
}


// [13] ���� ��� Ŭ����
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

// [14] ���� ����
void StartGame(void)
{
    int n;
    int kb;
    int c = 2;

    srand((unsigned)time(0));   // rnad() �Լ� ������

    while (1)
    {
        // ��� ���� ��ǥ (13,2)
        SetCursorPosition(13, 2);

        n = rand() % 7;

        n = n * 4;

        if (level == 10) // ���� 10�Ǹ� ���� �¸�
        {
            SetCursorPosition(40, 15);
            printf("���� Ŭ����");
            getchar();
            exit(1);
        }

        if (CanPositionedAt(n, 0, 0) == false)
            break; // ���� ��

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
                    BoardInit(n, 0, 0); //���� ���� �迭 1�߰�
                    RemoveLine();
                    break;
                }
                ClearBlock(n, 0, 1);
            }
            if (ww == 1)
                break;

            kb = _getch();

            // ����Ű
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
            case SPACE: // �Ʒ��� �������� ����
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

//[15] ���� ���� ȭ��
void EndGame()
{
    SetCursorPosition(40, 15);
    printf("���� ����");
    getchar();
    system("cls");
}
int main()
{
    ConsoleInit();   // ���� ȭ��

    DrawField();   // ���� ����

    ShowPoint();   // ������

    StartGame();   // ���� ����

    EndGame();      // ���� ����

    return 0;
}
