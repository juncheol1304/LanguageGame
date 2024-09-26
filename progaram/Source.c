#include <stdio.h>	// printf(), scanf()
#include <stdlib.h>	// rand()
#include <time.h>	// time()
#include <conio.h>	// _getch()
#include <windows.h>// wincon.h


#define true 1
#define false 0
#define bool int

#define BOARD_WIDTH 10	// 게임 가로 영역(열) >=10 :-
#define BOARD_HEIGHT 20	// 게임 세로 영역(행) >=20 :|

#define BOARD_X 4	// 보드 열 x좌표
#define BOARD_Y 2	// 보드 행 y좌표

#define DELAY 100	// 지연

// 키보드 방향키로 움직이고 스페이스로 떨어트림
enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

static int score = 0;	// 게임 점수
static int level = 1;	// 게임 레벨
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
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), & cursorInfo);
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
		"====================		\n"
		"조작법:						\n"
		"→     오른쪽 이동			\n"
		"←     왼  쪽 이동			\n"
		"↓     아래쪽 이동			\n"
		"↑     블  록 회전			\n"
		"space  블록 드랍				\n"
		"====================		\n");
	_getch();
	system("cls");
	CursorVisible(false);		// 커서 숨기기
	SetCursorPosition(0, 0);	// 보드 시작위치
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
		board[y][BOARD_WIDTH+1] = 1;
		SetCursorPosition(BOARD_X + (BOARD_WIDTH +2) *2, BOARD_Y + y);
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
		for (i = 0; i < 4; i++)		// 행 반복
		{
			for (j = 0; j < 4; j++)	// 열 반복
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

	int arrX = pos.X + move1;	// 콘솔 열 좌표
	int arrY = pos.Y + move2;	// 콘솔 행 좌표
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
		speed -= 30;	// 레빌 1증가할때 스피드 30밀리초 빨라짐
	}
	ShowPoint();
}

// [12] 블록 한줄 사라짐
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

// [13] 현재 블록 클리어
void ClearBlock(int rotation, int move1, int move2)
{
	int x, y;
}

int main()
{
	ConsoleInit();	// 시작 화면

	DrawField();	// 게임 영역

	ShowPoint();	// 점수판
	
	return 0;
}
