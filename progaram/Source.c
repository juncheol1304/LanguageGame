#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BOARD_WIDTH 17
#define BOARD_HEIGHT 20

// ��� ��� ����
char blocks[7][4][4] = {
    // I ���
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', '#'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // O ���
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // T ���
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // J ���
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {' ', ' ', '#', ' '},
        {' ', ' ', ' ', ' '}
    },
    // L ���
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', '#', ' '},
        {'#', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // S ���
    {
        {' ', ' ', ' ', ' '},
        {' ', '#', '#', ' '},
        {'#', '#', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    // Z ���
    {
        {' ', ' ', ' ', ' '},
        {'#', '#', ' ', ' '},
        {' ', '#', '#', ' '},
        {' ', ' ', ' ', ' '}
    }
};

int currentX = 4; // ����� X ��ǥ
int currentY = 0; // ����� Y ��ǥ
int currentBlock = 0; // ���� ��� �ε���
char board[BOARD_HEIGHT][BOARD_WIDTH + 1]; // ���� �迭
int score = 0; // ����

// ���� �ʱ�ȭ
void initBoard() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[y][x] = ' '; // �� ����
        }
        board[y][BOARD_WIDTH] = '\0'; // ���ڿ� ����
    }
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        board[y][0] = '|'; // ���� ��
        board[y][BOARD_WIDTH - 1] = '|'; // ������ ��
    }
    for (int x = 0; x < BOARD_WIDTH; x++) {
        board[0][x] = '-'; // ��� ��
        board[BOARD_HEIGHT - 1][x] = '-'; // �ٴ�
    }
}

// ���� ��� ����
void generateNewBlock() {
    currentBlock = rand() % 7; // ���� ��� ����
    currentX = 4; // �ʱ� X ��ǥ
    currentY = 0; // �ʱ� Y ��ǥ
}

// ��� ȸ�� �Լ�
void rotateBlock() {
    if (currentBlock == 1) return; // O ����� ȸ������ ����

    char temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = blocks[currentBlock][i][j]; // ȸ���� ���� ����
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            blocks[currentBlock][i][j] = temp[i][j];
        }
    }
}

// ���� �׸���
void drawBoard() {
    system("cls"); // ȭ�� �����
    printf("Score: %d\n", score); // ���� ���
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        printf("%s\n", board[y]); // ���� ���� ���� ���
    }
}

// ��� ��ġ
void placeBlock(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[currentBlock][i][j] == '#') {
                board[y + i][x + j] = '#'; // ��� ���� ��ġ
            }
        }
    }
}

// ��� ����
void clearBlock() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[currentBlock][i][j] == '#') {
                board[currentY + i][currentX + j] = ' '; // ���� ��ġ ����
            }
        }
    }
}

// �ٴ� �� �ٸ� ��� üũ
int isAtBottom() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[currentBlock][i][j] == '#') {
                if (currentY + i + 1 >= BOARD_HEIGHT - 1 ||
                    (currentY + i + 1 < BOARD_HEIGHT &&
                        currentX + j >= 1 &&
                        currentX + j < BOARD_WIDTH - 1 &&
                        board[currentY + i + 1][currentX + j] != ' ')) {
                    return 1; // �ٸ� ��Ͽ� ����
                }
            }
        }
    }
    return 0; // �ٴڿ� ���� ����
}

// �� ���� �Լ�
void clearLines() {
    for (int y = BOARD_HEIGHT - 2; y > 0; y--) {
        int complete = 1;
        for (int x = 1; x < BOARD_WIDTH - 1; x++) {
            if (board[y][x] == ' ') {
                complete = 0; // ���� �������� ������
                break;
            }
        }
        if (complete) {
            // �� ���� �� ���� ����
            score += 100;
            for (int i = y; i > 1; i--) {
                for (int x = 1; x < BOARD_WIDTH - 1; x++) {
                    board[i][x] = board[i - 1][x]; // �� ���� �Ʒ��� �̵�
                }
            }
            // ������ ���� �� ���� ����
            for (int x = 1; x < BOARD_WIDTH - 1; x++) {
                board[1][x] = ' ';
            }
        }
    }
}

// ��� �̵� �Լ�
void moveBlock(int dx, int dy) {
    clearBlock(); // ���� ��ġ ����
    currentX += dx; // X ��ǥ �̵�
    currentY += dy; // Y ��ǥ �̵�

    // ��� üũ
    if (currentX < 1) currentX = 1; // ���� ���� ���� �ʵ���
    if (currentX >= BOARD_WIDTH - 5) currentX = BOARD_WIDTH - 5; // ������ ���� ���� �ʵ���

    // �Ʒ��� �̵�
    if (isAtBottom()) {
        currentY--; // ����� �ٴڿ� ����
        placeBlock(currentX, currentY); // ���� ��� ��ġ
        clearLines(); // �� ����
        generateNewBlock(); // ���ο� ��� ����
    }
    else {
        placeBlock(currentX, currentY); // ���ο� ��ġ�� ��� ��ġ
    }
}

int main() {
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
    initBoard(); // ���� �ʱ�ȭ
    generateNewBlock(); // �ʱ� ��� ����
    placeBlock(currentX, currentY); // �ʱ� ��� ��ġ
    drawBoard(); // ���� �׸���

    // ���� ����
    while (1) {
        if (_kbhit()) { // Ű �Է� Ȯ��
            char ch = _getch();
            if (ch == 'q') break; // 'q'�� ������ ����
            else if (ch == 'a') moveBlock(-1, 0); // ���� �̵�
            else if (ch == 'd') moveBlock(1, 0); // ������ �̵�
            else if (ch == 's') moveBlock(0, 1); // �Ʒ� �̵�
            else if (ch == 'w') { // ��� ȸ��
                clearBlock(); // ���� ��ġ ����
                rotateBlock(); // ��� ȸ��
                placeBlock(currentX, currentY); // ���ο� ��ġ�� ��� ��ġ
            }
        }
        drawBoard();
        Sleep(100);
    }
    return 0;
}
