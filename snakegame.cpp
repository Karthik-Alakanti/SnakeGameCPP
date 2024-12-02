#include <iostream>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
bool gameover;
const int height = 20;
const int width = 20;
int headY, headX, fruitX, fruitY, score, tail_len;
int tailx[100], taily[100];

void setup();
void draw();
void input();
void logic();

int main() {
    char start;
    cout << "\t-------------------------->" << endl;
    cout << "\t\tSnakeGame--------------->" << endl;
    cout << "\t-------------------------->" << endl;
    cout << "Press 's' to start the game..." << endl;
    cin >> start;

    if (start == 's') {
        setup();
        while (!gameover) {
            draw();
            input();
            logic();
            Sleep(100); // Control game speed (100ms delay)
        }
    }

    return 0;
}

void setup() {
    gameover = false;
    dir = STOP;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tail_len = 0;
}

void draw() {
    system("cls"); // Clears the screen

    // Upper border
    for (int i = 0; i < width; i++) {
        cout << "=";
    }
    cout << endl;

    // Game grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Left border
            if (j == 0) {
                cout << "|";
            }

            // Snake head
            if (i == headY && j == headX) {
                cout << "O";
            }
            // Fruit
            else if (i == fruitY && j == fruitX) {
                cout << "*";
            }
            // Snake tail or space
            else {
                bool print = false;

                for (int k = 0; k < tail_len; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        cout << "o"; // Print tail
                        print = true;
                        break;
                    }
                }

                if (!print) {
                    cout << " "; // Print empty space
                }
            }

            // Right border
            if (j == width - 1) {
                cout << "|";
            }
        }
        cout << endl;
    }

    // Lower border
    for (int i = 0; i < width; i++) {
        cout << "=";
    }
    cout << endl;

    // Display Score
    cout << "Score: " << score << endl;
}

void input() {
    if (_kbhit()) { // Check if a key is pressed
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x': // Exit the game
            gameover = true;
            break;
        }
    }
}

void logic() {
    // Update tail position
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = headX;
    taily[0] = headY;

    for (int i = 1; i < tail_len; i++) {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move the head
    switch (dir) {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    // Check for collision with borders
    if (headX < 0 || headX >= width || headY < 0 || headY >= height) {
        gameover = true;
    }

    // Check for collision with itself
    for (int i = 0; i < tail_len; i++) {
        if (tailx[i] == headX && taily[i] == headY) {
            gameover = true;
        }
    }

    // Check if the snake eats the fruit
    if (headX == fruitX && headY == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tail_len++;
    }
}
