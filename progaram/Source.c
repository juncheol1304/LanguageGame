#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Ű �Է�
#include <windows.h> // Sleep() �Լ� ����� ����

// ���� 0== ���� ,1== �Ķ� , 2== �ʷ� ,3== ���� , 4== ����, 6==��� , 7== ���

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20 
// ����ũ�� ����,����

char board[BOARD_HEIGHT][BOARD_WIDTH+1]; // ���� �迭

// ���� �ʱ�ȭ ��Ű�� ���
void initBoard()
{
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            board[y][x] = ' '; // ���� ���� �� ����
        }
        board[y][BOARD_WIDTH] = '\0'; // ���ڿ� ����
    }
}

// ���� �׸��� ���
void drawBoard()
{
    system("cls"); // ȭ�� ����� �ڵ�
    
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        printf("%s\n", board[y]); // ���� ���� ���� ���
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