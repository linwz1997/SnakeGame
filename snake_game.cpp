#include <iostream>
#include <curses.h>
#include <time.h>
#include <string>
using namespace std;

bool gameOver; // game over flag

int width = 20; // width and height of game screen
int height = 20;

int x, y; // represent current position of the snake
int fruitX, fruitY; // represent the pos that the snake is going to eat
int score; // scores that player got

int tailX[100], tailY[100]; // arrays to store the pos of the snake's tail
int nTail; // records the length of the snake's tail

string fruit = "*"; // represents the mark of the fruit

enum Direction { // all possible directions that the snake will move
    STOP = 0,
    LEFT,
    RIGHT, 
    UP,
    DOWN
};
Direction dir;

void init(void)
{
    gameOver = false; 
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

int main(void)
{
    init();
}
