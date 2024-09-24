#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Ű �Է�
#include <windows.h> // Sleep() �Լ� ����� ����

// ���� 0== ���� ,1== �Ķ� , 2== �ʷ� ,3== ���� , 4== ����, 6==��� , 7== ���
// ����ũ�� ����,����,��� ũ��
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20 
#define BLOCK_SIZE 4

char board[BOARD_HEIGHT][BOARD_WIDTH + 1]; // ���� �迭
int currentX = 4; // ����� X ��ǥ
int currentY = 0; // ����� Y ��ǥ

// ���� ����ü
typedef struct {
    char shape[BLOCK_SIZE][BLOCK_SIZE];
    int width;
    int height;
} Tetromino;

// ���� ����
Tetromino I = { {{' ', ' ', ' ', ' '}, {'#', '#', '#', '#'}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}}, 4, 1 };
Tetromino O = { {{' ', ' ', ' ', ' '}, {' ', '#', '#', ' '}, {' ', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 2, 2 };
Tetromino T = { {{' ', ' ', ' ', ' '}, {'#', '#', '#', ' '}, {' ', '#', ' ', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino J = { {{' ', ' ', ' ', ' '}, {'#', ' ', ' ', ' '}, {'#', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino L = { {{' ', ' ', ' ', ' '}, {' ', ' ', '#', ' '}, {'#', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino S = { {{' ', ' ', ' ', ' '}, {' ', '#', '#', ' '}, {'#', '#', ' ', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };
Tetromino Z = { {{' ', ' ', ' ', ' '}, {'#', '#', ' ', ' '}, {' ', '#', '#', ' '}, {' ', ' ', ' ', ' '}}, 3, 2 };

// ���� �ʱ�ȭ
void initBoard() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[y][x] = ' '; // ���� ���� �� ����
        }
        board[y][BOARD_WIDTH] = '\0'; // ���ڿ� ����
    }
}

// ���� �׸���
void drawBoard() {
    system("cls"); // ȭ�� �����
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        printf("%s\n", board[y]); // ���� ���� ���� ���
    }
}

// ��� ��ġ
void placeBlock(int x, int y, char blockChar) {
    if (y >= 0 && y < BOARD_HEIGHT && x >= 0 && x < BOARD_WIDTH) {
        board[y][x] = blockChar; // ��� ���� ��ġ
    }
}

// ��� ����
void clearBlock() {
    if (currentY >= 0 && currentY < BOARD_HEIGHT && currentX >= 0 && currentX < BOARD_WIDTH) {
        board[currentY][currentX] = ' '; // ���� ��ġ ����
    }
}

// ���� ��ġ
void placeTetromino(int startX, int startY, Tetromino tetromino) {
    for (int y = 0; y < tetromino.height; y++) {
        for (int x = 0; x < tetromino.width; x++) {
            if (tetromino.shape[y][x] != ' ') {
                placeBlock(startX + x, startY + y, tetromino.shape[y][x]);
            }
        }
    }
}

// �� ���� �Լ�
void clearFullLines() {
    for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
        int full = 1; // ���� �� �� �ִ��� Ȯ���ϴ� ����
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[y][x] == ' ') {
                full = 0; // �� ������ ������ false
                break;
            }
        }
        if (full) {
            // �� ����
            for (int i = y; i > 0; i--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    board[i][x] = board[i - 1][x];
                }
            }
            // �� �� �� ����
            for (int x = 0; x < BOARD_WIDTH; x++) {
                board[0][x] = ' ';
            }
            y++; // �ٽ� �˻��ϱ� ���� y�� ����
        }
    }
}

// ��� �̵�
void moveBlock(int dx, int dy) {
    clearBlock();   // ���� ��ġ ����
    currentX += dx; // X ��ǥ �̵�
    currentY += dy; // Y ��ǥ �̵�
    placeTetromino(currentX, currentY, T); // ���ο� ��ġ�� ��� ��ġ (���� ����� T�� ����)
    clearFullLines(); // �� ���� üũ
}

int main() {
    initBoard(); // ���� �ʱ�ȭ
    placeTetromino(currentX, currentY, T); // �ʱ� ��� ��ġ
    drawBoard(); // ���� �׸���

    // ���� ����
    while (1) {
        if (_kbhit()) // Ű �Է� Ȯ��
        {
            char ch = _getch();
            if (ch == 'q') break; // 'q' �� ������ ����
            else if (ch == 'a') moveBlock(-1, 0); // ���� �̵�
            else if (ch == 'd') moveBlock(1, 0);  // ������ �̵�
            else if (ch == 's') moveBlock(0, 1);  // �Ʒ� �̵�
        }
        drawBoard();
        Sleep(100);
    }
    return 0;
}
