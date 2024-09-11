#include <stdio.h>
#include <windows.h>

void Position(int x, int y)
{
	// X와 Y축을 설정하는 구조체입니다.
	COORD position = { x, y };

	//콘솔 커서의 좌표를 설정하는 함수입니다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int main()
{
	while(1)
	{
		Position(4, 5);
		printf("☆");

		Position(5, 5);
		printf("★");

		system("cls");
	}
	
	return 0;
}
