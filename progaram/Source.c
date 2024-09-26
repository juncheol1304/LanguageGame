#include <stdio.h>	// printf(), scanf()
#include <stdlib.h>	// rand()
#include <time.h>	// time()
#include <conio.h>	// _getch()
#include <windows.h>// wincon.h


#define true 1
#define false 0
#define bool int

#define BOARD_WIDTH 10	// ���� ���� ����(��) >=10 :-
#define BOARD_HEIGHT 20	// ���� ���� ����(��) >=20 :|

#define BOARD_X 4	// ���� �� x��ǥ
#define BOARD_Y 2	// ���� �� y��ǥ

#define DELAY 100	// ����

// Ű���� ����Ű�� �����̰� �����̽��� ����Ʈ��
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

static int score = 0;	// ���� ����
static int level = 1;	// ���� ����
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
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & cursorInfo);
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
		"====================		\n"
		"���۹�:						\n"
		"��     ������ �̵�			\n"
		"��     ��  �� �̵�			\n"
		"��     �Ʒ��� �̵�			\n"
		"��     ��  �� ȸ��			\n"
		"space  ��� ���				\n"
		"====================		\n");
	_getch();
	system("cls");
	CursorVisible(false);		// Ŀ�� �����
	SetCursorPosition(0, 0);	// ���� ������ġ
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
		board[y][BOARD_WIDTH+1] = 1;
		SetCursorPosition(BOARD_X + (BOARD_WIDTH +2) *2, BOARD_Y + y);
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
		for (i = 0; i < 4; i++)		// �� �ݺ�
		{
			for (j = 0; j < 4; j++)	// �� �ݺ�
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

	int arrX = pos.X + move1;	// �ܼ� �� ��ǥ
	int arrY = pos.Y + move2;	// �ܼ� �� ��ǥ
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
		speed -= 30;	// ���� 1�����Ҷ� ���ǵ� 30�и��� ������
	}
	ShowPoint();
}

// [12] ��� ���� �����
void RemoveLine(void)
{
	int i;
	int x, y;
	int z = 0;

	for (y = 19; y >= 1; y--)
	{
		for (z = 0; z < 4; z++)
		{
			i = 0;
			for (x = 1; x < 11; x++)
			{
				if (board[y][x] == 1)
				{
					i++; 
					if (i == 10)
					{
						for (x = 1; x < 11; x++)
						{
							SetCursorPosition((x + 2) * 2, y + 2);
							printf("  ");
						}
						CountScore();
						Stepper(y);
					}
				}
			}
		}
	}

}

// [13] ���� ��� Ŭ����
void ClearBlock(int rotation, int move1, int move2)
{
	int x, y;
}

int main()
{
	ConsoleInit();	// ���� ȭ��

	DrawField();	// ���� ����

	ShowPoint();	// ������
	
	return 0;
}
